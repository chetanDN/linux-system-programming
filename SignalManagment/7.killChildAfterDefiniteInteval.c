/*
Write a program to create 3 child process from common parent use random delay between 1 to 10 
sec in each child. Use alarm in parent in such a manner that
Child1 should not exceeds more than 4 sec
Child2 should not exceeds more than 6
Chiid3 should not exceeds more than 8 sec.



ie prog - to create 3 child process to common parent
	after interval of 4 sec kill child 1
	after interval of 6 sec kill child 2
	after interval of 8 sec kill child 3
but  - if child finished work before this interval, its in zombie, 
	its status is collected, flag is set and removed before entering isr
	- in isr using flag, if child is not zombie, then only killed(otherwise meaningless)
	
Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com
*/

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>	//_exit()
#include <stdlib.h>	//exit(3)

int a[3];	//to store pid's of children
int cFlag[3];	//to set flag=1 , when child completes instruction and become zombie
				//collect status in wait() in parent, so no need to further process in my_isr

void my_isr(int n)		//if child has not completed instruction, i.e not removed by wait() in parent
{				//then remove it using my_isr
	printf("in isr..\n");
	static int i;

		if((cFlag[i]!=1) )//if first child "not turned into zombie and removed by parent" then kill it
		{
			printf("killing child#%d\n",i+1);
			kill(a[i],9);
		}
		else
		{	
			printf("zombie child#%d has been removed previously\n",i+1);
		}
	
		i++;
		
		if(i!=3)			//set alarm when i increments to 1 and 2 only, dont set when 3
			alarm(2);
}

int main()
{	

	if( (a[0]=fork()) == 0)
	{
		int randNo;
		srand(getpid());
		randNo=rand()%10+1;
		printf("in c1 child sleep for %d sec\n",randNo);
		sleep(randNo);
//		printf("in c1 after sleep\n");
		exit(1);
	}
	else
	{
		if( (a[1]=fork()) == 0)
		{
			int randNo;
			srand(getpid());
			randNo=rand()%10+1;
			printf("in c2 child sleep for %d sec\n",randNo);
			sleep(randNo);
//			printf("in c2 after sleep\n");
			exit(2);
		}
		else
		{
			if( (a[3]=fork()) == 0)
			{
				int randNo;
				srand(getpid());
				randNo=rand()%10+1;
				printf("in c3 child sleep for %d sec\n",randNo);
				sleep(randNo);
//				printf("in c3 after sleep\n");
				exit(3);
			}
			else
			{
				int s;	//exit status of child
				printf("in parent setting 1st alarm of 4 sec to kill child 1\n");
				signal(SIGALRM,my_isr);
				alarm(4);
				while(wait(&s) != -1)
				{
					if( s>>8 == 1 )
						cFlag[0]=1;	//set the flag when exit status is received
					else if( s>>8 == 2)
						cFlag[1]=1;	//set the flag when child completed work before
								//alarm signal time alloted
					else if( s>>8 ==3)
						cFlag[2]=1;	//set the flags when zombies are removed
								
				}
			while(1);	//just to extend parent process time
						
			}
		}
	}
	return 0;
}
