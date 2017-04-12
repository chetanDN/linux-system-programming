// A UDP Client For The TIME Service 

#include <stdio.h>
#include <string.h>

#include <stdlib.h>
#include <sys/types.h>

#include <unistd.h>

#define BUFSIZE 64

#define UNIXEPOCH 2208988800 //unix epoch,in UCT secs
#define MSG "what time is it?\n"

typedef unsigned long u_long;
extern int errno;

int connectUDP(const char *host,const char *service);
int errexit(const char *format,...);

main(int argc,char *argv[]){
	char *host = "localhost";
	cahr *service = "time";
	time_t now;
	int s,n;


	switch (argc){
		case 1:
			host = "localhost";
			break;
		case 3:
			service = argv[2];
			//fall through
		case 2:
			host = argv[1];
			break;
		default:
			fprintf(stderr,"usage:UDPtime [host[port]]\n");
			exit(1);
	}

	s= connectUDP(host,service);
	(void)write(s,MSG,strlen(MSG));

	//read the time
	
	n= read(s,(char*)&now,sizeof(now));
	if(n<0)
		errexit("read failed: %s\n",strerror(errno));
	now = ntohl((u_long)now);
	now = now-UNIXEPOCH;
	printf("%s",ctime(&now));
	exit(0);
}
