#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h> 
#include <fcntl.h>
#include <poll.h>

int main(){
    setbuf(stdout, NULL);
    char hostname[1234];
    struct sockaddr_in saddr;
    struct hostent *h;
    int sockfd;
    unsigned short port = 8784;
    
    
    if ((sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error creating socket \n");
        return 1;
    }
    
    struct in_addr *address;
    printf("Enter host domain name: ");
    fgets(hostname, 1234, stdin);
    hostname[strlen(hostname) - 1] = '\0';

    if ((h=gethostbyname(hostname)) == NULL) {
        printf("Unknown host \n");
        return 1;
    }

    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    memcpy((char *) &saddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
    saddr.sin_port = htons(port);

    setsockopt(sockfd, SOL_SOCKET,
               SO_REUSEADDR, &(int){1},
               sizeof(int));
    
    if (connect(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0) {
        printf("Cannot connect\n");
        return 1;
    }
    
    int sockfl = fcntl(sockfd, F_GETFL, 0);
    sockfl |= O_NONBLOCK;
    fcntl(sockfd, F_SETFL, sockfl);

    struct pollfd stdin_pollfd;
    stdin_pollfd.fd = fileno(stdin);
    stdin_pollfd.events = POLLIN;
    
    printf("Connected\n");
    char clientms[1234], svms[1234];
    fflush(stdout);
    while (1){
        printf("Client: ");
        do
        {
            fgets(clientms, 1234, stdin);
            if (strcmp(clientms,"/quit\n\0")==0) {
                send(sockfd, clientms, strlen(clientms) + 1, 0);
                close(sockfd);
                printf("Client disconnected \n");
                return 0;
            }
            send(sockfd, clientms, strlen(clientms) + 1, 0);
        } 
        
        while (clientms[strlen(clientms) - 1] != '\n');
        printf("Message from server: ");
        if (poll(&stdin_pollfd, 1, 0) > 0) {
            if (stdin_pollfd.revents & POLLIN){
                recv(sockfd, svms, 1234, 0);
                printf("%s\n",svms);
            } 
        while (svms[strlen(svms) - 1] != '\n');
    }
    return 0;
  }
}