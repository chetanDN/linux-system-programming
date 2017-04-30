#include <stdio.h>	/* for fprintf */
#include <string.h>	/* for memcpy */
#include <stdlib.h> //exit(1)
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <netinet/in.h>
#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/
#define LISTENQ 8 /*maximum number of client connections */

int main (int argc, char **argv)
{
	int listenfd, connfd, n;
	socklen_t clilen;
	char buf[MAXLINE];
	struct sockaddr_in cliaddr, servaddr;

	//creation of the socket
	listenfd = socket (AF_INET, SOCK_STREAM, 0);

	//preparation of the socket address
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	bind (listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	listen (listenfd, LISTENQ);

	printf("Server running at port %d waiting for connections.\n",SERV_PORT);

	for ( ; ; ) {

		clilen = sizeof(cliaddr);
		connfd = accept (listenfd, (struct sockaddr *) &cliaddr, &clilen);
		printf("%s\n","Received request...");

		while ( (n = recv(connfd, buf, MAXLINE,0)) > 0)  {
			printf("String received from client and resent to the client is : %s\n",buf);
			//puts(buf);
			send(connfd, buf, n, 0);
			bzero(buf,MAXLINE); //clear buffer completely (\0), will not hold previous data
		}

		if (n < 0) {
			perror("Read error");
			exit(1);
		}
		close(connfd);

	}
	//close listening socket
	close (listenfd);
}


