#include "tcp.hpp"
#include <cstring>

TCP::TCP() : addrlen(sizeof(address)) {
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    memset(buffer, 0, sizeof buffer);
}

int TCP::server(int port) {
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on port " << port << "...\n";
    return 0;
}

int TCP::acceptClient() {
    int clientSocket;
    if ((clientSocket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept failed");
        return -1;
    }

    struct sockaddr_in client_address;
    socklen_t client_addr_len = sizeof(client_address);

    if (getpeername(clientSocket, (struct sockaddr*)&client_address, &client_addr_len) == -1) {
        perror("getpeername failed");
        return -1;
    }

    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(client_address.sin_addr), client_ip, INET_ADDRSTRLEN);

    std::cout << "Client IP address: " << client_ip << std::endl;

    return clientSocket;
}

const char* TCP::serverReceive(int socket) {
    read(socket, buffer, 1024);
    return buffer;
}

int TCP::serverTransmit(int socket, const char* message) {
    if (socket < 0) {
        return -1;
    }
    send(socket, message, strlen(message), 0);
    return 0;
}

void TCP::endServer() {
    close(server_fd);
}

void TCP::endSocket(int socket) {
    close(socket);
}

int TCP::client(const char* server_ip, int port) {
    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    if (inet_pton(AF_INET, server_ip, &address.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        return -1;
    }

    if (connect(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Connection failed");
        return -1;
    }

    return server_fd;
}

void TCP::clientTransmit(int socket, const char* message) {
    if (socket < 0) {
        std::cerr << "Invalid socket\n";
        return;
    }
    send(socket, message, strlen(message), 0);
}

const char* TCP::clientReceive(int socket) {
    if (socket < 0) {
        std::cerr << "Invalid socket\n";
        return nullptr;
    }
    read(socket, buffer, 1024);
    return buffer;
}
