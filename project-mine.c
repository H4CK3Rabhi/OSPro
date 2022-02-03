#include<pthread.h>
#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

#define NEW 0
#define READY 1
#define RUNNING 2
#define WAITING 3
#define EXIT 4
#define SRT 0
#define RR 1
#define Q1 1
#define Q2 2
pthread_t *tid;
pthread_mutex_t rtmutex;
pthread_mutex_t enmutex;
pthread_mutex_t demutex;
int TimeQuantum=2;
int runningtime=0;
int currex=SRT;
int currenttime=0;
int ALLEXIT=0;
struct Proc
{
	int pid;
	int state;
	int timeleft;
	int arrival_time;
	int wt,tat,ct;
	int qno;
	struct Proc *next;
};
struct Queue
{
   struct Proc* front, *rear;
}*q1,*q2,*q3;

void swap(struct Proc *p1,struct Proc *p2,struct Proc *prev)
{
	prev->next=p2;
	p1->next=p2->next;
	p2->next=p1;
}

void sortq1()
{
	struct Proc *start;
         start=q1->front;
	int swapped,i;
	struct  Proc *ptr1;
	struct Proc *lptr=NULL;
	struct Proc *prev=NULL;
	if(start==NULL)
	{
		printf("error");
		return;
	}
	do
	{
		swapped=0;
		ptr1=start;

		while(ptr1->next!=lptr)
		{      if(ptr1->timeleft>ptr1->next->timeleft)
			{
			swap(ptr1,ptr1->next,prev);
			swapped=1;
			}
			prev=ptr1;
			ptr1=ptr1->next;
		}
		lptr=ptr1;
	}
	while(swapped);
        ptr1=start;
	while(ptr1->next!=NULL);
        q1->rear=ptr1;
}


//struct Proc * create_process(int pid,int bt,int at,int qno)
//{
//	eturn temp;
//}
struct Queue * createQueue()
{
	struct Queue* q=(struct Queue*)malloc(sizeof(struct Queue));
	q->front=NULL;q->rear=NULL;
	return q;
}
void enQueue(struct Queue* q,struct Proc * p)
{
  

    if(p->state==EXIT || p->state==READY)
    {		
	    
	    return;
            
    }
    if(q->rear==NULL)
    {
	    q->front=p;
	    q->rear=p;
	    p->state=READY;
            
    	    return;
    }
    q->rear->next=p;
    q->rear=p;
    p->state=READY;
    
   
}
void enQueuep(struct Queue* q,struct Proc *p)
{
    if(p->state==EXIT|| p->state==READY)
    {
		return;
     }
    struct Proc * start=q->front;
    if(q->front==NULL)
    { 
       q->front=q->rear=p;
       return;
     }
    if (q->front->timeleft >p->timeleft) { 
  
        // Insert New Node before head 
        p->next = q->front; 
        q->front = p; 
    } 
    else { 
   
        while (start->next != NULL && 
               start->next->timeleft < p->timeleft) { 
            start = start->next; 
        } 
  
        // Either at the ends of the list 
        // or at required position 
        p->next = start->next; 
        start->next = p; 
        }
	start=q->front;
        while(start->next!=NULL) start=start->next;
	 q->rear=start;
}
struct Proc * deQueue(struct Queue *q)
{      
	
	if(q->front==NULL)
	{
		return NULL;
	}
	struct Proc *p= q->front;
	q->front=q->front->next;
	if(q->front==NULL)
	{
		q->rear=NULL;
	}
	p->state=RUNNING;
	return p;
}
void running(struct Proc *p)
{
if(p!=NULL)
{
   runningtime=0;
   
   
   while(p->timeleft>0)
   {
      printf("Ruuning process is %d",p->pid);  
       runningtime++;
       currenttime++;
       sleep(1);
	p->timeleft--;
       if(q1->front!=NULL)
	{
       if(q1->front->timeleft<p->timeleft&& currex==SRT)
       {
	      break;
       }
	}
       if(runningtime>=TimeQuantum && currex==RR)
       {
	       break;
       }
       

   }
   
 }  
}
void *scheduler_srft(void* xx)
{  while(1)
  {
if(ALLEXIT)
{
break;
}
   pthread_mutex_lock(&demutex);
  struct Proc *p=deQueue(q1);
  pthread_mutex_unlock(&demutex); 
   if(p==NULL)
   {
	currex=RR;
	continue;
   }
   else
   {
	currex=SRT;
   }
   if(currex==SRT &p!=NULL);
   {      pthread_mutex_lock(&rtmutex);
	   running(p);
        pthread_mutex_unlock(&rtmutex);
	   if(p->timeleft<=0)
	   {
		   p->ct=currenttime;
		   p->state=EXIT;
	   }
	   else
	   {	pthread_mutex_lock(&enmutex);
		   enQueuep(q1,p);
		pthread_mutex_unlock(&enmutex);
	   }


   }
  }
pthread_exit(0);
}
void *scheduler_rr(void* xx)
{
while(1)
{
if(ALLEXIT)
{
break;
}
if(currex==RR)
{
  pthread_mutex_lock(&demutex);
  struct Proc *p=deQueue(q2);
  pthread_mutex_unlock(&demutex); 
  if(p==NULL)
   { currex=SRT;continue;}
   pthread_mutex_lock(&rtmutex);
     running(p);
      pthread_mutex_unlock(&rtmutex);
  if(p->timeleft==0)
  {
	  p->ct=currenttime;
	  p->state=EXIT;
	  pthread_mutex_lock(&enmutex);
	  enQueue(q3,p);
          pthread_mutex_lock(&enmutex);
  }
  else
  {	pthread_mutex_lock(&enmutex);
	  enQueue(q2,p);
	pthread_mutex_unlock(&enmutex);
  }
}
}
pthread_exit(0);
}

void *lterm(void* xx)
{ 
  int n;
  printf("Enter No of processes to schedule");
  scanf("%d",&n);
  int szeof=sizeof(struct Proc); 
  struct Proc pa[n];
  for(int i=0;i<n;i++)
  {      
	int pid_in,exectime,qno_in,at;
	printf("Enter Pid No for %d process : ",(i+1));
	scanf("%d",&pid_in);
	printf("Enter Burst Time for %d process : ",(i+1));
	scanf("%d",&exectime);
	printf("Enter Arrival Time for %d process :",(i+1));
	scanf("%d",&at);
	printf("Enter Queue no for %d process : ",(i+1));
	scanf("%d",&qno_in);
	printf("\n\n");


	pa[i].pid=pid_in;
	pa[i].state=NEW;
	pa[i].timeleft=exectime;
	pa[i].arrival_time=at;
	pa[i].next=NULL;
	pa[i].qno=qno_in;
	printf("%d",pa[i].pid);
	
	
  }
  int flag=1;
  while(flag)
  {
   int flag2=0;
   for(int i=0;i<n;i++)
  {

   if(pa[i].arrival_time>=currenttime)
   {
        if(pa[i].qno==Q1)
	{      pthread_mutex_lock(&enmutex);
	enQueuep(q1,&pa[i]);
		pthread_mutex_unlock(&enmutex);
	}
	else
	{      pthread_mutex_lock(&enmutex);
		enQueue(q2,&pa[i]);
	       pthread_mutex_unlock(&enmutex);
	}

   }
   if(pa[i].state==EXIT)
     {
	flag2++;
     }
  }
  if(flag2==n)
  {
    ALLEXIT=1;
    break;
   }
  }
  pthread_exit(0);
}


int main()
{
        q1=createQueue();
	q2=createQueue();
        q3=createQueue();
        pthread_attr_t attrDefault;
	pthread_attr_init(&attrDefault);
	tid=malloc(sizeof(pthread_t)*4);
        pthread_mutex_init(&rtmutex,NULL);
	pthread_mutex_init(&enmutex,NULL);
	pthread_mutex_init(&demutex,NULL);
        pthread_create((tid+1),NULL,scheduler_srft,NULL);
	pthread_create((tid+2),NULL,scheduler_rr,NULL);
        pthread_create((tid+0),NULL,lterm,NULL);
        pthread_join(*(tid+1),NULL);
	pthread_join(*(tid+2),NULL);
	pthread_join(*(tid+0),NULL);
	printf("Everything executed successfully");

}

