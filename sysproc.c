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

// return the year of which the Unix version 6 was released
int
sys_getyear (void)
{
  return 1975;
}

// return the year of which the Unix version 6 was released
int
sys_getmysize (void)
{
  return myproc()->sz;
}


int
sys_getkernalstartaddr (void)
{
  return KERNBASE;
}

int
sys_getkernalendaddr (void)
{
  return KERNBASE + PHYSTOP;
}

int
sys_getkernalvariaddr (void)
{
  int i = 222;
  return (int)&i;

}

int
sys_getsystemcalladdr (void)
{
  return (int)&sys_fork;
}

int
sys_setpriority(void)
{
  int n;

  struct proc *p = myproc();
  if(argint(0, &n) > 0)
    return -1;
  p->priority = n;
  return p->priority;
}

int
sys_ps(void)
{
    int size;
    char *buf;
    char *s;

    struct proc* proc = getPtable();

    if (argint(0, &size) <0){
        return -1;
    }

    if (argptr(1, &buf,size) <0){
        return -1;
    }

    s = buf;

    while(buf + size > s){
        *(int *)s = proc->pid;
        s+=4;
        *(uint *)s = proc->sz;
        s+=4;
        strncpy(s, proc->name,16);
        s+=16;
        proc++;
    }

    return 1;
}

