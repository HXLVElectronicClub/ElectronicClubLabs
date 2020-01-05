#include "LedControl.h"

#define DIN 12
#define CLK 10
#define CS 11

LedControl lc = LedControl(DIN,CLK,CS,1);

void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
}

/*
 * 0 (0,0)
 * 1 (0,0)(0,1)(1,0)(1,1)
 * 2
 * 3
 */
bool stat = 1;
void loop() {
  // another method
  for (int i=0; i<8; i++) {
    for (int row = 0; row <=i; row++) {
      for (int col =0; col <=i; col++) {
          lc.setLed(0, row, col, stat);
      }      
    }
    delay(300);
  }
  stat = !stat;  
}
