#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>

int main(){
    setbuf(stdout, NULL);
    int sockfd, clen, clientfd;
    struct sockaddr_in saddr, caddr;
    unsigned short port = 8784;
    

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("Error creating socket\n");
        return 1;
    }

    setsockopt(sockfd, SOL_SOCKET,
               SO_REUSEADDR, &(int){1},
               sizeof(int));
    
    int sockfl = fcntl(sockfd, F_GETFL, 0);
    sockfl |= O_NONBLOCK;
    fcntl(sockfd, F_SETFL, sockfl);

    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0){
        perror("Error binding");
        return 1;
    }

    if (listen(sockfd, 5) < 0){
        perror("Error listening");
        return 1;
    }

    struct pollfd stdin_pollfd;
    stdin_pollfd.fd = fileno(stdin);
    stdin_pollfd.events = POLLIN;
    
    clen = sizeof(caddr);
    if ((clientfd = accept(sockfd, (struct sockaddr *)&caddr, &clen)) < 0){
        perror("Error accepting connection");
        return 1;
    }

    printf("Connected!\n");
    
    int clientfl = fcntl(clientfd, F_GETFL, 0);
    clientfl |= O_NONBLOCK;
    fcntl(clientfd, F_SETFL, clientfl);

    char clientms[1234], svms[1234];
    while(1)
    {
        clientfd = accept(sockfd, (struct sockaddr *)&caddr, &clen);
        if (clientfd > 0)
        {
            printf("A client connected!\n");
            printf("Type: ");

            int clientfl = fcntl(clientfd, F_GETFL, 0);
            clientfl |= O_NONBLOCK;
            fcntl(clientfd, F_SETFL, clientfl);
            int Connected = 1;
            while (Connected)
            {
                if (recv(clientfd, svms, sizeof(svms), 0) > 0)
                {
                    printf("\rClient message: ");
                    printf("%s", svms);
                    printf(">>> ");
                }
                if (poll(&stdin_pollfd, 1, 0) > 0){
                    if (stdin_pollfd.revents & POLLIN) {
                        fgets(clientms, sizeof(clientms), stdin);
                        send(clientfd, svms, strlen(svms) + 1, 0);
                        printf(">>>");
                    }
                }
            }

            close(clientfd);
        }
    }
    close(sockfd);
    return 0;
}