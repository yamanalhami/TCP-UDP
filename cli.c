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

void cli(FILE * fp, int sockfd) {
	
	int n;	
	char sendline[MAXLINE], rcvline[MAXLINE];
		
	while (fgets(sendline, MAXLINE, fp) != NULL) {
		printf("Input text is: %s", sendline);
		n = write(sockfd, sendline, strlen(sendline));
		if (n < 0) perror("str_cli: write error"); 
		
		n = read(sockfd, rcvline, MAXLINE);
		if (n <= 0) perror("str_cli: read error");
		rcvline[n] = 0;
		
		printf("Received text is: ");
		fputs(rcvline, stdout);
		exit(0);
	}
}

int main(int argc, char ** argv) {

	int sockfd, c_retVal;
	struct sockaddr_in servaddr;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) perror("main: socket error");

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	servaddr.sin_port = htons(atoi(argv[2])); 

	c_retVal = connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	if (c_retVal < 0) perror("main: connect error");
	
	cli(stdin, sockfd);
	return 0;
	}
