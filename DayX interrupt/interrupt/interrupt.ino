#define BUTTON 2
#define LED 7

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON),blink,FALLING);
}

volatile bool on=0;
bool led = 0;
void loop() {
  if (on == 1) {
    led = !led;
    digitalWrite(LED,led);
    delay(1000);
  }
}

void blink() {
  on = !on;
}
