/*
CAUTION - this program is incomplete, there's always room for improvement.

The tee command reads its standard input until end-of-file, writing a copy of the input
to standard output and to the file named in its command-line argument.
Implement tee using I/O system calls. By default, tee overwrites any existing file with
the given name. Implement the —a command-line option (tee —a file), which causes tee
to append text end of a file if it  already exists.
implement the -i command-line option which causes tee to ignore interrupt signals.


   ./a.out <newFile>
   
Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com
 */
#include "header.h"
void my_isr(int n)
{
	;	//ignoring SIGINT signal
}

main(int argc,char *argv[])
{
	char ch;
	int fd_w,i;


	i=1;
	while(argv[i] != NULL )
	{
		printf("in while\n");
		if(strcmp(argv[i],"-i")==0) 
		{
			signal(SIGINT,my_isr);
		}
		i++;
	}


	if(argv[1]==NULL || (strcmp(argv[1],"-i")==0) )			//case 1) if no argument is passed
	{
		while(read(0,&ch,1) != 0)	//'0'->represents file discriptor for "stdin"
		{
			write(1,&ch,1);		//(write(stdout_fd,&ch,1));
		}
	}
	else
	{
		//case 4) ignoring the interrupt

		if(argv[1][0] == '-')
		{
			printf("in 1\n");
		}
		//case 2) argument passed is not an option ,then its fileName
		if( (argv[1][0] != '-') && ( (argv[2]==NULL ) || (strcmp(argv[2],"-i")==0) ) )		
		{
			printf("in 2\n");
			fd_w=open(argv[1],O_WRONLY|O_TRUNC|O_CREAT,0644);

			if(fd_w <0)
			{
				perror("open");
				printf("file write opening\n");
				return;
			}

			while(read(0,&ch,1) != 0)	//'0'->represents file discriptor for "stdin"
			{
				write(fd_w,&ch,1);	//write to file(argv[1])
				write(1,&ch,1);		//(write(stdout_fd,&ch,1);
			}
		}

		//case 3) append mode
		if( (argv[1][0] != '-') && (strcmp(argv[2],"-a")==0) ) 		
		{
			printf("in 3\n");
			fd_w=open(argv[1],O_WRONLY|O_APPEND,0644);

			if(fd_w <0)
			{
				perror("open");
				printf("file write opening\n");
				return;
			}

			while(read(0,&ch,1) != 0)	//'0'->represents file discriptor for "stdin"
			{
				write(fd_w,&ch,1);	//write to file(argv[1])
				write(1,&ch,1);		//(write(stdout_fd,&ch,1);
			}
		}


	}
}

