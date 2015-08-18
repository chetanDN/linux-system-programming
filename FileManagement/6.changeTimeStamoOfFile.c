/*
	Write a program to modify the older file timestamp to that of new file, input given from command line?
	Hint: compare times of 2 files. Use stat() and utime()


change the time of older file to newer file time stamp
./a.out <fileOld> <fileNewTimeStamp>

Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com
*/
#include "header.h"
#include <utime.h>	//utime struct def
/*
struct utimbuf {
	time_t actime;       
	time_t modtime;      
};
*/

main(int argc,char *argv[])
{	
	struct stat f1,f2;
	struct utimbuf v;
	
	if(argc!=3)
	{
		printf("usage: ./a.out <fileOld> <fileNewTimeStamp>\n");
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

	printf("file 1 times before\n");
	printf("access_time =%lu \n",f1.st_atime );
	printf("modifc_time =%lu \n",f1.st_mtime );
	printf("staChg_time =%lu \n",f1.st_ctime );

	printf("file 2 times before\n");
	printf("access_time =%lu \n",f2.st_atime );
	printf("modifc_time =%lu \n",f2.st_mtime );
	printf("staChg_time =%lu \n",f2.st_ctime );

	v.actime=f2.st_atime;	//get new file access time
	v.modtime=f2.st_mtime;	//get new file modified time

	/*overwrite old file accesstime and modification time with new accesstime and modification time*/
	utime(argv[1],&v);
/*this will not print updated values as struct var f1 and f2 are not updated
	printf("file 1 times after\n");
	printf("access_time =%lu \n",f1.st_atime );
	printf("modifc_time =%lu \n",f1.st_mtime );
	printf("staChg_time =%lu \n",f1.st_ctime );

	printf("file 2 times after\n");
	printf("access_time =%lu \n",f2.st_atime );
	printf("modifc_time =%lu \n",f2.st_mtime ); 
	printf("staChg_time =%lu \n",f2.st_ctime );
*/
}
		
	
