#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/shm.h>

int main()
{
	int k;
	void *sh_m;
	char s[100];
	int shmid=shmget((key_t)2222,1000,0666|IPC_CREAT);
	printf("Key of shm is %d\n",shmid);
	sh_m=shmat(shmid,NULL,0);
	printf("Process attached at %X\n",(int)sh_m);
	read(0,s,100);
	strcpy(sh_m,s);
}

