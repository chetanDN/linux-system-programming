/*
process 1 will send directory name to process2.
Process2 after receiving directory name, open directory and count no. of files and that result send back to process1.

Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com
*/
#include "header.h"
main()
{
	char dirName[100]={};		//to store  user entered string
	int fd1,fd2;
	char fileCount[10]={};
	int c;
	
	DIR *dp;
	struct dirent *rDir;

	mkfifo("fifoFile1",0644);
	mkfifo("fifoFile2",0644);

	fd1=open("fifoFile1",O_RDONLY);	
	fd2=open("fifoFile2",O_WRONLY);	

	if(fd1<0)
	{
		perror("open");
		return;
	}
	if(fd2<0)
	{
		perror("open");
		return;
	}


	read(fd1,dirName,sizeof(dirName));

	printf("received String in process2: %s\n",dirName);

	c=0;
	dp=opendir(dirName);
	perror("opendir");

	while(rDir=readdir(dp))
	{
		if(rDir->d_name[0] != '.')
		{
			c++;
		}
	}

	sprintf(fileCount,"%d",c);	//making int to string
	
	write(fd2,fileCount,strlen(fileCount)+1);

}
