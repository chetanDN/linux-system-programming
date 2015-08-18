/*
Write a program to execute a Command with its arguments given at command line.
i/p :   ./a.out ls -l
	./a.out cal 2011.


./a.out ls -l
./a.out cal 2011

Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com
*/

#include <stdio.h>
#include <unistd.h>
main(int argc,char *argv[])
{
	execvp(argv[1],argv+1);	// first argument single pointer, 2nd argment double pointer
}
