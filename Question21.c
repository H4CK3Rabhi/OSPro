#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int main()
{
  int pfst_not_mod=8;
  int pfst_mod=20;
  int mem_access_time=100;
  int effat=200;
  float per_of_mod=0.8;;

   float denom=effat-mem_access_time/(per_of_mod*pfst_mod*pow(10.0,6.0))+((1-per_of_mod)*pfst_not_mod*pow(10.0,6.0))-mem_access_time;
   float pfr=num/denom;
   printf("Maximum Accepted Page Fault Rate is:(%f/%f)= %12.5e\n",num,denom,pfr);
}
