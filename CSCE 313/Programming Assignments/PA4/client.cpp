// your PA1 client code here
#include "common.h"
#include "FIFORequestChannel.h"
#include "MQRequestChannel.h"
#include "SHMRequestChannel.h"
#include <sys/wait.h>
// basic file operations
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
using namespace std;

vector<RequestChannel *> the_channels;

int main(int argc, char *argv[])
{
	int opt;
	int num_chan = 0;
	int p = 1;
	double t = 0.0;
	int e = 1;
	bool c = false;
	bool f_flag = false;
	int capacity = MAX_MESSAGE;
	int p_flag = false;
	string m_cap = "256";
	string ipc = "f";

	string filename = "";
	while ((opt = getopt(argc, argv, "p:t:e:m:f:c:i:")) != -1)
	{
		switch (opt)
		{
		case 'p':
			p = atoi(optarg);
			p_flag = true;
			break;
		case 't':
			t = atof(optarg);
			break;
		case 'e':
			e = atoi(optarg);
			break;
		case 'c':
			num_chan = atoi(optarg);
			c = true;
			break;
		case 'f':
			filename = optarg;
			f_flag = true;
			break;
		case 'm':
			capacity = atoi(optarg);
			m_cap = to_string(capacity);
			break;
		case 'i': // added for ipc
			ipc = optarg;
			break;
		}
	}

	pid_t pid_val = fork(); // returns two processes
	if (pid_val == 0)
	{
		char *args[] = {(char *)"./server", (char *)"-m", (char *)m_cap.c_str(), (char *)"-i", (char *)ipc.c_str(), NULL};
		execvp("./server", args);
	}
	else
	{

		RequestChannel *chan;
		if (ipc == "q")
		{
			chan = new MQRequestChannel("control", RequestChannel::CLIENT_SIDE, capacity);
			if (c)
			{
				for (int j = 0; j < num_chan; j++)
				{
					char buf2[MAX_MESSAGE];
					MESSAGE_TYPE msg = NEWCHANNEL_MSG;
					chan->cwrite(&msg, sizeof(MESSAGE_TYPE));
					chan->cread(buf2, MAX_MESSAGE);
					string chan2 = buf2;
					RequestChannel *chan3 = new MQRequestChannel(chan2, RequestChannel::CLIENT_SIDE,capacity);
					the_channels.push_back(chan3);
				}
			}
		}
		else if (ipc == "f")
		{
			chan = new FIFORequestChannel("control", RequestChannel::CLIENT_SIDE);
			RequestChannel *chan3;
			if (c)
			{
				for (int j = 0; j < num_chan; j++)
				{
					char buf2[MAX_MESSAGE];
					MESSAGE_TYPE msg = NEWCHANNEL_MSG;
					chan->cwrite(&msg, sizeof(MESSAGE_TYPE));
					chan->cread(buf2, MAX_MESSAGE);
					string chan2 = buf2;
					chan3 = new FIFORequestChannel(chan2, RequestChannel::CLIENT_SIDE);
					the_channels.push_back(chan3);
				}
			}
		}
		else if (ipc == "s")
		{
			chan = new SHMRequestChannel("control", RequestChannel::CLIENT_SIDE, capacity);
			if (c)
			{
				for (int j = 0; j < num_chan; j++)
				{
					char buf2[MAX_MESSAGE];
					MESSAGE_TYPE msg = NEWCHANNEL_MSG;
					chan->cwrite(&msg, sizeof(MESSAGE_TYPE));
					chan->cread(buf2, MAX_MESSAGE);
					string chan2 = buf2;
					RequestChannel *chan3 = new SHMRequestChannel(chan2, RequestChannel::CLIENT_SIDE,capacity);
					the_channels.push_back(chan3);
				}
			}
		}

		if (p_flag == true)
		{
			if (t > 0) {
				// example data point request
				datamsg x(p, t, e);
				chan->cwrite(&x, sizeof(datamsg)); // question
				double reply;
				chan->cread(&reply, sizeof(double)); // answer
				cout << "For person " << p << ", at time " << t << ", the value of ecg " << e << " is " << reply << endl;
			}
			else {
				// data points
				if (num_chan == 0) {
					ofstream datapoints;
					datapoints.open("received/x1.csv");
					for (double time = 0.0; time < 4; time += 0.004)
					{
						datapoints << time << ",";
						e = 1;
						datamsg ecg1(p, time, e);
						//cout << &ecg1 << endl;
						chan->cwrite(&ecg1, sizeof(datamsg)); // ask ecg1
						double replye1;
						chan->cread(&replye1, sizeof(double)); // reply
						datapoints << replye1 << ",";

						e = 2;
						datamsg ecg2(p, time, e);
						chan->cwrite(&ecg2, sizeof(datamsg)); // ask ecg2
						double replye2;
						chan->cread(&replye2, sizeof(double)); // reply
						datapoints << replye2 << endl;
					}
					datapoints.close();
				}
				for (int i = 0; i < num_chan; i++)
				{
					ofstream datapoints;
					datapoints.open("received/x" + to_string(i + 1) + ".csv");
					for (double time = 0.0; time < 4; time += 0.004)
					{
						datapoints << time << ",";
						e = 1;
						datamsg ecg1(p, time, e);
						// cout << &ecg1 << endl;
						the_channels[i]->cwrite(&ecg1, sizeof(datamsg)); // ask ecg1
						double replye1;
						the_channels[i]->cread(&replye1, sizeof(double)); // reply
						datapoints << replye1 << ",";

						e = 2;
						datamsg ecg2(p, time, e);
						the_channels[i]->cwrite(&ecg2, sizeof(datamsg)); // ask ecg2
						double replye2;
						the_channels[i]->cread(&replye2, sizeof(double)); // reply
						datapoints << replye2 << endl;
					}
					datapoints.close();
				}
			}
		}

		// requesting a new channel

		// else if (c == true)
		// {
		// 	// The client sets the MESSAGE_TYPE to NEWCHANNEL_MSG
		// 	MESSAGE_TYPE client_message = NEWCHANNEL_MSG;
		// 	//  and sends this message to the server
		// 	chan->cwrite(&client_message, sizeof(client_message));
		// 	char buff2[MAX_MESSAGE];
		// 	// The server then creates a communication channel, joins it from the server side, and returns the name of the channel created
		// 	chan->cread(&buff2, MAX_MESSAGE);														 // answer
		// 	fifo_channels.push_back(new FIFORequestChannel(buff2, FIFORequestChannel::CLIENT_SIDE)); // add created new channel to fifo channels vector so that we can close all new created channels
		// }

		else if (f_flag == true)
		{
			string filepath = "received/" + filename;
			FILE *output_file = fopen(filepath.c_str(), "wb");
			filemsg fm(0, 0); // requesting contents of file
			int len = sizeof(filemsg) + (filename.size() + 1);

			char *buff3 = new char[len];
			memcpy(buff3, &fm, sizeof(filemsg));
			strcpy(buff3 + sizeof(filemsg), filename.c_str()); // char * strcpy ( char * destination, const char * source );
			chan->cwrite(buff3, len);

			__int64_t fileSize;
			chan->cread(&fileSize, sizeof(__int64_t));

			char *buff4 = new char[capacity];
			fm.length = capacity;

			int64_t requests = fileSize / capacity;
			int counter = 0;
			while (counter < requests)
			{
				memcpy(buff3, &fm, sizeof(filemsg));
				strcpy(buff3 + sizeof(filemsg), filename.c_str());
				chan->cwrite(buff3, len);

				memset(buff4, 0, capacity);
				chan->cread(buff4, capacity);
				fwrite(buff4, 1, capacity, output_file);
				counter++;
				fm.offset += capacity;
			}
			// remainder
			fm.length = fileSize % capacity;
			memcpy(buff3, &fm, sizeof(filemsg));
			strcpy(buff3 + sizeof(filemsg), filename.c_str());
			chan->cwrite(buff3, len);

			chan->cread(buff4, fm.length);
			fwrite(buff4, 1, fm.length, output_file);
			delete[] buff4;
			delete[] buff3;
			fclose(output_file);
		}

		// closing additional  channels
		MESSAGE_TYPE m = QUIT_MSG; // creates a QUIT Message request that is sent to the server
		RequestChannel *current_channel = nullptr;
		while(the_channels.size() > 0)
		{
			current_channel = the_channels.back();
			current_channel->cwrite(&m, sizeof(MESSAGE_TYPE));
			the_channels.pop_back();
			delete current_channel;
		}
		// closing main channel
		chan->cwrite(&m, sizeof(MESSAGE_TYPE));
		wait(0);
		delete chan;
		//
		//
		//
	}
}