/*
6. Write a program to create 3 new jobs, in such a manner that all the 3 new Jobs should have
Common parent.
x --->bash
x+1-->x
x+2-->x
x+3-->x

x -> x+1
x -> x+2
x -> x+3

Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com
*/
#include <stdio.h>
main()
{
	if(fork()==0)//exclusive child 1 code of common parent
	{
		printf("child 1 pid=%d ppid=%d\n",getpid(),getppid());
	}
	else
	{
		if(fork()==0)//exclusive child 2 code of common parent
		{
			printf("child 2 pid=%d ppid=%d\n",getpid(),getppid());
		}
		else
		{
			if(fork()==0) //exclusive child 3 code of common parent
			{
				printf("child 3 pid=%d ppid=%d\n",getpid(),getppid());
			}
			else	//exclusive parent code
			{
				printf("parent pid=%d ppid=%d\n",getpid(),getppid());
				while(1);
			}
			
			//common code to child3 and parent
		}

		//common code to child2, child3 and parent
			
	}

	//common code to all, ie child1, child2, child3 and Parent
}
