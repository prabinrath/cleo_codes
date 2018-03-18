#include <leddisplay.h>
leddisplay sony;
void setup()
{  
  sony.high();
}
int count=0;
void loop()
{
  sony.disp(count);
  count++;
}
