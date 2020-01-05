#include "LedControl.h"

#define DIN 12
#define CLK 10
#define CS 11

#define Key 2
#define XPIN A0
#define YPIN A1

LedControl lc = LedControl(DIN,CLK,CS,1);
byte empty[8] = {B00000000,
                 B00000000,
                 B00000000,
                 B00000000,
                 B00000000,
                 B00000000,
                 B00000000,
                 B00000000,};

void setup() {
  randomSeed(analogRead(0));
  pinMode(Key, INPUT);
  digitalWrite(Key, HIGH);
  lc.shutdown(0, false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
}

void loop() {
  int key = 1-digitalRead(Key);
  int X = analogRead(XPIN);
  int Y = analogRead(YPIN);
  int x = map(X/10,0,102, 0,7);
  int y = map(Y/10,0,102, 0,7);

  lc.clearDisplay(0):
  lc.setLed(0,x,y,1); // control a single pixel
}

void displayMatrix(byte* shape) {
  for(int row=0;row<8;row++) {
    lc.setRow(0,row,shape[row]);
  }
}
