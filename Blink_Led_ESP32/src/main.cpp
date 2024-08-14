#include <Arduino.h>

// put function declarations here:
#define internal_led 2

void setup() {
  // put your setup code here, to run once:
  pinMode(internal_led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(internal_led, HIGH);
  delay(2000);
 // digitalWrite(internal_led, LOW);
  //delay(2000);
}

// put function definitions here: