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
   //uncomment for animation
//byte shape1[8] = {B01100110,
//                  B11111111,
//                  B11011011,
//                  B11000011,
//                  B01100110,
//                  B00111100,
//                  B00011000,
//                  B00000000};
//byte shape2[8] = {B01100110,
//                  B11111111,
//                  B11111111,
//                  B11111111,
//                  B01111110,
//                  B00111100,
//                  B00011000,
//                  B00000000}; 


void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
}

void loop() {
  displayMatrix(shape);
   //uncomment for animation
//  delay(500);
//  displayMatrix(shape1);
//  delay(500);
//  displayMatrix(shape2);
//  delay(500);
  
}

void displayMatrix(byte* shape) {
  for(int row=0;row<8;row++) {
    lc.setRow(0,row,shape[row]);
  }
}
