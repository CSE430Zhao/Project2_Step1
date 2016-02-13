/* 
 *  Christopher David Monken
 *  Project 1
 *  CSE430: Operating Systems
 */

#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux.sched.h>

struct task_struct{

	pid_t pid;

	cputime_t utime, stime;

	char comm[TASK_COMM_LEN];

	struct signal_struct *signal;

}

struct signal_struct{

	struct tty_struct *tty;

}

struct tty_struct{

	char name[64];

}

asmlinkage long sys_my_syscall(int a, int b, char *c)
{
	char kernel_buff[1024];
	int len = 0;

	// put information in kernel_buff


	for_each_process(my_task){
		cputime_t utime = 0;
		cputime_t stime = 0;

		thread_group_cputime_adjusted(tas, &utime, &stime);

		jiff = utime + stime;

	}

	}



	// put length of this information in variable len

	if(len > b)
		len = b;

	int n = copy_to_user(c, kernel_buff, len);
	return n;
}

