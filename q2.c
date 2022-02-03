#include<stdio.h>
#include<unistd.h>


int main()
{
	int n=fork();
       if(n>0)
	{
		int k=fork();
		if(k>0)
		{
			printf("I am a Parent P1 with pid:%d\n",getpid());
		}
		else if(k==0)
		{      
			int j=fork();
			if(j>0)
			{
	                     printf("I am a child P2 with pid:%d and my parent is=%d\n",getpid(),getppid());
			}
			else if(j==0)
			{
			  int jj=fork();
                          if(jj>0)
			  {
				   printf("I am Child P4 with pid=%d and my parent is=%d\n",getpid(),getppid());
			  }
			  else if(jj==0)
			  {
                                      printf("I am Child P5 with pid=%d and my parent is=%d\n",getpid(),getppid());
			  }
			  else
			  {
				  printf("error in creating p5");
			  }
			}
			else
			{
				printf("error in creating P4");
			}
		}
		else
		{
			printf("error in creating P2");
		}
	}
       else if(n==0)
	 {
		 printf("I am Child P3 with pid=%d and my parent is=%d\n",getpid(),getppid());
	 }
	else
	{
		printf("error in creating P2");
	}
}
