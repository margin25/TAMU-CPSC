// webserver
// take requests from loadbalancer
// process request 
// ask for new request
#ifndef REQUEST_CPP
#include "request.cpp"
#endif
#include <iostream>
#include <string>
#include <queue>
class webserver{
public:
        /**
         * Default Constructor : initializes request start time to 0.
         * initializes server name to ' '.
         * 
         */
        webserver()
        {
            request_start_time  = 0;
            server_name = ' ';
        }
        /**
         * Overloaded Constructor : initializes request start time to 0.
         * initializes server name to char.
         * 
         */
        webserver(char c)
        {
            request_start_time  = 0;
            server_name = c;
        }

        /**
         * Adds request to server
         * @param req, request being added
         * @param current_time, time @ which request was added
         */
        void add_request(request req, int current_time)
        {
            r = req;
            request_start_time = current_time;
        
        }

        /**
         * obtains request from the server
         * @return Request, returns current request that is being run by the server.
         * 
         */
        request get_request()
        {
            return r;
        }
        /**
         * obtains server name
         * @return char, returns char that refers to the server name
         * 
         */
        char get_name()
        {
            return server_name;
        }

        /**
        * Returns whether a request has been completed. 
        * @param current_time, current time
        * @return bool, true if request completed (otherwise false)
        */
        bool is_request_done(int current_time)
        {
            if (current_time > (request_start_time + r.process_time))
            {
                return true;
            }

            else
            {
                return false;
            }
        }
private:
    request r;
    int request_start_time;
    char server_name;
};