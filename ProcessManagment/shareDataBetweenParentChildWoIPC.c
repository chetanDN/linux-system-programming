/*
Write a program to i/p 2 small(1 to 50) integers from command line and add two integers in child process and print the sum in parent process

	./a.out 10 20
	o/p -> 30 printed from parent process
	
usually can be done using exit(#number < 255 ) and catching that exit status with wait, but for more generic
using vfork() to use common memory between parent and child.(here problem is to solve without IPC concept)

vfork() will execute parent first ,later parent process is executed

Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com
*/
#include <stdio.h>
main(int argc,char* argv[])
{
  int sum;
	if(argc != 3)
	{
	  printf("usage: %s <int1> <int2>\n",argv[0]);
	  return;
	}
	
	if(vfork()==0)  //vfork() to execute child first and memory are shared between parent-child
	{
		sum=atoi(argv[1])+atoi(argv[2]);
	}
	else
	{
		printf("in parent sum=%d\n",sum);
	}
}
