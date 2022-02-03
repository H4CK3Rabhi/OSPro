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

int nowtime=0,time_in_exec=0,EXITED=0,TimeQuantum,CONTEXT_SWITCH_ALLOWED=1,TQ,n;
struct PROCESS_BLOCK 
{
	int pid;
	int state;
	int timeleft;
        int priority;
	int at;
	int wt,tat,ct,exect;
	struct PROCESS_BLOCK *prev;
	struct PROCESS_BLOCK *next;
} *PROCESS_ARRAY;
int chpp;
struct Queue
{
	struct PROCESS_BLOCK *front ,*rear;
}*READY_QUEUE;

void enqueue(struct PROCESS_BLOCK *p)
{
	if(READY_QUEUE->front==NULL)
	{
		READY_QUEUE->front=p;
		READY_QUEUE->rear=p;
		p->next=NULL;
	}
        
	else
	{
		if(p->priority>READY_QUEUE->front->priority)
		{
			p->next=READY_QUEUE->front;
			READY_QUEUE->front->prev=p;
			READY_QUEUE->front=p;
		}
               else if(p->priority==READY_QUEUE->front->priority)
		{
			p->next=READY_QUEUE->front->next;
			p->prev=READY_QUEUE->front;
			READY_QUEUE->front->next=p;
                         if(p->next!=NULL)
                      {
                        p->next->prev=p;
                      }
		}
		else if(p->priority<READY_QUEUE->rear->priority)
		{
			p->next=NULL;
			READY_QUEUE->rear->next=p;
			p->prev=READY_QUEUE->rear;
			READY_QUEUE->rear=p;
		}
		else
		{
                   struct PROCESS_BLOCK *start=READY_QUEUE->front->next;
		   while(start->priority>p->priority)
		   {
			   start=start->next;
		   }
                   if(start!=NULL&& p->priority==start->priority)
                   {
                          p->next=start->next;
                          start->next=p;
                          p->prev=start;
                      
                   }
                  else
               {
		   (start->prev)->next=p;
		   p->next=start;
		   p->prev=start->prev;
		   start->prev=p;
                }

		}
	}
}
struct PROCESS_BLOCK *  deQueue()
{
     if(READY_QUEUE->front==NULL)
     {
	     return NULL;
     }
     struct PROCESS_BLOCK * temp=READY_QUEUE->front;
     READY_QUEUE->front=READY_QUEUE->front->next;
     temp->next=NULL;
     if(READY_QUEUE->front==NULL)
     {
	     READY_QUEUE->rear=NULL;
     }
     return temp;
}
void checkqueue()
{
int count=0;
           for(int i=0;i<n;i++)
	   {
                   
		   if(PROCESS_ARRAY[i].state == NEW && nowtime>=PROCESS_ARRAY[i].at)
		   {      
			   
			   enqueue(&PROCESS_ARRAY[i]);
			   PROCESS_ARRAY[i].state=READY;
			   
                    }
                  if(PROCESS_ARRAY[i].state==EXIT)
                  {
                    count++;
			}
	   }
	   if(count==n)
	   {
		  EXITED=1; 
		  
	   }
}
int main()
{


READY_QUEUE =(struct Queue*) malloc(sizeof(struct Queue));
	printf("Please enter No of processes to schedule");
	scanf("%d",&n);
	printf("\n Please Enter Time qunatum");
	scanf("%d",&TimeQuantum);
        TQ=TimeQuantum;
	PROCESS_ARRAY=(struct PROCESS_BLOCK *)malloc(sizeof(struct PROCESS_BLOCK)*n);
	for(int i=0;i<n;i++)
	{
             printf("\n\n Enter Process Id For %d Process",(i+1));
	     scanf("%d",&(PROCESS_ARRAY[i].pid));
	     printf("\n Enter arrival time For %d Process",(i+1));
	     scanf("%d",&(PROCESS_ARRAY[i].at));
	     printf("\n Enter Execution time For %d Process",(i+1));
	     scanf("%d",&(PROCESS_ARRAY[i].timeleft)); 
              printf("\n Enter Priority For %d Process",(i+1));
	     scanf("%d",&(PROCESS_ARRAY[i].priority)); 
	     
            PROCESS_ARRAY[i].exect=PROCESS_ARRAY[i].timeleft;
	    PROCESS_ARRAY[i].state=NEW;
	        
	}
 struct PROCESS_BLOCK key; 
    int i,j;
    for (i = 1; i < n; i++) { 
        key = PROCESS_ARRAY[i]; 
        j = i - 1; 
  
        while (j >= 0 && PROCESS_ARRAY[j].at > key.at) { 
            PROCESS_ARRAY[j + 1] = PROCESS_ARRAY[j]; 
            j = j - 1; 
        } 
        PROCESS_ARRAY[j + 1] = key; 
    } 

struct PROCESS_BLOCK *running_process;
printf("Gannt Chart::\n-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
struct PROCESS_BLOCK *prev;
while(1)
{
        checkqueue();
        if(EXITED==1)
        {

                    break;      
        }
        
        if(READY_QUEUE->front!=NULL && CONTEXT_SWITCH_ALLOWED==1)
	{
             time_in_exec=1;
             prev=running_process;
	     running_process=deQueue();
             running_process->state=RUNNING;
             if(prev!=running_process)
            {
             printf("| %d |  Process %d  ",nowtime,running_process->pid);
             }
             running_process->timeleft--;
	     nowtime++;
             TQ=running_process->priority*TimeQuantum;
             if(time_in_exec==running_process->exect)
             {
                  CONTEXT_SWITCH_ALLOWED=1;
                  running_process->state=EXIT;
                  running_process->ct=nowtime;
                  running_process->tat=nowtime-running_process->at;
                  running_process->wt=running_process->tat-running_process->exect;
             }
             else
            {
               CONTEXT_SWITCH_ALLOWED=0;
              }
	}
        else if(CONTEXT_SWITCH_ALLOWED==0&&running_process!=NULL && running_process->state==RUNNING )
	{
             if(running_process->timeleft==0)
             {
                  CONTEXT_SWITCH_ALLOWED=1;
                  running_process->state=EXIT;
                  running_process->ct=nowtime;
                  running_process->tat=nowtime-(running_process->at);
                  running_process->wt=(running_process->tat)-(running_process->exect);
                  continue;
             }      
             time_in_exec++;
             running_process->timeleft--;
            nowtime++;

             if(running_process->timeleft==0)
             {
                  CONTEXT_SWITCH_ALLOWED=1;
                  running_process->state=EXIT;
                  running_process->ct=nowtime;
                  running_process->tat=nowtime-(running_process->at);
                  running_process->wt=(running_process->tat)-(running_process->exect);
             }            
             else if(time_in_exec==TQ)
             {
                running_process->state=READY;
                enqueue(running_process);
                CONTEXT_SWITCH_ALLOWED=1;
              }
            else
          { 
              CONTEXT_SWITCH_ALLOWED=0;
	  }

          
             
          
	}
else
{
printf("| %d | IDLE");
nowtime++;
}
}
printf("| %d |",nowtime);
printf("\n------------------------------------------------------------------------------------------------------------------------------------------------------\n");
int sumwt=0,sumtat=0;
for(int i=0;i<n;i++)
	{
           printf("\nprocess pid=%d ::  ct=%d\ttat=%d\twt=%d",PROCESS_ARRAY[i].pid,PROCESS_ARRAY[i].ct,PROCESS_ARRAY[i].tat,PROCESS_ARRAY[i].wt);
           sumwt+=PROCESS_ARRAY[i].wt;
           sumtat+=PROCESS_ARRAY[i].tat;
           
	}
printf("\n\n Avergae TAT=%f \n Average WT=%f\n",(sumtat/(n*1.0)),(sumwt/(n*1.0)));
}
