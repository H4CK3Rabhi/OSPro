#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
pthread_mutex_t R1,R2;

void * proc1()
{
        
	pthread_mutex_lock(&R1);
	sleep(1);
	pthread_mutex_unlock(&R2);
	pthread_mutex_lock(&R2);
	   printf("Process 1 Running");
	pthread_mutex_unlock(&R2);
	pthread_mutex_unlock(&R1);
}
void * proc2()
{
	
        pthread_mutex_lock(&R2);
	sleep(1);
	pthread_mutex_unlock(&R1);
	pthread_mutex_lock(&R1);
	   printf("Process 2 Running");
	pthread_mutex_unlock(&R1);
	pthread_mutex_unlock(&R2);
}


int main()
{

        pthread_mutex_init(&R2,NULL);
	pthread_mutex_init(&R1,NULL);
	pthread_t t1,t2;
	pthread_create(&t1,NULL,proc1,NULL);
	pthread_create(&t2,NULL,proc2,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);


}
