#include "BoundedBuffer.h"

using namespace std;

BoundedBuffer::BoundedBuffer(int _cap) : cap(_cap)
{
    // modify as needed
    cap = _cap;
    occupy = 0;
}

BoundedBuffer::~BoundedBuffer()
{
    // modify as needed
}

void BoundedBuffer::push(char *msg, int size)
{
    // 1. Convert the incoming byte sequence given by msg and size into a vector<char>
    //          use one of the vector constructor's
    vector<char> c(msg, msg + size);
    // 2. Wait until there is room in the queue (i.e., queue lengh is less than cap)
    //          - waiting on slot available
    unique_lock<mutex> i(m);
    slot_available.wait(i, [this]{ 
        return (int(q.size()) < cap); 
    });
    // 3. Then push the vector at the end of the queue
    q.push(c);
	occupy += size;
	i.unlock();
    // 4. Wake up threads that were waiting for push
    //      notifying data available
    data_available.notify_one();

}

int BoundedBuffer::pop(char *msg, int size)
{
    // 1. Wait until the queue has at least 1 item
    //          waiting on data available
    unique_lock<mutex> i(m);
    data_available.wait (i, [this]{
        return q.size() > 0;
    });
    // 2. Pop the front item of the queue. The popped item is a vector<char>
    vector<char> w = q.front();
	q.pop();
	occupy -= w.size();
	i.unlock();
    // 3. Convert the popped vector<char> into a char*, copy that into msg; assert that the vector<char>'s length is <= size
    //          use vector::data()
    // 4. Wake up threads that were waiting for pop
    //          notifying slot available
    slot_available.notify_one ();
    assert(int(w.size()) <= size);
    memcpy(msg, w.data(), w.size());
    // 5. Return the vector's length to the caller so that they know how many bytes were popped
    return w.size();
}

size_t BoundedBuffer::size()
{
    return q.size();
}