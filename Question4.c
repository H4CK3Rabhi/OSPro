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

int nowtime=0,timeinrunning=0,EXIT_PROCESS_STATUS=0,DO_CT=1,n,i,j;
struct Process_Cont_struct 
{
	int pid;
	int state;
	int timeleft;
	int at;
	float priority;
	int timeinwt;
	int wt,tat,ct,exect;
	struct Process_Cont_struct *prev;
	struct Process_Cont_struct *next;
} *process_all;
struct Queue
{
	struct Process_Cont_struct *left ,*right;
}*RQ;

void enqueue(struct Process_Cont_struct *proc)
{
	if(RQ->left==NULL)
	{
		RQ->left=proc;
		RQ->right=proc;
		proc->next=NULL;
	}
        
	else
	{
		if(proc->priority>RQ->left->priority)
		{
			proc->next=RQ->left;
			RQ->left->prev=proc;
			RQ->left=proc;
		}
               else if(proc->priority==RQ->left->priority)
		{
			proc->next=RQ->left->next;
			proc->prev=RQ->left;
			RQ->left->next=proc;
                         if(proc->next!=NULL)
                      {
                        proc->next->prev=proc;
                      }
		}
		else if(proc->priority<RQ->right->priority)
		{
			proc->next=NULL;
			RQ->right->next=proc;
			proc->prev=RQ->right;
			RQ->right=proc;
		}
		else
		{
                   struct Process_Cont_struct *start=RQ->left->next;
		   while(start->priority>proc->priority)
		   {
			   start=start->next;
		   }
                   if(start!=NULL&& proc->priority==start->priority)
                   {
                          proc->next=start->next;
                          start->next=proc;
                          proc->prev=start;
                      
                   }
                  else
               {
		   (start->prev)->next=proc;
		   proc->next=start;
		   proc->prev=start->prev;
		   start->prev=proc;
                }

		}
	}
}
struct Process_Cont_struct *  deQueue()
{
     if(RQ->left==NULL)
     {
	     return NULL;
     }
     struct Process_Cont_struct * temp=RQ->left;
     RQ->left=RQ->left->next;
     temp->next=NULL;
     if(RQ->left==NULL)
     {
	     RQ->right=NULL;
     }
     return temp;
}
void UPQ()
{
int counter=0;
           for(i=0;i<n;i++)
	   {
                   
		   if(process_all[i].state == NEW && nowtime>=process_all[i].at)
		   {      
			   
			   enqueue(&process_all[i]);
			   process_all[i].state=READY;
			   
                    }
                  if(process_all[i].state==EXIT)
                  {
                    counter++;
			}
	   }
	   if(counter==n)
	   {
		  EXIT_PROCESS_STATUS=1; 
		  
	   }
}
int main()
{


RQ =(struct Queue*) malloc(sizeof(struct Queue));
	printf("Please Enter No of Processes to schedule :::");
	scanf("%d",&n);
	process_all=(struct Process_Cont_struct *)malloc(sizeof(struct Process_Cont_struct)*n);
	for(i=0;i<n;i++)
	{
             printf("\n\n Enter Process Id For %d Process ::: ",(i+1));
	     scanf("%d",&(process_all[i].pid));
	     printf("\n Enter arrival time For %d Process ::: ",(i+1));
	     scanf("%d",&(process_all[i].at));
	     printf("\n Enter Execution time For %d Process ::: ",(i+1));
	     scanf("%d",&(process_all[i].timeleft)); 
	     
            process_all[i].exect=process_all[i].timeleft;
	    process_all[i].state=NEW;
	        
	}
 struct Process_Cont_struct key; 
    for (i = 1; i < n; i++) { 
        key = process_all[i]; 
        j = i - 1; 
  
        while (j >= 0 && process_all[j].at > key.at) { 
            process_all[j + 1] = process_all[j]; 
            j = j - 1; 
        } 
        process_all[j + 1] = key; 
    } 
printf("\n\nGannt Chart ******\n-------------------------------------------------------------------------------------------------------------------------------------------------\n");
struct Process_Cont_struct *pr,*prev;
while(1)
{
        UPQ();
	
        if(EXIT_PROCESS_STATUS==1)
        {

                    break;      
        }
        
        if(RQ->left!=NULL && DO_CT==1)
	{
             timeinrunning=1;
             prev=pr;
	     pr=deQueue();
             if(prev!=pr)
            {
               printf("%d ] Process%d [",nowtime,pr->pid);
            }
             pr->state=RUNNING;
             pr->timeleft--;
	     nowtime++;
             for(i=0;i<n;i++)
	     {
		if(process_all[i].state==READY&&process_all[i].timeleft>0)
		{
                  process_all[i].timeinwt++;
                  process_all[i].priority=1+process_all[i].timeinwt/process_all[i].timeleft;   
		}
	     }
             if(timeinrunning==pr->exect)
             {
                  DO_CT=1;
                  pr->state=EXIT;
                  pr->ct=nowtime;
                  pr->tat=nowtime-pr->at;
                  pr->wt=pr->tat-pr->exect;
             }
             else
            {
               DO_CT=0;
              }
	}
        else if(DO_CT==0&&pr!=NULL && pr->state==RUNNING )
	{
             if(pr->timeleft==0)
             {
                  DO_CT=1;
                  pr->state=EXIT;
                  pr->ct=nowtime;
                  pr->tat=nowtime-(pr->at);
                  pr->wt=(pr->tat)-(pr->exect);
                  continue;
             }      
             timeinrunning++;
             pr->timeleft--;
            nowtime++;
             for(i=0;i<n;i++)
	     {
		if(process_all[i].state==READY&&process_all[i].timeleft>0)
		{
                  process_all[i].timeinwt++;
                  process_all[i].priority=1+process_all[i].timeinwt/process_all[i].timeleft;   
		}
	     }
             if(pr->timeleft==0)
             {
                  DO_CT=1;
                  pr->state=EXIT;
                  pr->ct=nowtime;
                  pr->tat=nowtime-(pr->at);
                  pr->wt=(pr->tat)-(pr->exect);
             }            
            else
          { 
              DO_CT=0;
	  }

          
             
          
	}
else
{
printf("%d] IDLE [",nowtime);
nowtime++;
}
}
printf("%d\n",nowtime);
printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");
int sumwt=0,sumtat=0;
for(i=0;i<n;i++)
	{
           printf("\n\nprocess pid=%d\tct=%d\ttat=%d\twt=%d",process_all[i].pid,process_all[i].ct,process_all[i].tat,process_all[i].wt);
           sumwt+=process_all[i].wt;
           sumtat+=process_all[i].tat;
           
	}
printf("\n\n Avergae TAT=%f \t Average WT=%f\n",(sumtat/(n*1.0)),(sumwt/(n*1.0)));
}
