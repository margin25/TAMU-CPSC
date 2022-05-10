#ifndef _SHMREQUESTCHANNEL_H_
#define _SHMREQUESTCHANNEL_H_

#include <semaphore.h>

#include "RequestChannel.h"
using namespace std;


class SHMQueue {
private:
    std::string name;
    int length;

    char* segment;
    sem_t* recv_done;
    sem_t* send_done;
    
public:
    SHMQueue(const std::string _name, int _length);
    ~SHMQueue();

    int shm_receive (void* msgbuf, int msgsize);
    int shm_send (void* msgbuf, int msgsize);
};

class SHMRequestChannel : public RequestChannel {
// TODO: declare derived components of SHMRequestChannel from RequestChannel
// member attributes
    // two SHM Queue* pointers, one for write & one for read
    
    // member methods
    // constructor - params: name,side,length of the segment, create the names for the SHMQueue objects, and then call new SHMQueue with name and length
    
    // destructor - delete SHMQueue pointers
    // cread - shm_receive
    // cwrite - shm_send
    // 
private:
    SHMQueue* rq;
    SHMQueue* wq;
    std::string shm1;
    std::string shm2;
    int size;
public: 
    SHMRequestChannel(const string seg_name, const Side seg_side, int seg_len);
    ~SHMRequestChannel();
    int cread (void* msgbuf, int msgsize);
    int cwrite (void* msgbuf, int msgsize);
};

#endif
