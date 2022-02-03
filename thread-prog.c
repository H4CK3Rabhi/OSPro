#include<stdio.h>
#include<pthread.h>

void * fivonaaci(void * param)
{
	int *getval=(int *)param;
        int num=getval[2];
	int i,first=getval[0],second=getval[1];
	printf("%d+%d",first,second);
        for(i=0;i<num-2;i++)
	{  
	
                int next=first+second;
		first=second;
		second=next;
		printf("%d",second);
	}
}
void * fact(void * param)
{

	int *num=(int *)param;
	int f=1,i;
	for(i=1;i<=*num;i++)
	{
		f=f*i;
	}
	printf("\n%d\n",f);
	pthread_exit((void *)f);

}
int main()
{
	int n;
	scanf("%d",&n);
	pthread_t t1,t2;
	void * ans;
	int nums[3]={0,1,n};
	pthread_create(&t1,NULL,fivonaaci,&nums);
	pthread_create(&t2,NULL,fact,&n);
	pthread_join(t1,NULL);
	pthread_join(t2,&ans);
	printf("%d\n",ans);
}
