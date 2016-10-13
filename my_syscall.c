/*
 *  Christopher David Monken, Adam Mastov, Fan, Martin Kuna
 *  Project 2
 *  CSE430: Operating Systems
 */

#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/jiffies.h>
#include <linux/tty.h>
#include <linux/uaccess.h>


//" 6982 ?        00:00:00 gnome-pty-helpe"


asmlinkage long sys_my_syscall(void)
{
	int len = 0;
	int i = 0;
	int sec, sec2min, min, hr;
    unsigned long jiff, time;
    struct task_struct *p;                   // pointer for iterating across task list

    // get the task list length
    for_each_process(p){
        len++;
    }

    char my_buffer[len*39];                  // buffer to pass data to user-space

    for_each_process(p){

		cputime_t utime = 0;
		cputime_t stime = 0;

        printk("%i ", p->pid);

/*
    // add pid to buffer
        if (p->pid < 10)
            printk("    %i ", p->pid);
        else if (p->pid < 100)
            printk("   %i ", p->pid);
        else if (p->pid < 1000)
            printk("  %i ", p->pid);
        else if (p->pid < 10000)
            printk(" %i ", p->pid);
        else
            printk("%i ", p->pid);

    // add tty to buffer
        if (p->signal->tty == NULL)          // change NULL to '?' -> tty format in 'ps -e'
            printk("?        ");
        else{


        }
            printk
            strcpy(task_array[i].task_tty, p->signal->tty->name);

    // add time to buffer
		jiff = utime + stime;
        time = jiff / HZ;                    // convert jiffies to seconds
        sec2min = time / 60;                 // converft seconds to miknutes
        sec = time % 60;                     // get remaining seconds
        hr = sec2min / 60;                   // convert minutes to hours
        min = sec2min % 60;                  // get remaining minutes

        if (hr < 10)
            printk("0%i:", hr);
        else
            printk("%i:", hr);
        if (min < 10)
            printk("0%i:", min);
        else
            printk("%i:", min);
        if (sec < 10)
            printk("0%i ", sec);
        else
            printk("%i ", sec);

    // add comm to buffer
        for (i = 0, i < 15 && p->comm[i] != '\0', i++)        // get domm upto 15 characters
            printk("%s", p->comm[i]);
        if (i < 14){                                          // if comm is less than 15 characters
            for (i, i < 15, i++)                              // make the remaining characters spaces
                printk(" ");
        }

*/
    }
    // copy array to user space
    return 0;
}
