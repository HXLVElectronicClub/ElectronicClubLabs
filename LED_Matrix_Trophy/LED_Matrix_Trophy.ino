#include "LedControl.h"

#define DIN 12
#define CLK 10
#define CS 11

LedControl lc = LedControl(DIN,CLK,CS,4);
byte data[32] ={
0x00, 0x00, 0x18, 0x18, 0x3c, 0xff, 0xff, 0xbd, 0xbd, 0xbd, 0xbd, 0xbd, 0xbd, 0xbd, 0xff, 0x7e, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x18, 0x18, 0x18, 0x3c, 0x3c, 0x7c, 0x7e, 0x7e, 0xff, 0xff
};

void setup() {
  for (int dev=0;dev<4;dev++) {
  lc.shutdown(dev, false);
  lc.setIntensity(dev,8);
  lc.clearDisplay(dev);
  }
  pinMode(13,OUTPUT);
}
int i=0;
void loop() {
  /*for (int width = 8; width>=-6; width-=2) {
    displayMatrix(scale(abs(scale)));
    delay(200);
  }*/
  displayMatrix(data);
  delay(500);
  i=1-i;
  digitalWrite(13,i);
}
/*
// scale image, and center
void scale(int width) {
  if (scale == 8) { 
    return data;
  } else {
    byte newdata[32],tmp;
    for (int i=0;i<32;i++) {
      if ((scale/2)==3) {
        bitWrite(newdata[i],7,0);
        tmp = bitRead(data[i],6) + bitRead(data[i],7)*3;
        bitWrite(newdata[i],6,tmp/3);
        
        bitWrite(newdata[i],5,((int)bitRead(data[i],5)*2 + (int)bitRead(data[i],6)*2)/3);
        bitWrite(newdata[i],4,((int)bitRead(data[i],4)*3 + (int)bitRead(data[i],5))/3);
        bitWrite(newdata[i],3,((int)bitRead(data[i],3)*3 + (int)bitRead(data[i],2))/3);
        bitWrite(newdata[i],2,((int)bitRead(data[i],2)*2 + (int)bitRead(data[i],1)*2)/3);
        bitWrite(newdata[i],1,((int)bitRead(data[i],1)   + (int)bitRead(data[i],0)*3)/3);
        bitWrite(newData[i],0,0));
      } else if((scale/2)==2) {
        bitWrite(newdata[i],7,0);
        bitWrite(newData[i],6,0);
        bitWrite(newdata[i],5,((int)bitRead(data[i],6)+(int)bitRead(data[i],7))/2);
        bitWrite(newdata[i],4,((int)bitRead(data[i],4)+(int)bitRead(data[i],5))/2);
        bitWrite(newdata[i],3,((int)bitRead(data[i],3)+(int)bitRead(data[i],2))/2);
        bitWrite(newdata[i],2,((int)bitRead(data[i],1)+(int)bitRead(data[i],0))/2);
        bitWrite(newdata[i],1,0);
        bitWrite(newData[i],0,0);
      } else if ((scale/2)==1) {
        bitWrite(newdata[i],7,0);
        bitWrite(newdata[i],6,0);
        bitWrite(newdata[i],5,0);
        bitWrite(newData[i],4,((int)bitRead(data[i],4)+(int)bitRead(data[i],5)+(int)bitRead(data[i],6)+(int)bitRead(data[i],7))/4);
        bitWrite(newData[i],3,((int)bitRead(data[i],3)+(int)bitRead(data[i],2)+(int)bitRead(data[i],1)+(int)bitRead(data[i],0))/4);
        bitWrite(newdata[i],2,0);
        bitWrite(newdata[i],1,0);
        bitWrite(newdata[i],0,0);
      }
    }
  }
}
*/
void displayMatrix(byte* shape) {
  for (int dev=0;dev<4;dev++){
    for(int col=0;col<8;col++) {
      lc.setColumn(dev,7-col,data[dev*8+col]);
    }
  }
}
