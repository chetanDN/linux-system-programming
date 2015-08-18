/*
Write a program to print the type of given file, input from command line?


./a.out <fileName>
find the given file is
1)regular file
2)directory file
3)char device file
4)block device file
5)fifo(pipe) file	//$mkfifo p1 to creat pipe file
6)symbolic link file
7)socket file

Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com
*/

#include "header.h"

main(int argc,char **argv)
{
	struct stat f1;
	if(argc != 2)
	{
		printf("usage: ./a.out <path/filename>\n");
		return;
	}
/*dont use stat, it will fail checking for symbolic link file */
	if( lstat(argv[1],&f1) < 0)	//error -1 and FileManager will fill 'f1' struct members
	{
		perror("stat");
		return;
	}
	
	printf("%o\n",f1.st_mode);

	if( ( f1.st_mode >> 15 & 1) && ( f1.st_mode >> 14 & 1) )	//order to be highest bit set first
		printf("Socket File\n");			//otherwise will print regular file for this
	else if( ( f1.st_mode >> 15 & 1) && ( f1.st_mode >> 13 & 1) )		
		printf("Symbolic Link File\n");
	else if( f1.st_mode >> 15 & 1)		//check the flag value of st_mode in $man 2 stat
		printf("Regular File\n");
	else if((f1.st_mode >> 14 & 1) && (f1.st_mode >> 13 & 1) )	
		printf("Block Dev File\n");
	else if(f1.st_mode >> 14 & 1)		//or use direct flag MACRO names in man page
		printf("Directory File\n");
	else if(f1.st_mode >> 13 & 1)		
		printf("Char Dev File\n");
	else if(f1.st_mode >> 12 & 1)		
		printf("FIFO/PIPE File\n");
	else
		printf("misc file\n");

}
