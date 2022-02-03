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
int n=read(fid,s,10);//read from 1st-10th charcters from file to s

write(1,s,n);//write to console

lseek(fid,-5,SEEK_CUR);//Go back 5 characters from current(positive means forward negative means backwords cursor movement)
//Possible flags:
//SEEK_CUR=from current cursor position
//SEEK_SET=from start(only takes + values as previous argument i.e. can move only forward from start
//SEEK_END=from End (can only take negitive values)

n=read(fid,s,10);// read from 5th-15th characters in file
write(1,s,n);
close(fid);//close file
return 0;
}
