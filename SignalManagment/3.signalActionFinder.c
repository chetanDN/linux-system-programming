/*
Create a function named “fìnd-isr”,which when calling by passing an interrupt number then it should inform the action of that signal in current program
Signal action————>defaulted 
o/p—>Ignore.
	userdefine.
Hint: use signal() function to return value.

Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com

*/

#include <stdio.h>
#include <signal.h>

void *find_isr(int n)	//function to find signal action from siganl table
{
	void (*p)(int);

	p=signal(n,SIG_IGN);	//get signal action
		signal(n,p);	//set back signal action in table

	return p;
}

void my_isr(int n)
{
	//dummy my_isr to write in isr table, this code never runs, but my_isr addr req to write in table
	//printf("in my_isr catching signal #%d doing nothing..\n",n);
}
	

main()
{
	void (*p)(int);
	int sig_num;

// set signal 2 and 3 diff action to cross check later
	signal(2,my_isr);
	signal(3,SIG_IGN);


	printf("enter the signal number(1 to 64)\n");
	scanf("%d",&sig_num);

	p=find_isr(sig_num);	//call function to know signal action
	
	if(p==SIG_DFL)
		printf("signal#%d is doing default action\n",sig_num);
	else if(p==SIG_IGN)
		printf("signal#%d is being ignored\n",sig_num);
	else
		printf("signal#%d is user action\n",sig_num);
}
		
