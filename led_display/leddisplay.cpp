#include "Arduino.h"
#include "leddisplay.h"

ShiftRegister74HC595 sr (2, 4, 5, 6);
int c=0,d=1,e=2,f=3,g=4,h=5,i=6,j=7,k=8,l=9,m=10,n=11,o=12,p=13;
int seg=0,dig=0,dat[3];
int pin[21][2]={{d,g},{c,g},{c,h},{c,f},{d,f},{d,i},{d,h},
                    {c,j},{d,j},{d,k},{d,l},{c,l},{c,i},{c,k},
                    {d,n},{c,n},{c,o},{c,m},{d,m},{d,p},{d,o}};

void leddisplay::high()
{
    sr.setAllHigh();
}

//switching function
void leddisplay::on(int pos, int neg)
{
  if(pos == 1)
  {sr.set(1,HIGH);sr.set(0,LOW);}
  else
  {sr.set(0,HIGH);sr.set(1,LOW);}

  sr.set(neg,LOW);
  delayMicroseconds(300);
  sr.set(neg,HIGH);
  sr.set(pos,LOW);
}

//setting function
void leddisplay::store(int col, int num)
{
    if(col==1)
        seg=0;
    else if(col==2)
        seg=7;
    else if(col==3)
        seg=14;

    if(num==0)
        {
            on(pin[seg][0],pin[seg][1]);on(pin[seg+1][0],pin[seg+1][1]);on(pin[seg+2][0],pin[seg+2][1]);on(pin[seg+3][0],pin[seg+3][1]);on(pin[seg+4][0],pin[seg+4][1]);on(pin[seg+5][0],pin[seg+5][1]);
        }
   else if(num==1)
        {
            on(pin[seg+5][0],pin[seg+5][1]);on(pin[seg+4][0],pin[seg+4][1]);
        }
    else if(num==2)
        {
            on(pin[seg][0],pin[seg][1]);on(pin[seg+5][0],pin[seg+5][1]);on(pin[seg+6][0],pin[seg+6][1]);on(pin[seg+2][0],pin[seg+2][1]);on(pin[seg+3][0],pin[seg+3][1]);
        }
    else if(num==3)
        {
            on(pin[seg][0],pin[seg][1]);on(pin[seg+5][0],pin[seg+5][1]);on(pin[seg+6][0],pin[seg+6][1]);on(pin[seg+4][0],pin[seg+4][1]);on(pin[seg+3][0],pin[seg+3][1]);
        }
    else if(num==4)
        {
            on(pin[seg+1][0],pin[seg+1][1]);on(pin[seg+6][0],pin[seg+6][1]);on(pin[seg+5][0],pin[seg+5][1]);on(pin[seg+4][0],pin[seg+4][1]);
        }
    else if(num==5)
        {
            on(pin[seg][0],pin[seg][1]);on(pin[seg+1][0],pin[seg+1][1]);on(pin[seg+6][0],pin[seg+6][1]);on(pin[seg+4][0],pin[seg+4][1]);on(pin[seg+3][0],pin[seg+3][1]);
        }
    else if(num==6)
        {
            on(pin[seg][0],pin[seg][1]);on(pin[seg+1][0],pin[seg+1][1]);on(pin[seg+2][0],pin[seg+2][1]);on(pin[seg+3][0],pin[seg+3][1]);on(pin[seg+4][0],pin[seg+4][1]);on(pin[seg+6][0],pin[seg+6][1]);
        }
    else if(num==7)
        {
            on(pin[seg][0],pin[seg][1]);on(pin[seg+5][0],pin[seg+5][1]);on(pin[seg+4][0],pin[seg+4][1]);
        }
    else if(num==8)
        {
            on(pin[seg][0],pin[seg][1]);on(pin[seg+1][0],pin[seg+1][1]);on(pin[seg+2][0],pin[seg+2][1]);on(pin[seg+3][0],pin[seg+3][1]);on(pin[seg+4][0],pin[seg+4][1]);on(pin[seg+5][0],pin[seg+5][1]);on(pin[seg+6][0],pin[seg+6][1]);
        }
    else if(num==9)
        {
            on(pin[seg][0],pin[seg][1]);on(pin[seg+1][0],pin[seg+1][1]);on(pin[seg+6][0],pin[seg+6][1]);on(pin[seg+5][0],pin[seg+5][1]);on(pin[seg+4][0],pin[seg+4][1]);on(pin[seg+3][0],pin[seg+3][1]);
        }
}

//decoding function
void leddisplay::disp(int data)
{
    if(data<0 || data>=1000)
        {
            on(d,h);on(c,k);on(d,o);
        }
    else
        {
            while(data>0)
            {
                dat[dig]=data%10;
                data/=10;
                dig++;
            }

            if(dig==1)
                {
                    for(int itr=0;itr<100;itr++)
                    {store(1,dat[0]);}
                }
            else if(dig==2)
                {
                    for(int itr=0;itr<60;itr++)
                    {store(1,dat[1]);store(2,dat[0]);}
                }
            else if(dig==3)
                {
                    for(int itr=0;itr<40;itr++)
                    {store(1,dat[2]);store(2,dat[1]);store(3,dat[0]);}
                }
            dig=0;
        }
}