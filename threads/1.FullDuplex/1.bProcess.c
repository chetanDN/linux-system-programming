/*
1.implement full duplex communication.

Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com
*/

#include "header.h"

void* threadFn1(void* p)
{
	char a[20];
	int fileD;

	fileD=open("f2",O_WRONLY);
	printf("enter data\n");
	while(1)
	{
		scanf("%s",a);
		write(fileD,a,strlen(a)+1);
	}
		
}

void* threadFn2(void* p)
{

	char a[20];
	int fileD;

	fileD=open("f1",O_RDONLY);
	while(1)
	{
		if( read(fileD,a,sizeof(a)) < 0 )	//takin if() to avoid inf. loop when other thread close
		{					//bug, still not solved
			return;
		}
		printf("%s\n",a);
	}
}

main()
{
	pthread_t threadId1,threadId2;

	mkfifo("f1",0644);
	mkfifo("f2",0644);

	pthread_create(&threadId1,NULL,threadFn1,NULL);
	pthread_create(&threadId2,NULL,threadFn2,NULL);

	while(1);
}

