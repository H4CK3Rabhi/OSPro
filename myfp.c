#include<stdio.h>

int main()
{
   float sum=0, marks[5];
   int i;
   for(i=0;i<5;i++)
   {
        scanf("%f",&marks[i]);
        sum+=marks[i];
   }
   float per=100*(sum/500);
   if(per<40)
  {
      printf("Failed");
  }
  else if(per>=40 && per<60)
  {
    printf("Passed");
   }
 else if(per>=60 && per<80)
  {
    printf("Good");
   }
 else if(per>=80 && per<100)
  {
    printf("Excellent");
   }
 else
  {
      printf("Invalid Marks");
}
   
  



}
