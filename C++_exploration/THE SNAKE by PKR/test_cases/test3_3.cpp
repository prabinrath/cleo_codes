#include<iostream>
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

int main()
{
top p;
ifstream i("topo.dat",ios::binary);
while(i.read((char *)&p,sizeof(p)))
{
	cout<<p.ret()<<endl;
}
i.close();
return 0;
}
