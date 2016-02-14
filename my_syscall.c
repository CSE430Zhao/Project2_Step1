/*
 *  Christopher David Monken, Adam Mastov, Fan, Martin Kuna
 *  Project 2
 *  CSE430: Operating Systems
 */

#include <linux/syscalls.h>
//#include <linux/fs.h>
#include <linux/jiffies.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/tty.h>
#include <linux/uaccess.h>
#include <string.h>

struct my_task{
    int  task_pid;
    char task_tty[64];
    unsigned long task_time;
    char task_comm[15];
}

asmlinkage long sys_my_syscall(void)
{
	int task_list_len = 0;
    int i = 0;                                                          // for traversing my_task_array
    unsigned long jiff, time;
    struct task_struct *p;                                              // pointer for iterating across task list

    for_each_process(p){
        task_list_len++;                                                // get the task list length
    }

    struct my_task task_array[task_list_len];                           // array to pass data to user-space

    for_each_process(p){
		cputime_t utime = 0;
		cputime_t stime = 0;

        task_array[i].task_pid = (int) p->pid;

        if(p->signal->tty->name == NULL)                                // change NULL to '?' -> tty format in 'ps -e'
            strcat(task_array[i].task_tty, "?");
        else
            strcpy(task_array[i].task_tty, p->signal->tty->name);

        strcpy(task_array[i].task_comm, p->comm);

		thread_group_cputime_adjusted(p, &utime, &stime);
		jiff = utime + stime;
        time = jiff / HZ;                                               // convert jiffies to seconds
        task_array[i].task_time = time;

        i++;
    }

    // copy array to user space
}
