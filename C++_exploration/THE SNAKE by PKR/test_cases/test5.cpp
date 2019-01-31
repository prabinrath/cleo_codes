#include<iostream>
#include<string.h>
using namespace std;

void *ret(int a)
{
char c[10],*p;
strcpy(c,"prabin");
p=c;
cout<<p<<endl;
int dat=116,*k;
k=&dat;
if(a==1)
	return (void *)p;
if(a==2)
	return (void *)k;
}

int main()
{
cout<<(char *)ret(1);
cout<<*((int *)ret(2));
}
