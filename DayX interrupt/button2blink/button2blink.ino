#define BUTTON 8
#define LED 7
void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

bool on=0;
bool led = 0;
void loop() {
  int but = digitalRead(BUTTON);
  Serial.println(but);
  if (but==0) {
    on = !on;
    delay(200);
  }
  if (on == 1) {
    led = !led;
    digitalWrite(LED,led);
    delay(1000);
  } else {
    digitalWrite(LED,0);
  }
}
