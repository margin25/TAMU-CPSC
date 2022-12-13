#include <string>
#include <queue>

using namespace std;

/**
*This class represent the request object. The request object holds a source (IP in ) IP4 address, a destination (IP out ) IP4 address, and a process time variable (expected time to run the request)
*/
class request 
{
    public:
        // request 
        //  IP (Internet Protocol Address) in 
        //  IP (Internet Protocol Address) out
        //  time (int)
        string source; /**< Source IP Address */
        string destination; /**< Destination IP Address */
        int process_time; /**< seconds taken to run request */
        request(){}

};
