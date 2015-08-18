/*
Write a program to compare the ages of two files given from command line?


./a.out	<file1> <file2>
compare ages of file from cmd line i/p
camparing the st_mtime ie modified time

Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com
*/
#include "header.h"
#include <time.h>	//ctime()
main(int argc,char *argv[])
{	
	struct stat f1,f2;
	
	if(argc!=3)
	{
		printf("usage: ./a.out <file1> <file2>\n");
		return;
	}
	
	if( stat(argv[1],&f1)<0 )	//success=0; error=-1
	{	
		printf("in %s opening : ",argv[1]);
		perror("stat");	//error by check first stat later 2nd stat
		return;
	}

	if(stat(argv[2],&f2) <0 )	//success=0; error=-1
	{	
		printf("in %s opening : ",argv[2]);
		perror("stat");	//error by check first stat later 2nd stat
		return;
	}



	if(f1.st_mtime > f2.st_mtime)
		printf("File: %s is newer\n",argv[1]);
	else if(f1.st_mtime < f2.st_mtime)
		printf("File: %s is newer\n",argv[2]);
	else
	{
		time_t t1 =f1.st_mtime; 
		printf("both File are of same time %lu %s\n",f1.st_mtime,ctime(&t1));	//f2.st_mtime
	}
}

