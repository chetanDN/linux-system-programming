/*
	Implement copy command?


./a.out <oldFile> <newFile>

Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com
*/
#include "header.h"
main(int argc,char *argv[])
{
	char ch;
	int fd_r,fd_w;

	if(argc!=3)
	{
		printf("usage: ./a.out <oldFile> <newFile>\n");
		return;
	}

	fd_r=open(argv[1],O_RDONLY);

	if(fd_r <0)
	{
		perror("open");
		printf("file read opening\n");
		return;
	}

	fd_w=open(argv[2],O_WRONLY|O_TRUNC|O_CREAT,0644);

	if(fd_r <0)
	{
		perror("open");
		printf("file write opening\n");
		return;
	}

	while(read(fd_r,&ch,1) != 0)
	{
		write(fd_w,&ch,1);
	}
}
	
