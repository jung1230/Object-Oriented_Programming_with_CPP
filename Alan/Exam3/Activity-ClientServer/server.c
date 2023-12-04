#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define LISTENQ 10
#define MAXLINE 100

int open_listenfd(int port)  
{ 
  int listenfd, optval=1; 
  struct sockaddr_in serveraddr; 
   
  /* Create a socket descriptor */ 
  if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    return -1; 
  
  /* Eliminates "Address already in use" error from bind. */ 
  if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR,  
		 (const void *)&optval , sizeof(int)) < 0) 
    return -1; 
 
  /* Listenfd will be an endpoint for all requests to port 
     on any IP address for this host */ 
  bzero((char *) &serveraddr, sizeof(serveraddr)); 
  serveraddr.sin_family = AF_INET;  
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);  
  serveraddr.sin_port = htons((unsigned short)port);  
  if (bind(listenfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0) 
    return -1; 
 
  /* Make it a listening socket ready to accept 
     connection requests */ 
  if (listen(listenfd, LISTENQ) < 0) 
    return -1; 
 
  return listenfd; 
} 

// Function to handle the communication with a client
void *echo_thread(void *arg) {
  int connfd = *((int *)arg);
  size_t n;
  char buf[MAXLINE];

  while ((n = read(connfd, buf, MAXLINE)) != 0) {
    printf("server received %ld bytes\n", n);
    write(connfd, buf, n);
  }

  close(connfd);
  free(arg);
  pthread_exit(NULL);
}

int main(int argc, char **argv) {
  int listenfd, *connfd;
  pthread_t tid;
  socklen_t clientlen;
  struct sockaddr_in clientaddr;

  int port = atoi(argv[1]);
  listenfd = open_listenfd(port);

  while (1) {
    clientlen = sizeof(clientaddr);
    connfd = (int *)malloc(sizeof(int));
    *connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);

    if (pthread_create(&tid, NULL, echo_thread, (void *)connfd) != 0) {
      perror("pthread_create");
      close(listenfd);
      exit(EXIT_FAILURE);
    }

    // Detach the thread to allow it to clean up resources on exit
    if (pthread_detach(tid) != 0) {
      perror("pthread_detach");
      close(listenfd);
      exit(EXIT_FAILURE);
    }
  }

  // The program will never reach this point in this example
  close(listenfd);
  return 0;
}


// g++ -o server server.c
//./client eceprog1 5000