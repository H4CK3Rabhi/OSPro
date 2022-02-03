#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

long long sum=0;
void* sum_runner(void* arg)//thread function
{
	long long *limit_ptr=(long long*)arg;
	long long limit=*limit_ptr;
	long long i;
	for(i=0;i<=limit;i++)
	{
		sum+=i;
	}
	//TODO:::Something
	pthread_exit(0);

}

int main(int argc,char **argv)
{
	if(argc<1)
	{
	printf("usage : ./pthreadf.c <limit>");
	}
	long long  limit=atoll(argv[1]);
	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	pthread_create(&tid,NULL,sum_runner,&limit);
	//waiting from thr
	pthread_join(tid,NULL);
	printf("%lld",sum);
	
}
