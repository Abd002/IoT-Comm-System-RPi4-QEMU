#include <iostream>
#include <thread>
#include "tcp.hpp"
using namespace std;
void receiveMessages(TCP& tcpClient, int clientSocket) {
    while (true) {
        const char* serverResponse = tcpClient.clientReceive(clientSocket);
        if (serverResponse) {
            cout << "Received from server: " << serverResponse << std::endl;
        } else {
            cerr << "Server disconnected or error occurred.\n";
            break;
        }
    }
}
void sendMessages(TCP& tcpClient, int clientSocket) {
    const char* message = "Hello from client!";
    while (true) {
        tcpClient.clientTransmit(clientSocket, message);
        cout << "Message sent to server: " << message << std::endl;
        receiveMessages(tcpClient, clientSocket);
        this_thread::sleep_for(chrono::seconds(2));
    }
}



int main() {
    TCP tcpClient;

    const char* serverIp = "192.168.0.1";
    int port = 8080;

    int clientSocket = tcpClient.client(serverIp, port);
    if (clientSocket < 0) {
        cerr << "Failed to connect to server.\n";
        return -1;
    }

    cout << "Connected to server.\n";

    thread sendThread(sendMessages, std::ref(tcpClient), clientSocket);

    sendThread.join();

    tcpClient.endSocket(clientSocket);

    return 0;
}
