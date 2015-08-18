/*
a)Process 1 will one string to process 2?
b) process2 receive the string and store alphabets in one array and digits(Numeric characters) in another array?
Ex: i/p:  vision2020india
      o/p: visionindia ---->char array
              2020           ---->integer array

Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com
*/

#include "../header.h"
main()
{
	char a[50]={};
	int fd;

	mkfifo("fifoFile1",0644);

	fd=open("fifoFile1",O_WRONLY);

	if(fd<0)
	{
		perror("open");
		return;
	}

//	printf("fd=%d\n",fd);

	printf("enter the string : \n");
	gets(a);

	write(fd,a,strlen(a)+1);

}
