/*
Implement full duplex communication using one message queue?
Hint: use different mtypes?

implementing full duplex using message Q

in this program, parent process will send message to message Q with mtype=2, 
		 & child process will retrieve message(from other user) written at mtype=3;

when message Q with specific mtype is empty retriving is blocked, thus helping in full duplex

Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com
*/

#include "header.h"

struct msgbuf
{
	int mtype;
	char message[20];
};

main()
{
	struct msgbuf v;
	int msgqid;
	char usrmsg[200]={};


	msgqid=msgget(4,IPC_CREAT|0644);
	if(msgqid<0)
	{
		perror("msgget");
		return;
	}

//fill the message box(struture) under key-4, and add its mtype
	if(fork())
	{
		v.mtype=3;	//sending fixed to mtype '3'
		printf("enter the message\n");
		while(1)	//parent in foreground, always scan data and put into mtype 2, queue
		{
			scanf("%s",usrmsg);
			strcpy(v.message,usrmsg);
			msgsnd(msgqid,&v,strlen(v.message)+1,0);
//			perror("msgsnd :");
		}
	}
	else	//child process
	{
		while(1)	//in background ,child always retrieve data when ever other process write to to mtype=3
		{
			msgrcv(msgqid,&v,sizeof(v),2,0);	//fixed retrieve from 2
//			perror("msgrcv :");
			printf("data rx = %s\n",v.message);
		}
	}
	
}
