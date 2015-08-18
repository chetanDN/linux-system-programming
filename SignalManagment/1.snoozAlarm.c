/*
1. Write a program to deliver the alarm signal periodically after (n-1)sec from the last interrupt.

Hint: Start first alarm at 10 sec then next alarm at 9sec so on up to n=0 terminate.

Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com
*/

#include <stdio.h>
#include <signal.h>
static int count;
void my_isr(int num)
{
	printf("in my_isr..\n",count);
	count=count-1;
	printf("in isr alarm subsequent waiting %d sec\n",count);
	alarm(count);

	if(count==0)		// kill self, when count==0 
		raise(9);

}
main()
{
	printf("enter the count for snooze alarm\n");
	scanf("%d",&count);
	signal(SIGALRM,my_isr);
	printf("in main alarm waiting %d sec\n",count);
	alarm(count);
	while(1);
}
