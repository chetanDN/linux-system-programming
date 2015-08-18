/*
from the previous given program execute Is, pwd ,cal ,date command by x,x+1,x+2,x+3 respectively.

   ./a.out ls,pwd,cal,date
   but each hirarchy child process running each command
   x   -> running -> ls
   x+1 -> running -> pwd
   x+2 -> running -> cal
   x+3 -> running -> date
   
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
				printf("in child 3 running \"date\"\n");
				system("date");
				while(1);
			}
			else	//part of second child
			{
				printf("in child 2 running \"cal\"\n");
				system("cal");
				while(1);
			}
		}
		else	//part of first child
		{
			printf("in child 1 running \"pwd\"\n");
			system("pwd");
			while(1);
		}
	}
	else	//part of main parent
	{
		printf("parent code running \"ls\"\n");
		system("ls");
		while(1);
	}
}

