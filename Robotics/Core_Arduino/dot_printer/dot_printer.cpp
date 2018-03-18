#include "Arduino.h"
#include "dot_printer.h"
int slide_val=20,dot_pos=10,to_bal=0;
bool master=true;
const int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution, 2,7,8,3);
Servo myservo;

int A[5][9]={{1,1,1,1,1,1,1,1,1},{1,0,0,0,1,0,0,0,0},{1,0,0,0,1,0,0,0,0},{1,0,0,0,1,0,0,0,0},{1,1,1,1,1,1,1,1,1}};
int B[5][9]={{0,1,1,1,0,1,1,1,0},{1,0,0,0,1,0,0,0,1},{1,0,0,0,1,0,0,0,1},{1,0,0,0,1,0,0,0,1},{1,1,1,1,1,1,1,1,1}};
int C[5][9]={{1,0,0,0,0,0,0,0,1},{1,0,0,0,0,0,0,0,1},{1,0,0,0,0,0,0,0,1},{1,0,0,0,0,0,0,0,1},{1,1,1,1,1,1,1,1,1}};
int D[5][9]={{0,0,1,1,1,1,1,0,0},{0,1,0,0,0,0,0,1,0},{1,0,0,0,0,0,0,0,1},{1,0,0,0,0,0,0,0,1},{1,1,1,1,1,1,1,1,1}};
int E[5][9]={{1,0,0,0,1,0,0,0,1},{1,0,0,0,1,0,0,0,1},{1,0,0,0,1,0,0,0,1},{1,0,0,0,1,0,0,0,1},{1,1,1,1,1,1,1,1,1}};
int F[5][9]={{1,0,0,0,1,0,0,0,0},{1,0,0,0,1,0,0,0,0},{1,0,0,0,1,0,0,0,0},{1,0,0,0,1,0,0,0,0},{1,1,1,1,1,1,1,1,1}};
int G[5][9]={{1,0,0,0,1,1,1,1,1},{1,0,0,0,1,0,0,0,1},{1,0,0,0,0,0,0,0,1},{1,0,0,0,0,0,0,0,1},{1,1,1,1,1,1,1,1,1}};
int N[5][9]={{1,1,1,1,1,1,1,1,1},{0,0,0,0,0,0,1,1,0},{0,0,0,0,1,1,0,0,0},{0,0,1,1,0,0,0,0,0},{1,1,1,1,1,1,1,1,1}};
int I[5][9]={{1,0,0,0,0,0,0,0,1},{1,0,0,0,0,0,0,0,1},{1,1,1,1,1,1,1,1,1},{1,0,0,0,0,0,0,0,1},{1,0,0,0,0,0,0,0,1}};
int T[5][9]={{1,0,0,0,0,0,0,0,0},{1,0,0,0,0,0,0,0,0},{1,1,1,1,1,1,1,1,1},{1,0,0,0,0,0,0,0,0},{1,0,0,0,0,0,0,0,0}};
int R[5][9]={{0,1,1,1,0,0,1,1,1},{1,0,0,0,1,1,0,0,0},{1,0,0,0,1,0,0,0,0},{1,0,0,0,1,0,0,0,0},{1,1,1,1,1,1,1,1,1}};
int K[5][9]={{1,1,0,0,0,0,1,1,1},{0,0,1,0,0,1,0,0,0},{0,0,0,1,1,0,0,0,0},{0,0,0,1,0,0,0,0,0},{1,1,1,1,1,1,1,1,1}};
int L[5][9]={{0,0,0,0,0,0,0,0,1},{0,0,0,0,0,0,0,0,1},{0,0,0,0,0,0,0,0,1},{0,0,0,0,0,0,0,0,1},{1,1,1,1,1,1,1,1,1}};
int hpn[5][9]={{0,0,0,0,1,0,0,0,0},{0,0,0,0,1,0,0,0,0},{0,0,0,0,1,0,0,0,0},{0,0,0,0,1,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
int P[5][9]={{0,1,1,1,0,0,0,0,0},{1,0,0,0,1,0,0,0,0},{1,0,0,0,1,0,0,0,0},{1,0,0,0,1,0,0,0,0},{1,1,1,1,1,1,1,1,1}};
int X[5][9]={{1,1,0,0,0,0,0,1,1},{0,0,1,1,0,1,1,0,0},{0,0,0,0,1,1,0,0,0},{0,0,1,1,0,1,1,0,0},{1,1,0,0,0,0,0,1,1}};
int O[5][9]={{1,1,1,1,1,1,1,1,1},{1,0,0,0,0,0,0,0,1},{1,0,0,0,0,0,0,0,1},{1,0,0,0,0,0,0,0,1},{1,1,1,1,1,1,1,1,1}};
int M[5][9]={{1,1,1,1,1,1,1,1,1},{1,1,0,0,0,0,0,0,0},{0,0,1,1,1,0,0,0,0},{1,1,0,0,0,0,0,0,0},{1,1,1,1,1,1,1,1,1}};
int H[5][9]={{1,1,1,1,1,1,1,1,1},{0,0,0,0,1,0,0,0,0},{0,0,0,0,1,0,0,0,0},{0,0,0,0,1,0,0,0,0},{1,1,1,1,1,1,1,1,1}};
int U[5][9]={{1,1,1,1,1,1,1,1,1},{0,0,0,0,0,0,0,0,1},{0,0,0,0,0,0,0,0,1},{0,0,0,0,0,0,0,0,1},{1,1,1,1,1,1,1,1,1}};

void dot_printer::initialize()
{
  Serial.begin(9600);
  myStepper.setSpeed(30);
  pinMode(A5,INPUT);
  pinMode(9,OUTPUT);
  pinMode(13,OUTPUT);
  digitalWrite(9,LOW);
  myservo.attach(10);
  myservo.write(0);delay(1000);slide(60);delay(2000);
  Serial.println("initialized printer");
}
void dot_printer::dot()
{
  myservo.write(dot_pos);delay(100);myservo.write(0);delay(100);
}

void dot_printer::slide(int val)
{
  digitalWrite(9,HIGH);delay(val);digitalWrite(9,LOW);
}

void dot_printer::drag(int stp)
{
  myStepper.step(stp);
}

void dot_printer::check()
{
  if(analogRead(A5)<100)
  digitalWrite(13,HIGH);
  else
  digitalWrite(13,LOW);
  Serial.println(analogRead(A5));
}

void dot_printer::printdata(String dat)
{
int len=dat.length();
int cnt=0;
if(len>12)
{
	drag(10);drag(-10);
}
else
{
	while(len>0)
	{
		printchar(dat[len-1]);
		Serial.println(dat[len-1]);
		len--;
		cnt++;if(cnt>1){if(master==true){slide_val=25;dot_pos=12;to_bal=5;}}
	}
}
}

void dot_printer::next()
{
	slide(slide_val*1.5-to_bal);
	delay(1000);
	Serial.println("next");
}

void dot_printer::draw(int let[5][9])
{
	for(int i=0;i<5;i++)
		{
			for(int j=0;j<9;j++)
			{
				if(let[i][j]==1)
					dot();
				drag(10);
				check();
			}
			slide(slide_val);
			drag(-90);
		}
}

void dot_printer::set(char ch=20,int val=10)
{
	if(ch=='s')
		slide_val=val;
	else if(ch=='d')
		dot_pos=val;

	if(master==true)
	master=false;
	else
		master=true;
}

void dot_printer::printchar(char ch)
{
	if(ch=='A')
	{draw(A);}
	else if(ch=='B')
	{draw(B);}
	else if(ch=='C')
	{draw(C);}
	else if(ch=='D')
	{draw(D);}
	else if(ch=='E')
	{draw(E);}
	else if(ch=='F')
	{draw(F);}
	else if(ch=='N')
	{draw(N);}
	else if(ch=='I')
	{draw(I);}
	else if(ch=='T')
	{draw(T);}
	else if(ch=='R')
	{draw(R);}
	else if(ch=='K')
	{draw(K);}
	else if(ch=='P')
	{draw(P);}
	else if(ch=='G')
	{draw(G);}
	else if(ch=='O')
	{draw(O);}
	else if(ch=='U')
	{draw(U);}
	else if(ch=='H')
	{draw(H);}
	else if(ch=='L')
	{draw(L);}
	//else if(ch=='-')
	//{draw(hpn);}
	next();
}