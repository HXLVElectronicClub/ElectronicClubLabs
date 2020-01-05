#include "LedControl.h"

#define DIN 12
#define CLK 10
#define CS 11
#define Key 2
#define XPIN A0
#define YPIN A1

LedControl lc = LedControl(DIN,CLK,CS,1);

unsigned long frameDelay = 1000/15 ;
int stat = 0; 
bool keyin = false;
unsigned long curMillis, passedMillis;

void setup() {
  randomSeed(analogRead(5));
  Serial.begin(9600);
  pinMode(Key, INPUT);
  digitalWrite(Key, HIGH);
  lc.shutdown(0, false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
  curMillis = millis();
}

void loop() {
  static unsigned long lastMillis =0;
  static unsigned long passedMillis =0;
  passedMillis = millis() - lastMillis;
  if (passedMillis >= frameDelay) {
    //Serial.println(passedMillis);
    lastMillis = millis();
    //passedMillis-=frameDelay;
    readJoyStick();
    //lc.clearDisplay(0);
    drawTree();
    drawDino();
    collision();
  }
}

void readJoyStick() {
  static bool lastkey;
  bool key = 1-digitalRead(Key);
  //int X = analogRead(XPIN);
  int Y = analogRead(YPIN);
  //int x = map(X/10,0,102, 0,7);
  int y = map(Y/10,0,102, 0,7);

  if (!keyin) {
    if (!lastkey && key) {
      keyin = true;
    }
  } else {
    keyin = false;
  }
  lastkey = key;
}
int dinoUpFrame = 10;
int dinoDownFrame = 10;
void drawDino() {
  static int dinoStat;
  static int framecount;
  static byte dino = 15;
  int offset = 0;
  if (dinoStat == 0) {
    if(keyin) { // start to jump
      dinoStat = 1; // go up
      framecount = 0;
    }
  } if (dinoStat == 1) {
    if (framecount == dinoUpFrame) {
      dinoStat = 2; // go down
      framecount = dinoDownFrame;
    }
    framecount ++;
    offset = (framecount*5)/dinoUpFrame;
  } else if (dinoStat == 2) {
    if (framecount == 0) {
      dinoStat = 0;
    }
    framecount --;
    offset = (framecount *5)/dinoDownFrame;
  }
  lc.setColumn(0,0,dino<<offset);
}
int dinoSpeed = 3;
void drawTree() {
  static byte trees[8];
  static int pointer = 0;
  static int framecount = 0;
  framecount++;
  if (framecount == dinoSpeed) {
    framecount = 0;
    trees[pointer] = (random(4)== 4);
    pointer ++;
    if (pointer == 8) pointer = 0;
    
    for (int i=7;i>0;i--) {
      int col = i + pointer;
      if (col > 8 ) col -= 8;
      if (trees[col] > 0) {
        lc.setColumn(0,i+1, 7);
      } else {
        lc.setColumn(0,i+1,0);
      }
    }
  }
}

void collision() {
  
}
