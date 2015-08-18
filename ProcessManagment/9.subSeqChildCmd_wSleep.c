/*
from the previous program the o/p sequence must be date>pwd>ca1>ls

   ./a.out 
   but each hirarchy child process running each command
   x   -> running -> ls
   x+1 -> running -> pwd
   x+2 -> running -> cal
   x+3 -> running -> date

	but child should run first

	o/p seq -> date->pwd then ->cal ->ls
	
Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com

*/

#include <stdio.h>
#include <unistd.h>
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

			}
			else	//part of second child
			{
				sleep(5);
				printf("\nin child 2 running \"cal\"\n");
				system("cal");
			}
		}
		else	//part of first child
		{
			sleep(3);
			printf("\nin child 1 running \"pwd\"\n");
			system("pwd");
		}
	}
	else	//part of main parent
	{
		sleep(9);
		printf("\nin parent code running \"ls\"\n");
		system("ls");
	}
}

