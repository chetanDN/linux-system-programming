/*
modify above program in such a way that sort the data according  to descending order, then send back o/p to process1.
	o/p: vsonniiiida
		2200

Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com

*/
#include "header.h"
main()
{
	char a[100]={};		//to store  user entered string
	char cArr[50]={};	//to stored sorted char string
	char iArr[50]={};	//to store sorted numstring
	int fd1,fd2;

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


	printf("enter the string : \n");
	scanf("%s",a);
	write(fd1,a,strlen(a)+1);
	
	read(fd2,cArr,sizeof(cArr));
	
//self blocking	
	read(fd2,iArr,sizeof(iArr));

	printf("decending char string :%s\n",cArr);
	printf("decending num string :%s\n",iArr);



}
