/*
 * The following code is an implementation for the arduino library developed for using in a 2D Dot matrix printer ie a DIY project made from old CD drives.
 */

#include <dot_printer.h>
dot_printer prt;

void setup()
{
prt.initialize();
}
boolean mast=false;
//int fig[9][9]={{0,1,1,1,1,0,0,0,0},{1,0,0,0,0,1,0,0,0},{1,0,0,0,0,0,1,0,0},{0,1,0,0,0,0,0,1,0},{0,0,1,0,0,0,0,0,1},{0,1,0,0,0,0,0,1,0},{1,0,0,0,0,0,1,0,0},{1,0,0,0,0,1,0,0,0},{0,1,1,1,1,0,0,0,0}};
//int fighpy[10][10]={{0,0,1,1,1,1,1,1,0,0},{0,1,0,0,0,0,0,0,1,0},{1,0,0,1,0,0,0,0,0,1},{1,0,1,1,0,1,1,0,0,1},{1,0,0,0,0,0,0,1,0,1},{1,0,0,0,0,0,0,1,0,1},{1,0,1,1,0,1,1,0,0,1},{1,0,0,1,0,0,0,0,0,1},{0,1,0,0,0,0,0,0,1,0},{0,0,1,1,1,1,1,1,0,0}};
//int figsad[10][10]={{0,0,1,1,1,1,1,1,0,0},{0,1,0,0,0,0,0,0,1,0},{1,0,0,1,0,0,1,1,0,1},{1,0,1,1,0,1,0,0,0,1},{1,0,0,0,0,1,0,0,0,1},{1,0,0,0,0,1,0,0,0,1},{1,0,1,1,0,1,0,0,0,1},{1,0,0,1,0,0,1,1,0,1},{0,1,0,0,0,0,0,0,1,0},{0,0,1,1,1,1,1,1,0,0}};
void loop()
{
if(mast==false)
{
  /*
  for(int i=0;i<9;i++)
    {
      for(int j=0;j<9;j++)
      {
        if(fig[i][j]==1)
          prt.dot();
        prt.drag(10);
      }
      prt.slide(25);
      prt.drag(-90);
    }
    */
    /*
    for(int i=0;i<10;i++)
    {
      for(int j=0;j<10;j++)
      {
        if(fighpy[i][j]==1)
          prt.dot();
        prt.drag(15);
      }
      prt.slide(25);
      prt.drag(-150);
    }
    prt.slide(40);
    prt.set('d',12);
    for(int i=0;i<10;i++)
    {
      for(int j=0;j<10;j++)
      {
        if(figsad[i][j]==1)
          prt.dot();
        prt.drag(15);
      }
      prt.slide(30);
      prt.drag(-150);
    }
    */
   prt.printdata("GREEN");
  mast=true;
}
}
