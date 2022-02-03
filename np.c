#include<stdio.h>


struct Student
{
	int rollno;
	char name[30];
	float marks;
}s[3];

int main()
{
	int i;
	
	for(i=0;i<3;i++)
	{
		printf("Roll No:");
                scanf("%d",&(s[i].rollno));
		printf("Name:");
		scanf("%s",&(s[i].name));
		printf("Marks:");
		scanf("%f",&(s[i].marks));
	} 
        for(i=0;i<3;i++)
	{
		printf(" Roll No:%d",s[i].rollno);
		printf(" Name:%s",s[i].name);
		printf(" Marks:%f\n",s[i].marks);
	} 



}
