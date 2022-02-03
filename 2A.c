#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

int main()
{
          int i;
	int fd=open("f1.txt",O_RDONLY,0777);
	int pos=lseek(fd,0,SEEK_END);
	for(i=pos-1;i>=0;i--)
	{       
               lseek(fd,i,SEEK_SET);
		char s[2];
		read(fd,s,1);
		write(1,s,1);
	       
	}
}
