#include<stdio.h>

int main()
{
	int n,i;
	scanf("%d",&n);

	int arr[n];
	for(i=0;i<n-1;i++)
	{
		scanf("%d",&arr[n]);
	}
	int dat,pos;
	scanf("%d %d",dat,pos);

	for(i=n-2;i>=pos;i--)
	{
		arr[i+i]=arr[i];
	}
	arr[pos]=dat;
	for(i=0;i<n;i++)
	{
		printf("%4d",arr[i]);
	}
}
