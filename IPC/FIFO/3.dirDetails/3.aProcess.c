/*
process 1 will send directory name to process2.
Process2 after receiving directory name, open directory and count no. of files and that result send back to process1.


pass the directory name from cmd line
./a.out <dirName>

Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com
*/
#include "header.h"
main(int argc,char *argv[])
{
	int fd1,fd2;
	char fileCount[10]={};		//to count no of files

	if(argc!=2)
	{
		printf("usage: %s <dirName>\n",argv[0]);
		return;
	}


	mkfifo("fifoFile1",0644);
	mkfifo("fifoFile2",0644);

	fd1=open("fifoFile1",O_WRONLY);	//other will RDONLY fd1
	fd2=open("fifoFile2",O_RDONLY);	//other will WRONLY fd2

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

	write(fd1,argv[1],strlen(argv[1])+1);
	
	read(fd2,fileCount,sizeof(fileCount));	//reading to a char string
	
	printf("no of files :%s\n",fileCount);

}
