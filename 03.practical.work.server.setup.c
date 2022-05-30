#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(){
    int sockfd, clen, clientfd;
    struct sockaddr_in saddr, caddr;
    unsigned short port = 8784;
    if ((sockfd = socket(AF_INET, SOCK_STREAM,0)) < 0){
        printf("Error creating socket\n");
        return 1;
    }
    
    memset(&saddr,0,sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(port);

    if ((bind(sockfd, (structsockaddr *) &saddr,sizeof(saddr)) < 0){
        perror(“Error binding\n”);
        return 1;
    }

    if (listen(sockfd,5) < 0) {
        perror(“Error listening\n”);
        return 1;
    }

    clen = sizeof(caddr);
    if ((clientfd = accept(sockfd, (structsockaddr *) &caddr, &clen)) < 0){
        perror(“Error accepting connection\n”);
        return 1;
    }
    printf("Accepting connection\n");
    return 0;
}

