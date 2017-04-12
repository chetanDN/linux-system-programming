// A UDP Client For The ECHO Service 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern int errno;

int UDPecho(const char *host,const char *service);
int errexit(const char *format,...)
int connectUDP(const char *host,const char *service);

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
			fprintf(stderr,"usage:UDPecho [host[port]]\n");
			exit(1);
	}
	
	UDPecho(host,service);
	exit(0);
}

//UDPecho
int UDPecho(const char * host,const char *service){
	char buf[LINELEN+1];	//buffer for one line of textattr
	int s,chars;				//socket fd, read count
	//int outchars,inchars;	//sent and recv characters
	
	s = connectUDP(host,service);
	
	while(fgets(buf,sizeof(buf),stdin)){
		buf[LINELEN] = '\0'; //insure line null-terminated
		chars = strlen(buf);
		(void)write(s,buf,chars);
		
		//read it back
		
/* 		for(inchars=0;inchars<outchars;inchars+=n){	//tcp stream oriented, so you may not receive all cahr at once
			n = read(s,&buf[inchars],outchars-inchars);
			if (n<0)
				errexit("socket read failed: %s\n",strerror(errno));
		} */
		
		if (read(s,buf,chars)<0)
			errexit("socket read failed: %s\n",strerror(errno));
		
		fputs(buf,stdout); 
	}
}
