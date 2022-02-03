#include<stdlib.h>
#include<unistd.h>//system call are defined here(read,write,fork ..etc)
#include<fcntl.h>// file control(open,close sys calls)
#include<sys/types.h>//Macros are defined here =O_CREAT,O_RDWR etc
int main()
{
int fid=open("new.txt",O_CREAT|O_RDWR,0777);// open a file
//O_CREAT=Create if Not exists 
// O_RDWR=open in read and write mode
// O_RDONLY=Read mode
// O_WR_ONLY=Write mode
// 0777=permissions
char s[50];
int n=read(1,s,50);//read from console
write(fid,s,n);//write to file
close(fid);//close file
return 0;
}
