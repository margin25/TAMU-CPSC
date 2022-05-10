#include <mqueue.h>

#include "MQRequestChannel.h"

using namespace std;


// TODO: implement MQRequestChannel constructor/destructor and functions
MQRequestChannel::MQRequestChannel (const string _name, const Side _side, int size) : RequestChannel(_name, _side) {
    mq1 = "/mq_" + my_name + "1";
	mq2 = "/mq_" + my_name + "2";
    
    _size=size;

	if (my_side == CLIENT_SIDE) { 
		rfd = open_mq(mq1, O_RDONLY);
		wfd = open_mq(mq2, O_WRONLY);
	}
	else {
		wfd = open_mq(mq1, O_WRONLY);
		rfd = open_mq(mq2, O_RDONLY);
	}
}

MQRequestChannel::~MQRequestChannel () {
    mq_close(rfd);
    mq_close(wfd);
    mq_unlink(mq1.c_str());
    mq_unlink(mq2.c_str());
        
}

int MQRequestChannel::open_mq(string _fifo_name, int _mode) {
    mq_attr attr{};
    attr.mq_maxmsg = 1;
    attr.mq_msgsize = _size; //capacity
	mqd_t fd = mq_open(_fifo_name.c_str(), _mode | O_CREAT, 0600, &attr);

	if (fd < 0) {
        perror("mqopen");   
		EXITONERROR(_fifo_name);
	}
	return fd;
}

int MQRequestChannel::cread (void* msgbuf, int msgsize) {
    char buf[_size];
    int error = mq_receive(rfd,buf,_size, NULL);
    if( error == -1){ 
		EXITONERROR("mqrecv");
    }
    memcpy(msgbuf,buf,msgsize);
    return error;
}

int MQRequestChannel::cwrite (void* msgbuf, int msgsize) {
    int i = mq_send(wfd, (char*)msgbuf, msgsize,0);
    if( i == -1){ 
		EXITONERROR("mqsend");
    }
	return i;
}

