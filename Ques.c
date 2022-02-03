#include<stdio.h>

int [] sorted(int &arr,int n)
{
	
	for(int i=0;i<n;i++)
	{
		int j=0;
		while(arr[i+j]==1)
		{
			arr[i+j]=0;
			j++;
		}
		for(int k=0;i<j;i++)
		{
			arr[n-j+k]=1;
		}
	}
}
int main()
{
	int arr[5]={1,0,1,1,1};
	arr=sorted(arr,5);
       for(int i=0;i<5;i++)
       {
	     printf("%d ",arr[i]);
       }	       
}
