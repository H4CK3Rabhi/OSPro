#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
//Q: Print a very large sums upto a range using different proccess

//Coder: Abhishek Sharma(Git: @H4CK3Rabhi)

int main()
{
        long long n;
	scanf("%lld",&n);
	int pd=fork();
	if(pd>0)
	{
		long long sum=0;
		for(long i=0;i<n/2;i++)
		{
	
			sum+=i;
			
		}
		long long status;
		wait(&status);
		long long val=WEXITSTATUS(status);
		sum+=val;
		printf("%lld is the sum",sum);
	}
	else if(pd==0)
	{
		long long sum=0;
		for(int i=n/2;i<=n;i++)
                  {
		
                         sum+=i;
			
	           }
	        _exit(sum);
		
	}
	else
	{  printf("Error in forking");

	}
	return 0;
}	
