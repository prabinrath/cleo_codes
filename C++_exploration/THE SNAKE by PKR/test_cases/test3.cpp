#include<iostream>
#include<stdlib.h>
#include<fstream>
using namespace std;
class top
{
int k;
public:
top()
{cin>>k;}
int ret()
{return k;}
};
void loading() //global function 1
{
 cout<<"loading";
 cout<<".";
 for(int k=0;k<800000000;k++);
 cout<<".";
 for(int k=0;k<800000000;k++);
 cout<<".";
 for(int k=0;k<800000000;k++);
}

int main()
{
loading();
int i=2;
top p[3];
ofstream o("topo.dat",ios::binary|ios::app);

while(i>=0)
{
	o.write((char *)&p[i],sizeof(p[i]));
	i--;
}
o.close();
return 0;
}



