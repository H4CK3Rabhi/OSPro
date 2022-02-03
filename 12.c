#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

int main()
{

	int fd=open("f1.txt",O_CREAT|O_RDONLY,0777);
	int fd2=open("f2.txt",O_CREAT|O_WRONLY,0777);
	char s[12];
	lseek(fd,-10,SEEK_END);
        read(fd,s,10);
	write(fd2,s,10);
	printf("%d %s",sizeof(fd2),s);
}
