/*
Write a program to compare the links of two files ,input from command line?


./a.out file1 file2
prog - to check file linkages between file1 and file 2

1 step) - create a file and populate it
$ vi one
2 step) - create hard link
$ ln one two
3 step) - create  another file
$ vi abc
4 step) - create symbolic link for this file instead of hard link
$ ln -s abc def

then run this prog to check linkage
cross check using
$ls -li

Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com
*/

#include "header.h"

main(int argc,char **argv)
{
	struct stat f1,f2;
	if(argc != 3)
	{
		printf("usage: ./a.out <path/filename1> <path/filename2>\n");
		return;
	}

	if( (stat(argv[1],&f1) < 0) || (stat(argv[2],&f2) < 0) )	//error -1 and FileManager will fill 'f1' struct members
	{
		printf("in error\n");
		perror("stat");
		return;
	}

	if(f1.st_ino == f2.st_ino)	//to check link exist(hard link or soft link), stat to be used, which is filled in previou if( )
	{
		/*now to check files linked are hard linked or soft linked,lstat() i node value required*/
		lstat(argv[1],&f1);
		lstat(argv[2],&f2);

		if(f1.st_ino == f2.st_ino)
		{
			printf("files have Hard Link\n");
		}
		else
		{
			printf("files have Soft/Symbolic Link\n");		
		}
	}
	else
	{
		printf("files are not linked at all\n");
	}

}
