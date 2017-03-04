

///////////////////////////////////
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
        char sendline[MAXLINE],recvline[MAXLINE];
        time_t ts;
        if(argc != 2)
        {
                printf("usage %s server-IP-addr\n",argv[0]);
                exit(0);
        }
        if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
        {
                printf("Problem in creating the socket");
                exit(0);
        }
        printf("socket creation successful");

        servaddr.sin_family =AF_INET;
        servaddr.sin_port = htons(SERVER_PORT);
        servaddr.sin_addr.s_addr= inet_addr(argv[1]);
        if((connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr)))<0)
        {
                printf("Error : Server connect failed.\n");
                exit(0);
        }
        printf("client got connected to the server\n");
        printf("info Type 'exit' to end the session\n");
        while(1){
                ts = time(NULL);
                printf("[%s Enter Message] : ",asctime(localtime(&ts)));
                scanf("%s",sendline);
                printf("%s\n",sendline);
                if(strcmp(sendline,"exit")==0)
                        break;
                if((n=write(sockfd,sendline,sizeof(sendline)))<0)
                {
                        printf("n = %d Error : Client message sending to serverf failed\n",n);
                        return 1;
                }
                printf("n= %d Info : Client Message a sent to server successfully\n",n);
                if((n=read(sockfd,recvline,sizeof(recvline)))<0)
                {
                        printf("Error : server reply messsage didnt received\n");
                        return 1;
                }
                ts=time(NULL);
                printf("[%s Server Message] : %s\n\n",asctime(localtime(&ts)),recvline);
        }
        close(sockfd);
        printf("client terminated the server session\n");
        return 0;
}
