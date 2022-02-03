#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/shm.h>
#include<unistd.h>
int main()
{
     int shmid=shmget((key_t)7888,1000,0666|IPC_CREAT);
     void * sharedm;
     sharedm=shmat(shmid,NULL,0);
     char s[100];
     read(1,s,100);
     strcpy(sharedm,s);
}
