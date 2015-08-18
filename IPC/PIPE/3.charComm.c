/* 
a) Parent process will send one character to child process.
   b)child receiving the character from parent and  display received char on screen.


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
		char ch;	
		printf("enter a char :\n");
		scanf("%c",&ch);
		
		//now write the scanned string to pipe so that child could read from this pipe
		write(p[1],&ch,sizeof(char));

		wait(0);	//dont terminate till child displays string on screen
	}
	else	//child
	{
		char ch;
//		printf("in child before reading from pipe..\n");
		
		read(p[0],&ch,sizeof(char));
		printf("in child, char read is : %c\n", ch);
	}
}










		
	

