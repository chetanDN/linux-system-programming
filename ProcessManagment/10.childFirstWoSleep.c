/*
from the previous program do not use sleep but o/p sequence must be child first & then parent.
   ./a.out 
   but each hirarchy child process running each command
   x   -> running -> ls
   x+1 -> running -> pwd
   x+2 -> running -> cal
   x+3 -> running -> date

	without sleep()
	o/p the child first
	
Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com

*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
main()
{

	if(fork()==0)
	{
		if(fork()==0)
		{
			if(fork()==0)
			{
				printf("\nin child 3 running \"date\"\n");
				system("date");
				exit(0);
			}
			else	//part of second child
			{
				wait(0);
				printf("\nin child 2 running \"cal\"\n");
				system("cal");
				exit(0);
			}
		}
		else	//part of first child
		{
			wait(0);
			printf("\nin child 1 running \"pwd\"\n");
			system("pwd");
			exit(0);
		}
	}
	else	//part of main parent
	{
		wait(0);
		printf("\nin parent code running \"ls\"\n");
		system("ls");
	}
}

