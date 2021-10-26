#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
  
#define PORT    10004
#define MAXLINE 1024

int main() {
    int sockfd;
    
    struct sockaddr_in servaddr, cliaddr;
    char data[16];
      
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
  
    len = sizeof(cliaddr);  //len is value/result
  
    while (true) {
        
        n = recvfrom(sockfd, (char *)data, 22, 
                MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                &len);

        
        uint32_t seq_num;
        float joystick_x; 
        float joystick_y;
        float gripTrigger;
        float indexTrigger;
        bool a;
        bool b;

        memcpy(&seq_num, data, 4);
        memcpy(&joystick_x, data + 4, 4);
        memcpy(&joystick_y, data + 8, 4);
        memcpy(&gripTrigger, data + 12, 4);
        memcpy(&indexTrigger, data + 16, 4);
        memcpy(&a, data + 20, 4);
        memcpy(&b, data + 21, 4);


        printf("seq_num %d\n", seq_num);
        printf("joystick_x %f\n", joystick_x);
        printf("joystick_y %f\n", joystick_y);
        printf("indexTrigger %f\n", indexTrigger);
        printf("gripTrigger %f\n", gripTrigger);
        printf("a %d\n", a);
        printf("b %d\n", b);

        
    }
      
    return 0;
}