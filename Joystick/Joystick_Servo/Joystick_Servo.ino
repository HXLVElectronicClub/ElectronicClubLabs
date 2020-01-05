//Joystick controlling servo
#include "Servo.h"

const int K_pin = 2;
const int X_pin = A0;
const int Y_pin = A1;
const int servo1_pin = 3;
const int servo2_pin = 5;
const int servo3_pin = 6;
const int servo4_pin = 9;

Servo servo1;
//Servo servo2;
//Servo servo3;
//Servo servo4;
void setup() {
  servo1.attach(servo1_pin);
  //servo2.attach(servo2_pin);
  //servo3.attach(servo3_pin);
  //servo4.attach(servo4_pin);
  pinMode(K_pin, INPUT);
  digitalWrite(K_pin, HIGH); // Press down will read as 0, release will be 1
  Serial.begin(9600);
}

void loop() {
  int key = 1-digitalRead(K_pin);
  int X = analogRead(X_pin);
  int Y = analogRead(Y_pin);
  
  // Print current status with Serial
  Serial.print("Key: ");
  Serial.print(key);
  Serial.print(",X= ");
  Serial.print(X);
  Serial.print(",Y= ");
  Serial.println(Y);

  if (key == 1) {
    
  } else {
    
  }
  int x = map(X/10, 0, 102, -20, 20); // map joystick offset to angle (-10 to 10 degree)
  int degree = servo1.read();
  degree = degree + x;
  servo1.write(degree);

  delay(100);
}
