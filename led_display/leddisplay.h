#ifndef LEDDISPLAY_H
#define LEDDISPLAY_H

#include "Arduino.h"
#include <ShiftRegister74HC595.h>

class leddisplay 
{
private:
  void on(int pos,int neg);
public:
  void store(int col, int num);
  void disp(int data);
  void high();
};

#endif
