#include "LedControl.h"

#define DIN 12
#define CLK 10
#define CS 11

// change this varialbe from 1 to 5 to show different demo
int DEMO = 2; //1, 2, 3, 4,5

//   0 1 2 3 4 5 6 7
// 0 O O O O O O O O
// 1 O O O O O O O O
// 2 O O O O O O O O
// 3 O O O O O O O O
// 4 O O O O O O O O
// 5 O O O O O O O O
// 6 O O O O O O O O
// 7 O O O O O O O O

LedControl lc = LedControl(DIN,CLK,CS,1);
int stat = 0;

void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
}

void loop() {
  if (DEMO == 1) { // set a single LED
//   0 1 2 3 4 5 6 7
// 0 O O O O O O O O
// 1 O O O O O O O O
// 2 O O O O O O O O
// 3 O O O O O O O O
// 4 O O O O X O O O
// 5 O O O O O X O O
// 6 O O O O O O X O
// 7 O O O O O O O O
    lc.setLed(0, 4, 4, 1);
    lc.setLed(0, 5, 5, 1);
    lc.setLed(0, 6, 6, 1);
  } else if (DEMO == 2) { // scan every LED
    for (int row= 0; row <8; row++) {
      for (int col=0; col<8;col++) {
        lc.setLed(0, row, col, stat);
        delay(200);
      }
    }
    if (stat==1) 
      stat = 0;
    else 
      stat = 1;
  } else if (DEMO == 3) { // flash every LED
    for (int row = 0; row < 8; row ++) {
      for (int col = 0; col < 8; col ++) {
        lc.setLed(0, row, col, 1 );
        delay(300);
        lc.setLed(0, row, col, 0);
      }
    }    
  } else if (DEMO == 4) { // flash interval                                 
    //XOXOXOXO
    //OXOXOXOX
    //XOXOXOXO
    //OXOXOXOX
    //XOXOXOXO
    //OXOXOXOX
    //XOXOXOXO
    //OXOXOXOX
    for (int row=0;row<8;row++) {
      for (int col = 0; col < 8; col++) {
        if (stat == 1) {
          if ((row+col)%2 == 0) {
            lc.setLed(0, row, col, 1);
          } else {
            lc.setLed(0, row, col, 0);
          }
        } else if (stat == 0) {
          if ((row+col)%2 == 1) {
            lc.setLed(0, row,col, 1);
          } else {
            lc.setLed(0, row, col, 0);
          }
        }
      }
    }
    if (stat == 1) stat = 0 ;
    else stat = 1;
    delay(500);
  } else if (DEMO == 5) { // same as demo 4, Optimzied code
    for (int row=0;row<8;row++) {
      for (int col=0; col<8;col++) {
        bool light = ((row+col)%2 == stat);
        lc.setLed(0, row, col, light); 
      }
    }
    stat = 1-stat;
    delay(300);
  }
}
