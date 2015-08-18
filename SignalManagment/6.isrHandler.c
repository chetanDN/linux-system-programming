/*
Write a program to Install ISR(handIer) for SIGINT and SIGQUIT. Restore the SIGINT to default after 3 times occurrence. SIGQUIT to default after 5 times occurrence.

in short prog - for 3 occurance of SIGINT ignore it then, set it back to default action
	for 5 occurances of SIGQUIT ignore it then, set it back to default action
	
Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com
*/
#include <stdio.h>
#include <signal.h>

void my_isr_handler(int n)
{
	static int c1,c2;	//default value 0;
	
	if(n==2)	//for SIGINT occurances
	{
		c1++;
		if(c1==3)
		{
			signal(n,SIG_DFL);	//here n is 2 only, so setting SIGINT to DEFAULT action
		}
	}
	else if(n==3)
	{	
		c2++;
		if(c2==5)
		{
			signal(n,SIG_DFL);	//here n is 3, so setting SIGQUIT to DEFAULT action
		}
	}
}

main()
{
	signal(SIGINT,my_isr_handler);	//whenever SIGINT(ctrl+c) signal comes handle it in my_isr_handler

	signal(SIGQUIT,my_isr_handler);
	
	while(1);
}
		

