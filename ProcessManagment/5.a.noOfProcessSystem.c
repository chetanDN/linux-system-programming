/*
5. Write a program to execute the no of commands from command line
a) using system( )

Note: no of new process created must be equal to no of cmd given at command line)


   ./a.out ls,pwd,cal,date
   but each child process running each command, with all child sharing common parent
   
Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com

*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
main(int argc,char *argv[])
{
	int i,j;
	char temp[10]={};
	
	if(argc != 2)
	{
		printf("usage: ./a.out ls,pwd,cal (any combination with , seperating each command)\n");
		return;
	}
	
	i=0;j=0;
	while(argv[1][i])
	{
		temp[j++]=argv[1][i++];	// 1 step to copy char into temp array

		if( (argv[1][i]==',') || (argv[1][i+1]=='\0') )	//checking argv[1][i]='\0' will end while loop before executing last command
		{
			if( (argv[1][i+1]=='\0') && (argv[1][i] != ',' ) ) //spl case: last cmd not termtd by ','
				temp[j++]=argv[1][i];	//special code to copy last caommand completely

			temp[j]='\0';
			
			if(fork()==0)
			{
				system(temp);
				sleep(5);
				exit(0);// in child code avoiding below code to ewecute
			}

			j=0;	//j reset so  after if block, temp[j++] can store new command
			i=i+1;	//i has to index after ',' character
		}
		wait(0);
		
	}
sleep(20);
}







