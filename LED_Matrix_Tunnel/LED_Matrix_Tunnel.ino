#include "LedControl.h"

#define DIN 12
#define CLK 10
#define CS 11

LedControl lc = LedControl(DIN,CLK,CS,1);
int stat = 0;

void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
}

/*
 * 0 (0,0)
 * 1 (0,1)(1,0)
 * 2 (0,2)(1,1)(2,0)
 * 3 (0,3)(1,2)(2,1)(3,0)
 * 4      (1,3)(2,2)(3,1)  
 * 5           (2,3)(3,2)
 * 6                (3,3)
 */ 
 
void loop() {
  /*
  for (int i=7;i>=0;i--) {
   for (int j=0;j<=i;j++) {
     int row = j;
     int col = i-j;
     if (col < 4 && row < 4) {
      lc.setLed(0,row,col,1);
      lc.setLed(0,row,7-col,1);
      lc.setLed(0,7-row,col,1);
      lc.setLed(0,7-row,7-col,1);
     }
   }
   delay(100);
   lc.clearDisplay(0);
  }*/

   // another method
  for (int i=7;i>=0;i--) {
    for (int row=0;row<4;row++) {
      for (int col = 0; col <4; col++) {
        if (row+col    == i 
          || row + col  == i+3 
        
        ){
          lc.setLed(0, row, col, 1);
          lc.setLed(0,row,7-col,1);
          lc.setLed(0,7-row,col,1);
          lc.setLed(0,7-row,7-col,1);
        }
      }
    }
    delay(100);
    lc.clearDisplay(0);
  }
  
}
