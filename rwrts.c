
#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
  
pthread_t tid[8]; 
int counter; 
pthread_mutex_t lock,wrt; 
 int readcnt;
int rdrs_wrts[8]={2,2,2,1,1,1,1,1};
int qty=1;
void* trythis(void* arg) 
{ 
   int i=*((int *)arg);  
    do {
    
   // Reader wants to enter the critical section
    pthread_mutex_lock(&lock); 

   // The number of readers has now increased by 1
   readcnt++;                          
  

   if (readcnt==1)     
       pthread_mutex_lock(&wrt); 
        if(rdrs_wrts[i]==2)
{
  printf("writer %d has stopped writing\n",(i+1));
}                   
         
   // other readers can enter while this current reader is inside 
   // the critical section
    pthread_mutex_unlock(&lock);                    
if(rdrs_wrts[i]==1)
{
  printf("Reader %d has started reading\n",(i-2));
}
sleep(1);
   // current reader performs reading here
    pthread_mutex_lock(&lock);   // a reader wants to leave
    if(rdrs_wrts[i]==1)
{
  printf("Reader %d has stopped reading\n",(i-2));
}

   readcnt--;

   // that is, no reader is left in the critical section,
   if (readcnt == 0) 
        pthread_mutex_unlock(&wrt); 
          if(rdrs_wrts[i]==2)
{
  printf("writer %d has started writing\n",(i+1));
}       // writers can enter
    
    pthread_mutex_unlock(&lock);
 // reader leaves

qty++; //counter for loop;

} while(qty<=40);
    
  
    return NULL; 
} 
  
int main(void) 
{ 
    int i = 0; 
    int error; 
  
    if (pthread_mutex_init(&lock, NULL) != 0) { 
        printf("\n mutex init has failed\n"); 
        return 1; 
    } 
    
    while (i < 8) { 
        error = pthread_create(&(tid[i]), 
                               NULL, 
                               &trythis, &i); 
        if (error != 0) 
            printf("\nThread can't be created :[%s]", 
                   strerror(error)); 
        i++; 
    } 
i=0;
 while (i < 8) { 
        pthread_join(tid[i], NULL); 
        
    } 
  
    
    
  
    return 0; 
} 

