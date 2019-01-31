#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#define rw 45
#define cn 148
using namespace std;

struct life
{
	int ini,fin;
};
	
life l[rw][cn];

void reset()
{
	int i,j;
  	for(i=0;i<rw;i++)
     for(j=0;j<cn;j++)
   	  l[i][j].ini=0;
}
	

main()
{
    int i=0,j,t1,t2,n,k,t;
    long o;
	
	cout<<"Press 999 to initialize the game\n";
	reset();
    while(i==0)
    {
    	cout<<"Enter the row number\n";
    	cin>>t1;
    	if(t1==999)
    	break;
    	cout<<"Enter the column Number\n";
    	cin>>t2;
    	l[t1][t2].ini=1;
	}
	
	cout<<"Enter the number of iterations\n";
	cin>>n;
	while(n!=0)
	{
		system("clear");
		cout<<"                                            WELCOME TO THE CONWAY'S GAME OF LIFE\n";
		
		for(i=0;i<rw;i++)
		{
		 for(j=0;j<cn;j++)
		  {
		  	t1=0;
		  	
		  	 	if(i==0)
		  	 	 k=(rw-1);
		  	 	else
		  	 	 k=i-1;
		  	 	 
		  	 	if(j==0)
		  	 	 t=(cn-1);
		  	 	else
		  	 	 t=j-1;
		  	 	 
		  	 	if(l[k][t].ini==1)
		  	 	t1++;
		  	 	if(l[i][t].ini==1)
		  	 	t1++;
		  	 	if(l[(i+1)%rw][t].ini==1)
		  	 	t1++;
		  	 	if(l[(i+1)%rw][j].ini==1)
		  	 	t1++;
		  	 	if(l[(i+1)%rw][(j+1)%cn].ini==1)
		  	 	t1++;
		  	 	if(l[i][(j+1)%cn].ini==1)
		  	 	t1++;
		  	 	if(l[k][(j+1)%cn].ini==1)
		  	 	t1++;
		  	 	if(l[k][j].ini==1)
		  	 	t1++;
		  	 	
		  	 	if(t1<2 && l[i][j].ini==1)
		  	 	l[i][j].fin=0;
		  	 	else if((t1==2 || t1==3) && l[i][j].ini==1)
		  	 	l[i][j].fin=1;
		  	 	else if(t1>3 && l[i][j].ini==1)
		  	 	l[i][j].fin=0;
		  	 	else if(t1==3 && l[i][j].ini==0)
		  	 	l[i][j].fin=1;
		   }
	    }
	    
	    for(i=0;i<rw;i++)
       {
	   for(j=0;j<cn;j++)
	   cout<<l[i][j].ini;
	   cout<<endl;
       }
       
	    for(i=0;i<rw;i++)
		 for(j=0;j<cn;j++)
		  l[i][j].ini=l[i][j].fin;
	n--;
	for(o=0;o<55000000;o++);	  
	}
}
