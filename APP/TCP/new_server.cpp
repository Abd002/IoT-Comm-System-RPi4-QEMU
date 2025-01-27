#include <iostream>
#include <thread>
#include "tcp.hpp"

// Function to handle client communication
void handleClient(int clientSocket, TCP& tcpServer) {
    while (true) {
        // Receive message from client
        const char* clientMessage = tcpServer.serverReceive(clientSocket);
        if (clientMessage == nullptr || strlen(clientMessage) == 0) {
            std::cerr << "Client disconnected or error occurred.\n";
            break;
        }
        std::cout << "Received from client: " << clientMessage << std::endl;

        // Prepare and send response to client
        const char* responseMessage = "Sending acknowledgment. Current Temperature is 39 ⁰C";
        tcpServer.serverTransmit(clientSocket, responseMessage);
        std::cout << "Response sent to client.\n";
    }

    // Close the client socket
    tcpServer.endSocket(clientSocket);
}

int main() {
    TCP tcpServer;
    int port = 8080;

    // Bind and listen on the specified port
    if (tcpServer.server(port) < 0) {
        std::cerr << "Failed to start server.\n";
        return -1;
    }

    std::cout << "Server is listening on port " << port << "...\n";

    while (true) {
        // Accept a new client connection
        int clientSocket = tcpServer.server(port);
        if (clientSocket < 0) {
            std::cerr << "Failed to accept client connection.\n";
            continue;
        }

        std::cout << "Server is connected to client.\n";

        // Handle client communication in a separate thread
        std::thread clientThread(handleClient, clientSocket, std::ref(tcpServer));
        clientThread.detach(); // Detach the thread to handle the client independently
    }

    // Close the server socket (this won't be reached in this example)
    tcpServer.endServer();

    return 0;
}
