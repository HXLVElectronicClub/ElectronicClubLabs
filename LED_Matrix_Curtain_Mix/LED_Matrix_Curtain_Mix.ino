#include "LedControl.h"

#define DIN 12
#define CLK 10
#define CS 11

LedControl lc = LedControl(DIN,CLK,CS,1);

byte A[8] = {0x00,0x3c,0x66,0x66,0x7e,0x66,0x66,0x66};
byte Buffer[8];

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
  for (int i=0; i<8; i++) {
    for (int row = 0; row <=8; row++) {
      for (int col =0; col <=8; col++) {
        if ( row <=i && col <=i) {
         bitWrite(Buffer[row],col,stat);
        } else {
          bitWrite(Buffer[row],col,!stat);
        }
      }      
    }
    for (int row = 0; row < 8; row++) {
      Buffer[row] = Buffer[row] ^ A[row];
    }
    displayImage(Buffer);
    delay(300);
  }
  stat = !stat;  
}

void displayImage(byte *image) {
  for(int row=0;row<8;row++) {
    lc.setRow(0,row,image[row]);
  }
}
