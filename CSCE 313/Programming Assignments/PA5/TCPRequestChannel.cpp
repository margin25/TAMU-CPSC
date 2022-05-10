#include "TCPRequestChannel.h"

using namespace std;
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
// bind()
#include <netinet/in.h>

TCPRequestChannel::TCPRequestChannel(const std::string _ip_address, const std::string _port_no)
{
    // if server
    //      create a socket on the specified
    //          - specify domain, type, and protocol
    //      bind the socket to address set-ups listening
    //      mark socket as listening
    struct addrinfo hints, *res;
    struct sockaddr_storage address_val;
    hints.ai_protocol = 0;
    socklen_t address_size;
    if (_ip_address == "")
    {
        int update_fd;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE;
        getaddrinfo(NULL, _port_no.c_str(), &hints, &res);
        //      create a socket on the specified
        //          - specify domain, type, and protocol
        cout << "passed get addr info" << endl;
        sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol); // (int __domain, int __type, int __protocol)
        cout << "passed socket" << endl;
        if (sockfd == -1)
        {
            perror("socket");
            exit(EXIT_FAILURE);
        }
        //      bind the socket to address set-ups listening
        if (bind(sockfd, res->ai_addr, res->ai_addrlen) == -1) // int bind(int __fd, const sockaddr *__addr, socklen_t __len)
        {
            perror("bind");
            exit(EXIT_FAILURE);
        }
        freeaddrinfo(res); // CLEAN UP: free address info
        listen(sockfd, 30); // why 30?
    }
    else
    {
        // if client
        //      create a socket on the specified
        //          - specify domain, type, and protocol
        //      connect socket to the IP address of the server
        int update_fd;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE;
        getaddrinfo(_ip_address.c_str(), _port_no.c_str(), &hints, &res);
        //      create a socket on the specified
        //          - specify domain, type, and protocol
        sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol); // (int __domain, int __type, int __protocol)
        if (sockfd == -1)
        {
            perror("socket");
            exit(EXIT_FAILURE);
        }
        // connect
        if (connect(sockfd, res->ai_addr, res->ai_addrlen) == -1)
        {
            perror("connect");
            exit(EXIT_FAILURE);
        }
        // CLEAN UP: free address info
        freeaddrinfo(res);
    }
}

TCPRequestChannel::TCPRequestChannel(int _sockfd)
{
    sockfd = _sockfd;
}

TCPRequestChannel::~TCPRequestChannel()
{
    // close the sockfd
    close(sockfd);
}

int TCPRequestChannel::accept_conn()
{
    // struct sockaddr_storage - used to implement client connection
    // implementing accept(...) - return value - the sockfd of client

    int socket = accept(sockfd, NULL, NULL);
    if (socket < 0)
    {
        perror("Error: Accpeting different connections");
        exit(EXIT_FAILURE);
    }
    return socket;
}

// read/write, recv/send
int TCPRequestChannel::cread(void *msgbuf, int msgsize)
{
    return recv(sockfd, msgbuf, msgsize, 0);
}

int TCPRequestChannel::cwrite(void *msgbuf, int msgsize)
{
    return send(sockfd, msgbuf, msgsize, 0);
}
