/*
	Original author of the starter code
    Tanzir Ahmed
    Department of Computer Science & Engineering
    Texas A&M University
    Date: 2/8/20
	
	Please include your Name, UIN, and the date below
	Name: Mualla Argin
	UIN: 728003004
	Date: 2/2/2022
*/
#include "common.h"
#include "FIFORequestChannel.h"
#include <sys/wait.h>
// basic file operations
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

vector<FIFORequestChannel*> fifo_channels; 


int main (int argc, char *argv[]) {
	int opt;
	int p = 1;
	double t = 0.0;
	int e = 1;
	bool c = false;
	bool f_flag = false;
	int capacity = MAX_MESSAGE;
	string m_cap = "256";
	
	string filename = "";
	while ((opt = getopt(argc, argv, "p:t:e:m:f:c")) != -1) {
		switch (opt) {
			case 'p':
				p = atoi (optarg);
				// p_flag = true;
				break;
			case 't':
				t = atof (optarg);
				break;
			case 'e':
				e = atoi (optarg);
				break;
			case 'c':
				c = true;
				break;
			case 'f':
				filename = optarg;
				f_flag = true;
				break;
			case 'm':
				capacity = atoi(optarg);
				m_cap = optarg;
				break;
		}
	}

	pid_t pid_val = fork(); // returns two processes
	if(pid_val == 0){
		char* args[] = {(char*)"./server",(char*)"-m",(char*)m_cap.c_str(), NULL};
		execvp("./server", args);
	}
	else{
		FIFORequestChannel chan("control", FIFORequestChannel::CLIENT_SIDE);
		// example data point request
		char buf[MAX_MESSAGE]; // 256
		datamsg x(p,t,e);
		memcpy(buf, &x, sizeof(datamsg));
		chan.cwrite(buf, sizeof(datamsg)); // question
		double reply;
		chan.cread(&reply, sizeof(double)); //answer
		cout << "For person " << p << ", at time " << t << ", the value of ecg " << e << " is " << reply << endl;
		// data points 
		ofstream datapoints;
		datapoints.open("received/x1.csv");
		for ( double time = 0.0; time < 4; time +=0.004)
		{
				datapoints << time << ",";
				e = 1;
				datamsg ecg1 (p, time, e);
				chan.cwrite (&ecg1, sizeof (datamsg)); //ask ecg1
				double replye1;
				chan.cread (&replye1, sizeof(double)); //reply
				datapoints << replye1 << ",";

				e = 2;
				datamsg ecg2 (p, time, e);
				chan.cwrite (&ecg2, sizeof (datamsg)); //ask ecg2
				double replye2;
				chan.cread (&replye2, sizeof(double)); //reply
				datapoints << replye2 << endl;

		}
		datapoints.close();

	// requesting a new channel 

	if(c == true){
		// The client sets the MESSAGE_TYPE to NEWCHANNEL_MSG
		MESSAGE_TYPE client_message = NEWCHANNEL_MSG;
		//  and sends this message to the server
		chan.cwrite (&client_message, sizeof(client_message));
		char buff2[MAX_MESSAGE]; 
		// The server then creates a communication channel, joins it from the server side, and returns the name of the channel created
		chan.cread(&buff2, MAX_MESSAGE); //answer
		fifo_channels.push_back(new FIFORequestChannel(buff2, FIFORequestChannel::CLIENT_SIDE)); // add created new channel to fifo channels vector so that we can close all new created channels
	}

	if(f_flag == true){
		string filepath = "received/" + filename;
		FILE* output_file = fopen (filepath.c_str(), "wb");
		filemsg fm(0,0); //requesting contents of file
		int len = sizeof(filemsg) + (filename.size() + 1); 
		
		char* buff3 = new char[len];
		memcpy (buff3, &fm, sizeof (filemsg));
		strcpy (buff3 + sizeof (filemsg), filename.c_str()); // char * strcpy ( char * destination, const char * source );
		chan.cwrite (buff3, len);

		__int64_t fileSize;
		chan.cread(&fileSize, sizeof(__int64_t));
		
		char* buff4 = new char[capacity];
		fm.length = capacity; 

		int64_t requests = fileSize / capacity;
		int counter = 0;
		while(counter < requests){
			memcpy (buff3, &fm, sizeof (filemsg));
			strcpy (buff3 + sizeof (filemsg), filename.c_str());
			chan.cwrite(buff3, len);

			memset(buff4, 0, capacity);
			chan.cread(buff4, capacity);
			fwrite(buff4, 1, capacity, output_file);
		    counter++;
			fm.offset += capacity;
		}
		// remainder
		fm.length = fileSize % capacity;
		memcpy (buff3, &fm, sizeof (filemsg));
		strcpy (buff3 + sizeof (filemsg), filename.c_str());
		chan.cwrite(buff3, len);

		chan.cread(buff4, fm.length);
		fwrite(buff4, 1, fm.length, output_file);
		delete[] buff4;
		delete[] buff3; 
	}

	
	 


    // sending a non-sense message, you need to change this
	/* filemsg fm(0, 0);
	string fname = "1.csv";
	
	int len = sizeof(filemsg) + (fname.size() + 1);
	char* buf2 = new char[len];
	memcpy(buf2, &fm, sizeof(filemsg));
	strcpy(buf2 + sizeof(filemsg), fname.c_str());
	chan.cwrite(buf2, len);  // I want the file length;
	delete[] buf2; */
	
	// closing additional  channels
	MESSAGE_TYPE m = QUIT_MSG; // creates a QUIT Message request that is sent to the server
	FIFORequestChannel * current_channel = nullptr;
	for(long unsigned int i =0; i < fifo_channels.size();i++){
		current_channel = fifo_channels.back();
		current_channel->cwrite(&m, sizeof(MESSAGE_TYPE));
		fifo_channels.pop_back();
		delete current_channel;
	}
    // closing main channel
    chan.cwrite(&m, sizeof(MESSAGE_TYPE));	
	wait(0);

	}    
}
