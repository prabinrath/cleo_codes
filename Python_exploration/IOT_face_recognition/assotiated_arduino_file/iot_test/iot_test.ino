//Green led attached to pin 11 an Red led attached to pin 6
void setup() {
  // put your setup code here, to run once:
  pinMode(6,OUTPUT);
  pinMode(11,OUTPUT);
  Serial.begin(9600);
}

String choice;
void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available())
  {
    choice=Serial.readString();
    if(choice=="r")
    {digitalWrite(6,HIGH);digitalWrite(11,LOW);}
    else if(choice=="g")
    {digitalWrite(6,LOW);digitalWrite(11,HIGH);}
    else
    {digitalWrite(6,LOW);digitalWrite(11,LOW);}
  }
}
