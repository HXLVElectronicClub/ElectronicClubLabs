#include "LedControl.h"

#define DIN 12
#define CLK 10
#define CS 11

LedControl lc = LedControl(DIN,CLK,CS,1);
byte shape[8] = {B01100110,
                 B10011001,
                 B10000001,
                 B10000001,
                 B01000010,
                 B00100100,
                 B00011000,
                 B00000000};
byte shape1[8] = {B01100110,
                  B11111111,
                  B11011011,
                  B11000011,
                  B01100110,
                  B00111100,
                  B00011000,
                  B00000000};
byte shape2[8] = {B01100110,
                  B11111111,
                  B11111111,
                  B11111111,
                  B01111110,
                  B00111100,
                  B00011000,
                  B00000000}; 


void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
}

int dir = 2;
void loop() {
  displayMatrix(shape);
  delay(200);
  shift(dir, shape);
  shift(dir, shape1);
  shift(dir, shape2);
  displayMatrix(shape1);
  delay(200);
  shift(dir, shape);
  shift(dir, shape1);
  shift(dir, shape2);
  displayMatrix(shape2);
  delay(200);
  shift(dir, shape);
  shift(dir, shape1);
  shift(dir, shape2);
}

// dir: direction, left B10, right B11, up 1000, down 1100
void shift(int dir, byte* data) {
  if (dir & 0x3) {
    if (dir & 0x1) { // left
      for(int row=0; row<8; row++) {
        data[row] = (data[row] << 1) + (data[row] >> 7);
      }
    } else { // right
      for(int row=0; row<8; row++) {
        data[row] = (data[row] >> 1) + (data[row] << 7);
      }
    }
  }
  if (dir & 0xC) {
    if (dir & 0x4) { // down
      byte tmp = data[7];
      for(int row=7; row>0;row--) {
        data[row] = data[row-1];
      }
      data[0] = tmp;
    } else { // up
      byte tmp = data[0];
      for(int row=0; row<7;row++) {
        data[row] = data[row+1];
      }
      data[7] = tmp;
    }
  }
}

void displayMatrix(byte* shape) {
  for(int row=0;row<8;row++) {
    lc.setRow(0,row,shape[row]);
  }
}
