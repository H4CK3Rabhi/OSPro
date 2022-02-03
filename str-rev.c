#include<stdio.h>
#include<string.h>
int main()
{
	
	char s[10],s1[10];
	scanf("%s",&s);
	int i=0;
        while(s[i]!='\0')
		i++;
	int len=i-1;
	for(i=0;i<=len;i++)
	{
                 s1[i]=s[len-i];
	}
        s1[i]='\0';
	printf("%s",&s1);
}
