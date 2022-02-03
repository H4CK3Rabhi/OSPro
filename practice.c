//#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
char s[60];
//printf("%c",s[61]);
int n=read(1,s,60);
write(1,s,n);
return 0;
}
