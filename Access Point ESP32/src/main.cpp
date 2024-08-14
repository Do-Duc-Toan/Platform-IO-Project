#include <Arduino.h>
#include<WiFi.h>

const char *ssid = "Harume-e chan";
const char *password = "abc1234567";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
}

void loop() {
  // put your main code here, to run repeatedly:
}
