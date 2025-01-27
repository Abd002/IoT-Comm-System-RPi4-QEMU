#ifndef TCP_HPP
#define TCP_HP

#include <iostream> 
#include <string>
#include <unistd.h>  
#include <netinet/in.h> 
#include <arpa/inet.h>  
#include <string.h>  

class TCP{
    int server_fd ;
    char buffer[1024];
    struct sockaddr_in address;
    int addrlen = sizeof(address);
public:
    TCP();

    int server(int port);
    int acceptClient();
    const char* serverReceive(int socket);
    int serverTransmit(int socket,const char *message);
    void endServer();

    void endSocket(int socket);
    
    
    int client(const char * server_ip, int port);
    void clientTransmit(int socket, const char *message);
    const char * clientReceive(int socket);



};

#endif
