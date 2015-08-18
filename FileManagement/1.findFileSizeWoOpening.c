/*
Write a program to find the size of file without opening the file?

ask the file manager to know file size w/o opening itA
./a.out <fileNameToFindSize>

Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com
*/
#include "header.h" 
main(int argc,char **argv)
{
	struct stat v;

	if(argc != 2)
	{
		printf("usage: ./a.out fileName\n");
		return;
	}

	if(stat(argv[1],&v) < 0)	//On success, zero is returned, fill v;  On error, -1 is returned,
	{
		perror("stst");
		return;
	}

	printf("size = %lu\n",v.st_size);
}
