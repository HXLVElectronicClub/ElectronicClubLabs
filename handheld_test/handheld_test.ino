#include "LedControl.h"

/* Joystick PINs */
#define VRX     13
#define VRY     12
#define SW      14
#define JOY_VCC 27

/* Display PINs */
#define CLK     2
#define CS      4
#define DIN     16

#define CLK2 25
#define CS2  33
#define DIN2 32

#define BTNP 5
#define BTNN 18

LedControl lc2 = LedControl(DIN, CLK, CS, 1);
LedControl lc = LedControl(DIN2, CLK2, CS2, 1);

void setup() {
  // put your setup code here, to run once:
  pinMode(SW, INPUT_PULLUP);
  pinMode(BTNP, INPUT_PULLUP);
  pinMode(BTNN, OUTPUT);
  pinMode(VRX, INPUT);
  pinMode(VRY, INPUT);
  pinMode(JOY_VCC,OUTPUT);
  
  digitalWrite(JOY_VCC,1);
  digitalWrite(BTNN, 0);

  lc.shutdown(0, false);
  lc.setIntensity(0, 4);
  
  lc2.shutdown(0, false);
  lc2.setIntensity(0, 4);
}

int state = 0;
void loop() {
  if (state == 0) {
    testLed();
    state = 1;
  } else {
    testControl();
  }
}

void testLed() {
  for (int r = 0; r<16; r++) {
    for (int c = 0; c < 8; c++) {
         if (r < 8) {
          lc.setLed(0,r,c,1);
         } else {
          lc2.setLed(0,r-8,c,1);
         }
         delay(100);
    }
  }
}

void testControl() {
    // put your main code here, to run repeatedly:
  int dx = map(analogRead(VRX), 0, 4095, 0, 7);
  int dy = map(analogRead(VRY), 0, 4095, 7, 0);

  int sw = digitalRead(SW);
  int btn = digitalRead(BTNP);

  lc.clearDisplay(0);
  lc.setLed(0,dx, dy, 1);

  lc2.clearDisplay(0);
  if (sw == 0 || btn == 0) {
    lc2.setRow(0,3,0x18);
    lc2.setRow(0,4,0x18);
    delay(50);
    lc2.setRow(0,2,0x18);
    lc2.setRow(0,3,0x24);
    lc2.setRow(0,4,0x24);
    lc2.setRow(0,5,0x18);
  } 
  
  delay(100);
}
