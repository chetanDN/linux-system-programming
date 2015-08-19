/*
Implement full duplex communication.
Hint: use two shared memories.

	Full-Duplex comunication using shared-memory and semaphore(much required here to synchronize)

	5 sub-semaphore declared, 4 are used
		two shared memory are got by shmp1 and shmp2

	parent1(sem1) >> shmp1 >> child2(sem2)
	child1(sem4)  >> shmp2 >> parent2(sem3)
	
Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com

*/

#include "header.h"
main()
{
	char *shmp1,*shmp2;
	int shmid,semid;
	struct sembuf v;

	shmid = shmget (4,50,IPC_CREAT|0644);
	if(shmid<0)
	{
		perror("shmget");
		return;
	}

	shmp1=shmat(shmid,NULL,0);		//get the allocated memory addr
	shmp2=shmat(shmid,NULL,0);		//get the allocated memory addr
	
	semid=semget(4,5,IPC_CREAT|0644);	//creating 3 sub semaphores( but using last 2 only)
	if(semid<0)
	{
		perror("semget");
		return;
	}

	/* clearing the value or else use program to clear these subsemaphore*/
	semctl(semid,3,SETVAL,0);
	semctl(semid,4,SETVAL,1);//lock so that child dont print junk initially
	/*----------------------------------------------------*/

	if(fork())
	{
		v.sem_num=3;
		v.sem_op=0;
		v.sem_flg=0;

		printf("enter the data\n");
		while(1)
		{
			semop(semid,&v,1);
		 	semctl(semid,4,SETVAL,1);	//set lock to process 1 child
			scanf("%s",shmp1);
			semctl(semid,3,SETVAL,1);	//lock self
			semctl(semid,4,SETVAL,0);	//open lock to process 1 child
		}
	}
	else
	{
		
		v.sem_num=2;
		v.sem_op=0;
		v.sem_flg=0;

		while(1)
		{
			semop(semid,&v,1);
			semctl(semid,1,SETVAL,1);	//set lock to process 1 parent
			printf("data p1 rx=%s\n",shmp2);
			semctl(semid,2,SETVAL,1);	//self lock
			semctl(semid,1,SETVAL,0);	//open lock for process 1 parent
		}
	}
}
