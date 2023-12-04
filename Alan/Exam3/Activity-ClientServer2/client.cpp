#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <thread>
#include <iostream>

#define RESPONSE_MAX_LENGTH 1000

int connectToServer(std::string serverIpUsingDNS, uint16_t serverPort)
{
  int sock = -1;
  struct sockaddr_in serv_addr;
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    std::cout << "[" << __TIME__ << " "
              << "Client_.cpp:" << __LINE__ << "] "
              << "connectToServer(): Socket creation error\n";
    return -1;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(serverPort);
  hostent *serverInfo = gethostbyname(serverIpUsingDNS.c_str());
  std::string serverIp(inet_ntoa(**(in_addr **)serverInfo->h_addr_list));
  // Convert IPv4 and IPv6 addresses from text to binary form
  if (inet_pton(AF_INET, serverIp.c_str(), &serv_addr.sin_addr) <= 0)
  {
    std::cout << "[" << __TIME__ << " "
              << "Client_.cpp:" << __LINE__ << "] "
              << "connectToServer(): Invalid address"
                 "Address not supported \n";
    return -1;
  }

  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
  {
    std::cout << "[Client_.cpp:" << __LINE__ << "] "
              << "connectToServer(): nConnection Failed\n";
    return -1;
  }
  struct sockaddr_in myAddr;
  bzero(&myAddr, sizeof(myAddr));
  socklen_t addrLen = sizeof(myAddr);
  getsockname(sock, (struct sockaddr *)&myAddr, &addrLen);
  uint16_t port = htons(myAddr.sin_port);
  std::cout << "[Client_.cpp:" << __LINE__ << "] "
            << "PORT:" << port << "\n";
  return sock;
}

void receiver(int socketId, std::string serverIpUsingDNS, uint16_t serverPort)
{

  std::string msg;

  // this buffer will hold the received bytes at socket.
  std::string data(RESPONSE_MAX_LENGTH + 1, 0);
  while (true)
  {
    std::cout << "[" << __TIME__ << " "
              << "Client_.cpp:" << __LINE__ << "] "
              << "Please enter your msg: ";
    std::getline(std::cin, msg);

    size_t msgLen = msg.length();
    if (msgLen == 0)
    {
      std::cout << "[" << __TIME__ << " "
                << "Client_.cpp:" << __LINE__ << "] "
                << "[Error] message is empty!";

      continue;
    }
    std::cout << "[" << __TIME__ << " "
              << "Client_.cpp:" << __LINE__ << "] " << msg << " --> server @"
              << serverIpUsingDNS << ":" << serverPort << "\n";
    send(socketId, msg.c_str(), msgLen, 0);

    bzero(&data[0], RESPONSE_MAX_LENGTH);
    ssize_t bytesRead = read(socketId, &data[0], RESPONSE_MAX_LENGTH);
    std::cout << "[" << __TIME__ << " "
              << "Client_.cpp:" << __LINE__ << "] " << msg << " <-- server @"
              << serverIpUsingDNS << ":" << serverPort << "\n";
  }
}

int main(int argc, char **argv)
{

  if (argc < 3)
  {
    std::cout << "Usage Error: please enter server IP along with port number\n";
    return -1;
  }

  int socketId = connectToServer(argv[1], std::atoi(argv[2]));
  if (socketId == -1)
  {
    exit(0);
  }
  std::thread recvThread(receiver, socketId, argv[1], std::atoi(argv[2]));
  recvThread.join();
  return 0;
}