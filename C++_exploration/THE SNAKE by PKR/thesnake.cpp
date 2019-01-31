//*************THE SNAKE GAME by Prabin Rath***************START OF THE PROJECT(#' 'OX)
#include<iostream>
#include<unistd.h>//for delay
#include<stdlib.h>
#include<cstdlib>//for threading and random number generation
#include<fstream>//for data file handling
#include<string.h>//for string functions
#include<ctime>//for random number generation
#include<pthread.h>//for input tread generation

using namespace std;

#define rw 20
#define co 60

//declaring global variables
int delay,control=0;
char dir,prevdir,gamestat='c';

void loading() //global function 1
{
 system("clear");
 char ch[14]="Loading";
 for(int i=0;i<4;i++)
	{
	cout<<ch<<endl;
	ch[i+7]='.';
	ch[i+8]='\0';
	usleep(1000000);
	system("clear");
	}
}

void *input(void *arg) //global function 2
{
 while(control==1)
 {	
  cin>>gamestat;
  if(gamestat=='A' || gamestat=='a' || gamestat=='W' || gamestat=='w' || gamestat=='S' || gamestat=='s' || gamestat=='D' || gamestat=='d')
  {dir=gamestat;gamestat='c';}
 }
pthread_exit(NULL);
}

int namechk(char *); //prototype for global function 5
void saverec();  //prototype for global function 4
void savendel(); //prototype for global function 3

struct trv
{
 int r,c;
};

struct cell
{
char dat,p,b;
int forb;
};

struct record
{
 char name[20];
 int stage,score;
};

//the main game class defination starts
class game
{
 char plr[20],direction;
 cell cl[rw][co];
 trv f,l;//keeps track of the head and tail of the sanke
 int stg,scr,spd,chc,rf,cf;  //stg:-stage,scr:-score,spd:-speed,chc:-chance,rf:-food row,rc:-food column

 public:
 void reset() //to assign default datas
 {
  strcpy(plr,"anonymous");
  direction='a';
  stg=1;
  scr=0;
  spd=1;
  chc=3;
 rf=rw/5;cf=co/3;
 cl[rf][cf].dat='#'; //initial food cell
  for(int i=0;i<rw;i++)
   for(int j=0;j<co;j++)
    {cl[i][j].p='z';cl[i][j].b='z';cl[i][j].forb=0;}

 }
 
 void setmatrix();  //member function to set the initial game matrix according to the stage
 int setdir();  //member function to manupulate the matrix according to the input
 void play(int);  //member function to create user interface

 void *dataret(int a)
	{
	int *k;
	if(a==1)
		{char *nm;nm=plr;return (void *)nm;}
	if(a==2)
		{k=&scr;return (void *)k;}
	if(a==3)
		{k=&stg;return (void *)k;}
	}
};

game g,tp;

void game::setmatrix() //member function 1
{
 if(stg==1)
 {
  for(int i=0;i<rw;i++)
   for(int j=0;j<co;j++)
    {cl[i][j].dat=' ';}

  cl[rw/2][co/2].dat='O';
  cl[rw/2][(co/2)+1].dat='O';
  cl[rw/2][(co/2)+2].dat='O';
  
  f.r=rw/2; f.c=co/2;
  l.r=rw/2; l.c=f.c+2;

	 cl[rw/2][(co/2)+2].p='a';
	 cl[rw/2][(co/2)+1].p='a';
 }

 if(stg==2)
 {
  for(int i=0;i<rw;i++)
   for(int j=0;j<co;j++)
    {
     if(i==0||j==0||(i==rw-1)||(j==co-1))
     {cl[i][j].dat='X';cl[i][j].forb=1;}
     else
     {cl[i][j].dat=' ';}
    }
   
    cl[rw/2][co/2].dat='O';
    cl[rw/2][(co/2)+1].dat='O';
    cl[rw/2][(co/2)+2].dat='O';

    f.r=rw/2; f.c=co/2;
    l.r=rw/2; l.c=f.c+2;

    	 cl[rw/2][(co/2)+2].p='a';
	 cl[rw/2][(co/2)+1].p='a';
 }

 if(stg==3)
 {
  for(int i=0;i<rw;i++)
   for(int j=0;j<co;j++)
    {
     if(i==0||j==0||(i==rw-1)||(j==co-1))
     {cl[i][j].dat='X';cl[i][j].forb=1;}
     else
     {cl[i][j].dat=' ';}
    }

  for(int i=rw*0.25;i<rw*0.5;i++)
   for(int j=co*0.25;j<co*0.5;j++)
    {cl[i][j].dat='X';cl[i][j].forb=1;}

  for(int i=rw*0.5;i<rw*0.75;i++)
   for(int j=co*0.5;j<co*0.75;j++)
    {cl[i][j].dat='X';cl[i][j].forb=1;}

   cl[8][10].dat='O';
   cl[8][11].dat='O';
   cl[8][12].dat='O';

   f.r=8; f.c=10;
   l.r=8; l.c=f.c+2;

	 cl[8][12].p='a';
	 cl[8][11].p='a';
 }
}

int game::setdir() //core logic of the game #traversinglogic //member function 2
{
int fd=0,z=1,h=0,k,cir;

if(dir!='a' && dir!='A' && dir!='w' && dir!='W' && dir!='s' && dir!='S' && dir!='d' && dir!='D')
return 3;

if((prevdir=='d' || prevdir=='D') && (dir=='a' || dir=='A'))
	{return 2;}
else if((prevdir=='a' || prevdir=='A') && (dir=='d' || dir=='D'))
	{return 2;}
else if((prevdir=='w' || prevdir=='W') && (dir=='s' || dir=='S'))
        {return 2;}
else if((prevdir=='s' || prevdir=='S') && (dir=='w' || dir=='W'))
        {return 2;}
else if(dir=='a' || dir=='A')
	{
	if(f.c==0)
		cir=co-1;
		else cir=f.c-1;
	if(cl[f.r][cir].dat=='X' || cl[f.r][cir].dat=='O')
	{z=3;h=1;chc--;}
	while(z>0)
	{
		if(f.c==0)
		cir=co-1;
		else cir=f.c-1;
		if(cl[f.r][cir].dat=='#')
			{fd=1;
			if(h==0)
			scr++;}
		if(cl[f.r][f.c].p=='z')
       		{cl[f.r][f.c].p='a';}
		else
		{cl[f.r][f.c].b=cl[f.r][f.c].p;
		cl[f.r][f.c].p='a';}
		if(cl[f.r][cir].dat==' ' || cl[f.r][cir].dat=='#')
		cl[f.r][cir].dat='O';
		f.c=cir;
		z--;
	}
	}
else if(dir=='d' || dir=='D')
        {
        if(cl[f.r][(f.c+1)%co].dat=='X' || cl[f.r][(f.c+1)%co].dat=='O')
	{z=3;h=1;chc--;}
	while(z>0)
	{
       		if(cl[f.r][(f.c+1)%co].dat=='#')
        		{fd=1;
			if(h==0)
			scr++;}
		if(cl[f.r][f.c].p=='z')
       		{cl[f.r][f.c].p='d';}
		else
		{cl[f.r][f.c].b=cl[f.r][f.c].p;
		cl[f.r][f.c].p='d';}
		if(cl[f.r][(f.c+1)%co].dat==' ' || cl[f.r][(f.c+1)%co].dat=='#')
       		cl[f.r][(f.c+1)%co].dat='O';
		f.c=(f.c+1)%co;
		z--;
	}
        }
else if(dir=='w' || dir=='W')
        {
	if(f.r==0)
		cir=rw-1;
		else cir=f.r-1;
        if(cl[cir][f.c].dat=='X' || cl[cir][f.c].dat=='O')
        {z=3;h=1;chc--;}
	while(z>0)
	{
		if(f.r==0)
		cir=rw-1;
		else cir=f.r-1;
        	if(cl[cir][f.c].dat=='#')
        		{fd=1;
			if(h==0)
			scr++;}
		if(cl[f.r][f.c].p=='z')
       		{cl[f.r][f.c].p='w';}
		else
		{cl[f.r][f.c].b=cl[f.r][f.c].p;
		cl[f.r][f.c].p='w';}
		if(cl[cir][f.c].dat==' ' || cl[cir][f.c].dat=='#')
        	cl[cir][f.c].dat='O';
		f.r=cir;
		z--;
	}
        }
else if(dir=='s' || dir=='S')
        {
        if(cl[(f.r+1)%rw][f.c].dat=='X' || cl[(f.r+1)%rw][f.c].dat=='O')
        {z=3;h=1;chc--;}
	while(z>0)
	{
        	if(cl[(f.r+1)%rw][f.c].dat=='#')
        		{fd=1;
			if(h==0)
			scr++;}
		if(cl[f.r][f.c].p=='z')
       		{cl[f.r][f.c].p='s';}
		else
		{cl[f.r][f.c].b=cl[f.r][f.c].p;
		cl[f.r][f.c].p='s';}
		if(cl[(f.r+1)%rw][f.c].dat==' ' || cl[(f.r+1)%rw][f.c].dat=='#')
        	cl[(f.r+1)%rw][f.c].dat='O';
		f.r=(f.r+1)%rw;
		z--;
	}
        }
if(fd==0)
	{
	if(cl[l.r][l.c].b=='z' && cl[l.r][l.c].forb==0)
	cl[l.r][l.c].dat=' ';
	
	if(l.c==0)                   //reusing variables z
		z=co-1;
	else    z=l.c-1;
	
	if(l.r==0)
		k=rw-1;
	else    k=l.r-1;
	
	if(cl[l.r][l.c].b!='z')
		{
		if(cl[l.r][l.c].b=='a')
		{cl[l.r][l.c].b='z';l.c=z;}
		else if(cl[l.r][l.c].b=='d')
		{cl[l.r][l.c].b='z';l.c=(l.c+1)%co;}
		else if(cl[l.r][l.c].b=='w')
		{cl[l.r][l.c].b='z';l.r=k;}
		else if(cl[l.r][l.c].b=='s')
		{cl[l.r][l.c].b='z';l.r=(l.r+1)%rw;}
		}
	else
		{
		if(cl[l.r][l.c].p=='a')
		{cl[l.r][l.c].p='z';l.c=z;}
		else if(cl[l.r][l.c].p=='d')
		{cl[l.r][l.c].p='z';l.c=(l.c+1)%co;}
		else if(cl[l.r][l.c].p=='w')
		{cl[l.r][l.c].p='z';l.r=k;}
		else if(cl[l.r][l.c].p=='s')
		{cl[l.r][l.c].p='z';l.r=(l.r+1)%rw;}
		}
	}
prevdir=dir;
if(h==1)
	return 0;
else
	return 1;
}

void game::play(int cnt) //member function 3
{
 int checker=4;
 if(cnt==1)
 goto lebc;
 
 lebi:
 cout<<"Enter your NAME: ";
 cin>>plr;
 if(namechk(plr)==1){cout<<"The NAME already exists in the save game list, Please enter a different name\n";goto lebi;}
 leba:
 cout<<"\nEnter the difficulty level(1 to 3): ";
 cin>>stg;
 if(stg<0 || stg>3)
  {
   cout<<"\ninvalid stage";
   goto leba;
  }
 lebb:
 cout<<"\nEnter the speed level of the snake(1 to 5): ";
 cin>>spd;
 if(spd<1 || spd>5)
  {
   cout<<"\ninvalid speed";
   goto lebb;
  }
 setmatrix();

 lebc:
 dir=direction;
 //initializing input thread
 if(control!=1)
 {control=1;
  pthread_t inp;
	int rc;
	rc=pthread_create(&inp,NULL,input,(void *)&dir);
	if(rc)
	{
	cout<<"\nError: creating input thread";
	exit(-1);
	}}
 

 srand((unsigned)time(0));
 loading();
 //check and set matrix,print 
	while(chc>0) //major printing and control loop
	{
	if(cl[rf][cf].dat!='#') //random food generation
	{	
		lebd:
		rf=(rand()%rw);
		cf=(rand()%co);
		if(cl[rf][cf].dat!=' ')
		goto lebd;
	cl[rf][cf].dat='#';
	}		
		
	checker=setdir();
	system("clear");
	cout<<"                          THE SNAKE GAME by Prabin Rath\n";
	for(int i=0;i<rw;i++)
		{
		for(int j=0;j<co;j++)
			cout<<cl[i][j].dat;
		cout<<endl;
		}
	cout<<endl<<"SCORE: "<<scr<<"       STAGE: "<<stg<<"        LIFE: "<<chc<<endl<<endl;
	cout<<"Enter A,W,S,D to guide the snake\n";
	if(checker==0)
	cout<<"You lost a life be CAREFUL with your moves :)\n";
	if(checker==3)
	cout<<"INVALID INPUT Enter again\n";
	if(checker==2)
	cout<<"INVALID MOVE Enter again\n";
	usleep(1000000/spd);
	if(gamestat=='O' || gamestat=='o')
		{
		cout<<"Game PAUSED,Enter\nR to restart the game\nQ to quit the game\nV to save and quit the game\nB to RESUME the game\n";
			for(delay=0;delay<8000000000;delay++)
			if(gamestat=='B' || gamestat=='b' || gamestat=='R' || gamestat=='r' || gamestat=='Q' || gamestat=='q' || gamestat=='V' || gamestat=='v')
			break;
			if(gamestat=='R' || gamestat=='r' || gamestat=='Q' || gamestat=='q' || gamestat=='V' || gamestat=='v')
			break;
			gamestat='c';
		}
	}
 
 if(gamestat=='R' || gamestat=='r')
	{
	setmatrix();
	scr=0;chc=3;
	goto lebc;
	}
 if(gamestat=='Q' || gamestat=='q')
	{goto end;}

 cout<<"\n\n****GAME OVER****GAME OVER****GAME OVER****GAME OVER****GAME OVER****\n\n";
 if(chc<=0)
	{saverec();cout<<"WELL PLAYED___TRY EVEN BETTER NEXT TIME\n";}
 usleep(3000000);
 direction=dir;
 if(chc!=0)
 savendel();
 end:
 prevdir='z';
 control=0;
}

int namechk(char *p) //global function 5
{
 int chk=0;
 ifstream i0("game_record.dat",ios::binary);
	 while(i0.read((char *)&tp,sizeof(tp)))
 	 {if(strcmp(p,(char *)tp.dataret(1))==0)
		{chk=1;break;}}
 i0.close();
 return chk;
}

void saverec() //global function 4
{
 record r;
 ofstream o("win_record.dat",ios::binary|ios::app);
 strcpy(r.name,(char *)g.dataret(1));
 r.score=*((int *)g.dataret(2));
 r.stage=*((int *)g.dataret(3));
 o.write((char *)&r,sizeof(r));
 o.close();
}

void savendel() //global function 3
{
 ifstream i("game_record.dat",ios::binary);
 ofstream o("temp.dat",ios::binary);
 while(i.read((char *)&tp,sizeof(tp)))
 {
	if(strcmp((char *)g.dataret(1),(char *)tp.dataret(1))!=0)
		o.write((char *)&tp,sizeof(tp));
 }
 i.close();
 o.close();
 remove("game_record.dat");
 rename("temp.dat","game_record.dat");

 ofstream f("game_record.dat",ios::binary|ios::app);
 f.write((char *)&g,sizeof(g));
 f.close();
}

//********************The main body of the program********************************************************************************************
//********************************************************************************************************************************************
	
int main()
{
 int shw,k;char pla[20];
 loading();
 lebf:
 system("clear");
 cout<<"                          $$$$$$___THE SNAKE GAME___$$$$ by Prabin Rath\n";
 cout<<"1:> NEW GAME\n2:> LOAD SAVED GAME\n3:> SCORE CARD\n4:> DELETE SAVED GAME\n5:> INSTRUCTIONS\n6:> CREDITS\n7:> EXIT GAME\n\nEnter your  choice number\n";
 cin>>shw;
 
 if(shw==1)
 {
	dir='a';
	g.reset();
	g.play(0);
	goto lebf;
 }
 else if(shw==2)
 {
	system("clear");cout<<"*********SAVED GAME LIST*************\n\n";
	int n=0;
	ifstream i1("game_record.dat",ios::binary);
        while(i1.read((char *)&g,sizeof(g)))
        {cout<<n+1<<":> "<<(char *)g.dataret(1)<<"\t"<<"stage: "<<*((int *)g.dataret(3))<<"\t"<<"score: "<<*((int *)g.dataret(2))<<endl;n++;}
	if(n==0)
	{cout<<"\n\nNO SAVED GAME FOUND\n\n";usleep(3000000);goto lebf;}
	i1.close();
	cout<<"\nEnter the name of the player to load the game or enter 0 to go back to main menu\n";
	lebg:
	cin>>pla;
	if(strcmp(pla,"0")==0)
	goto lebf;
	k=0;
	ifstream i2("game_record.dat",ios::binary);
	while(i2.read((char *)&g,sizeof(g)))
	{if(strcmp(pla,(char *)g.dataret(1))==0){k=1;break;}}
	i2.close();
	if(k==0)
	{cout<<"NO SUCH NAME FOUND enter again\n";goto lebg;}

	g.play(1);
	goto lebf;
 }
 else if(shw==3)
 {
	cout<<"\n*****SCORE RECORD*******\n";k=0;
	record r;
	ifstream i("win_record.dat",ios::binary);
	while(i.read((char *)&r,sizeof(r)))
	{cout<<k+1<<":> "<<r.name<<"\t"<<"stage: "<<r.stage<<"\t"<<"score: "<<r.score<<endl;k++;}
	if(k==0)
	cout<<"\nNO WIN RECORDS FOUND\n";
	i.close();
	cout<<"\nEnter any number to return to the main menu\n";
	cin>>k;
	if(k!=786)
	goto lebf;
 }
 else if(shw==4)
 {
	system("clear");cout<<"*********SAVED GAME LIST*************\n\n";
	int n=0;
	ifstream i1("game_record.dat",ios::binary);
        while(i1.read((char *)&g,sizeof(g)))
        {cout<<n+1<<":> "<<(char *)g.dataret(1)<<"\t"<<"stage: "<<*((int *)g.dataret(3))<<"\t"<<"score: "<<*((int *)g.dataret(2))<<endl;n++;}
	if(n==0)
	{cout<<"\n\nNO SAVED GAME FOUND TO DELETE\n\n";i1.close();usleep(3000000);goto lebf;}
	i1.close();

	cout<<"\nEnter the name of the player to delete the game or enter 0 to go back to man menu\n";
	lebh:
	cin>>pla;
	if(strcmp(pla,"0")==0)
	goto lebf;
	k=0;
	ifstream i2("game_record.dat",ios::binary);
	while(i2.read((char *)&g,sizeof(g)))
	{if(strcmp(pla,(char *)g.dataret(1))==0){k=1;break;}}
	i2.close();
	if(k==0)
	{cout<<"NO SUCH NAME FOUND enter again\n";goto lebh;}

	ofstream o("tempo.dat",ios::binary);
	ifstream i3("game_record.dat",ios::binary);
	while(i3.read((char *)&tp,sizeof(tp)))
	{if((strcmp((char *)g.dataret(1),(char *)tp.dataret(1))!=0))
		o.write((char *)&tp,sizeof(tp));}
	
	i3.close();
	o.close();
	remove("game_record.dat");
	rename("tempo.dat","game_record.dat");
	goto lebf;
 }
 else if(shw==5)
 {
	cout<<"\nunder construction\n";
	cout<<"\nEnter any number to return to the main menu\n";
	cin>>k;
	if(k!=786)
	goto lebf;
 }
 else if(shw==6)
 {
	cout<<"\n\nThe game is coded by Ms.Prabin Kumar Rath\nB.tech 1st Year\nComputer Science and Engineering Department\nNIT Rourkela\n\n";
	cout<<"\nEnter any number to return to the main menu\n";
	cin>>k;
	if(k!=786)
	goto lebf;	
 }
 else if(shw==7)
 {
	cout<<"\n\nBYE BYE THANKYOU FOR PLAYING THE GAME\n\n"<<endl<<sizeof(g)<<endl;
	exit(0);
 }
 else
 {cout<<"\nINVALID CHOICE Enter again\n";usleep(2000000);goto lebf;}
return 0;
}
//END of the PROJECT
