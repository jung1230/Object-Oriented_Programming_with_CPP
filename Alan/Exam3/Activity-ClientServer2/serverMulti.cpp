#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <string.h>  // Include for bzero
#include <unistd.h>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>
#include <algorithm>

#define RESPONSE_MAX_LENGTH 1000

using namespace std::chrono_literals;

// Global variables for storing active client information
std::mutex clientsMutex;
std::vector<std::string> activeClients;

void printActiveClients() {
    while (true) {
        std::this_thread::sleep_for(3s);

        std::lock_guard<std::mutex> lock(clientsMutex);
        if (!activeClients.empty()) {
            std::cout << "Active clients: ";
            for (const auto& client : activeClients) {
                std::cout << client << " ";
            }
            std::cout << std::endl;
        } else {
            std::cout << "No active clients." << std::endl;
        }
        // lock will be realse here

    }
}

void sender(uint8_t socketId, std::string clientAdd) {
    std::string data(RESPONSE_MAX_LENGTH + 1, 0);
    while (true) {
        ssize_t bytesRead;
        bzero(&data[0], RESPONSE_MAX_LENGTH);

        // get message
        bytesRead = read(socketId, &data[0], RESPONSE_MAX_LENGTH);

        if (bytesRead == 0) {
            {
                std::lock_guard<std::mutex> lock(clientsMutex);
                activeClients.erase(std::remove(activeClients.begin(), activeClients.end(), clientAdd), activeClients.end());
                // lock will be realse here
            }

            std::cout << "[" << __TIME__ << " "
                      << "Server_.cpp:" << __LINE__ << "] "
                      << "client " << clientAdd << " closed!\n";
            return;
        }

        std::cout << "[" << __TIME__ << " "
                  << "Server_.cpp:" << __LINE__ << "] "
                  << "Receiving " << data << " <-- " << clientAdd << "\n";

        std::cout << "[" << __TIME__ << " "
                  << "Server_.cpp:" << __LINE__ << "] "
                  << "Echoing " << data << " --> " << clientAdd << "\n";

        // return message
        send(socketId, &data[0], bytesRead, 0);
    }
}

uint8_t open_listenfd(int port) {
    uint8_t socketFileDescriptor;
    struct sockaddr_in address;
    int opt = 1;

    if ((socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(socketFileDescriptor, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt - Reuse-Address");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(socketFileDescriptor, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt - Reuse-Port");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(socketFileDescriptor, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(socketFileDescriptor, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    return socketFileDescriptor;
}

void listenToSocket(uint8_t listenfd, uint16_t port) {
    std::cout << "[" << __TIME__ << " "
              << "Server_.cpp:" << __LINE__ << "] "
              << "Listening @ PORT:" << port << "\n";
    while (true) {
        struct sockaddr_in address;
        int addrlen = sizeof(address);
        uint8_t connfd;

        // Accepts a connection using accept and obtains a new file descriptor (connfd) for the connection.
        if ((connfd = accept(listenfd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        char ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &address.sin_addr, ip, sizeof(ip));
        uint16_t port = htons(address.sin_port);
        std::string clientAdd = std::string(ip) + ":" + std::to_string(port);

        {
            std::lock_guard<std::mutex> lock(clientsMutex);
            activeClients.push_back(clientAdd);
            // lock will be realse here

        }

        std::cout << "[" << __TIME__ << " "
                  << "Server_.cpp:" << __LINE__ << "] "
                  << clientAdd
                  << " Connected!\n";
        // Detached threads are suitable for simple applications 
        // where you don't need to explicitly wait for the threads
        // to finish, and the threads can safely terminate when
        // the main thread exits.

        // After the accept function successfully returns with a new file 
        // descriptor connfd representing the accepted connection, 
        // the server immediately spawns a new thread to handle 
        // communication with that specific client. This newly created 
        // thread takes ownership of the connfd, and the main thread
        //  is free to go back to the accept function to wait for the
        // next incoming connection.
        std::thread(sender, connfd, clientAdd).detach();
    }

}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage Error: please select port number\n";
        return -1;
    }

    uint8_t socketFileDescriptor = open_listenfd(std::atoi(argv[1]));

    std::thread(printActiveClients).detach();
    listenToSocket(socketFileDescriptor, std::atoi(argv[1]));

    return 0;
}
