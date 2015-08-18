/*
Write a program to ignore the 
termination of process when its terminal will close.
Hint: use SIGHUP signal & signal().

in short avoid child process getting terminated when parent(terminal) is closed ->
default function of SIGHUP received is to terminate the child process, so catch that signal in my_isr and do nothing

Author	-	Chetan Naik
mailId	-	chetandevanaik@gmail.com
*/

#include <stdio.h>
#include <signal.h>
void my_isr(int n)
{
	printf("in isr pid=%d ppid=%d signal#=%d\n",getpid(),getppid(),n);
}

main()
{	
	signal(SIGHUP,my_isr);
	while(1);
}
