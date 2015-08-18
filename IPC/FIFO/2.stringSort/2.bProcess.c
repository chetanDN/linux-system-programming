/*
/*
modify above program in such a way that sort the data according  to descending order, then send back o/p to process1.
	o/p: vsonniiiida
		2200

Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com

*/


/*
sleep(2) is very much required because for input string "hello123", "olleh" and "321" needed to write back
when timeslice allocated to this process, both write() are executed before read() in other proceess executes,
thus instead of writing just "olleh"-> 6bytes to fifoFile2, 10 bytes are witten i.e "olleh" and "321",
thus while first read() in other process will read 10 bytes, but prints till first '\0'-> so printing "olleh";
and the second read() in other program will read 0 bytes, printing nothing.

thus sleep(2), will avoid this by putting this process to wait, and other process get time slice,
and read() only 6 bytes("olleh") and and sleep() this process again write() reamaing 4 byte("321"),
and consequently will read() 4 bytes only.

"so SLEEPING is good for processes also" (overcome sync problem)

*/

#include "header.h"
main()
{
	char a[100]={};		//to store  user entered string
	char cArr[50]={};	//to stored sorted char string
	char iArr[50]={};	//to store sorted numstring
	int fd1,fd2,i,j,k,i1,i2;
	char chTemp;

	mkfifo("fifoFile1",0644);
	mkfifo("fifoFile2",0644);

	fd1=open("fifoFile1",O_RDONLY);	
	fd2=open("fifoFile2",O_WRONLY);	

	if(fd1<0)
	{
		perror("open");
		return;
	}
	if(fd2<0)
	{
		perror("open");
		return;
	}


	read(fd1,a,sizeof(a));
	printf("received String : %s\n",a);

	j=0;k=0;
	for(i=0;a[i];i++)
	{
		if( (a[i] >= 'a' && a[i] <= 'z') || (a[i]>='A' && a[i] <='Z' ) )
		{
			cArr[j++]=a[i];
		}
		else if(a[i] >= '0' && a[i] <= '9' )
		{
			iArr[k++]=a[i];
		}
	}

	for(i1=0;i1<j-1;i1++)
	{
		for(i2=0;i2<j-1-i1;i2++)
		{
			if(cArr[i2]<cArr[i2+1])
			{
				chTemp=cArr[i2];
				cArr[i2]=cArr[i2+1];
				cArr[i2+1]=chTemp;
			}
		}
	}

	printf("modified cArr=%s\n",cArr);
	write(fd2,cArr,strlen(cArr)+1);

	for(i1=0;i1<k-1;i1++)
	{
		for(i2=0;i2<k-1-i1;i2++)
		{
			if(iArr[i2]<iArr[i2+1])
			{
				chTemp=iArr[i2];
				iArr[i2]=iArr[i2+1];
				iArr[i2+1]=chTemp;
			}
		}
	}

	printf("modified iArr=%s\n",iArr);
	
sleep(2);	//very much needed, or else cpu will execute this line also to FIFO as explained above

	write(fd2,iArr,strlen(iArr)+1);
}
