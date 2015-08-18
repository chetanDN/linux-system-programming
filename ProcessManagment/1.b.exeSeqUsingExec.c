/*
Write a program to execute Is, pwd & cal sequentially
b) Using exec()
Hint : use fork().


step 1) cannot run execl() sequencially, as code memory overwites, so use fork() then in each child run "cmd"
step 2) code runs depends on time slice allocated, so "cmd" may not run sequencially , so use wait() till each 
	child process completes each "cmd"
step 3) use wait() in final exclusive parent code(or while(1) ), so no child is made orphan

Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
main()
{
	printf("in parent pid=%d  ppid=%d\n",getpid(),getppid());

	if(fork()==0)
	{
		printf("in child %d ppid=%d\n",getpid(),getppid());
		execl("/bin/ls","ls",NULL);
		exit(1);
	}
	else
	{
		wait(0);
		if(fork()==0)
		{
			printf("in child %d ppid=%d\n",getpid(),getppid());
			execl("/bin/pwd","pwd",NULL);
			exit(2);
		}
		else
		{
			wait(0);
			if(fork()==0)
			{
				printf("in child %d ppid=%d\n",getpid(),getppid());
				execl("/usr/bin/cal","cal",NULL);
				exit(3);
			}
			else	//parent in while loop
			{
				wait(0);
			}
		}
	}

}

