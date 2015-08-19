/*
WAP to delete all message queues?

you can delete message queue's using KEY number also(use system(), but message Queue with KEY=0, cannot be removed in that way ->" ipcrm -Q 0 " not possible, better is get mesQid for each key, then use msgctl(msgQid,IPC_RMID,0);
in this way you can remove with key=0 also;

need to get msgqid by avoiding msgget() -> overhead but, worth doing


read MSG_INFO and MSG_STAT from $man 2 msgctl

Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

main()
{

	int maxind, ind, msqid;
	struct msqid_ds ds;	//dataStructure holding complete info for indexed message que
	struct msginfo msginfo;	//general buff copying data from MSG_INFO, has info of how many message que present right now

//STEP1)	/* Obtain size of kernel 'entries' array */
	maxind = msgctl(0, MSG_INFO, (struct msqid_ds *) &msginfo);	//copy kernel MSGQ_INFO to local buff
									//returns count of active message Q
	if (maxind < 0)
	{
		perror("msgctl in MSG_INFO");
		return;
	}

	printf("no of message Q active right now(KEY) : %d\n\n", maxind+1);	//index+1

//STEP2)	/* Retrieve meaasge Queue id's */

	for (ind = 0; ind <= maxind; ind++) // loop over the kernel's index system for active message queues
	{
		msqid = msgctl(ind, MSG_STAT, &ds);	//from each index using MSG_STAT -> ds, return msgqid
		if (msqid <0 ) 
		{
			perror("msgctl in MSG_STAT");
			return;
		}

//STEP3)	/* using msgqid remove the message queue */	
		if ( msgctl(msqid,IPC_RMID,0) < 0 )
		{
			perror("msgctl in IPC_RMID");
			return;
		}
			

	}

	printf("all message queues removed\n");

}
		
