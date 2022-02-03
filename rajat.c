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

int time_in_sys=0,time_in_exec=0,EVERYTHINGEXITED=0,TQ,ContextSwitch=1,n;
struct process_det 
{
	int pid;
	int state;
	int timeleft;
	int at;
	int wt,tat,ct,exect;
	struct process_det *prev;
	struct process_det *next;
} *pro_det;
struct Queue
{
	struct process_det *front ,*rear;
}*rqueue;

void enqueue(struct process_det *proc)
{
	  if(rqueue->front==NULL)
      { 
         proc->prev=NULL;

         proc->next=NULL;
         rqueue->front=proc;           
         rqueue->rear=proc;
         return;
      }
     proc->prev=rqueue->rear;
     rqueue->rear->next=proc;
     rqueue->rear=proc;
}
struct process_det *  deQueue()
{
     if(rqueue->front==NULL)
     {
	     return NULL;
     }
     struct process_det * temp=rqueue->front;
     rqueue->front=rqueue->front->next;
     temp->next=NULL;
     if(rqueue->front==NULL)
     {
	     rqueue->rear=NULL;
     }
     return temp;
}
void checkfornewlyarrived()
{
int count=0;
           for(int i=0;i<n;i++)
	   {
                   
		   if(pro_det[i].state == NEW && time_in_sys>=pro_det[i].at)
		   {      
			   
			   enqueue(&pro_det[i]);
			   pro_det[i].state=READY;
			   
                    }
                  if(pro_det[i].state==EXIT)
                  {
                    count++;
			}
	   }
	   if(count==n)
	   {
		  EVERYTHINGEXITED=1; 
		  
	   }
}
int main()
{


rqueue =(struct Queue*) malloc(sizeof(struct Queue));
	printf(" \t\tPlease enter No of processes to schedule --- ");
	scanf("%d",&n);
	printf("\n\t\tPlease Enter Time Quantum --- ");
	scanf("%d",&TQ);
	pro_det=(struct process_det *)malloc(sizeof(struct process_det)*n);
	for(int i=0;i<n;i++)
	{
             printf("\n\n\t\tEnter Process Id For %d Process --- ",(i+1));
	     scanf("%d",&(pro_det[i].pid));
	     printf("\n\t\tEnter arrival time For %d Process ---",(i+1));
	     scanf("%d",&(pro_det[i].at));
	     printf("\n\t\tEnter Execution time For %d Process ---",(i+1));
	     scanf("%d",&(pro_det[i].timeleft)); 
	     
            pro_det[i].exect=pro_det[i].timeleft;
	    pro_det[i].state=NEW;
	        
	}
 struct process_det key; 
    int i,j;
    for (i = 1; i < n; i++) { 
        key = pro_det[i]; 
        j = i - 1; 
  
        while (j >= 0 && pro_det[j].at > key.at) { 
            pro_det[j + 1] = pro_det[j]; 
            j = j - 1; 
        } 
        pro_det[j + 1] = key; 
    } 

struct process_det *pr;
while(1)
{
        checkfornewlyarrived();
        if(EVERYTHINGEXITED==1)
        {

                    break;      
        }
        
        if(rqueue->front!=NULL && ContextSwitch==1)
	{
             time_in_exec=1;
	     pr=deQueue();
             pr->state=RUNNING;
             pr->timeleft--;
	     time_in_sys++;
             if(time_in_exec==pr->exect)
             {
                  ContextSwitch=1;
                  pr->state=EXIT;
                  pr->ct=time_in_sys;
                  pr->tat=time_in_sys-pr->at;
                  pr->wt=pr->tat-pr->exect;
             }
             else
            {
               ContextSwitch=0;
              }
	}
        else if(ContextSwitch==0&&pr!=NULL && pr->state==RUNNING )
	{
             if(pr->timeleft==0)
             {
                  ContextSwitch=1;
                  pr->state=EXIT;
                  pr->ct=time_in_sys;
                  pr->tat=time_in_sys-(pr->at);
                  pr->wt=(pr->tat)-(pr->exect);
                  continue;
             }      
             time_in_exec++;
             pr->timeleft--;
            time_in_sys++;

             if(pr->timeleft==0)
             {
                  ContextSwitch=1;
                  pr->state=EXIT;
                  pr->ct=time_in_sys;
                  pr->tat=time_in_sys-(pr->at);
                  pr->wt=(pr->tat)-(pr->exect);
             }            
             else if(time_in_exec==TQ)
             {
                pr->state=READY;
                enqueue(pr);
                ContextSwitch=1;
              }
            else
          { 
              ContextSwitch=0;
	  }

          
             
          
	}
else
{
time_in_sys++;
}
}
int sumwt=0,sumtat=0;
for(int i=0;i<n;i++)
	{
           printf("\n\nprocess pid=%d\t:::ct=%d\t:::tat=%d\t:::wt=%d",pro_det[i].pid,pro_det[i].ct,pro_det[i].tat,pro_det[i].wt);
           sumwt+=pro_det[i].wt;
           sumtat+=pro_det[i].tat;
           
	}
printf("\n\n Avergae TAT=%f \t::: Average WT=%f\n\n",(sumtat/(n*1.0)),(sumwt/(n*1.0)));
}
