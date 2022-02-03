#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
//Process State Definations::
#define NEW 0                  
#define READY 1
#define WAITING 2
#define RUNNING 3
#define EXIT 4

int st=0,rtp=0,EXITEDSTATE=0,TQtm,SWITCH_PROCESS=1,n,i,j;
struct Process_represent 
{
	int pid;
	int state;
	int timeleft;
	int at;
	int wt,tat,ct,exect;
	struct Process_represent *prev;
	struct Process_represent *next;
} *proc_arr;

struct Queue
{
	struct Process_represent *front ,*rear;
}*READYQ;

void enqueue(struct Process_represent *proc)
{
	if(READYQ->front==NULL)
      { 
         proc->prev=NULL;

         proc->next=NULL;
         READYQ->front=proc;           
         READYQ->rear=proc;
         return;
      }
     proc->prev=READYQ->rear;
     READYQ->rear->next=proc;
     READYQ->rear=proc;
}
struct Process_represent *  deQueue()
{
     if(READYQ->front==NULL)
     {
	     return NULL;
     }
     struct Process_represent * temp=READYQ->front;
     READYQ->front=READYQ->front->next;
     temp->next=NULL;
     if(READYQ->front==NULL)
     {
	     READYQ->rear=NULL;
     }
     return temp;
}
void Add_Arrived_procs()
{
int cnt=0;
           for(i=0;i<n;i++)
	   {
                   
		   if(proc_arr[i].state == NEW && st>=proc_arr[i].at)
		   {      
			   
			   enqueue(&proc_arr[i]);
			   proc_arr[i].state=READY;
			   
                    }
                  if(proc_arr[i].state==EXIT)
                  {
                    cnt++;
			}
	   }
	   if(cnt==n)
	   {
		  EXITEDSTATE=1; 
		  
	   }
}
int main()
{


        READYQ =(struct Queue*) malloc(sizeof(struct Queue));
	printf("How Many Process to schdeule:?");
	scanf("%d",&n);
	printf("\n Time Quantum :: ?");
	scanf("%d",&TQtm);
	proc_arr=(struct Process_represent *)malloc(sizeof(struct Process_represent)*n);
	for(i=0;i<n;i++)
	{
             proc_arr[i].pid=i+1;
	     printf("\n Enter arrival time For %d Process",(i+1));
	     scanf("%d",&(proc_arr[i].at));
	     printf("\n Enter Execution time For %d Process",(i+1));
	     scanf("%d",&(proc_arr[i].timeleft)); 
	     
            proc_arr[i].exect=proc_arr[i].timeleft;
	    proc_arr[i].state=NEW;
	        
	}
 struct Process_represent key; 
    
    for (i = 1; i < n; i++) { 
        key = proc_arr[i]; 
        j = i - 1; 
  
        while (j >= 0 && proc_arr[j].at > key.at) { 
            proc_arr[j + 1] = proc_arr[j]; 
            j = j - 1; 
        } 
        proc_arr[j + 1] = key; 
    } 

struct Process_represent *pr;
while(1)
{
        Add_Arrived_procs();
        if(EXITEDSTATE==1)
        {

                    break;      
        }
        
        if(READYQ->front!=NULL && SWITCH_PROCESS==1)
	{
             rtp=1;
	     pr=deQueue();
             pr->state=RUNNING;
             pr->timeleft--;
	     st++;
             if(rtp==pr->exect)
             {
                  SWITCH_PROCESS=1;
                  pr->state=EXIT;
                  pr->ct=st;
                  pr->tat=st-pr->at;
                  pr->wt=pr->tat-pr->exect;
             }
             else
            {
               SWITCH_PROCESS=0;
              }
	}
        else if(SWITCH_PROCESS==0&&pr!=NULL && pr->state==RUNNING )
	{
             if(pr->timeleft==0)
             {
                  SWITCH_PROCESS=1;
                  pr->state=EXIT;
                  pr->ct=st;
                  pr->tat=st-(pr->at);
                  pr->wt=(pr->tat)-(pr->exect);
                  continue;
             }      
             rtp++;
             pr->timeleft--;
            st++;

             if(pr->timeleft==0)
             {
                  SWITCH_PROCESS=1;
                  pr->state=EXIT;
                  pr->ct=st;
                  pr->tat=st-(pr->at);
                  pr->wt=(pr->tat)-(pr->exect);
             }            
             else if(rtp==TQtm)
             {
                pr->state=READY;
                enqueue(pr);
                SWITCH_PROCESS=1;
              }
            else
          { 
              SWITCH_PROCESS=0;
	  }

          
             
          
	}
else
{
st++;
}
}
int sumwt=0,sumtat=0;
for(i=0;i<n;i++)
	{
           printf("\n\nprocess [pid=%d]\t[ct=%d]\t[tat=%d]\t[wt=%d]",proc_arr[i].pid,proc_arr[i].ct,proc_arr[i].tat,proc_arr[i].wt);
           sumwt+=proc_arr[i].wt;
           sumtat+=proc_arr[i].tat;
           
	}
printf("\n\n Avergae TAT=[%f] \t Average WT=[%f]",(sumtat/(n*1.0)),(sumwt/(n*1.0)));
}
