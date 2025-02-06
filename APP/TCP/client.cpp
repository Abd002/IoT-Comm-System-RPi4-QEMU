#include <iostream>
#include <iterator>
#include "tcp.hpp"  

int main(int argc, char**argv) {
    TCP tcpClient;  
    if(argc==1)
        return 0;
    const char* serverIp = argv[1];
    std::cout<<"Connecting to : "<<serverIp<<std::endl;
    int port = 8080; 


    int clientSocket = tcpClient.client(serverIp, port);
    if (clientSocket < 0) {
        std::cerr << "Failed to connect to server.\n";
        return -1;
    }

    std::cout << "Connected to server.\n";

    const char *message = "Hello from client!";
    tcpClient.clientTransmit(clientSocket, message);
    std::cout << "Message sent to server.\n";

    const char* serverResponse = tcpClient.clientReceive(clientSocket);
    std::cout << "Received from server: " << serverResponse << std::endl;


    tcpClient.endSocket(clientSocket);

    return 0;
}

