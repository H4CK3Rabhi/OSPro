#include<stdio.h>


int main()
{
	int n,i,j;
	scanf("%d",&n);
	int arr[n][n];
	int sum=0;
         for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
		     scanf("%d",&arr[i][j]);
		}
	}
         for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(i==j)
			{
                          sum+=arr[i][j];
			}
		}
	}
	printf("%d",sum);

}
