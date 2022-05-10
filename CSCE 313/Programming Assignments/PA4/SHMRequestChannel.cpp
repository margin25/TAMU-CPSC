#include <sys/mman.h>

#include "SHMRequestChannel.h"

using namespace std;

SHMQueue::SHMQueue(const string _name, int _length) : name(_name), length(_length)
{
    // TODO: implement SHMQueue constructor
    // call shm_open
    // truncate
    // mmap
    // create two semaphores

    send_done = 0;
    recv_done = 0;

    // TODO: open (and possibly create) the shared memory file using shm_open
    int fd = shm_open(name.c_str(), O_RDWR | O_CREAT, 0600);
    if (fd == -1)
    {
        perror("shm open");
        exit(EXIT_FAILURE);
    }
    // TODO: set the size of the shm with ftruncate

    if (ftruncate(fd, length) == -1)
    {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    } 
    segment = (char *)mmap(NULL, length, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    if (segment == MAP_FAILED){
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    // TODO: close the shm
    send_done = sem_open((name + "_sd").c_str(), O_CREAT, 0600, 0);
    if (send_done == SEM_FAILED){
        perror("send_done failed");
        exit(EXIT_FAILURE);
    }
    recv_done = sem_open((name + "_rd").c_str(), O_CREAT, 0600, 1);
    if (send_done == SEM_FAILED){
        perror("recv_done failed");
        exit(EXIT_FAILURE);
    }
    
    close(fd);
}

SHMQueue::~SHMQueue()
{
    // TODO: implement SHMQueue destructor
    // munmap - used to terminate mapping of part or all of a memory area previously mapped to a file by the mmap function
    // shm unlink
    // for both semaphores, call sem_close &sem_unlink

    munmap(segment, length);

    sem_close(recv_done);
    sem_close(send_done);

    sem_unlink((name + "_rd").c_str()); // receive
    sem_unlink((name + "_sd").c_str()); // write

    shm_unlink(name.c_str());
}

int SHMQueue::shm_receive(void *msgbuf, int msgsize)
{
    // TODO: implement shm_receive
    // memcpy, providing sync with the two semaphores
    // sem wait post ?
    sem_wait(send_done);
    memcpy(msgbuf, segment, msgsize);
    sem_post(recv_done);
    return msgsize;
}

int SHMQueue::shm_send(void *msgbuf, int msgsize)
{
    // TODO: implement shm_send
    // memcpy, providing sync with the two semaphores
    sem_wait(recv_done);
    memcpy(segment, msgbuf, msgsize);
    sem_post(send_done);
    return msgsize;
}

// TODO: implement SHMRequestChannel constructor/destructor and functions
// member attributes
// two SHM Queue* pointers, one for write & one for read
// member methods
// constructor - params: name,side,length of the segment, create the names for the SHMQueue objects, and then call new SHMQueue with name and length
// destructor - delete SHMQueue pointers
// cread - shm_receive
// cwrite - shm_send
SHMRequestChannel::SHMRequestChannel(const string seg_name, const Side seg_side, int seg_len) : RequestChannel(seg_name, seg_side)
{
    // constructor - params: name,side,length of the segment, create the names for the SHMQueue objects, and then call new SHMQueue with name and length
    shm1 = "/shm_" + my_name + "1";
    shm2 = "/shm_" + my_name + "2";

    size = seg_len;

    if (my_side == CLIENT_SIDE)
    {
        rq = new SHMQueue(shm1, size);
        wq = new SHMQueue(shm2, size);
    }
    else
    {
        rq = new SHMQueue(shm2, size);
        wq = new SHMQueue(shm1, size);
    }
}

SHMRequestChannel::~SHMRequestChannel()
{
    // destructor - delete SHMQueue pointers
    delete rq;
    delete wq;
}

int SHMRequestChannel::cread(void *msgbuf, int msgsize)
{
    // cread - shm_receive on shmqueue1
    return rq->shm_receive(msgbuf, msgsize);
}

int SHMRequestChannel::cwrite(void *msgbuf, int msgsize)
{
    // cwrite - shm_send on shmqueue2
    return wq->shm_send(msgbuf, msgsize);
}