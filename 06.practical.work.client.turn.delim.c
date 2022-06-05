#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h> 
#include<netdb.h>

int main(){
    char input[1234];
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
    fgets(input, 1234, stdin);
    input[strlen(input) - 1] = '\0';

    if ((h=gethostbyname(input)) == NULL) {
        printf("Unknown host \n");
        return 1;
    }

    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    memcpy((char *) &saddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
    saddr.sin_port = htons(port);

    if (connect(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0) {
        printf("Cannot connect\n");
        return 1;
    }
    printf("Connected to server successfully \n");
    char clientms[1234], svms[1234];

    while (1){
        printf(">>> ");
        do
        {
            fgets(clientms, 1234, stdin);
            if (send(sockfd, clientms, strlen(clientms) + 1, 0)<0){
                printf("Can not send to server!!!");
            };
        } while (clientms[strlen(clientms) - 1] != '\n');

        do
        {
            if (recv(sockfd, svms, 1234, 0)<0){
                printf("Can not get server's message!!!");
            }
            printf("%s\n",svms );
            
        } while (svms[strlen(svms) - 1] != '\n');
        
    }
    return 0;
}