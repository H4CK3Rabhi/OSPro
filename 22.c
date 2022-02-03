#include<pthread.h>
#include<stdio.h>
#include<semaphore.h>
sem_t sem1;
int shared=0;

void * proc()
{
       int x=shared;
       
       sem_wait(&sem1);
       x--;
       shared=x;
       sem_post(&sem1);
}
void * proc1()
{
	int x=shared;
	
	sem_wait(&sem1);
	x++;
	shared=x;
	sem_post(&sem1);
}
int main()
{
	sem_init(&sem1,0,1);
	pthread_t t1,t2;
	pthread_create(&t1,NULL,proc,NULL);
	pthread_create(&t2,NULL,proc1,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	printf("%d\n",shared);
}
