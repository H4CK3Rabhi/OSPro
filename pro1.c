#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

int main()
{
	char s[100];
	int fd=open("f1.txt",O_RDONLY,0777);
	int fd2=open("f2.txt",O_CREAT|O_WRONLY,0777);
	lseek(fd,15,SEEK_SET);
	read(fd,s,5);
	write(fd2,s,5);
	close(fd);
	close(fd2);
}
