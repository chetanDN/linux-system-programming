#define __USE_BSD 1

#include <sys/types.h>
//#include <sys/socket.h>
#include <WinSock2.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <netdb.h>
#include <string.h>
#include <stdlib.h>

#ifndef INADDR_NONE
#define INADDR_NONE 0xffffffff
#endif

typedef unsigned short u_short;
extern int errno;

int errexit(const char *format, ...);

/*connect socket - allocate and connect a sockeet*/
int connectsock(const char *host,const char *service,const char *transport){
	struct hostent *phe;
	struct servent *pse;
	struct protoent *ppe;
	struct sockaddr_in sin;
	int s,type;

	memset(&sin,0,sizeof(sin));
	sin.sin_family = AF_INET;

	//map service to port
	if ( pse = getservbyname(service,transport) ) //(http,tcp)
		sin.sin_port = pse->s_port;
	else if ( (sin.sin_port=  htons((u_short)atoi(service)) ) == 0 )
		errexit("cant get \" %s \" service entry\n",service);

	//map host name to IP
	if ( phe = gethostbyname(host) ) //(http,tcp)
		memcpy(&sin.sin_addr,phe->h_addr,phe->h_length);
	else if ( (sin.sin_addr= inet_addr(host)) == INADDR_NONE )
		errexit("cant get \" %s \" host entry\n",service);
}
