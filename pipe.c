#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
int main()
{
	int res;
	res=open("fifo1",O_WRONLY);
	write(res,"written",7);
	printf("writtedn to pipe %d",getpid());
sleep(10);
}
