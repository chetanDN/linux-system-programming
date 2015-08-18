/*
Write a Program - parent has to get the data from user and store the data in file. After that parent process will send one signal to child process. child process after receiving the
Signal ,open the file and convert data to opposite case and store again in same file.

Hint : Use pause() ¡n child process.
Use signal num 10(userSignal) in parent.


NOTE-
1) open file locally(inside each process) and use system calls to do file operation
2) globally opening file will be sharing file discriptor betwenn process(unlike varibales, where duplicate copies were ensured by copy-on-write mechanism), and use lseek() to reset file discriptor whenever needed
3) file operation using library functions is complicated, while dealing with parent-child, as every time, buffer need to be flushed- fflush(), 

Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com
*/

#include <stdio.h>
#include <unistd.h>	//read(),write()
#include <sys/types.h>	//next 3 for open()
#include <sys/stat.h>	
#include <fcntl.h>	//IMP FOR FILE OPENING
#include <string.h>	//strlen()
#include <signal.h>	//kill()
#include <wait.h>

void my_isr(int n)
{
	printf("in my isr signal caught is =%d\n",n);
}

int main()
{
	int cpid;

	cpid=fork();	//create child process

	if(cpid==0)
	{
		int fd;
		signal(10,my_isr);//much need to change default action(ie terminate process) of signal#10
		pause();	//if you just use pause(), default nature of sig#10(or any other signal) is to terminate process(here child will terminate not executing any of code below pause() ), so now using my_isr, we chnging the DEFAULT action of terminating to catch and procees process code below pause()
/*
 The  following system calls suspend execution of the calling process or
 thread until a signal is caught (or an unhandled signal terminates  the
 process):
 pause(2)        Suspends execution until any signal is caught.
*/
		
		fd=open("data",O_RDONLY);

		if(fd<0)
		{
			perror("open");
			printf("file read opening error in child\n");
			return;
		}
		
		char b[200];
		int i;

		printf("in child about to read\n");
		bzero(b,sizeof(b));			//clear junk in b[]
		read(fd,b,sizeof(b));
		printf("in child data=%s\n",b);
		close(fd);

		for(i=0;b[i];i++)
		{
			if(b[i]>='a' && b[i]<='z')
				b[i]=b[i]-32;
			else if(b[i]>='A' && b[i]<='Z')
				b[i]=b[i]+32;
		}

		printf("formatted data in child, before writing back to file=%s\n",b);

		//fd=open("data",O_WRONLY|O_TRUNC|O_TRUNC,0644);
		fd=open("data",O_WRONLY|O_TRUNC|O_CREAT,0644);
		if(fd<0)
		{
			perror("open");
			printf("file write opening error in child\n");
			return;
		}

		write(fd,b,strlen(b));	//write(fd,a,strlen(b)+1); -> +1 in case of writing to pipe file 
					//not for regular file	

		printf("child exiting\n");
		close(fd);
	}
	else
	{	//parent code
		int fd;
		fd=open("data",O_WRONLY|O_TRUNC|O_CREAT,0644);
		if(fd<0)
		{
			perror("open");
			printf("file write opening error in parent\n");
			return;
		}

		char a[200];
		printf("enter the data (in parent)\n");
//		scanf("%s",a);
		gets(a);

		printf("entered string is %s\n", a);
		write(fd,a,strlen(a));	//write(fd,a,strlen(a)+1); -> +1 in case of writing to pipe file 
		close(fd);		//not for regular file	

		printf("parent about to send signal#18 to child\n");
		kill(cpid,10);	//send signal#10 to child to further process on file

		wait(0); //wait till child completes file operation;
	}
}


				



		


