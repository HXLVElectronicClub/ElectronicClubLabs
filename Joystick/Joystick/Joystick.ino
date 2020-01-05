//Joystick module

const int K_pin = 3;
const int X_pin = A0;
const int Y_pin = A1;

void setup() {
  pinMode(K_pin, INPUT);
  digitalWrite(K_pin, HIGH); // Press down will read as 0, release will be 1
  Serial.begin(9600);
}

void loop() {
  Serial.print("Key: ");
  Serial.print(1-digitalRead(K_pin));
  Serial.print(",");
  Serial.print("X: ");
  Serial.print(analogRead(X_pin));
  Serial.print(", Y: ");
  Serial.print(analogRead(Y_pin));
  Serial.print("\n");
  delay(300);
}
