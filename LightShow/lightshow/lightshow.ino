// Define used pin
// red is at 7, green 8, white 9, blue 10
#define RED 7
#define GREEN 8
#define WHITE 9
#define BLUE 10
#define BUTTON 12

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(WHITE, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(BUTTON, INPUT);
}

void loop() {
  int beat= 710; // time every beat
  int start=0;

  do {
    start = digitalRead(BUTTON);
  } while (!start);
  
  red(1);         // We
  delay(beat);
  red(0);         // will
  delay(beat); 
  red(1);         // we
  delay(beat);
  red(0);          //will
  delay(beat);
  all(1);          //rock
  delay(beat/4);
  all(0);
  delay(beat/4);
  all(1);         //you
  delay(beat/4);
  all(0);
  delay(beat/4);
  delay(beat);   // boom     
  all(1);         // rock
  delay(beat/4);
  all(0);
  delay(beat/4);
  all(1);        // you
  delay(beat/4);
  all(0);
  delay(beat/4);
  delay(beat);
  red(1);         // We
  delay(beat);
  red(0);         // will
  delay(beat); 
  red(1);         // we
  delay(beat);
  red(0);          //will
  delay(beat);
  all(1);          //rock
  delay(beat/4);
  all(0);
  delay(beat/4);
  all(1);         //you
  delay(beat/4);
  all(0);
  delay(beat/4);
  delay(beat);   // boom     
  all(1);         // rock
  delay(beat/4);
  all(0);
  delay(beat/4);
  all(1);        // you
  delay(beat/4);
  all(0);
  delay(beat/4);
  delay(beat);
}

void red(int lit) {
  digitalWrite(RED, lit);
}

void blue(int lit) {
  digitalWrite(BLUE, lit);
}

void white(int lit) {
  digitalWrite(WHITE, lit);
}

void green(int lit) {
  digitalWrite(GREEN, lit);
}

void all(int lit) {
  red(lit);blue(lit);white(lit);green(lit);
}
