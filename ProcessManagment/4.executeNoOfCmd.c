/*
Write a program to pass num of commands each seperated by delimiter(,) through command
line.
i/p : ./a.out Is,pwd,cal,date

   ./a.out ls,pwd,cal,date	<- 4 th program assignment requirement
   
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
			system(temp);
			j=0;	//j reset so  after if block, temp[j++] can store new command
			i=i+1;	//i has to index after ',' character
		}
		
	}
}







