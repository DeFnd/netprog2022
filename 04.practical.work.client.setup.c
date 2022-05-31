#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>  
int main() {
	char name[255];
	struct sockaddr_in saddr;
	struct hostent *h;
	int sockfd;
	unsigned short port = 8784;
	
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Error creating socket\n");
		return 1;
	
	}
	struct in_addr *addr_list;
    printf("Enter host domain name: ");
    scanf("%s", name);


	if ((h = gethostbyname(name)) == NULL) {
		printf("Unknown host!\n");
		return 1;
	
	}
	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	memcpy((char *) &saddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
	saddr.sin_port = htons(port);

	if (connect(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0) {
		printf("Cannot connect");
		return 1;
	}
	printf("Successfully Connected\n");
	return 0;
}