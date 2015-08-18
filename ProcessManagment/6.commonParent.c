/*
Write a program to create 3 new jobs, in such a manner that all the 3 new Jobs should have
Common parent.
x --->bash
x+1-->x
x+2-->x
x+3-->x


in short - prog to create common parent to 3 child process with all process running infinitely
logic	- using for loop and break in eaach child process
pther logic	- use nested if else (used in random child termination prog 11) 

Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com
*/
#include <stdio.h>
main()
{
	int i;

	for(i=0;i<3;i++)
	{
		if(fork()==0)
		{
			printf("Created child with pid= %d and its parent is = %d\n",getpid(),getppid());
			break;
		}
		else
		{
			if(i==0)		//print the parent pid only once
				printf("In parent pid is = %d, its parent is = %d\n",getpid(),getppid());
				
		}
	}
while(1);	// while(1) required, if not, in ubuntu parent finishes first making child orphan with init 
		// as parent and while(1) is common code to child process also because if child finishes 
		// instruction it become zombie, so trying to keep all process alive with while(1)
}
