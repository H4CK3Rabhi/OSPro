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
