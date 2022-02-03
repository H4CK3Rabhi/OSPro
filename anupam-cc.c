#include<stdio.h>
#include<stdlib.h>

#define NEW 0
#define READY 1
#define WAITING 2
#define RUNNING 3
#define EXIT 4

int instancetime=0,runningtime=0,EXITED=0,Context_Switch_Allowed=1,n,i,j;
struct Process 
{
	int pid;
	int state;
	int timeleft;
	int at;
	int wt,tat,ct,exect;
	struct Process *prev;
	struct Process *next;
} *process_array,*process_array1;

struct Queue
{
	struct Process *front ,*rear;
}*Ready;
void put_in_Queue1(struct Process *p)
{
	if(Ready->front==NULL)
	{
		Ready->front=p;
		Ready->rear=p;
		p->next=NULL;
	}
        
	else
	{
		if(p->timeleft<Ready->front->timeleft)
		{
			p->next=Ready->front;
			Ready->front->prev=p;
			Ready->front=p;
		}
               else if(p->timeleft==Ready->front->timeleft)
		{
			p->next=Ready->front->next;
			p->prev=Ready->front;
			Ready->front->next=p;
                         if(p->next!=NULL)
                      {
                        p->next->prev=p;
                      }
		}
		else if(p->timeleft>Ready->rear->timeleft)
		{
			p->next=NULL;
			Ready->rear->next=p;
			p->prev=Ready->rear;
			Ready->rear=p;
		}
		else
		{
                   struct Process *start=Ready->front->next;
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

void put_in_Queue(struct Process *p)
{
	if(Ready->front==NULL)
	{
		Ready->front=p;
		Ready->rear=p;
		p->next=NULL;
	}
        
	else
	{
		if(p->timeleft>Ready->front->timeleft)
		{
			p->next=Ready->front;
			Ready->front->prev=p;
			Ready->front=p;
		}
               else if(p->timeleft==Ready->front->timeleft)
		{
			p->next=Ready->front->next;
			p->prev=Ready->front;
			Ready->front->next=p;
                         if(p->next!=NULL)
                      {
                        p->next->prev=p;
                      }
		}
		else if(p->timeleft<Ready->rear->timeleft)
		{
			p->next=NULL;
			Ready->rear->next=p;
			p->prev=Ready->rear;
			Ready->rear=p;
		}
		else
		{
                   struct Process *start=Ready->front->next;
		   while(start->timeleft>p->timeleft)
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
struct Process *  get_from_queue()
{
     if(Ready->front==NULL)
     {
	     return NULL;
     }
     struct Process * temp=Ready->front;
     Ready->front=Ready->front->next;
     temp->next=NULL;
     if(Ready->front==NULL)
     {
	     Ready->rear=NULL;
     }
     return temp;
}
void up_queue()
{
int count=0;
           for(i=0;i<n;i++)
	   {
                   
		   if(process_array[i].state == NEW && instancetime>=process_array[i].at)
		   {      
			   
			   put_in_Queue(&process_array[i]);
			   process_array[i].state=READY;
			   
                    }
                  if(process_array[i].state==EXIT)
                  {
                    count++;
			}
	   }
	   if(count==n)
	   {
		  EXITED=1; 
		  
	   }
}
void up_queue1()
{
int count=0;
           for(i=0;i<n;i++)
	   {
                   
		   if(process_array1[i].state == NEW && instancetime>=process_array1[i].at)
		   {      
			   
			   put_in_Queue1(&process_array1[i]);
			   process_array1[i].state=READY;
			   
                    }
                  if(process_array1[i].state==EXIT)
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


Ready =(struct Queue*) malloc(sizeof(struct Queue));
	printf("Please enter No of processes to schedule");
	scanf("%d",&n);
	process_array=(struct Process *)malloc(sizeof(struct Process)*n);
	process_array1=(struct Process *)malloc(sizeof(struct Process)*n);
	for(i=0;i<n;i++)
	{
             printf("\n\n Enter Process Id For %d Process",(i+1));
	     scanf("%d",&(process_array[i].pid));
	     printf("\n Enter arrival time For %d Process",(i+1));
	     scanf("%d",&(process_array[i].at));
	     process_array[i].timeleft=process_array[i].at*2; 
	     
            process_array[i].exect=process_array[i].timeleft;
	    process_array[i].state=NEW;
	    process_array1[i]=process_array[i];
	        
	}
 struct Process key; 
    
    for (i = 1; i < n; i++) { 
        key = process_array[i]; 
        j = i - 1; 
  
        while (j >= 0 && process_array[j].at > key.at) { 
            process_array[j + 1] = process_array[j]; 
            j = j - 1; 
        } 
        process_array[j + 1] = key; 
    } 

struct Process *pr;
struct Process *prev;

while(1)
{
        up_queue();
        if(EXITED==1)
        {

                    break;      
        }
        
        if(Ready->front!=NULL && Context_Switch_Allowed==1)
	{
             runningtime=1;
	     prev=pr;
	     pr=get_from_queue();
	    
             pr->state=RUNNING;
             pr->timeleft--;
	     instancetime++;
             if(runningtime==pr->exect)
             {
                  Context_Switch_Allowed=1;
                  pr->state=EXIT;
                  pr->ct=instancetime;
                  pr->tat=instancetime-pr->at;
                  pr->wt=pr->tat-pr->exect;
             }
             else
            {
               Context_Switch_Allowed=0;
              }
	}
        else if(Context_Switch_Allowed==0&&pr!=NULL && pr->state==RUNNING )
	{
             if(pr->timeleft==0)
             {
                  Context_Switch_Allowed=1;
                  pr->state=EXIT;
                  pr->ct=instancetime;
                  pr->tat=instancetime-(pr->at);
                  pr->wt=(pr->tat)-(pr->exect);
                  continue;
             }      
             runningtime++;
             pr->timeleft--;
            instancetime++;

             if(pr->timeleft==0)
             {
                  Context_Switch_Allowed=1;
                  pr->state=EXIT;
                  pr->ct=instancetime;
                  pr->tat=instancetime-(pr->at);
                  pr->wt=(pr->tat)-(pr->exect);
             }            
          
            else
          { 
              Context_Switch_Allowed=0;
	  }

          
             
          
	}
else
{

instancetime++;
}
}
printf("%d\n",instancetime);
pr=NULL;
prev=NULL;
instancetime=0;
Context_Switch_Allowed=1;
Ready->front=Ready->rear=NULL;
EXITED=0;

while(1)
{
        up_queue1();
        if(EXITED==1)
        {

                    break;      
        }
        
        if(Ready->front!=NULL && Context_Switch_Allowed==1)
	{
             runningtime=1;
	     prev=pr;
	     pr=get_from_queue();
             pr->state=RUNNING;
             pr->timeleft--;
	     instancetime++;
             if(runningtime==pr->exect)
             {
                  Context_Switch_Allowed=1;
                  pr->state=EXIT;
                  pr->ct=instancetime;
                  pr->tat=instancetime-pr->at;
                  pr->wt=pr->tat-pr->exect;
             }
             else
            {
               Context_Switch_Allowed=0;
              }
	}
        else if(Context_Switch_Allowed==0&&pr!=NULL && pr->state==RUNNING )
	{
             if(pr->timeleft==0)
             {
                  Context_Switch_Allowed=1;
                  pr->state=EXIT;
                  pr->ct=instancetime;
                  pr->tat=instancetime-(pr->at);
                  pr->wt=(pr->tat)-(pr->exect);
                  continue;
             }      
             runningtime++;
             pr->timeleft--;
            instancetime++;

             if(pr->timeleft==0)
             {
                  Context_Switch_Allowed=1;
                  pr->state=EXIT;
                  pr->ct=instancetime;
                  pr->tat=instancetime-(pr->at);
                  pr->wt=(pr->tat)-(pr->exect);
             }            
          
            else
          { 
              Context_Switch_Allowed=0;
	  }

          
             
          
	}
else
{

instancetime++;
}
}
printf("Run Using LJF");
int sumwt=0,sumtat=0,sumsjt=0,sumsjw=0;
for(i=0;i<n;i++)
	{
           printf("\n\nprocess pid=%d\nct=%d\ntat=%d\nwt=%d",process_array[i].pid,process_array[i].ct,process_array[i].tat,process_array[i].wt);
           sumwt+=process_array[i].wt;
           sumtat+=process_array[i].tat;
	   sumsjt+=process_array1[i].tat;
	   sumsjw+=process_array1[i].wt;
           
	}
printf("\n\nLJF: Avergae TAT=%f \t Average WT=%f\n SJF: Average TAT=%f Average WT=%f\n",(sumtat/(n*1.0)),(sumwt/(n*1.0)),(sumsjt/(n*1.0)),(sumsjw/(n*1.0)));
}

