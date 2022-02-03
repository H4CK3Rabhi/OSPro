#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
int main()
{
int fid=open("new.txt",O_CREAT|O_RDWR,0777);
char s[50];
int n=read(1,s,50);
lseek(fid,-2,SEEK_END);
write(fid,s,n);
close(fid);
return 0;
}
