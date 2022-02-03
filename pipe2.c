#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
int main()
{
	int res,n;
	char vuff[100];
	res=open("fifo1",O_RDONLY);
	n=read(res,vuff,100);
	
	write(1,vuff,7);
	printf("%d\n",getpid());
}
