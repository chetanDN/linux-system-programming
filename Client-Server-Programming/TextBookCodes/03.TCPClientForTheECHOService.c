// A TCP Client For The ECHO Service 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern int errno;

int TCPecho(const char *host,const char *service);
int errexit(const char *format,...)
int connectTCP(const char *host,const char *service);

#define LINELEN 128

int main(int argc,char 8 argv[]){
	char *host = "localhost";
	char *service = "echo";
	
	switch(argc){
		case 1:
			host ="localhost";
			break;
		case 3:
			service = argv[2];
		//fall through
		case 2:
			host = argv[1];
			break;
		default:
			fprintf(stderr,"usage:TCPecho [host[port]]\n");
			exit(1);
	}
	
	TCPecho(host,service);
	exit(0);
}

//TCPecho
int TCPecho(const char * host,const char *service){
	char buf[LINELEN+1];	//buffer for one line of textattr
	int s,n;				//socket fd, read count
	int outchars,inchars;	//sent and recv characters
	
	s = connectUDP(host,service);
	
	while(fgets(buf,sizeof(buf),stdin)){
		buf[LINELEN] = '\0'; //insure line null-terminated
		outchar = strlen(buf);
		(void)write(s,buf,outchars);
		
		//read it back
		
		for(inchars=0;inchars<outchars;inchars+=n){	//tcp stream oriented, so you may not receive all cahr at once
			n = read(s,&buf[inchars],outchars-inchars);
			if (n<0)
				errexit("socket read failed: %s\n",strerror(errno));
		}
		fputs(buf,stdout); 
	}
}
