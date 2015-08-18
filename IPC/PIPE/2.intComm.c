/*
a) Parent process will send one integer value to child process.
b)child after receiving integer value from parent ,display result on screen.


 program - parent process has to scan one int and send that int to child then,
		child process has to receive that int and display on screen
		
Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com
*/
#include "header.h"
main()
{
	int p[2];	//each pipe creation has 2 file discriptor -> one for read another for write
	
	pipe(p);	//create those two files discriptor, ie create pipe in kernel space
	perror("pipe");	//display error if not able to create


	if(fork())	//parent code
	{
		int i;
		printf("enter an integer :\n");
		scanf("%d",&i);
		
		//now write the scanned string to pipe so that child could read from this pipe
		write(p[1],&i,sizeof(int));

		wait(0);	//dont terminate till child displays string on screen
	}
	else	//child
	{
		int j;
//		printf("in child before reading from pipe..\n");
		
		read(p[0],&j,sizeof(int));
		printf("in child integer read is : %d\n", j);
	}
}










		
	

