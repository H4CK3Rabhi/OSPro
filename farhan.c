#include<pthread.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#define NEW 0
#define READY 1
#define WAITING 2
#define RUNNING 3
#define EXIT 4

int currenttime=0,runningtime=0,ALLEXIT=0,TimeQuantum,CT=1,n;
struct Proc 
{
	int pid;
	int state;
	int timeleft;
	int at;
        int ae;
	int wt,tat,ct,exect;
	struct Proc *prev;
	struct Proc *next;
} *pa;
struct Queue
{
	struct Proc *front ,*rear;
}*ReadyQueue;

void SortTimeleft()
{
    for(int i=1;i<n;i++)
    {
        for(int j=0;j<n-i;j++)
        {
            if(pa[j].timeleft > pa[j+1].timeleft)
             {
                struct Proc temp = pa[j];
               pa[j]=pa[j+1];
                pa[j+1]=temp;
            }
        }
    }

}
void enqueue(struct Proc *p)
{
	 if(ReadyQueue->front==NULL)
      { 
         p->prev=NULL;

         p->next=NULL;
         ReadyQueue->front=p;           
         ReadyQueue->rear=p;
         return;
      }
     p->prev=ReadyQueue->rear;
     ReadyQueue->rear->next=p;
     ReadyQueue->rear=p;
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
void checkqueue()
{
int count=0;
           for(int i=0;i<n;i++)
	   {
                   
		   if(pa[i].state == NEW && currenttime>=pa[i].at)
		   {      
			   
			   enqueue(&pa[i]);
			   pa[i].state=READY;
			   
                    }
                  if(pa[i].state==EXIT)
                  {
                    count++;
			}
	   }
	   if(count==n)
	   {
		  ALLEXIT=1; 
		  
	   }
}
int main()
{


ReadyQueue =(struct Queue*) malloc(sizeof(struct Queue));
	printf("Please enter No of processes to schedule");
	scanf("%d",&n);
	printf("\n Please Enter Time qunatum");
	scanf("%d",&TimeQuantum);
	pa=(struct Proc *)malloc(sizeof(struct Proc)*n);
	for(int i=0;i<n;i++)
	{
             printf("\n\n Enter Process Id For %d Process",(i+1));
	     scanf("%d",&(pa[i].pid));
	     printf("\n Enter arrival time For %d Process",(i+1));
	     scanf("%d",&(pa[i].at));
	     printf("\n Enter Execution time For %d Process",(i+1));
	     scanf("%d",&(pa[i].timeleft)); 
	     
            pa[i].exect=pa[i].timeleft;
	    pa[i].state=NEW;
	        
	}
 struct Proc key; 
    int i,j;
    for (i = 1; i < n; i++) { 
        key = pa[i]; 
        j = i - 1; 
  
        while (j >= 0 && pa[j].at > key.at) { 
            pa[j + 1] = pa[j]; 
            j = j - 1; 
        } 
        pa[j + 1] = key; 
    } 
int ps=0;
struct Proc *pr;
struct Proc *prev;
printf("\nGannt Chart===");
printf("\n=========================================================================================================================================\n");
while(1)
{
        checkqueue();
        if(ALLEXIT==1 || (ps==n&CT==1))
        {

                    break;      
        }
        
        if(ReadyQueue->front!=NULL && CT==1)
	{
              prev=pr;
             runningtime=1;
	     pr=deQueue();
             if(pr!=prev)
             {
                 printf(" [%d] | Process %d |",currenttime,pr->pid);
             }
             pr->state=RUNNING;
             if(pr->ae!=1)
             {
                 ps++;
                 pr->ae=1;
             }
             pr->timeleft--;
	     currenttime++;
             if(runningtime==pr->exect)
             {
                  CT=1;
                  pr->state=EXIT;
                  pr->ct=currenttime;
                  pr->tat=currenttime-pr->at;
                  pr->wt=pr->tat-pr->exect;
             }
             else
            {
               CT=0;
              }
	}
        else if(CT==0&&pr!=NULL && pr->state==RUNNING )
	{
             if(pr->timeleft==0)
             {
                  CT=1;
                  pr->state=EXIT;
                  pr->ct=currenttime;
                  pr->tat=currenttime-(pr->at);
                  pr->wt=(pr->tat)-(pr->exect);
                  continue;
             }      
             runningtime++;
             pr->timeleft--;
            currenttime++;

             if(pr->timeleft==0)
             {
                  CT=1;
                  pr->state=EXIT;
                  pr->ct=currenttime;
                  pr->tat=currenttime-(pr->at);
                  pr->wt=(pr->tat)-(pr->exect);
             }            
             else if(runningtime==TimeQuantum)
             {
                pr->state=READY;
                enqueue(pr);
                CT=1;
              }
            else
          { 
              CT=0;
	  }

          
             
          
	}
else
{
printf("[%d]| IDLE |",currenttime);
currenttime++;
}
}
SortTimeleft();
for(int i=0;i<n;i++)
{
        if(pa[i].state==READY)
        {
               printf("[%d]| Process %d |",currenttime,pa[i].pid);
               currenttime+=pa[i].timeleft;
               pa[i].ct=currenttime;
               pa[i].state=EXIT;
               pa[i].tat=pa[i].ct-pa[i].at;
               pa[i].wt=pa[i].tat-pa[i].exect;
         }
}
printf("[%d]",currenttime);
printf("\n=============================================================================================================================================\n");
int sumwt=0,sumtat=0;
for(int i=0;i<n;i++)
	{
           printf("\n\nprocess pid=%d =::= ct=%d\ttat=%d\twt=%d",pa[i].pid,pa[i].ct,pa[i].tat,pa[i].wt);
           sumwt+=pa[i].wt;
           sumtat+=pa[i].tat;
           
	}
printf("\n\n Avergae TAT=%f \n Average WT=%f\n",(sumtat/(n*1.0)),(sumwt/(n*1.0)));
}
