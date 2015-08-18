/*
Modify the above program .So that no two jobs have the common parent.
(each job have different parent).
x--->bash
x+1 -->x
x+2--->x+ 1
x+3--->x+2

prog to create subsequently 3 child, with no child having common parent

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
			printf("process created with pid = %d and its parent is = %d\n",getpid(),getppid());
		}
		else
		{
			if(i==0)
			printf("Main parent with pid is = %d, and its parent is = %d\n",getpid(),getppid());
			
			break;
		}
	}
while(1);	// while(1) required, if not, in ubuntu parent finishes first making child orphan with init 
		// as parent and while(1) is common code to child process also because if child finishes 
		// instruction it become zombie, so trying to keep all process alive with while(1)
}
