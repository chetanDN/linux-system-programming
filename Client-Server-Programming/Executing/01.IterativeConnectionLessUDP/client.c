#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>	/* for fprintf */
#include <string.h>	/* for memcpy */

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <stdlib.h>

#define PORT 1153   
int main(int argc, char **argv)
{
	struct hostent *hp;     /* host information */
	struct sockaddr_in servaddr;    /* server address */
	//char *my_message = "this is a test message";
	char my_message[1024]={};
	char *host=argv[1];
	char *port=argv[2];
	int fd;

	if(argc != 3){
		printf("Input ERROR - usage: %s serverip port\n",argv[0]);
		exit(1);
	}

	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("cannot create socket\n");
		return 0;
	}


	/* fill in the server's address and data */
	memset((char*)&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(port));

	/* look up the address of the server given its name */
	hp = gethostbyname(host);
	if (!hp) {
		fprintf(stderr, "could not obtain address of %s\n", host);
		return 0;
	}

	/* put the host's address into the server address structure */
	memcpy(&servaddr.sin_addr, hp->h_addr, hp->h_length);

	/*Get a message from user*/
	printf("Enter the message to be sent : ");
	//scanf(" %s",my_message);
	gets(my_message);

	/* send a message to the server */
	if (sendto(fd, my_message, strlen(my_message), 0, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
		perror("sendto failed");
		return 0;
	}
	printf("\nMessage Sent Successfully.! Check Server\n");
}
