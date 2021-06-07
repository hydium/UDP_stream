// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
  
#define PORT     8080
#define MAXLINE 1024
  
// Driver code
int main() {
    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in     servaddr;
  
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
  
    memset(&servaddr, 0, sizeof(servaddr));
      
    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;
      
    // int n;

    // socklen_t len;
    
    // int number = 0;
    // char* data;

    while (true) {
        // sprintf(data, "%d", number);
          
        char data[4];

        float f = 1.23f;
        // float q = 0.0f;
        // float q = f;

        memcpy(data, &f, 4);

        // memcpy(&q, data, 4);

        printf("data %f\n", *data);
        printf("f %f\n", f);
        // printf("q %f\n", q);

        sendto(sockfd, (const char *)data, 4, 
            MSG_DONTWAIT, 
            (const struct sockaddr *) &servaddr, 
            sizeof(servaddr));

        // std::cout << strlen(data) << endl;

        // printf("%d\n", strlen(data));

        // number++;
    }
    // printf("Hello message sent.\n");
          
    // n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
    //             MSG_WAITALL, (struct sockaddr *) &servaddr,
    //             &len);
    // buffer[n] = '\0';
    // printf("Server : %s\n", buffer);
  
    close(sockfd);
    return 0;
}