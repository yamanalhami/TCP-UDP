#include	<sys/socket.h>
#include	<netinet/in.h>	
#include   	<arpa/inet.h>
#include 	<netinet/in.h>
#include 	<stdio.h>
#include	<string.h>
#include	<stdlib.h>
#include	<errno.h>
#include 	<unistd.h>

#define MAXLINE 8192

void cli(FILE * fp, int sockfd, struct sockaddr* servaddr, socklen_t servlen ) 
{
	
	int n;	
	char sendline[MAXLINE], rcvline[MAXLINE+1];
		
	while (fgets(sendline, MAXLINE, fp) != NULL) {
	printf("Input text is: %s", sendline);

	n = sendto(sockfd, sendline, strlen(sendline), 0, servaddr, servlen);
	if (n < 0) { perror("sendto error");}

	n = recvfrom(sockfd, rcvline, MAXLINE, 0, NULL, NULL);
	if (n < 0) { perror("recvfrom error");}
		
	rcvline[n] = 0;
	printf("Received text is: ");
	fputs(rcvline, stdout);
	
	} // End while loop
}

int main(int argc, char ** argv) 
{

	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) perror("main: socket error");

	struct sockaddr_in servaddr;

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	servaddr.sin_port = htons(atoi(argv[2])); 

	
	cli(stdin, sockfd,(struct sockaddr*) &servaddr, sizeof(servaddr));
	
	return 0;
}
