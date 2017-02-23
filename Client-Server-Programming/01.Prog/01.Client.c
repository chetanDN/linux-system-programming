/*

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <time.h>

#define MAXLINE 4096
#define SERVER_PORT 4000
#define LISTENQ 5

int main(int argc,char **argv)
{
    
    int sockfd,n;
    struct sockaddr_in servaddr;
    char sendline[MAXLINE],recvLine[MAXLINE];
    time_t ts;
    
    if(argc != 2)
    {
        printf("usage ./cp server-IP-addr");
        exit(0);
    }
    
    if((sockfd=socket(AF_INET,sock_stream,0))<0)
    {
        printf("socket creation successful");
        memset(&servaddr,0,sizeof(servaddr));
        servaddr.sin_family = AD_INET;
        servaddr.sin_port = htons(SERVER_PORT);
        
        if((connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr)))!=0)
        {
            
        }
    }
    
    
    return 0;
}
