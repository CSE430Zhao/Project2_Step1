//#include <stdio.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/sched.h>
#include <linux/jiffies.h>
#include <linux/syscalls.h>
#include <linux/tty.h>
#include <linux/kernel.h>
#include <linux/uaccess.h>
//#include <string.h>
struct my_taskList
{
	int task_pid;
	char task_tty[64];
	unsigned long task_time;
	char task_comm[15];

}my_taskList;

asmlinkage long sys_my_ps(int b, char *c)
{
	
	struct my_taskList kernel_buff[1024];
	int len = 0;
	int num = 0;
	unsigned long jiff,time;
	int i = 0, n = 0;
			
	struct task_struct *task;
	//getting the size of the kernel_buffer
	num = sizeof(kernel_buff)/sizeof(my_taskList);

	//kernel_buff = kmalloc(1024 * sizeof(my_taskList),GFP_KERNEL);

	for_each_process(task)
	{
		cputime_t utime = 0;
		cputime_t stime = 0;
		//getting the time interval of the tasks
		thread_group_cputime_adjusted(task,&utime,&stime);
		jiff = utime+stime;		
		time  = jiff / HZ;
		printk("%d\n",task->pid);
		//pr_info("%s [%d]\n",task->comm,task->pid,task->signl->tty
			kernel_buff[i].task_time = time;
		//kernel_buff[i].task_tty = task->signal->tty->name;
			strcpy(kernel_buff[i].task_tty,task->signal->tty->name);
			kernel_buff[i].task_pid = task->pid;
			//kernel_buff[i].task_comm = task->comm;
			strcpy(kernel_buff[i].task_comm, task->comm);
	
		//memcpy(kernel_buffer,task,sizeof(task));

		len =  len + sizeof(my_taskList);
		i++;
	}
	 
	if(len>b)
	  len = b;

	n = copy_to_user(c,kernel_buff,len);

	//free(kernel_buff);

	return i;
}
