#include<stdio.h>

int main()
{
     int len=0;
     char x[20],x1[20];
       scanf("%s %s",&x,&x1);
     while(x[len]!='\0')
     {
           len++;
       }
    int i=0;
     while(x1[i]!='\0')
     {
        x[len+i]=x1[i];
i++;
      }
     printf("%s",x);
}
