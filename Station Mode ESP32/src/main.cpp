#include <Arduino.h>
#include<WiFi.h>

const char *ssid = "iPhone of Toan";
const char *password = "abc1234567";


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print(" ");
  Serial.print("Connecting to WiFi .....");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.print(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
}

