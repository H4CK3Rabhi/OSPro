#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

#define NEW 0
#define READY 1
#define WAITING 2
#define RUNNING 3
#define EXIT 4
int currenttime=0,runningtime=0,ALLEXIT=0,TimeQuantum;
pthread_mutex_t queuemut;
struct Proc 
{
	int pid;
	int state;
	int timeleft;
	int at;
	int wt,tat,ct,exect;
	struct Proc *prev;
	struct Proc *next;
};
int chpp;
struct Queue
{
	struct Proc *front ,*rear;
}*ReadyQueue;

void enqueue(struct Proc *p)
{
	if(ReadyQueue->front==NULL)
	{
		ReadyQueue->front=p;
		ReadyQueue->rear=p;
		p->next=NULL;
	}
	else
	{
		if(p->timeleft<ReadyQueue->front->timeleft)
		{
			p->next=ReadyQueue->front;
			ReadyQueue->front->prev=p;
			ReadyQueue->front=p;
		}
		else if(p->timeleft>ReadyQueue->rear->timeleft)
		{
			p->next=NULL;
			ReadyQueue->rear->next=p;
			p->prev=ReadyQueue->rear;
			ReadyQueue->rear=p;
		}
		else
		{
                   struct Proc *start=ReadyQueue->front->next;
		   while(start->timeleft<p->timeleft)
		   {
			   start=start->next;
		   }
		   (start->prev)->next=p;
		   p->next=start;
		   p->prev=start->prev;
		   start->prev=p;

		}
	}
}
struct Proc *  deQueue()
{
     if(ReadyQueue->front==NULL)
     {
	     return NULL;
     }
     struct Proc * temp=ReadyQueue->front;
     ReadyQueue->front=ReadyQueue->front->next;
     temp->next=NULL;
     if(ReadyQueue->front==NULL)
     {
	     ReadyQueue->rear=NULL;
     }
     return temp;
}
void *Scheduler()
{
	while(ALLEXIT==0)
	{
		pthread_mutex_lock(&queuemut);
		struct Proc* p=deQueue();
		pthread_mutex_unlock(&queuemut);
		chpp=0;
		if(p==NULL)
		{
			sleep(1);
                       if(chpp)
		       {
			       currenttime++;
		       } 
			continue;
		}
		else
		{       p->state=RUNNING;
			runningtime=0;
			
			while(p->timeleft>0&&TimeQuantum>=runningtime)
			{	printf("running pid %d on currtime %d",p->pid,currenttime);
	
				p->timeleft--;
                                currenttime++;
				runningtime++;
				sleep(1);
			}
			if(p->timeleft==0)
			{
				p->ct=currenttime;
				p->tat=currenttime-p->at;
				p->wt=p->tat-p->exect;
			}
			else 
			  {
				pthread_mutex_lock(&queuemut);
                                if(p->state==RUNNING)
				{
				enqueue(p);
				p->state=READY;
				}
				pthread_mutex_unlock(&queuemut);
			  }
		}

	}
	pthread_exit(0);
}
void *lterm()
{
	int n;
	printf("Please enter No of processes to schedule");
	scanf("%d",&n);
	printf("\n Please Enter Time qunatum");
	scanf("%d",&TimeQuantum);
	struct Proc *p=(struct Proc *)malloc(sizeof(struct Proc)*n);
	for(int i=0;i<n;i++)
	{
             printf("\n\n Enter Process Id For %d Process",(i+1));
	     scanf("%d",&(p[i].pid));
	     printf("\n Enter arrival time For %d Process",(i+1));
	     scanf("%d",&(p[i].at));
	     printf("\n Enter Execution time For %d Process",(i+1));
	     scanf("%d",&(p[i].timeleft)); 
	     
            p[i].exect=p[i].timeleft;
	    p[i].state=NEW;
	        
	}
	int flag=0;
	while(1)
	{
           int count=0;
           for(int i=0;i<n;i++)
	   {
                   chpp=1;
		   if(p[i].state == NEW && currenttime>=p[i].at)
		   {      
			   pthread_mutex_lock(&queuemut);
			   enqueue(&p[i]);
			   p[i].state=READY;
			   pthread_mutex_unlock(&queuemut);
		   }
                   if(p[i].state==EXIT)
		{ 
                    count++;
                   }
	   }
	   if(count==n)
	   {
		  ALLEXIT=1;
		   break; 
		  
	   }
	   sleep(1);
	}
        for(int i=0;i<n;i++)
	{
           printf("\n\nprocess pid=%d\nct=%d\ntat=%d\nwt=%d",p[i].pid,p[i].ct,p[i].tat,p[i].wt);
	}
	pthread_exit(0);
}
int main()
{
	ReadyQueue =(struct Queue*) malloc(sizeof(struct Queue));
	pthread_t thread1,thread2;
	pthread_mutex_init(&queuemut,NULL);
	pthread_create(&thread1,NULL,lterm,NULL);
	pthread_create(&thread2,NULL,Scheduler,NULL);
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
}
