/*
 WAP to see the difference between atime,mtime,utime?


program to know different times linked with file

Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com
*/
#include "header.h"
#include <time.h>
main(int argc,char *argv[])
{
	struct stat f1;

	if(argc != 2)
	{
		printf("usage: ./a.out <fileName>\n");
		return;
	}

	if( stat(argv[1],&f1) < 0)
	{	
		perror("stat");
		return;
	}
	
	time_t t1=f1.st_atime;
	time_t t2=f1.st_mtime;
	time_t t3=f1.st_ctime;

	printf("access_time =%lu %s\n",f1.st_atime,ctime(&t1) );
	printf("modifc_time =%lu %s\n",f1.st_mtime,ctime(&t2) );
	printf("staChg_time =%lu %s\n",f1.st_ctime,ctime(&t3) );
}

