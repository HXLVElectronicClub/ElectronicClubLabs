/**
 * Snake
 * Implementation of the classical Snake game 
 * where the snake moved constantly and the player
 * have to avoid intersections with itself and borders.
 * When the snake eats food it grows and speeds up a little bit.
 * 
 * 23 Jun 2016
 * by Sergey Royz and hunter Buzzell
 */

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

//#define SIZE    8
#define SIZE_W  8
#define SIZE_H  16

#define ADVANCE_DELAY 1300


int snake[SIZE_W*SIZE_H][2];
int length;
int food[2], v[2];
bool is_game_over = false;
long current_time;
long prev_advance;
int blink_count;
const short messageSpeed = 8;

LedControl lc2 = LedControl(DIN, CLK, CS, 1);
LedControl lc = LedControl(DIN2, CLK2, CS2, 1);

void init_game() {
  prev_advance = current_time = 0;
  blink_count = 3;
  int half = SIZE_W / 2;
  length = 2;

  for (int i = 0; i < length; i++) {
      snake[i][0] = half - 1;
      snake[i][1] = half + i;
  }

  randomFood();
  //food[0] = half + 1;
  //food[1] = half - 1;

  v[0] = 0;
  v[1] = -1;
}

byte buff[SIZE_H];

void render() {
  for (int i=0; i < SIZE_H; i++) {
    buff[i] = 0;
  }
  for (int i=0; i< length; i++) {
    buff[snake[i][0]] = buff[snake[i][0]] | (B10000000>>snake[i][1]);
  }
  
  buff[food[0]] = buff[food[0]] | (B10000000>>food[1]);
  
  for (int y = 0; y < SIZE_H; y++) {
    //if (buff[y] > 0) {
      if (y < 8) {
        lc.setRow(0,y,buff[y]);
      } else {
        lc2.setRow(0,y-8,buff[y]);
      }
    //}
  }
}

void clearScreen() {
  /*for (int x = 0; x < SIZE; x++) {
    for (int y = 0; y < SIZE; y++) {
      lc.setLed(0, x, y, 0);
    }
  }*/
  lc.clearDisplay(0);
  lc2.clearDisplay(0);
}

/**
 * moves the snake forward
 * returns true if the game is over
 */
bool advance() {
  int head[2] = {snake[0][0] + v[0], snake[0][1] + v[1]};

  if (head[0] < 0 || head[0] >= SIZE_H) {

            delay(1000);
    showGameOverMessage();
      return true;
  }

  if (head[1] < 0 || head[1] >= SIZE_W) {

            delay(1000);
    showGameOverMessage();
      return true;
  }

  for (int i = 1; i < length; i++) {
      if (snake[i][0] == head[0] && snake[i][1] == head[1]) {
            delay(1000);
        showGameOverMessage();
          return true;
      }
  }

  bool grow = (head[0] == food[0] && head[1] == food[1]);
  if (grow) {
      length++;    
      //randomSeed(current_time);
      //food[0] = random(SIZE_H);
      //food[1] = random(SIZE_W);
      randomFood();
  }

  for (int i = length - 1; i >= 0; i--) {
      snake[i + 1][0] = snake[i][0];
      snake[i + 1][1] = snake[i][1];
  }
  snake[0][0] += v[0];
  snake[0][1] += v[1];
  return false;
}

void setup() {
  randomSeed(analogRead(36));
  pinMode(SW, INPUT_PULLUP);
  pinMode(BTNP, INPUT_PULLUP);
  pinMode(BTNN, OUTPUT);
  pinMode(VRX, INPUT);
  pinMode(VRY, INPUT);
  pinMode(JOY_VCC,OUTPUT);
  
  digitalWrite(JOY_VCC,1);
  digitalWrite(BTNN, 0);
  attachInterrupt(digitalPinToInterrupt(SW), restart, RISING);

  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  

  lc2.shutdown(0, false);
  lc2.setIntensity(0, 8);
  
  init_game();
  render();
}

void loop() {
  if (!is_game_over) {
    //clearScreen();
    render();

    if (current_time - prev_advance > ADVANCE_DELAY) {
      is_game_over = advance();
      prev_advance = current_time;    
    }
  } else {
    while (blink_count > 0) {
      //clearScreen();
      delay(300);
      render();
      delay(300);
      blink_count--;     
         
    }
  }
  readControls();
  current_time++;
}

void restart() {  
  init_game();
  is_game_over = false;
}

void readControls() {
  int dx = map(analogRead(VRX), 0, 4095, -2, 2);
  int dy = map(analogRead(VRY), 0, 4095, 2, -2);
  if (dx != 0) {dx = dx / abs(dx);}
  if (dy != 0) {dy = dy / abs(dy);}

  if ((dx + v[0] != 0) || (dy + v[1] != 0)) { // == 0 means joystick goes backwards, no effect
  if (dy != 0 && v[0] != 0) {
    v[0] = 0;
    v[1] = dy;    
  }

  if (dx != 0 && v[1] != 0) {
    v[0] = dx;
    v[1] = 0;
  }
  }
}

const PROGMEM bool gameOverMessage[8][90] = {
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,0,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,1,0,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,1,1,0,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0}
}; 

void showGameOverMessage() {
  lc2.clearDisplay(0);
  for (int d = 0; d < sizeof(gameOverMessage[0]) - 7; d++) {
    for (int col = 0; col < 8; col++) {
      delay(messageSpeed);
      for (int row = 0; row < 8; row++) {
        // this reads the byte from the PROGMEM and displays it on the screen
        lc.setLed(0, row, col, pgm_read_byte(&(gameOverMessage[row][col + d])));
        //lc2.setLed(0, row, col, pgm_read_byte(&(gameOverMessage[row][col + d])));
      }
    }
  }
}

void randomFood() {
  int flag = 1;

  while (flag == 1) {
    flag = 0;  
    food[0] = random(SIZE_H);
    food[1] = random(SIZE_W);
    for (int i=0; i< length; i++) {
      if (food[0] == snake[i][0] && food[1] == snake[i][1]) {
        flag = 1;
        break;
      }
    }
  }
}
