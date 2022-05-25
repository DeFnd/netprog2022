#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h> 

int Resolve(char * h_name , char* ip_addr) {
        struct hostent *hostname;
        struct in_addr **addr_list;
        int i;
        if ((hostname = gethostbyname(h_name)) == NULL)  {             
                herror("Invalid hostname");             
        return 1;     
        }     
addr_list = (struct in_addr **) hostname->h_addr_list;     
for (i = 0; addr_list[i] != NULL; i++)  {             
        strcpy(ip_addr , inet_ntoa(*addr_list[i]));             
        return 0;     
        }     
return 1;
int Resolve(char *h_name , char *ip_addr);
int main(int argc , char *argv[]) {
        if (argc < 2) {
                printf("No hostname is given to resolve");
                exit(1);
        }
        char *h_name = argv[1];     
        char ip_addr[100];     
        resolveHost(h_name,ip_addr);     
        printf("%s resolved to %s" , h_name , ip_addr);     
   }
}