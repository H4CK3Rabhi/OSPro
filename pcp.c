#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<sys/types.h>

int N=5;
sem_t full,empty;
pthread_mutex_t mutex;
void * producer()
{
	while(1)
	{
	sem_wait(&empty);
	pthread_mutex_lock(&mutex);
        N++;
	printf("Size=%d\n",(full+empty));
	pthread_mutex_unlock(&mutex);
	sem_post(&full);
	}

}
void *consumer()
{
	while(1)
	{
	sem_wait(&full);
	pthread_mutex_lock(&mutex);
	N--;
        printf("Size=%d",(full+empty));
	pthread_mutex_unlock(&mutex);
	sem_post(&empty);
	}
}
int main()
{


	pthread_mutex_init(&mutex,NULL);
	sem_init(&full,0,0);
	sem_init(&empty,0,N);
        pthread_t pro,cons;
	pthread_create(&pro,NULL,producer,NULL);
	pthread_create(&cons,NULL,consumer,NULL);
	pthread_join(pro,NULL);
	pthread_join(cons,NULL);
}
