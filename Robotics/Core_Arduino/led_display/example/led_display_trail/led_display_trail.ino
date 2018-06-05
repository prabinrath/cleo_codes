#include <leddisplay.h>
leddisplay sony;
int show[9];

void setup()
{  
  sony.high();
  show[0]=-1;show[1]=-1;show[2]=-1;
}

int num=129;
void loop()
{
  /*
 for(int i=3;i>0;i--)
 {
    for(int j=0;j<100;j++)
    {
      sony.store(i,4);
    }
 }
 */  
 int itr=3,latch=num;
 while(num>0)
 {
  show[itr]=num%10;
  num=num/10;
  itr++;
 }

  int j=itr+3,dig=itr,k;
  while(itr<j){show[itr]=-1;itr++;}

  for(itr=0;itr<dig;itr++)
  {
    for(int l=0;l<100;l++)
    {
    for(j=itr,k=3;j<itr+3;j++,k--)
    {
      if(show[j]!=-1)
      {
          sony.store(k,show[j]);
      }
    }
    }
    delay(500);
  }
  num=latch;
}
