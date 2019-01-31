#include<iostream>
#include<stdlib.h>
#include<cstdlib>
#include<fstream>
#include<iomanip>
#include<ctype.h>
#include<string>
#include<ctime>
#include<pthread.h>
using namespace std;

int main()
{
int a,b=100,c;
cin>>c;
if(c==0)
exit(0);
srand((unsigned)time(0));
while(b>=0)
{
a=(rand()%20);
c=(rand()%20);
if(a==0 || b==0 || a==19 || b==19)
cout<<a<<"\t"<<c<<endl;
b--;
}
}
