// ClientSoftware.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int connectsock(const char *host,const char *service,const char *transport);

/* connectTCP.c */

int connectTCP(const char *host,const char *service){
	return connectsock(host,service,"tcp");
}

int main(int argc, char* argv[])
{
	printf("Working");



	getchar();
	return 0;
}

