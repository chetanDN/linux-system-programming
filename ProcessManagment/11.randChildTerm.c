/*
Write a program to create a three child process ‘from the common parent use random delay between 1 to 10 sec in each child. Use the exit value in such a manner so that parent should know the sequence of the child exits.
Hint : while(wait(&status) != -1)
	{
	;
	}


in short - program to create 3 child process with common parent , use rand life upto 10 sec for each child, 
and from common parent know which child is exiting
	ie not to print from child after exiting child but,
	collect status from child, and from parent print which child is terminated
	
Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com
*/
#include <stdio.h>
#include <stdlib.h>
main()
{
	if(fork()==0)		//exclusive child code
	{			//child 1 created
		int r;
		srand(getpid());	//seed
		r=rand()%10+1;		// will generate [(0 to 9) +1] = [1 to 10]
		printf("In Child 1 pid=%d before waiting %d sec\n",getpid(),r);
		sleep(r);
		exit(1);
	}
	else		//exclusive parent code
	{
		if(fork()==0)	//in parent code part, create second child, so we have common parent
		{		//child 2 created
			int r;
			srand(getpid());	//seed
			r=rand()%10+1;		// will generate [(0 to 9) +1] = [1 to 10]
			printf("In Child 2 pid=%d before waiting %d sec\n",getpid(),r);
			sleep(r);
			exit(2);
		}
		else		//exclusive parent code
		{
			if(fork()==0)	//in parent code part, create third child, so we have common parent
			{		//child 2 created
				int r;
				srand(getpid());	//seed
				r=rand()%10+1;		// will generate [(0 to 9) +1] = [1 to 10]
				printf("In Child 3 pid=%d before waiting %d sec\n",getpid(),r);
				sleep(r);
				exit(3);
			}
			else	//THE MAIN EXCLUSIVE CODE OF PARENT
			{
				int s;	//status variable after collecting exit() from child
				printf("In Parent ....\n");
				while(wait(&s)!=-1)	//generic code to wait till all child process finishes
				{
					s=s>>8;
					if(s==1)
						printf("child 1 exited\n"); //child 1 exit status received
					else if(s==2)
						printf("child 2 exited\n"); //child 2 exit status received
					else if(s==3)
						printf("child 3 exited\n"); //child 3 exit status received
				}



			
				printf("In Parent finished waiting for all child to exit..\n");
				while(1);
			}
		}
	}

}		
