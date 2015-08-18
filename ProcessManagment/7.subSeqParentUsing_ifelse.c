/*
Modify the above program .So that no two jobs have the common parent.
(each job have different parent).
x--->bash
x+1 -->x
x+2--->x+ 1
x+3--->x+2


hierarchy childs
(X) -> (X+1) -> (X+2) -> (X+3)

Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com
*/

#include <stdio.h>
main()
{
	if(fork()==0)
	{
		if(fork()==0)
		{
			if(fork()==0)
			{
				printf("in child 3 pid=%d,ppid=%d \n",getpid(),getppid());	//this is last child created, not 1st
				while(1);
			}
			else
			{
				printf("in child 2 pid=%d,ppid=%d \n",getpid(),getppid());	//this is isecond child created
				while(1);
			}
		}
		else
		{
			printf("in child 1 pid=%d,ppid=%d \n",getpid(),getppid());		//this is the first child created ,not last
			while(1);
		}
	}
	else
	{
		printf("in parent..pid=%d,ppid=%d \n",getpid(),getppid());
		while(1);
	}
}
