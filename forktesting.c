#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
int x=1;
int pid=fork(),pid2=fork();
if(pid>0&&pid2>0)
{
printf("Value in Parent pd=%d of parent %d:- %d\n ",getpid(),getppid(),++x);
wait(0);
printf("Called after wait%d",0);
}
else if(pid==0)
{
printf("Value in child pid=%d of parent %d:- %d\n",getpid(),getppid(),--x);
_exit(3);
}
else if(pid2==0)
{
printf("Value in child pid=%d of parent %d:- %d\n",getpid(),getppid(),--x);
_exit(3);
}
else
{
printf("Error in Forking");
}
return 0;
}

