#include<unistd.h>
#include<stdio.h>

int main()
{
  int n=fork();
  int n1=fork();
  if(n>0&n1>0)
  {
	  printf("I am parent P1 with pid %d\n",getpid());
  }
  else if(n==0)
  {
	  if(n1>0)
	  {
       printf("I am  child p3 with pid %d and parent pid=%d\n",getpid(),getppid());
	  }
	  else if(n1==0)
	  {
		  printf("I am Child P4 with pid%d and parent pid=%d\n",getpid(),getppid());
	  }
	  else
	  {
		  printf("error in creating p4");
	  }

  }
  else if(n1==0&n>0)
  {
	printf("I am Child p2 with pid=%d and parent is %d\n",getpid(),getppid());
  }
  else
  {
	  printf("error in fork");
  }

}

