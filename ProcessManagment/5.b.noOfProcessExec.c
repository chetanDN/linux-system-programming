/*
5. Write a program to execute the no of commands from command line

b) using exec()
Note: no of new process created must be equal to no of cmd given at command line)


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
				execlp(temp,temp,NULL);//cannot take execvp(single pointer , double pointer)
				sleep(5);
			}
		/*this below code never runs in child process due to exec() */
			j=0;	//j reset so  after if block, temp[j++] can store new command
			i=i+1;	//i has to index after ',' character
		}
		
	}
sleep(20);
}







