/*
process 1 will send directory name to process2.
Process2 after receiving directory name, open directory ,send back sizeof file and no. of hard links to process1.

one process will send the dirname to messageQ (take  mtype=2)
another process will open this directory name, get the file names and hard links 
and put back to msgQ(mtype=3 consecutively)
then again process 1 will read and print the contents from msg Q

Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com
*/

#include "header.h"

struct fDetails
{
	char fileName[50];	//first use for sending dir name, later for getting file name
	int hLinks;		//hard links of file
};

struct msgbuf
{
	int mtype;
	struct fDetails fdv;	//fileDetails variable
};

main(int argc,char *argv[])
{
	struct msgbuf v;
	int msgqid;
	
	if(argc != 2)
	{
		printf("usage: %s <dirname>\n",argv[0]);
		return;
	}

	msgqid=msgget(4,IPC_CREAT|0644);	//for sending dir name
	
	if(msgqid<0)
	{
		perror("msgget");
		return;
	}

	v.mtype=2;
	strcpy(v.fdv.fileName,argv[1]);	//copy dir name
	msgsnd(msgqid,&v,sizeof(struct fDetails),0);	//send the dir name at mtype=2
//	perror("msgsnd");
	
/*now printng the directory content -> file name and hard links*/
	printf("file name \t\t hard links\n");
	while(1)
	{
		if( msgrcv(msgqid,&v,sizeof(struct msgbuf),3,0) == 0)	//retrieve data from mtype=3, ==0 not error, when zero bytes read occur, so that to come out of loop
		{
			perror("msgrcv");
			break;
		}

		printf("%s \t\t %d \n",v.fdv.fileName,v.fdv.hLinks);
	}


}
