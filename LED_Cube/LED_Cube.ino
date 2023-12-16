#define TIMER_INTERRUPT_DEBUG         0
#define _TIMERINTERRUPT_LOGLEVEL_     0

#define USE_TIMER_1     true

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "TimerInterrupt.h"

#define TIMER1_INTERVAL_MS    5

#define CLOCK  0
#define LATCH 1
#define DATA 3
#define EN   2
#define LEVEL0 4
#define LEVEL1 5
#define LEVEL2 6
#define LEVEL3 7

unsigned int cache[4];

void setup() {
  ITimer1.init();
  ITimer1.attachInterruptInterval(TIMER1_INTERVAL_MS, display);

  pinMode(CLOCK, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(DATA,  OUTPUT);
  pinMode(EN  ,  OUTPUT);
  pinMode(LEVEL0, OUTPUT);
  pinMode(LEVEL1, OUTPUT);
  pinMode(LEVEL2, OUTPUT);
  pinMode(LEVEL3, OUTPUT);
  digitalWrite(LEVEL0, HIGH);
  digitalWrite(LEVEL1, HIGH);
  digitalWrite(LEVEL2, HIGH);
  digitalWrite(LEVEL3, HIGH);
  
}

void display() {
  static int level = 3;
  if (cache[level] != 0) digitalWrite(level + LEVEL0, HIGH);
  level = (++level)&0x3;
  digitalWrite(LATCH, LOW);
  digitalWrite(EN, HIGH);
  shiftOut(DATA,CLOCK,MSBFIRST, cache[level]>>8);
  shiftOut(DATA,CLOCK,MSBFIRST, cache[level]);
  digitalWrite(LATCH, HIGH);
  digitalWrite(EN, LOW);
  if (cache[level] != 0) digitalWrite(level + LEVEL0, LOW);
}

void setLed(char x, char y, char z, char val) {
  if (val) {
    cache[z] |= 1 << (y*4+x);
  } else {
    cache[z] &= ~(1 << (y*4+x));
  }
}

void clear() {
  cache[0] = 0;
  cache[1] = 0;
  cache[2] = 0;
  cache[3] = 0;
}

void animation1() {
  static int u = 1, v = 0;
  for(int i=0;i<4;i++) {
    for (int j=0;j<4;j++) {
      for(int k=0;k<4;k++) {
        if (i+j+k<=v) {
          setLed(i, j, k, u);
        } else {
          setLed(i, j, k, 1-u);
        }
      }
    }
  }
  if (v==9) {
    v = 0;
    u = 1-u;
  } else {
    v++;
  }
  delay(150);  
}

void animation2() {
  for (int x = 0; x < 4; x++) {
    setLed(x, 1, 0, 1);
    setLed(x, 2, 0, 1);
    setLed(x, 0, 1, 1);
    setLed(x, 3, 1, 1);
    setLed(x, 0, 2, 1);
    setLed(x, 3, 2, 1);
    setLed(x, 1, 3, 1);
    setLed(x, 2, 3, 1);
    delay(200);
    clear();
  }
}

void rectangle() {
  setLed(0,0,0,1);
  setLed(0,0,1,1);
  setLed(0,0,2,1);
  setLed(0,0,3,1);
  setLed(3,0,1,1);
  setLed(3,0,2,1);
  setLed(3,0,3,1);
  setLed(3,0,0,1);
  setLed(1,0,0,1);
  setLed(1,0,3,1);
  setLed(2,0,0,1);
  setLed(2,0,3,1);
  delay(1000);
}

void cube() {
  for(int x=0;x<4;x++) {
    for(int y=0;y<4;y++) {
      for(int z=0;z<4;z++) {
        if (z==0 || z==3) {
          if (x==0 || x==3 || y==0 || y==3)
            setLed(x, y, z, 1);
        } else { // z==1,2
          if (((x*y==0)&&(x+y==0 || x+y==3)) || x+y==6)
            setLed(x, y, z, 1);
        }
      }
    }
  }
  delay(1000);
}

void loop() {
  setLed(0, 0, 0, 1);
  //rectangle();
  //cube();
  //animation1();
  //animation2();
}
