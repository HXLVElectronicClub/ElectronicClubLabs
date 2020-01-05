
#include "LedControl.h"

#define DIN 12
#define CLK 10
#define CS 11

LedControl lc = LedControl(DIN,CLK,CS,1);
int stat = 0;
int stat2 = 0;

void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
}

void loop() {
  for (int row=0;row<8;row++) {
    for (int col = 0; col < 8; col++) {
      if (row <= stat && col <= stat)
        lc.setLed(0, row, col, stat2);
      else
        lc.setLed(0, row, col, 1-stat2);
    }
  }
  stat ++;
  if (stat > 7) {
    stat = 0;
    stat2 = 1-stat2;  // toggle stat2
  }
  
  delay(500);
}
