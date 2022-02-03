#include<stdio.h>
#define N 15
struct FileT
{
	char name[N][10];
	int start[N];
	int size[N];
}ft;
int main()
{
	int FilledT[15];
	for(int i=0;i<N;i++)
	{
		FilledT[i]=0;
	}
	int count=0;
	while(1)
	{
		printf("Enter Name of File:::");
	        scanf("%s",&(ft.name[count]));
	        printf("Enter Size of File:::");
		scanf("%d",&(ft.size[count]));
		int flag=0;
		for(int i=0;i<(N-(ft.size[count]));i++)
		{
			int scount=0;
                     for(int j=0;j<ft.size[count];j++)
		     {
                        if(FilledT[i+j]==0)
			{
				scount++;
			}
	             }
		  	       if(scount==ft.size[count])
		     {
                      for(int j=0;j<ft.size[count];j++)
		     {
                        FilledT[i+j]=1;
	             }
		  	ft.start[count]=i;
		        flag=1;
		         break;	
		     }
              }
		if(flag)
		{
		      for(int i=0;i<=count;i++)
		      {
                           printf("Name:%s\nStart:%d\nSize:%d\n\n",ft.name[i],ft.start[i],ft.size[i]);
		      }
		      count++;
		}
		else
		{
			printf("Could not Allocate");
		}
          }

}
