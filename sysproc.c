#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

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

unsigned long numcalls = 0;

int
sys_info(void)
{
    //procdump();
	int x;
	int num;
	argptr(0, (void *)&num, sizeof(num));
	
	if (num==1)
	{
	x = procCount();
	cprintf("Count of processes in the system: %d\n", x);
	
	}
	else if (num==2)
	{
		cprintf("Count of the total number of system calls that the current process has made so far: %d\n", numcalls);
		
	}
	else if (num==3)
	{
		int memory=myproc()->sz;
		int mem1=memory/4096;
		cprintf("Number of memory pages the current process is using: %d\n", mem1);
		
	}
	else
	{
		cprintf("Enter input 1,2 or 3");
	}
	
	return -1;
	
}






//lottery
//function to set the tickets for the lottery test
int
sys_settickets(void){
  int ticket_number;
  if (argint(0, &ticket_number) < 0)
  {
     myproc()->tickets = 10; 	//setting the default value
  }
  else{
     myproc()->tickets = ticket_number;
  }
  return 0;
}





