#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
int main()
{
int fid=open("Myf",O_APPEND,0777);
//lseek(fid,7,SEEK_SET);
char s[13];
int n=read(1,s,13);
write(fid,s,n);

}
