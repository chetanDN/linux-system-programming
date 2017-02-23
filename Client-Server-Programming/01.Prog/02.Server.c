/**/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <time.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAXLINE 4096
#define SERVER_PORT 4000
#define LISTENQ 5

int main(int argc,char **argv)
{
    
    int listenfd,connfd,n;
    socklen_t clilen;
    char buff[MAXLINE];
    struct sockaddr_in cliaddr,servaddr;
    //char sendline[MAXLINE],recvline[MAXLINE];
    time_t ts;
    
    if((listenfd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        printf("server socket creation failed\n");
        exit(0);
    }
    
    printf("Server Socket created successfully\n");

    memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family =AF_INET;
    servaddr.sin_port        = htons(SERVER_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
 
    //servaddr.sin_addr.s_addr=htons(SERVER_PORT);
    
    if(bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0)
    {
        printf("Error : Server bind to port %d failed \n",SERVER_PORT);
        exit(0);
    }
    printf("Server bound to port %d successfully\n",SERVER_PORT);
    if(listen(listenfd,LISTENQ)<0)
    {
        printf("ERROR : server is not listening\n");
        exit(0);
    }
    
    printf("Server is listening  ..\n client requests are accepted\n\n");
    
    for(;;)
    {
        clilen=sizeof(cliaddr);
        if((connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&clilen))<0)
        {
            printf("Error : Server didnt accept the client request \n");
            exit (0);
        }
        printf("Server accepted the accept() request from client\n");
        while((n=read(connfd,buff,MAXLINE))<0)
        {
            ts=time(NULL);
            printf("%s client message : %s \n\n",asctime(localtime(&ts)),buff);
            fflush (stdin);
        }
        if(n==0)
            printf("Error :Client Disconnected\n");
        else if(n==-1)
            printf("Error :Server receive operation failed\n");
        }
 
    close(connfd);
    
    return 0;
}
