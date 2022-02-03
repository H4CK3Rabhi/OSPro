#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/shm.h>

int main()
{
     int shmid=shmget((key_t)7888,1000,0666);
     void * sharedm;
     sharedm=shmat(shmid,NULL,0);
     printf("%s",sharedm);
}
