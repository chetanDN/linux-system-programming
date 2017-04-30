#include <stdio.h>	/* for fprintf */
#include <string.h>	/* for memcpy */
#include <stdlib.h> //exit(1)
#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/

int main(int argc, char **argv)
{
	int sockfd;
	struct sockaddr_in servaddr;
	char sendline[MAXLINE], recvline[MAXLINE];

	//basic check of the arguments
	//additional checks can be inserted
 	if (argc != 2) {
		perror("Usage: TCPClient <IP address of the server>\n");//perror outputs addition string : Success
		//printf("Usage: TCPClient <IP address of the server>\n");
		exit(1);
	}

	//Create a socket for the client
	//If sockfd<0 there was an error in the creation of the socket
	if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
		perror("Problem in creating the socket");
		exit(2);
	}

	//Creation of the socket
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr= inet_addr(argv[1]);
	servaddr.sin_port =  htons(SERV_PORT); //convert to big-endian order

	//Connection of the client to the socket
	if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))<0) {
		perror("Problem in connecting to the server");
		exit(3);
	}
	
	while (1) {
//		printf("Enter the string to send : ");
//		if(fgets(sendline, MAXLINE, stdin) == NULL)
//			exit(1);

//		send(sockfd, sendline, strlen(sendline), 0);

		if (recv(sockfd, recvline, MAXLINE,0) == 0){
			//error: server terminated prematurely
			printf("The server closed the connection\n");	
			//perror("The server terminated prematurely");	//this will display in 2nd itter of while loop
			exit(4);				//as DT server closes after every single service
		}
		fprintf(stdout,"Date TIme received back from the server is : %s\n",recvline);
		bzero(recvline,MAXLINE);	//not needed as its single itteration
		//fputs(recvline, stdout);
	}

	exit(0);
}


