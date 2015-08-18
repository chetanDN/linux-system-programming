/*
Modify the above program so that parent will wait upto child #2 exit. So after child2 parent will also exit  making other Zombie or Orphan

i.e program to create 3 child process with common parent , use rand life upto 10 sec for each child, 
and from common parent know which child is exiting
	ie not to print from child after exiting child but,
	collect status from child, and from parent print which child is terminated

	wait till 2nd child completes, then terminate main parent, making others zombie or orphan
	
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
				wait(&s);	//wait till  all child process finishes
				
				s=s>>8;
				
				if(s==2)
					{
						printf("child 2 exited\n"); //child 2 exit status received
						exit(0);	//EXITING THE MAIN PARENT
					}
			}
			
			
		}
	}

}		
