#include <fstream>
#include <iostream>
#include <thread>
#include <sys/time.h>
#include <sys/wait.h>

#include "BoundedBuffer.h"
#include "common.h"
#include "Histogram.h"
#include "HistogramCollection.h"
#include "FIFORequestChannel.h"

// ecgno to use for datamsgs
#define EGCNO 1

using namespace std;

int opt;
int file_size = 0;
bool f_flag = false;
int n = 100;
int p = 10;
int w = 100;
int b = 20;
int m = MAX_MESSAGE;
string filename;
int h = 1;

// FUNCTIONS

void closeChannel(FIFORequestChannel *chan)
{
    MESSAGE_TYPE quit_msg = QUIT_MSG;
    chan->cwrite(&quit_msg, sizeof(MESSAGE_TYPE));
    delete chan;
    return;
}

void patient_thread_function(BoundedBuffer &request_buf, int pat)
{
    // functionality of the patient threads

    // take a patient p_no
    // for n requests, produce a datamsg(p_no, time, ECGNO) and push to request_buffer
    //          - time dependent on current requests
    //          - at 0 -> time = 0.00; at 1 -> time = 0.004; at 2 -> time = 0.008
    datamsg data_msg(pat, 0, 1);
    for (int i = 0; i < n; i++)
    {
        data_msg.seconds = i * 0.004;
        char buf[sizeof(datamsg)];
        memcpy(buf, &data_msg, sizeof(datamsg));
        request_buf.push(buf, sizeof(datamsg));
    }
}

void file_thread_function(BoundedBuffer &request_buf, FIFORequestChannel *control_chan)
{
    // functionality of the file thread
    filemsg file_msg(0, 0);
    int len = sizeof(filemsg) + filename.size() + 1;
    char buf[len];
    memcpy(buf, &file_msg, sizeof(filemsg));
    strcpy(buf + sizeof(filemsg), filename.c_str());
    control_chan->cwrite(buf, len);
    control_chan->cread(&file_size, sizeof(size_t));

    // Allocate file in memory
    FILE *fp;
    if ((fp = fopen(("received/" + filename).c_str(), "wb")) == NULL)
    {
        perror("open");
        exit(1);
    }
    fseek(fp, file_size, SEEK_SET);
    fclose(fp);

    // Push file requests to buffer, chunk by chunk
    // while offset < file_size, produce a filemsg(offset,m) + filename and push to request buffer
    //          - incrementing offset; and be careful with the final message
    char buf2[len];
    filemsg file_msg2(0, 0);
    for (int i = 0; i < ceil(double(file_size) / m); i++)
    {
        if (file_size - file_msg2.offset < m)
        {
            file_msg2.length = file_size - file_msg2.offset;
        }
        else
        {
            file_msg2.length = m;
        }
        memcpy(buf2, &file_msg2, sizeof(filemsg));
        strcpy(buf2 + sizeof(filemsg), filename.c_str());
        request_buf.push(buf2, len);
        file_msg2.offset += file_msg2.length;
    }
    return;
}

void worker_thread_function(BoundedBuffer &request_buf, BoundedBuffer &response_buffer, FIFORequestChannel *w_chan)
{
    while (true) // forever loop (produce requests until its told to stop)
    {
        // Pop a request from the request buffer
        int len = sizeof(filemsg) + filename.size() + 1;
        char request[256];
        request_buf.pop(request, 256);
        MESSAGE_TYPE msg = *(MESSAGE_TYPE *)request;
        char response[m];
        if (msg == FILE_MSG)
        { // if FILE:
            //      - collect the filename from the message
            //      - open the file in update mode (PA3 FAQ)
            //      - fseek(SEEK_SET) to offset of the filemsg
            //      - write the buffer from the server
            filemsg file_msg = *(filemsg *)request;
            w_chan->cwrite(request, len);
            w_chan->cread(response, m);

            FILE *fp = fopen(("received/" + filename).c_str(), "rb+"); // cstring accounts for null byte
            fseek(fp, file_msg.offset, SEEK_SET);
            fwrite(response, sizeof(char), file_msg.length, fp);
            fclose(fp);
        }
        else if (msg == DATA_MSG)
        {
            // if DATA:
            //      - create pair of p_no from message and response from server
            //      - push that pair to the response_buffer
            datamsg data_msg = *(datamsg *)request;
            w_chan->cwrite(request, sizeof(datamsg));
            w_chan->cread(response, sizeof(double));
            double ecg1 = *(double*)response;
            char buf[sizeof(pair<int, double>)];
            pair<int, double> data = make_pair(data_msg.person, ecg1); // create pair of p_no from message and response
            memcpy(buf, &data, sizeof(pair<int, double>));
            response_buffer.push(buf, sizeof(pair<int, double>));
        }
        else if (msg == QUIT_MSG) //worker
        {
            break;
        }
        else
        { 
            w_chan->cwrite(request, len);
            w_chan->cread(response, m);
        }
    }
    closeChannel(w_chan);
    return;
}

void histogram_thread_function(BoundedBuffer &response_buffer, HistogramCollection &histo_collection)
{
    // functionality of the histogram threads
    while (true)
    { // forever loop
        char response_res[sizeof(pair<int, double>)]; // create pair of p_no from message and response
        // pop response from the response_buffer
        response_buffer.pop(response_res, sizeof(pair<int, double>));
        pair<int, double> data = *(pair<int, double> *)response_res;
        int p = data.first; // separating values from pair
        double ecg1 = data.second; // separating values from pair
        if (p >= 1 && p <= 15)
        {
            // call HistogramCollection :: update(resp->p_no, resp->double)
            histo_collection.update(p, ecg1);
        }
        else if(p = 0)
        {
            break;
        }
        else
        {
            break;
        }
    }
    return;
}

FIFORequestChannel *newChannel(FIFORequestChannel *chan)
{
    MESSAGE_TYPE new_msg = NEWCHANNEL_MSG;
    chan->cwrite(&new_msg, sizeof(MESSAGE_TYPE));
    char name[30];
    chan->cread(&name, sizeof(name));                                                             // new channel's name
    FIFORequestChannel *new_chan = new FIFORequestChannel(name, FIFORequestChannel::CLIENT_SIDE); // Access the new channel
    return new_chan;
}

int main(int argc, char *argv[])
{
    n = 1000;        // default number of requests per "p"
    p = 10;          // number of ps [1,15]
    w = 100;         // default number of worker threads
    h = 20;          // default number of histogram threads
    b = 20;          // default capacity of the request buffer (should be changed)
    m = MAX_MESSAGE; // default capacity of the message buffer
    string f = "";   // name of file to be transferred

    // read arguments
    int opt;
    srand(time_t(NULL));

    while ((opt = getopt(argc, argv, "n:p:w:b:m:f:h:")) != -1)
    {
        switch (opt)
        {
        case 'n':
            n = atoi(optarg);
            break;
        case 'p':
            p = atoi(optarg);
            break;
        case 'w':
            w = atoi(optarg);
            break;
        case 'b':
            b = atoi(optarg);
            break;
        case 'm':
            m = atoi(optarg);
            break;
        case 'f':
            f_flag = true;
            filename = optarg;
            break;
        case 'h':
            h = atoi(optarg);
            break;
        }
    }

    int pid = fork();
    if (pid == 0) // Server
    {
        execl("./server", "./server", "-m", (char *)to_string(m).c_str(), nullptr);
    }
    else // Client
    {
        FIFORequestChannel *chan = new FIFORequestChannel("control", FIFORequestChannel::CLIENT_SIDE);
        BoundedBuffer request_buf(b);
        BoundedBuffer response_buffer(b);
        HistogramCollection histo_collection;

        // Timing stuff
        struct timeval start, end;
        gettimeofday(&start, 0);

        /* create all threads here */
        // if data:
        //      - create p patient_threads (store producer array)
        //      - create w worker_threads (store worker array)
        //          -> create channel (store FIFO array)

        //      - create h histogram_threads (store hist array)
        // if file:
        //      - create 1 file_thread (store producer array)
        //      - create w worker_threads (store worker array)
        //          -> create w channels (store FIFO array)

        // 1) create worker channels 
        FIFORequestChannel *w_channels[w];
        for (size_t i = 0; i < w; i++)
            w_channels[i] = newChannel(chan);

        if (f_flag) // if file request / transfer
        {
            thread w_threads[w];                                               // workers thread
            thread file_request(file_thread_function, ref(request_buf), chan); // file request thread
            // iterate over all thread arrays, calling join
            //          - order is important; producers before consumers
            for (size_t x = 0; x < w; x++)
                w_threads[x] = thread(worker_thread_function, ref(request_buf), ref(response_buffer), w_channels[x]);
            file_request.join();
            for (size_t y = 0; y < w; y++)
            {
                MESSAGE_TYPE q = QUIT_MSG; // push quit messages at the end of every request buffer after patients are done
                // this signals to worker threads
                request_buf.push((char *)&q, sizeof(MESSAGE_TYPE));
            }
            for (thread &i : w_threads) // workers join thread
                i.join();
        }
        else // if data request
        {
            for (size_t i = 0; i < p; i++) // creation of histograms
            {
                Histogram *hist = new Histogram(30, -1.5, 1.5);
                histo_collection.add(hist);
            }
            thread w_threads[w];           // initiate worker threads
            thread h_threads[h];           // initiate histogram threads
            thread p_threads[p];           // initiate p threads
            for (size_t l = 0; l < w; l++) // fill w threads
                w_threads[l] = thread(worker_thread_function, ref(request_buf), ref(response_buffer), w_channels[l]);
            for (size_t m = 0; m < h; m++) // fill h  threads
                h_threads[m] = thread(histogram_thread_function, ref(response_buffer), ref(histo_collection));
            for (size_t n = 0; n < p; n++) // fill p threads
                p_threads[n] = thread(patient_thread_function, ref(request_buf), n + 1);
            // iterate over all thread arrays, calling join
            //          - order is important; producers before consumers
            for (thread &i : p_threads) // join p threads
                i.join();
            for (size_t x = 0; x < w; x++) // quit msg to workers
            {
                MESSAGE_TYPE qm = QUIT_MSG;
                request_buf.push((char *)&qm, sizeof(MESSAGE_TYPE));
            }
            for (thread &x : w_threads) // join w threads
                x.join();

            for (size_t j = 0; j < h; j++) // quitting histogram threads
            {
                pair<int, double> quit = make_pair(0, 0);
                response_buffer.push((char *)&quit, sizeof(pair<int, double>));
            }
            for (thread &j : h_threads)
                j.join();
        }

        gettimeofday(&end, 0);
        // print the results
        histo_collection.print();
        int secs = (end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec) / (int)1e6;
        int usecs = (int)(end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec) % ((int)1e6);
        cout << "Took " << secs << " seconds and " << usecs << " micro seconds" << endl;

        closeChannel(chan);
        cout << "All Done!!!" << endl;
    }
}
