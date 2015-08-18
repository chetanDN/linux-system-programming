/*
Write a program to compare the size of two files ,input from command line
	Hint : ./a.out file1 file2


compare two filesizes entered from command line
./a.out <file1> <file2>

Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com
*/
#include "header.h"
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

	if(f1.st_size > f2.st_size)
		printf("File: %s is bigger\n",argv[1]);
	else if(f1.st_size < f2.st_size)
		printf("File: %s is bigger\n",argv[2]);
	else
		printf("both File are of equal size %lu\n",f1.st_size);	//f2.st_size
}
		
	
