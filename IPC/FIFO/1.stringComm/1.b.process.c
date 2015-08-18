/*
a)Process 1 will one string to process 2?
b) process2 receive the string and store alphabets in one array and digits(Numeric characters) in another array?
Ex: i/p:  vision2020india
      o/p: visionindia ---->char array
              2020           ---->integer array

Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com

*/

#include "header.h"
main()
{
	char a[100]={};
	char cArr[50]={};
	char iArr[50]={};
	int fd,i,j,k;

	mkfifo("fifoFile1",0644);

	fd=open("fifoFile1",O_RDONLY);

	if(fd<0)
	{
		perror("open");
		return;
	}

	read(fd,a,sizeof(a));
	printf("data received=%s\n",a);

	j=0;k=0;
	for(i=0;a[i];i++)
	{
		if( (a[i] >= 'a' && a[i] <= 'z') || (a[i]>='A' && a[i] <='Z' ) )
		{
			cArr[j++]=a[i];
		}
		else if(a[i] >= '0' && a[i] <= '9' )
		{
			iArr[k++]=a[i];
		}
	}

	printf("character array elements are : ");
	for(i=0;i<j;i++)
	{
		printf("%c ",cArr[i]);
	}
	printf("\n");

	printf("integer array elements are : ");
	for(i=0;i<k;i++)
	{
		printf("%c ",iArr[i]);
	}
	printf("\n");
	
}
