#include<stdio.h>

int main()
{
int i;
   for(i=0;i<6;i++)
   {
	int n;
	scanf("%d",&n);
	switch(n)
	{
            case 1: printf("1 was Entered value stored in var is=%d",n);
                    break;
            case 2: printf("2 was Entered value stored in var is=%d",n);
                    break;
            default:
                   printf("Something Different was Entered value stored in var is=%d",n);
	}
  }
}
