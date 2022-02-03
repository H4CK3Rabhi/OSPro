#include<stdio.h>

int main()
{
	int n;
	scanf("%d",&n);
	int arr[n];
        int sum=0;
	for(int i=0;i<n;i++)
	{
                scanf("%d",&arr[i]);
		if(arr[i]%5==0&&arr[i]%2==0)
		sum+=arr[i];
	}
	printf("\n%d\n",sum);
}


