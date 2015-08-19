/*
process 1 will send directory name to process2.
Process2 after receiving directory name, open directory ,send back sizeof file and no. of hard links to process1.

receive dir name, open dir, get file name and hard links, put back to msgQ(mtype=3)


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

main()
{
	struct msgbuf v;
	int msgqid;
	DIR *dp;
	struct dirent *readDirP;
	struct stat statBuff;
	
	char path[200];
	char dirName[200];
	
	msgqid=msgget(4,IPC_CREAT|0644);
	
	msgrcv(msgqid,&v,sizeof(struct msgbuf),2,0);	//get the directory name

	strcpy(dirName,v.fdv.fileName);

	dp=opendir(dirName);
	perror("diropen");
	
	while( (readDirP=readdir(dp) ) != NULL)
	{
		if( readDirP->d_name[0] != '.')
		{
			strcpy(path,dirName);
			strcat(path,"/");
			strcat(path,readDirP->d_name);

			if(lstat(path,&statBuff) >= 0)
			{
				v.mtype=3;
				strcpy(v.fdv.fileName,readDirP->d_name);	//copy file name
				v.fdv.hLinks = statBuff.st_nlink;

				msgsnd(msgqid,&v,sizeof(struct fDetails),0);//send the file name at mtype=3, consecutively
			}
		}
	}


}
