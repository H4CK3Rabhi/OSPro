#include<pthread.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<semaphore.h>
#define HUNGRY 0
#define EATING 1
#define THINKING 2
#define N 5

int state[N];
pthread_mutex_t mutex;
sem_t S[N];
int phil[N]={0,1,2,3,4};
int LEFT(int i)
{ 
    if(i>=N-1)
	     {
	     return 0;
     }
     else
     {
	     return i+1;
     } 
}
int RIGHT(int i)
{
      if(i<=0)
     {
	     return N-1;
     }
     else
     {
	     return i-1;
     }    
            
}
void test(int i)
{
	if(state[i]==HUNGRY&&state[LEFT(i)]!=EATING && state[RIGHT(i)]!=EATING)
	{
		state[i]=EATING;
		printf("\nPhilospher %d is EATING\n",i);
		sem_post(&S[i]);
	}
}
void take_chops(int i)
{
      pthread_mutex_lock(&mutex);
      state[i]=HUNGRY;
      //printf("\nPhilospher %d is HUNGRY\n",i);
      test(i);
      pthread_mutex_unlock(&mutex);
      sem_wait(&S[i]);
}
void real_chops(int i)
{
	pthread_mutex_lock(&mutex);
	state[i]=THINKING;
	//printf("\nPhilospher %d is THINKING\n",i);
	test(LEFT(i));
	test(RIGHT(i));
	pthread_mutex_unlock(&mutex);
}
void think()
{
	sleep(1);
}
void eat()
{
	sleep(0);
}
void * philospher(void * num)
{
	int *i=num;
	while(1)

	{     
		
	       think(); 	
		take_chops(*i);
                eat();
		real_chops(*i);
	}

}
int main()
{
  pthread_mutex_init(&mutex,NULL);
  for(int i=0;i<N;i++)
  {
    sem_init(&S[i],0,0);
  }
  pthread_t tid[N];
  for(int i=0;i<N;i++)
  {
	  pthread_create(&tid[i],NULL,philospher,&phil[i]);
  }
  for(int i=0;i<N;i++)
  {
      pthread_join(tid[i],NULL);
  }
}
