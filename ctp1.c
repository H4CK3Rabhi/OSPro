#include<stdio.h>

int main()
{
   char x[20];
   scanf("%s",&x);
   int i=0;
          while(x[i]!='\0')
   {
	   int n=(int) x[i];
           if(n>=65 && n<=90)
           {
                  n=n-65+97;
                  x[i]=(char) n;
               
           }
i++;
   }
printf("%s",x);

}
