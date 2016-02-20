#include <unistd.h>
#include <linux/sched.h>
#include <string.h>
#include <stdio.h>
#define __NR_my_ps 359
struct my_struct 
{
	int task_pid;
	char task_tty[64];
	unsigned long task_time;
	char task_comm[15];	
}my_struct;

int main()
{	
	int i=0;
	int num =0; 
	struct my_struct userbuff[1024];

//	num = sizeof(userbuff)/sizeof(my_struct);

/*
	printf("PID TTY\tTIME CMD\n");

	for(i =0;i<num;i++)
	{
        	printf("%d ",userbuff[i].task_pid);
		printf("%s",userbuff[i].task_tty);
		printf("%lu\t ",userbuff[i].task_time);
		printf("%s\n",userbuff[i].task_comm);
	}
*/

	syscall (__NR_my_ps,sizeof(userbuff),userbuff);
	
	printf("PID TTY\tTIME CMD\n");
	
	for(i =0;i<num;i++)
	{
        	printf("%d ",userbuff[i].task_pid);
		printf("%s",userbuff[i].task_tty);
		printf("%lu\t ",userbuff[i].task_time);
		printf("%s\n",userbuff[i].task_comm);
	}

	return 0;
}

