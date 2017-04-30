/*
Design, develop, and execute a program in C under UNIX / LINUX environment to implement a simple Day / Time Server and demonstrate its functioning. 
*/

#include<sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h> //bzero()
#include <time.h>
#include <stdlib.h>

#define PORT 3000 //default DT server port 13 for TCP/UDP port

int main(int argc, char **argv)
{
	int listenfd, connfd;

	struct sockaddr_in servaddr;
	char buff[1000];
	time_t ticks;


	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	listen(listenfd, 8);
	printf("Serving Date Time on port %d\n",PORT);
	for (;;) {
		connfd = accept(listenfd, (struct sockaddr *) NULL, NULL);

		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		write(connfd, buff, strlen(buff));
		close(connfd);
	}
}
