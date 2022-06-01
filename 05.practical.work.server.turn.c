#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>

int main()
{
    int sockfd, clen, clientfd;
    struct sockaddr_in saddr, caddr;
    unsigned short port = 8784;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Error creating socket\n");
        return 1;
    }

    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
    {
        perror("Error binding");
        return 1;
    }

    if (listen(sockfd, 5) < 0)
    {
        perror("Error listening");
        return 1;
    }
    printf("Listening on port %d...\n", port);

    clen = sizeof(caddr);
    if ((clientfd = accept(sockfd, (struct sockaddr *) &caddr, &clen)) < 0) {
        printf("Error accepting connection\n"); 
        return 1;
    }
    printf("A client is connected.\n");

    char clientms[1234], svms[1234];
    while(1){
        recv(clientfd, clientms , sizeof(clientms),0);
        printf("%s\n", clientms); 
        printf("Enter a message to client: ");
        scanf("%s", svms); 
        send(clientfd, svms , sizeof(svms) , 0); 
        if (strncmp("bye", svms , 4) == 0) {
            printf("Exit!!!!!\n");
            break;
        }
    }
    return 0;
}