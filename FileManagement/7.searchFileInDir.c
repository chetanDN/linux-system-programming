/* 
	WAP to search a given file in a given directory?
	Hint: ./a.out test.c  /home/userName


./a.out <pathToSearch> <fileName>

Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com
*/
#include "header.h"
#include <dirent.h>
main(int argc,char *argv[])
{
	DIR *dp;		//dp pointing to directory file streeam
	struct dirent *rDir;	//rDir pointer to structure(having details of next filename entry in dir file)

	if(argc!=3)
	{
		printf("usage: ./a.out <pathToSearch> <fileName>\n");
		return;
	}

	dp=opendir(argv[1]);
	if(dp==0)
	{
		perror("opendir");
		return;
	}

	
	while( (rDir=readdir(dp)) != NULL )// readdir() returns NULL on reaching last entry filename of DIR file
	{
		if(rDir->d_name[0] != '.')
		{
			if(strcmp(rDir->d_name,argv[2]) == 0)
			{
				printf("\"%s\" file is present in \"%s\" path\n",argv[2],argv[1]);
				closedir(dp);
				return;
			}
		}
	}
	printf("\"%s\" file is not present in \"%s\" path\n",argv[2],argv[1]);
	closedir(dp);
}



