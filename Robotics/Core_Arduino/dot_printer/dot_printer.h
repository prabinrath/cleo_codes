#ifndef DOT_PRINTER_H
#define DOT_PRINTER_H

#include "Arduino.h"
#include <Servo.h>
#include <Stepper.h>
#include <String.h>

class dot_printer
{
private:
  void draw(int let[5][9]); //to draw a letter
  void check(); //to check the state for leds
  void next(); //helper function
public:
  void initialize(); //to initialize printer parameters
  void dot(); //function to put a singlr dot on paper axis-z control servo
  void slide(int); //function to slide the paper along y axis-y control DC motor
  void drag(int); //function to drag along x axis-x control mini stepper
  void printdata(String dat); //to recieve a string to be printed
  void printchar(char); //to print a character on paper by selecting specific 2D binary array
  void set(char,int); //set parameter dynamically
};
#endif