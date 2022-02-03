#include<stdlib.h>
#include<stdio.h>

int min(int *arr,int n)
{
      int mini=arr[0];
      for(int i=0;i<n;i++)
      {
             if(arr[i]<mini)
             {
                   mini=arr[i];
               }
      }
     return mini;

}
int max(int *arr,int n)
{
      int maxi=arr[0];
      for(int i=0;i<n;i++)
      {
             if(arr[i]>maxi)
             {
                   maxi=arr[i];
               }
      }
     return maxi;

}
int main()
{
       printf("Enter Number of Requests to Entertain ::");
       int n,prev,start,largest,smallest;
       scanf("%d",&n);
       int *arr=(int *)malloc(n*sizeof(int));
       printf("Enter Lowest Possible Cylinder no ::");
       scanf("%d",&smallest);
       printf("Enter Highest Possible Cylinder no ::");
       scanf("%d",&largest);
       printf("Enter All Request Cylinder Nos::\n");
       for(int i=0;i<n;i++)
       {
           scanf("%d",&arr[i]);
        }
      printf("Enter Current Head Position :: ");
      scanf("%d",&start);
      printf("Enter Previous Head Position :: ");
      scanf("%d",&prev);
      int minimum=min(arr,n);
      int maximum=max(arr,n);
      int sum=0; 
      if((start-prev)>0)
     {
             sum=(largest-start)+(largest-minimum);
      }
     else if((start-prev)<0)
    {
             sum=(start-smallest)+(maximum-smallest);         
    }
   else
   {
               printf("Error:Could Not Find Direction");
    }
   printf("\nTotal Distance Travelled :: %d \n",sum);

}
