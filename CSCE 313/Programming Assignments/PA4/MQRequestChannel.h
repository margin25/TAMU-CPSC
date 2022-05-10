#ifndef _MQREQUESTCHANNEL_H_
#define _MQREQUESTCHANNEL_H_
#include <mqueue.h>
#include "RequestChannel.h"

class MQRequestChannel : public RequestChannel{
    // TODO: declare derived components of MQRequestChannel from RequestChannel

    // member attributes
    // one int var , the size of a msg in the queue
    // two mqd_t vars, one for write & one for read
    // two string vars, one for each of the message queues

    // member methods 
    // helper method to open the mqueue - create mq_attr struct, mq_open with provided mode (include O_CREAT)
    // constructor - params: name, side , msgsize - create the names for the message queues (prepend '/'), open the two mqueues dependent  side
    // destructor - mq_close, mq_unlink for both message queues
    // cread - mq_receive
    // cwrite - mq_send 
private:
    int _size; // one int var , the size of a msg in the queue
    // two mqd_t vars, one for write & one for read
    mqd_t wfd;
    mqd_t rfd;
    // two string vars, one for each of the message queues
    std::string mq1;
    std::string mq2;
    int open_mq(std::string _mq_name, int _mode);

public:
    MQRequestChannel(const std::string _name, const Side _side,int size);
    ~MQRequestChannel();

    int cread(void *msgbuf, int msgsize);
    int cwrite(void *msgbuf, int msgsize);
};

#endif
