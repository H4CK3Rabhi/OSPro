#include<stdio.h>
#include<stdlib.h>

#define NEW 0
#define READY 1
#define WAITING 2
#define RUNNING 3
#define EXIT 4

int systime=0,time_spent_run=0,EXITS=0,TQ=1,Do_Context_Switch=1,n;
struct Process 
{
	int pid;
	int state;
	int timeleft;
        int priority;
        int lte;
	int at;
	int wt,tat,ct,exect;
	struct Process *prev;
	struct Process *next;
} *process_store;
struct Queue
{
	struct Process *front ,*rear;
}*rq;

void enqueue(struct Process *pros)
{
	if(rq->front==NULL)
	{
		rq->front=pros;
		rq->rear=pros;
		pros->next=NULL;
	}
        
	else
	{
		if(pros->priority>rq->front->priority)
		{
			pros->next=rq->front;
			rq->front->prev=pros;
			rq->front=pros;
		}
               else if(pros->priority==rq->front->priority)
		{
                      
			pros->next=rq->front->next;
			pros->prev=rq->front;
			rq->front->next=pros;
                         if(pros->next!=NULL)
                      {
                        pros->next->prev=pros;
                      }
		}
		else if(pros->priority<rq->rear->priority)
		{
			pros->next=NULL;
			rq->rear->next=pros;
			pros->prev=rq->rear;
			rq->rear=pros;
		}
		else
		{
                   struct Process *start=rq->front->next;
		   while(start->priority>pros->priority)
		   {
			   start=start->next;
		   }
                   if(start!=NULL&& pros->priority==start->priority)
                   {
                          pros->next=start->next;
                          start->next=pros;
                          pros->prev=start;
                      
                   }
                  else
               {
		   (start->prev)->next=pros;
		   pros->next=start;
		   pros->prev=start->prev;
		   start->prev=pros;
                }

		}
	}
}
struct Process *  deQueue()
{
     if(rq->front==NULL)
     {
	     return NULL;
     }
     struct Process * temp=rq->front;
     rq->front=rq->front->next;
     temp->next=NULL;
     if(rq->front==NULL)
     {
	     rq->rear=NULL;
     }
     return temp;
}
void add_arrived_processes()
{
int count=0;
           for(int i=0;i<n;i++)
	   {
                   
		   if(process_store[i].state == NEW && systime>=process_store[i].at)
		   {      
			   
			   enqueue(&process_store[i]);
			   process_store[i].state=READY;
			   
                    }
                  if(process_store[i].state==EXIT)
                  {
                    count++;
			}
	   }
	   if(count==n)
	   {
		  EXITS=1; 
		  
	   }
}
int main()
{


rq =(struct Queue*) malloc(sizeof(struct Queue));
	printf("\t\tPlease enter No of processes to schedule >>");
	scanf("%d",&n);
	process_store=(struct Process *)malloc(sizeof(struct Process)*n);
	for(int i=0;i<n;i++)
	{
             printf("\n\n\t\tEnter Process Id For %d Process >>",(i+1));
	     scanf("%d",&(process_store[i].pid));
	     printf("\n\t\tEnter arrival time For %d Process  >>",(i+1));
	     scanf("%d",&(process_store[i].at));
	     printf("\n\t\tEnter Execution time For %d Process >>",(i+1));
	     scanf("%d",&(process_store[i].timeleft)); 
	     printf("\n\t\tEnter Priority For %d Process >>",(i+1));
	     scanf("%d",&(process_store[i].priority)); 
            process_store[i].exect=process_store[i].timeleft;
	    process_store[i].state=NEW;
	        
	}
 struct Process key; 
    int i,j;
    for (i = 1; i < n; i++) { 
        key = process_store[i]; 
        j = i - 1; 
  
        while (j >= 0 && process_store[j].at > key.at) { 
            process_store[j + 1] = process_store[j]; 
            j = j - 1; 
        } 
        process_store[j + 1] = key; 
    } 
printf("\nProcess Run in following order\n");
struct Process *process_in_running;
while(1)
{
        add_arrived_processes();
        if(EXITS==1)
        {

                    break;      
        }
        
        if(rq->front!=NULL && Do_Context_Switch==1)
	{
            
             time_spent_run=1;
	     process_in_running=deQueue();
             for(int i=0;i<n;i++)
        	{
                         if(process_store[i].state==READY)
                          {
                                       process_store[i].priority+=2;
                            }
        	}
             printf("(%d) [Process%d] ",systime,process_in_running->pid);
             process_in_running->state=RUNNING;
             process_in_running->timeleft--;
             process_in_running->priority++;
             process_in_running->lte=systime;
	     systime++;
             if(time_spent_run==process_in_running->exect || process_in_running->timeleft==0)
             {
                  Do_Context_Switch=1;
                  process_in_running->state=EXIT;
                  process_in_running->ct=systime;
                  process_in_running->tat=systime-process_in_running->at;
                  process_in_running->wt=process_in_running->tat-process_in_running->exect;
             }
             else
            {
                process_in_running->state=READY;
                enqueue(process_in_running);
              }
	}
        
else
{
for(int i=0;i<n;i++)
        	{
                         if(process_store[i].state==READY)
                          {
                                       process_store[i].priority+=2;
                            }
        	}
printf("(%d) [IDLE] ",systime);
systime++;
}
}
printf("(%d)",systime);
int sumwt=0,sumtat=0;
for(int i=0;i<n;i++)
	{
           printf("\n\nprocess pid=%d\t|ct=%d\t|tat=%d\t|wt=%d",process_store[i].pid,process_store[i].ct,process_store[i].tat,process_store[i].wt);
           sumwt+=process_store[i].wt;
           sumtat+=process_store[i].tat;
           
	}
printf("\n\n Avergae TAT=%f \t Average WT=%f\n",(sumtat/(n*1.0)),(sumwt/(n*1.0)));
}
