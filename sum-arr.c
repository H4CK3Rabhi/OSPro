#include<stdio.h>

int main()
{
	int n,i;
	 scanf("%d",&n);
	 int arr[n];
	 int sum=0;
	 for(i=0;i<n;i++)
	 {
		 scanf("%d",&arr[i]);
		 sum+=arr[i];
	 }
	 printf("%d",sum);
}
