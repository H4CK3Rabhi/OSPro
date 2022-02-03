#include<stdlib.h>
#include<unistd.h>
int main()
{
char s[60];
int n=read(1,s,60);// reading from console
write(1,s,n);//writing to console
return 0;
}
