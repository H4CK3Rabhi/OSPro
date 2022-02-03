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
#define SRT 0
#define RR 1

int currenttime=0,runningtime=0,ALLEXIT=0,CT=1,n,CURRMODE=RR,ALREADYRUNNING=0,TimeQuantum;
struct Proc 
{
	int pid;
	int state;
	int timeleft;
	int at;
	int wt,tat,ct,exect,qno;
	struct Proc *prev;
	struct Proc *next;
} *pa;
struct Queue
{
	struct Proc *front ,*rear;
}*ReadyQueue1,*ReadyQueue2;

void enqueuep(struct Proc *p)
{
	if(ReadyQueue1->front==NULL)
	{
		ReadyQueue1->front=p;
		ReadyQueue1->rear=p;
		p->next=NULL;
	}
        
	else
	{
		if(p->timeleft<ReadyQueue1->front->timeleft)
		{
			p->next=ReadyQueue1->front;
			ReadyQueue1->front->prev=p;
			ReadyQueue1->front=p;
		}
               else if(p->timeleft==ReadyQueue1->front->timeleft)
		{
			p->next=ReadyQueue1->front->next;
			p->prev=ReadyQueue1->front;
			ReadyQueue1->front->next=p;
                        if(p->next!=NULL)
                      {
                        p->next->prev=p;
		      }
                }
		else if(p->timeleft>ReadyQueue1->rear->timeleft)
		{
			p->next=NULL;
			ReadyQueue1->rear->next=p;
			p->prev=ReadyQueue1->rear;
			ReadyQueue1->rear=p;
		}
		else
		{
                   struct Proc *start=ReadyQueue1->front->next;
		   while(start->timeleft<p->timeleft)
		   {
			   start=start->next;
		   }
                   if(start!=NULL&& p->timeleft==start->timeleft)
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
struct Proc *  deQueuep()
{
     if(ReadyQueue1->front==NULL)
     {
	     return NULL;
     }
     struct Proc * temp=ReadyQueue1->front;
     ReadyQueue1->front=ReadyQueue1->front->next;
     temp->next=NULL;
     if(ReadyQueue1->front==NULL)
     {
	     ReadyQueue1->rear=NULL;
     }
     return temp;
}

void enqueue(struct Proc *p)
{
      if(ReadyQueue2->front==NULL)
      { 
         p->prev=NULL;

         p->next=NULL;
         ReadyQueue2->front=p;           
         ReadyQueue2->rear=p;
         return;
      }
     p->prev=ReadyQueue2->rear;
     ReadyQueue2->rear->next=p;
     ReadyQueue2->rear=p;
}
struct Proc * deQueue()
{
if(ReadyQueue2->front==NULL)
     {
	     return NULL;
     }
     struct Proc * temp=ReadyQueue2->front;
     ReadyQueue2->front=ReadyQueue2->front->next;
     temp->next=NULL;
     if(ReadyQueue2->front==NULL)
     {
	     ReadyQueue2->rear=NULL;
     }
     return temp;
}
void updateQueue()
{
           int count=0;
           for(int i=0;i<n;i++)
	   {
                   
		   if(pa[i].state == NEW && currenttime>=pa[i].at)
		   {      
			   if(pa[i].qno==1)
                           {
			       enqueuep(&pa[i]);
			       pa[i].state=READY;
			   }
                           else if(pa[i].qno==2)
                          {
                                enqueue(&pa[i]);
                                pa[i].state=READY;
                          }
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
        ReadyQueue1 =(struct Queue*) malloc(sizeof(struct Queue));
        ReadyQueue2 =(struct Queue*) malloc(sizeof(struct Queue));
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

	     printf("\n Enter QueueNo For %d Process",(i+1));
	     scanf("%d",&(pa[i].qno)); 
           
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
       
        struct Proc *pr=NULL;
       while(1)
       {
            updateQueue();
            if(ALLEXIT)
            {
                  break;
            }
           if(ReadyQueue1->front!=NULL &&  ALREADYRUNNING==0)
           {
                    if(pr!=NULL && pr->qno==2)
                    {
                        enqueue(pr);
                        pr->state=READY;
                        pr=NULL;
                     }
                      
		    CURRMODE=SRT;
                     runningtime=1;
	     	     pr=deQueuep();
             	     pr->state=RUNNING;
             	     pr->timeleft--;
	             currenttime++;
                    if(runningtime==pr->exect)
                    {
                  	CT=1;
                        ALREADYRUNNING =0;
                  	pr->state=EXIT;
                  	pr->ct=currenttime;
                  	pr->tat=currenttime-pr->at;
                        pr->wt=pr->tat-pr->exect;
                        pr=NULL;
           
                    }
                    else
                    {
                       CT=0;
                       ALREADYRUNNING=1;
                     }
            }
          else if(ReadyQueue2->front!=NULL&& ReadyQueue1->front==NULL && pr==NULL && CT==1)
         {
                     CURRMODE=RR;
                     runningtime=1;
	     	     pr=deQueue();
             	     pr->state=RUNNING;
             	     pr->timeleft--;
	             currenttime++;
                    if(runningtime==pr->exect)
                    {
                  	CT=1;
                  	pr->state=EXIT;
                  	pr->ct=currenttime;
                  	pr->tat=currenttime-pr->at;
                        pr->wt=pr->tat-pr->exect;
                        pr=NULL;
           
                    }
                    else
                    {
                       CT=0;
                     }                 
         }
         else if(pr!=NULL && pr->qno==1 && CT==0&&pr->state==RUNNING)
         {
                  
                     if(pr->timeleft==0)
             {
                  CT=1;
                  ALREADYRUNNING=0;
                  pr->state=EXIT;
                  pr->ct=currenttime;
                  pr->tat=currenttime-(pr->at);
                  pr->wt=(pr->tat)-(pr->exect);
                  pr=NULL;
                  continue;
             }  
         
		if(ReadyQueue1->front!=NULL)
             {
               if(pr->timeleft>ReadyQueue1->front->timeleft)
               {
                pr->state=READY;
                enqueuep(pr);
                ALREADYRUNNING=0;
                pr=NULL;
                CT=1;
               continue;
               }
             }    
             runningtime++;
             pr->timeleft--;
            currenttime++;

             if(pr->timeleft==0)
             {
                  CT=1;
                  ALREADYRUNNING=0;
                  pr->state=EXIT;
                  pr->ct=currenttime;
                  pr->tat=currenttime-(pr->at);
                  pr->wt=(pr->tat)-(pr->exect);
                  pr=NULL;
             }            
             else if(ReadyQueue1->front!=NULL)
             {
               if(pr->timeleft>ReadyQueue1->front->timeleft)
               {
                pr->state=READY;
                enqueuep(pr);
                ALREADYRUNNING=0;
                pr=NULL;
                CT=1;
               }
               else
               {
                  CT=0;
                 ALREADYRUNNING=1;
               }
              }
            else
          { 
              CT=0;
             ALREADYRUNNING=1;
	  }            
         }
         else if(pr!=NULL && pr->qno==2&& pr->state==RUNNING && CT==0)
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
                pr=NULL;
                CT=1;
              }
            else
          { 
              CT=0;
	  }
         }
        else
        {
          currenttime++;
         }
                 
       }
      int sumwt=0,sumtat=0;
for(int i=0;i<n;i++)
	{
           printf("\n\nprocess pid=%d\nct=%d\ntat=%d\nwt=%d",pa[i].pid,pa[i].ct,pa[i].tat,pa[i].wt);
           sumwt+=pa[i].wt;
           sumtat+=pa[i].tat;
           
	}
printf("\n\n Avergae TAT=%f \n Average WT=%f",(sumtat/(n*1.0)),(sumwt/(n*1.0)));
}
