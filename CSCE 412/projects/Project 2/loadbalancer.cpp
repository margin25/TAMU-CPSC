#include <string>
#include <iostream>
#include <ctime>
#include<stdio.h>
#include <cstdlib>
#include <sstream>
#include <queue>
#include <stdexcept>
using namespace std;
#include "webserver.cpp"
// loadbalancer
// queue of requests
// keep track of time

class loadbalancer{
public:
    /**
    * Default constructor: initialized system time to 0.
    */
    loadbalancer(){
        system_time = 0;
    }

    /**
    * Getter: gets time of load balancer
    */
    int get_time(){
        return system_time;
    }

    /**
    * Incrementer: increases the clock cycle of load balancer by 1.
    */
    void inc_time(){
        system_time++;
    }

    /**
    * Adds a request to the queue
    *
    * @param request variable of type request which is defined in request.cpp.
    */
    void add_request(request r)
    {
        request_queue.push(r);
        inc_time();
    }


    /**
    * Obtains request content and then removes the request from the queue.
    *
    * @return Request that was removed from queue.
    */
    request get_request()
    {
        inc_time();
        if(!request_queue.empty())
        {
            request r = request_queue.front();
            request_queue.pop();
            return r;
        }
        else
        {
            throw logic_error( "You cannot remove from an empty queue");
        }

        
    }

    /**
    * creates and returns random request with ip source,destination, and process time values.
    *
    * @return randomly generated request.
    */
    request create_random_request()
    {
        stringstream ips, ipd; // source & destination IPs
        request r;
        ips << (rand() % 256 ) << "." << (rand() % 256 ) << "." << (rand() % 256 ) << "." << (rand() % 256 );
        ipd << (rand() % 256 ) << "." << (rand() % 256 ) << "." << (rand() % 256 ) << "." << (rand() % 256 );
        r.source = ips.str();
        r.destination = ipd.str();
        r.process_time = rand() % 500; // how long it takes for r to be created
        return r;
    }

    /**
    * Returns true if requestQueue is empty and false otherwise
    *
    * @return bool, true if request queue empty
    */
    bool is_rq_empty()
    {
        return request_queue.empty();
    }

    /**
    * Returns the size/length of the queue
    *
    * @return int, size/length of requestQueue 
    */
    int rq_size() 
    {
    return request_queue.size();
    }

private:
    int system_time;
    queue<request> request_queue;

};

int main(){
    // get # of servers from user
    int num_web_servers;
    cout << "Input Number of web servers(at least 1) : " ;
    cin >> num_web_servers;
    // array of web servers
    webserver webarray[num_web_servers];
    // get value ofbalancer runtime from user
    int input_lb_runtime;
    cout << "Input Load Balancer Run Time: ";
    cin >> input_lb_runtime;
    

        // random number generator
        srand(time(0));
        // create a loadbalancer
        loadbalancer lb = loadbalancer();
        // start off with a "full" queue
        for (size_t x = 0 ; x < num_web_servers * 2; x++)
        {
            request r = (lb.create_random_request());
            lb.add_request(r);
        }
        int min_task_time = 2;
        int max_task_time = 305;
        cout << "Starting Queue Size: " <<  lb.rq_size() << endl;
        //populate webserver 
        for (int y = 0; y < num_web_servers;y++)
        {
            webserver w((char)(y+65)); // giving each webserver a name
            webarray[y].add_request(lb.get_request(), lb.get_time());
            webarray[y] = w;
        }
    
        // loop 
    while (lb.get_time() < input_lb_runtime )
    {
        if (lb.is_rq_empty()) {
            cout << "Empty Request Queue. Please try again!" << endl;
            break;
        }
        int current_time = lb.get_time();
        // check each webserver if its done 
        if (webarray[current_time %  num_web_servers  ].is_request_done(current_time))
        {
           request r  = webarray[current_time % num_web_servers].get_request();
           cout << "At time: " << current_time << " server " << webarray[current_time % num_web_servers].get_name() << " processed request from " << r.source << " to " << r.destination  << endl;
            // then give it a new request
           webarray[current_time % num_web_servers].add_request(lb.get_request(),current_time);
        }
        // every random amount of time, we get a new request.
        if (rand() % 10 == 0)
        {
            request r = (lb.create_random_request());
            lb.add_request(r);
        }
        lb.inc_time();
    }
    cout << "task time range: " << min_task_time << " - " << max_task_time << " seconds." << endl;
    cout << "Ending Queue Size: " <<  lb.rq_size()  << endl;
    return 0;
}