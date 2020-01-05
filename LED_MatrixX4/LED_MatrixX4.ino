#include "LedControl.h"

#define DIN 12
#define CLK 10
#define CS 11
#define DEVICE_NUM 8

LedControl lc = LedControl(DIN,CLK,CS,DEVICE_NUM);
int stat = 0;

byte displayBuffer[DEVICE_NUM*8];

int deviceOrder[DEVICE_NUM] = {0,1,2,3,
                               7,6,5,4,
                               8,9,10,11,
                               15,14,13,12};
//
int deviceOren[DEVICE_NUM] = {1,0,0,0,
                              2,2,2,2,
                              1,0,0,0,
                              2,2,2,2};

void setup() {
  for (int i=0;i<DEVICE_NUM;i++) {
    lc.shutdown(i, false);
    lc.setIntensity(i,8);
    lc.clearDisplay(i);
  }
}

void loop() {
  for (int i=0;i<DEVICE_NUM;i++) {
    uint64_t letter;
    memcpy_P(&letter, &LETTERS[i], 8);
    display64(i,letter);
  }
  //displayImage();
  delay(2000);
}

void display64(int dev, uint64_t image) {
  for (int i=0;i<8;i++) {
    byte row=(image >>i*8) & 0xFF;
    lc.setRow(dev,i,row);
  }
}

void displayImage() {
  for (int i=0; i<DEVICE_NUM;i++) {
    for (int row=0; row<8; row++) {
      lc.setRow(i, row, displayBuffer[i*8+row]);
    }
  }
}
