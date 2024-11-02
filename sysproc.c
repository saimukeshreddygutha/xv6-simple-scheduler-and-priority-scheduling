#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"


int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

void sys_hello(void){
cprintf("Hello from the Kernel!\n");
}

int sys_ticks_running(void) {
    int pid;
    
    if (argint(0, &pid) < 0)
        return -1;

    return ticks_running(pid);
}

int sys_sjf_job_length(void) {
    int pid;
    
    if (argint(0, &pid) < 0)
        return -1;

    return sjf_job_length(pid);
}

void 
sys_set_sched_priority(void){
	int priority;
    
    	if (argint(0, &priority) < 0)
        	return;

       	set_sched_priority(priority);

}

void 
sys_set_sched_priority_for_pid(void){
	int pid, priority;
    
    	if (argint(0, &pid) < 0)
        	return;
       	if (argint(1, &priority) < 0)
        	return;

       	set_sched_priority_for_pid(pid, priority);

}

int 
sys_get_sched_priority(void){
	int pid;
	if (argint(0, &pid) < 0)
        	return -1;
	return get_sched_priority(pid);

}

/*void 
sys_set_lottery_tickets(void){
	int tickets;
    
    	if (argint(0, &tickets) < 0)
        	return;
       	set_lottery_tickets(tickets);

}*/

/*int 
sys_get_lottery_tickets(void){
	int pid;
	if (argint(0, &pid) < 0)
        	return -1;
	return get_lottery_tickets(pid);

}*/

/*int
sys_cps(void)
{
  return cps();
}*/



