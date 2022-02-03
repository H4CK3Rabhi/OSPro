#include<stdio.h>

int main()
{
	char x[20];
	scanf("%s",&x);
	int len=0;
	while(x[len]!='\0')
	{
		len++;
	}
	printf("%d",len);
}
