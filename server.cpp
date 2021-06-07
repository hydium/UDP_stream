#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
  
#define PORT    10001
#define MAXLINE 1024

int main() {
    int sockfd;
    
 
    struct sockaddr_in servaddr, cliaddr;
    char buffer[16];
      
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
      
    memset(&servaddr, 0, sizeof(servaddr));
    // memset(&cliaddr, 0, sizeof(cliaddr));
      
    // Filling server information
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
      
    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
      
    int n;

    socklen_t len;
  
    len = sizeof(cliaddr);  //len is value/resuslt
  

    while (true) {
        
        n = recvfrom(sockfd, (char *)buffer, 16, 
                MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                &len);

        
        uint32_t seq_num;
        float roll; 
        float yaw;
        float pitch;

        memcpy(&seq_num, buffer, 4);
        memcpy(&roll, buffer + 4, 4);
        memcpy(&yaw, buffer + 8, 4);
        memcpy(&pitch, buffer + 12, 4);


        printf("seq_num %d\n", seq_num);
        printf("roll %f\n", roll);
        printf("yaw %f\n", yaw);
        printf("pitch %f\n", pitch);
    }
    // printf("Client : %s\n", buffer);
    // sendto(sockfd, (const char *)hello, strlen(hello), 
    //     MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
    //         len);
    // printf("Hello message sent.\n"); 
      
    return 0;
}