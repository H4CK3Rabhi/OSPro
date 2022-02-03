#include<stdio.h>

void swap(int *a, int *x)
{
	int y=*a;
	*a=*x;
	*x=y;
}

int main()
{
     int a,x;
     scanf("%d %d",&a,&x);
     printf("a=%d x=%d",a,x);
     swap(&a,&x);
     printf("a=%d x=%d",a,x);
}
