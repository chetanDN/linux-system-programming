/*
just creating few message queues, for the other program to delete these queues
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

main()
{
	int key;
	int msgQid;

	for(key=0;key<50;key++)
	{
		if(key%2 ==  0)	//just creating even key message queue
			msgQid=msgget(key,IPC_CREAT|0644);

		printf("msgQid=%d\n",msgQid);
	}
}
		
