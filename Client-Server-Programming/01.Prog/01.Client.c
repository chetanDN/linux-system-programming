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
    char sendline[MAXLINE],recvline[MAXLINE];
    time_t ts;
    
    if(argc != 2)
    {
        printf("usage ./cp server-IP-addr");
        exit(0);
    }
    
    if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        printf("socket creation successful");
        memset(&servaddr,0,sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(SERVER_PORT);
        
        if((connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr)))!=0)
        {
            printf("Error :  Server connect failed.\n");
            exit(0);
        }
        printf("client got connected to the server\n");
        printf("info Type 'exit' to end the session\n");
        
        while(1){
            ts = time(NULL);
            printf("[%Enter Message] : ",asctime(localtime(&ts)));
            scanf("%s",sendline);
            printf("...%s",sendline);
            
            if(sendline == "exit")
                break;
                
            if((n=write(sockfd,sendline,sizeof(sendline)))<0)
            {
                printf("Error : Client message sending to serverf failed\n");
                return 1;
            }
            printf("Info : Client Message asent to server successfully\n");
            
            if((n=read(sockfd,recvline,sizeof(recvline)))<0)
            {
                printf("Error : server reply messsage didnt received\n");
                break;
            }
            
            ts=time(NULL);
            printf("[%s Server Message] : %s\n\n",asctime(localtime(&ts)),recvline);
            
        }
        close(sockfd);
        printf("client terminated the server session\n");
    }
    
    
    return 0;
}
