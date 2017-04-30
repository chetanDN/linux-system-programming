/*
Design, develop, and execute a program in C under UNIX / LINUX environment to implement a simple concurrent connection-oriented server and demonstrate its functioning. 

Concurrent server handles multiple requests at one time.
–	More difficult to design and build
–	Better performance

Concurrency is achieved using fork call:

#include<unistd.h>
  int fork();
Return 0 in child, process ID of child in parent –1 on error

There are two typical uses of fork
–	A process makes a copy of itself so that one copy handle one operation while the other copy does another task.
–	A process wants to execute another program. Since the only way to create a new process is by calling fork, the process first calls fork to make a copy of itself, and then one of the copies(child) calls exec to replace itself with the new program


*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/
#define LISTENQ 8 /*maximum number of client connections*/

int main (int argc, char **argv)
{
	int listenfd, connfd, n;
	pid_t childpid;
	socklen_t clilen;
	char buf[MAXLINE];
	struct sockaddr_in cliaddr, servaddr;

	//Create a socket for the soclet
	//If sockfd<0 there was an error in the creation of the socket
	if ((listenfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
		perror("Problem in creating the socket");
		exit(2);
	}


	//preparation of the socket address
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	//bind the socket
	bind (listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	//listen to the socket by creating a connection queue, then wait for clients
	listen (listenfd, LISTENQ);

	printf("%s\n","Server running...waiting for connections.");

	for ( ; ; ) {

		clilen = sizeof(cliaddr);
		//accept a connection
		connfd = accept (listenfd, (struct sockaddr *) &cliaddr, &clilen);

		printf("%s\n","Received request...");

		if ( (childpid = fork ()) == 0 ) {//if it’s 0, it’s child process

			printf ("%s\n","Child created for dealing with client requests");

			//close listening socket
			close (listenfd);

			while ( (n = recv(connfd, buf, MAXLINE,0)) > 0)  {
				printf("%s","String received from and resent to the client:");
				puts(buf);
				send(connfd, buf, n, 0);
				bzero(buf,MAXLINE);
			}

			if (n < 0)
				printf("%s\n", "Read error");
			exit(0);
		}
		//close socket of the server
		close(connfd);
	}
}
