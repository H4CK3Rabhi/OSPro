#include<stdio.h>

int main()
{
	int n,i,j;
	scanf("%d",&n);
	int arr[n][n];
        int tarr[n][n];
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
			tarr[j][i]=arr[i][j];
		}
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%4d",tarr[i][j]);
	            }
		printf("\n");
	}

}
