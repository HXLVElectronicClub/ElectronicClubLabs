#include "LedControl.h"

#define DIN 12
#define CLK 10
#define CS 11
#define Key 2
#define XPIN A0
#define YPIN A1

LedControl lc = LedControl(DIN,CLK,CS,1);
const int fps = 30;
const unsigned long frameDelay = 1000/fps ;
const int snakeFrame = 80; //one move take 20 frame = 1000/30 * 20 ms

int length = 2; //initial length
enum Direction {
  UP=1,
  DOWN=2,
  LEFT=4,
  RIGHT=8
};
Direction snake[64];// snake directions

byte snakePos = 36; // snake position (row*8+col), default is the center of board
byte buffer[8]; // display buffer
Direction keyDir;

int stat;
bool keyPress=false;;

void setup() {
  randomSeed(analogRead(5));
  Serial.begin(9600);
  pinMode(Key, INPUT);
  digitalWrite(Key, HIGH);
  lc.shutdown(0, false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
  for (int i=0;i<8;i++) buffer[i] = 0;
}

void loop() {
  static unsigned long lastMillis =millis();
  static unsigned long passedMillis =0;
  passedMillis += millis() - lastMillis;
  if (passedMillis >= frameDelay) {
    lastMillis = millis();
    passedMillis-=frameDelay;
    readJoyStick();
    if (stat == 0) {
      if (keyPress) {
        snakePos = 36;
        stat = 1;
      }
    } else {
      if (frameSync()) {
        snakeMove(keyDir);
        drawSnake();
        if (collision()){ // check collision after snake move, incase head hit tail
          //stat = 0;
        }
        Serial.println();
      }
    }
    drawBuffer();
  }
}

void readJoyStick() {
  static bool lastkey;
  bool key = 1-digitalRead(Key);
  int X = analogRead(XPIN);
  int Y = analogRead(YPIN);
  int x = map(X/10,0,102, 0,7);
  int y = map(Y/10,0,102, 0,7);

  if (!keyPress) {
    if (!lastkey && key) {
      keyPress = true;
    }
  } else {
    keyPress = false;
  }
  lastkey = key;

  if (x > 5 ) keyDir = LEFT;
  else if (y > 5 ) keyDir = UP;
  else if (x < 3) keyDir = RIGHT;
  else if (y < 3) keyDir = DOWN;  
}

bool frameSync() {
  static int frameCount = 0;
  frameCount++;
  if (frameCount < snakeFrame) {
    return false;
  } else {    
    frameCount=0;
    return true;
  }
}

void snakeMove(Direction dir) {
  int y = snakePos/8;
  int x = snakePos%8;
  if ((dir == UP && snake[0] == DOWN)
    ||(dir == DOWN && snake[0] == UP)
    ||(dir == LEFT && snake[0] == RIGHT)
    ||(dir == RIGHT && snake[0] == LEFT)) {
        return;
  }
  // shift the position
  for (int i=0; i<length-1;i++)
    snake[i+1] = snake[i];
  snake[0] = dir;
  if (dir==UP && y>0) {
    y--;
  } else if (dir==DOWN && y<7) {
    y++;
  } else if (dir==LEFT && x<7) {
    x++;
  } else if (dir==RIGHT && x>0) {
    x--;
  }
  snakePos = y*8+x;
}

void drawSnake() {
  int y = snakePos/8;
  int x = snakePos%8;
  // trace the snake from head to tail
  bitSet(buffer[y],x); //set the new head
  Serial.print("dir:");
  Serial.print(keyDir);
  Serial.print("x=");
  Serial.print(x);
  Serial.print("y=");
  Serial.print(y);
  for(int i=0;i<length;i++) {
    if (snake[i]==UP) {
      y++;    
    } else if (snake[i]==DOWN) {
      y--;
    } else if (snake[i]==LEFT) {
      x--;
    } else if (snake[i]==RIGHT) {
      x++;
    }
  }
  bitClear(buffer[y],x);// clear the bit on tail
  Serial.print("    clear tail x=");
  Serial.print(x);
  Serial.print("y=");
  Serial.print(y);
}

bool collision() {
  int x = snakePos%8;
  int y = snakePos/8;
  // check if the snake hit the boundary
  if ((snake[0] == UP && y==0) ||
      (snake[0] == DOWN && y==7)||
      (snake[0] == LEFT && x==0)||
      (snake[0] == RIGHT && x==7)) {
        return true;    
  }
  // check if the snake hit itself
  if (bitRead(buffer[y],x) == 1){
    return true;
  }
  return false;
}

void drawBuffer() {
  lc.clearDisplay(0);
  for(int i=0;i<8;i++) {
    lc.setRow(0,i,buffer[i]);
  }
}

void rotateBuffer(int angle) {
  byte buffer2[8];
  for (int row=0;row<8;row++) {
    for (int col=0;col<8;col++) {
      if (bitRead(buffer[row],col)==1) {
        float col1 = col*cos(angle)-row*sin(angle);
        float row1 = col*sin(angle)+row*cos(angle);
        bitWrite(buffer[(int)row1],(int)col1,1);
      }
    }
  }
  for (int row=0;row<8;row++) {
    buffer[row] = buffer2[row];
  }
}
