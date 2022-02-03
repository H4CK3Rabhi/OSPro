#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int main()
{
  int pagefaultservicetime_wo_mod=8;
  int pagefaultservicetime_mod=20;
  int memmoryAT=100;
  int effective_access_time=200;
  float modification_percentage=0.8;;
   
   float ans=effective_access_time-memmoryAT/(modification_percentage*pagefaultservicetime_mod*pow(10.0,6.0))+((1-modification_percentage)*pagefaultservicetime_wo_mod*pow(10.0,6.0))-memmoryAT;
   
   printf("Maximum Page Fault rate= %12.5e\n",ans);
}
