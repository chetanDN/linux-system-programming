/*

Create a watch dog timer in parent which should watch T.A.T of its child and terminate the child.
Condition: The child have random delay(1-10 sec)
If the child take more than 5 sec then parent terminate it
Hint: fork(),sleep(),kill(),alarm()

in short prog - to create 3 child process to common parent
	after interval of 5 sec kill remove all child
	
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

	while(i<3)	//loop to kill all child
	{
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
	}
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
				printf("in parent setting alarm of 5 sec to kill all child \n");
				signal(SIGALRM,my_isr);
				alarm(5);
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
