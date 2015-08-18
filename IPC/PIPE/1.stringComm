/*
a) Parent process will send one string to child process.
   b)child receive the string from parent and display received data on screen.


 program - parent preocess has to scan one string and send that string to child then,
		child process has to receive that string and display on screen
		
Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com
*/
#include "header.h"
main()
{
	int p[2];	//each pipe creation has 2 file discriptor -> one for read another for write
	
	pipe(p);	//create those two files discriptor, ie create pipe in kernel space
	perror("pipe");	//display error if not able to create

//	printf("read end has p[0] = %d int file discriptor value\n and write end has p[1] = %d int file discriptor value\n",p[0],p[1]);

	if(fork())	//parent code
	{
		char a[50]={};
		printf("enter a string :\n");
//		scanf("%s",a);
		gets(a);
		
		//now write the scanned string to pipe so that child could read from this pipe
		write(p[1],a,strlen(a)+1);

		wait(0);	//dont terminate till child displays string on screen
	}
	else	//child
	{
		char b[50]={};
//		printf("in child before reading from pipe..\n");
		
		read(p[0],b,sizeof(b));
		printf("in child string read is : %s\n", b);
	}
}










		
	

