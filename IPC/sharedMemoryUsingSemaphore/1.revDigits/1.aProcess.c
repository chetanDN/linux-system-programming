/*
process 1 will send one number to process2.
Process2 after receiving one number, then reverse the digits of the given number send back results to process1

Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com
*/

#include "header.h"
main()
{
	int *shmp;
	int shmid,semid;
	struct sembuf v;

	shmid = shmget (4,50,IPC_CREAT|0644);
	if(shmid<0)
	{
		perror("shmget");
		return;
	}

	shmp=(int*)shmat(shmid,NULL,0);		//get the allocated memory addr
	
	semid=semget(4,3,IPC_CREAT|0644);	//creating 3 sub semaphores( but using last 2 only)
	if(semid<0)
	{
		perror("semget");
		return;
	}

	/* clearing the value or else use program to clear these subsemaphore*/
	semctl(semid,1,SETVAL,0);
	semctl(semid,2,SETVAL,0);
	/*----------------------------------------------------*/

	v.sem_num=1;
	v.sem_op=0;
	v.sem_flg=0;

	//now entering critical section of code
	semctl(semid,2,SETVAL,1);	//lock for other process to not access resources
	printf("enter the number : ");
	scanf("%d",shmp);

	semctl(semid,1,SETVAL,1);	//lock self
	semctl(semid,2,SETVAL,0);	//open for other process

		semop(semid,&v,1);	//wait till other process complets its operation and open lock for this process
		printf("data in p1 later =%d\n",*shmp);
}
