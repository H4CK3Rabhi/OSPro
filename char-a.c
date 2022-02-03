#include<stdio.h>

int main()
{
	char s[10];
	int i;
	int flg=1;
	scanf("%s",&s);
	for(i=0;s[i]!='\0';i++)
	{
		if(s[i]=='a')
		{
			flg=0;
			printf("Found at %d\n",i);
		}
	}
	if(flg)
	{
		printf("Not Found");

	}
}
