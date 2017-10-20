#include <ros.h>
#include <drive/drivedata.h>

ros::NodeHandle  nh;

drive::drivedata dat;

int x5=5,x6=11,x1=10,x2=9,x3=6,x4=8;
int a=230,b=230;
char drv='l';

void straight()
{
  analogWrite(x5,a);
  analogWrite(x6,b);
  digitalWrite(x1,LOW);
  digitalWrite(x2,HIGH);
  digitalWrite(x3,LOW);
  digitalWrite(x4,HIGH);
}

void right()
{
  analogWrite(x5,a);
  analogWrite(x6,b);
  digitalWrite(x1,LOW);
  digitalWrite(x2,HIGH);
  digitalWrite(x3,HIGH);
  digitalWrite(x4,LOW);
}
void slowright()
{
  analogWrite(x5,a);
  analogWrite(x6,b);
  digitalWrite(x1,LOW);
  digitalWrite(x2,HIGH);
  digitalWrite(x3,LOW);
  digitalWrite(x4,HIGH); 
}
void left()
{
  analogWrite(x5,a);
  analogWrite(x6,b);
  digitalWrite(x1,HIGH);
  digitalWrite(x2,LOW);
  digitalWrite(x3,LOW);
  digitalWrite(x4,HIGH);
}
void slowleft()
{
  analogWrite(x5,a);
  analogWrite(x6,b);
  digitalWrite(x1,LOW);
  digitalWrite(x2,HIGH);
  digitalWrite(x3,LOW);
  digitalWrite(x4,HIGH); 
}
void back()
{
  analogWrite(x5,a);
  analogWrite(x6,b);
  digitalWrite(x1,HIGH);
  digitalWrite(x2,LOW);
  digitalWrite(x3,HIGH);
  digitalWrite(x4,LOW);
}

void STOP()
{
  analogWrite(x5,a);
  analogWrite(x6,b);
  digitalWrite(x1,LOW);
  digitalWrite(x2,LOW);
  digitalWrite(x3,LOW);
  digitalWrite(x4,LOW);
}

void messageCb( const drive::drivedata& msg)
{
  dat.num1=msg.num1;dat.num2=msg.num2;dat.drive=msg.drive;
  drv=msg.drive;
  if(drv=='w')
  straight();
  else if(drv=='a')
  left();
  else if(drv=='s')
  back();
  else if(drv=='d')
  right();
  else
  STOP();
}

ros::Subscriber<drive::drivedata> sub("drive_pub", &messageCb );
ros::Publisher pub("check", &dat);

void setup()
{ 
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(pub);
  
  pinMode(x1,OUTPUT);//for motor
  pinMode(x2,OUTPUT);//for motor
  pinMode(x3,OUTPUT);
  pinMode(x4,OUTPUT);
  pinMode(x5,OUTPUT);
  pinMode(x6,OUTPUT);

}

void loop()
{
  pub.publish(&dat);
  nh.spinOnce();
  delay(100);
}

