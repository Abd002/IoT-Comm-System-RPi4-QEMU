#include <iostream>
#include "tcp.hpp"

int main() {
    TCP tcpServer;

    int port = 8080;

    
    if (tcpServer.server(port) < 0) {
        std::cerr << "Failed to start server.\n";
        return -1;
    }

    std::cout << "Server is listening on port " << port << "...\n";

    while (true) {
        int clientSocket = tcpServer.acceptClient();
        if (clientSocket < 0) {
            std::cerr << "Failed to accept client connection.\n";
            continue;
        }

        std::cout << "Server is connected to client.\n";

        const char* clientMessage = tcpServer.serverReceive(clientSocket);
        std::cout << "Received from client: " << clientMessage << std::endl;

        const char* responseMessage = "Sending acknowledgment. Current Temperature is 39 ⁰C";
        tcpServer.serverTransmit(clientSocket, responseMessage);
        std::cout << "Response sent to client.\n";

        tcpServer.endSocket(clientSocket);
        std::cout<<std::endl;
    }

    tcpServer.endServer();

    return 0;
}
