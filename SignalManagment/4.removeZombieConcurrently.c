/*
Write a program to remove the zombie. 
Hint: Use SIGCHLD & signal().

in short program to terminate child from zombie, concurrently executing parent process, 
ie not to block parent till child is completed

Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com
*/

#include <stdio.h>
#include <signal.h>
void my_isr(int n)
{
	printf("in isr pid=%d ppid=%d\n",getpid(),getppid());
	wait(0);	//doesnt wait for second exit call but return immadetly
		//~from $ man 2 wait
		//~If  a  child has already changed state, then these calls return immediately. Otherwise 
		//~they block until either a child changes  state  or  a signal  handler interrupts the call
}

main()
{	
	if(fork()==0)
	{
		printf("in child pid=%d ppid=%d\n",getpid(),getppid());
		sleep(10);
	}
	else
	{
		signal(SIGCHLD,my_isr);	//if wait() is used here itself, parent code blocked, concurrency not achieved
		while(1);
	}
}
