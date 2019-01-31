#include<iostream>
#include<cstdlib>
#include<pthread.h>
using namespace std;

char ch='O';

void *inputthread(void *arg)
{
while(1)
 {
  cin>>ch;
  if(ch=='X')
  break;
 }
pthread_exit(NULL);
} 

int main()
{
 char mat[25][60];
 pthread_t input;
 int rc,i=0,j,k;
 
 rc=pthread_create(&input,NULL,inputthread,(void *)&i);
 if(rc)
 {
  cout<<"error creating thread";
  exit(-1);
 }
 
 while(i<50)
 {
  system("clear");
  for(j=0;j<25;j++)
   {
    for(k=0;k<60;k++)
     {
      mat[j][k]=ch;
      cout<<mat[j][k];
     }
    cout<<endl;
   }
  cout<<"enter the next charecter\n";
  for(j=0;j<500000000;j++);
  i++;
 }
 return 0;
}

