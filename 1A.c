#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
     
     int fd[2];	
     int p=fork();
     if(p>0)
     {
	   close(fd[1]);
	   char s[100];
	   read(fd[0],s,100);
	   printf("%s",s);
     }
     else if(p==0)
     {
	     close(fd[0]);
	     write(fd[1],"written",7);
     }
     else
     {
	     printf("error in fork");
     }


}
