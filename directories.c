#include<stdio.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
// show all Contents of a pre existing directory
//Coder:Abhishek Sharma(Github: @H4CK3Rabhi)

int main()
{
	DIR* dir;
	struct dirent *de;
	char name[100];
	scanf("%s",name);
	dir=opendir(name);
	if(dir==0)
	{
		printf("Error is opening directory");
		exit(1);
	}
	while((de=readdir(dir))!=0)
	{
		printf("Directory is %s",de->d_name);
   		printf("Inode no is:%ld Size:%d Type is %c \n",de->d_ino,de->d_reclen,de->d_type);
	}
}
