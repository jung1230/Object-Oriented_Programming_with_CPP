/************
 This code was originally developed by Ehab Ghabashneh, Ph.D student of Professor Sanjay Rao
 to help with the 39595 OO class, and some adaptations have been made.
*************/

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <string.h>
#include <unistd.h>

#include <chrono>
#include <iostream>


#define RESPONSE_MAX_LENGTH 1000

using namespace std::chrono_literals;


/******
  sender: This function receives messages from a client and echoes
          them back.
  socketId: Id of socket to a connected connection to a client
  clientAdd: IP address and port of the client to which connection established.
******/
void sender(uint8_t socketId, std::string clientAdd)
{
  std::string data(RESPONSE_MAX_LENGTH + 1, 0);
  while (true)
  {
    // this buffer will hold the received bytes at socket.
    ssize_t bytesRead;
    // fill the buffer with zeros
    bzero(&data[0], RESPONSE_MAX_LENGTH);
    bytesRead = read(socketId, &data[0], RESPONSE_MAX_LENGTH);

    // if true, then client has closed the connection
    if (bytesRead == 0)
    {
      std::cout << "[" << __TIME__ << " "
                << "Server_.cpp:" << __LINE__ << "] "
                << "client " << clientAdd << " closed!\n";
      return;
    }

    std::cout << "[" << __TIME__ << " "
              << "Server_.cpp:" << __LINE__ << "] "
              << "Receving " << data << " <-- " << clientAdd << "\n ";

    std::cout
        << "[" << __TIME__ << " "
        << "Server_.cpp:" << __LINE__ << "] "
        << "Echoing " << data << " --> " << clientAdd << "\n ";

    send(socketId, &data[0], bytesRead, 0);
  }
}

/****
 This function creates a socket, binds it to the necessary
 port and sets it in listening mode. No change is needed for
 the class activity.
*****/
uint8_t open_listenfd(int port)
{
  uint8_t socketFileDescriptor;
  struct sockaddr_in address;
  int opt = 1;

  // Creating socket file descriptor
  if ((socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0)) == 0)
  {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  if (setsockopt(socketFileDescriptor, SOL_SOCKET, SO_REUSEADDR, &opt,
                 sizeof(opt)))
  {
    perror("setsockopt - Reuse-Address");
    exit(EXIT_FAILURE);
  }

  if (setsockopt(socketFileDescriptor, SOL_SOCKET, SO_REUSEPORT, &opt,
                 sizeof(opt)))
  {
    perror("setsockopt - Reuse-Port");
    exit(EXIT_FAILURE);
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);

  if (bind(socketFileDescriptor, (struct sockaddr *)&address, sizeof(address)) <
      0)
  {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  if (listen(socketFileDescriptor, 3) < 0){
    perror("listen");
    exit(EXIT_FAILURE);
  }

  return socketFileDescriptor;
}

/******
This function waits for an incoming client connection,
processes it, and then waits for the next connection.
*******/

void listenToSocket(uint8_t listenfd, uint16_t port)
{

  std::cout << "[" << __TIME__ << " "
            << "Server_.cpp:" << __LINE__ << "] "
            << "Listening @ PORT:" << port << "\n";
  while (1)
  {
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    uint8_t connfd;


    if ((connfd = accept(listenfd, (struct sockaddr *)&address,
			 (socklen_t *)&addrlen)) < 0)
    {
      perror("accept");
      exit(EXIT_FAILURE);
    }

    char ip[INET_ADDRSTRLEN];
    // Converts a binary 32 bit IP address into a character array (e.g., "128.2.14.29"); stores result in ip.
    inet_ntop(AF_INET, &address.sin_addr, ip, sizeof(ip));
    uint16_t port = htons(address.sin_port);
    //clientAdd is a string that contains the IP address and port (in string form)
    std::string clientAdd = std::string(ip) + ":" + std::to_string(port);

    std::cout << "[" << __TIME__ << " "
              << "Server_.cpp:" << __LINE__ << "] "
              << clientAdd
              << " Connected!\n";

    sender(connfd, clientAdd);
  }
}

int main(int argc, char **argv)
{

  if (argc < 2)
  {
    std::cout << "Usage Error: please select port number\n";
    return -1;
  }
  
  // initialize the server listening socket.
  uint8_t socketFileDescriptor = open_listenfd(std::atoi(argv[1]));

  listenToSocket(socketFileDescriptor,std::atoi(argv[1]));
  return 0;
}