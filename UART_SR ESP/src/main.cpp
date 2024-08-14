#include <Arduino.h>

#include <HardwareSerial.h>
HardwareSerial SerialPort(2); // use UART2

int LED = 2;

void setup()
{
  SerialPort.begin(9600, SERIAL_8N1, 16, 17);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  if (SerialPort.available()) {
    String RxData = SerialPort.readString();
    digitalWrite(LED, HIGH);
    Serial.println("Received: " + RxData);
  }
}

// #include <Arduino.h>
// #include <ESPSoftwareSerial.h>

// // Khai báo ESPSoftwareSerial với các chân GPIO mong muốn
// ESPSoftwareSerial mySerial(16, 17); // RX, TX
// int LED = 2;
// void setup() {
//   Serial.begin(9600);          // Mở cổng Serial chính cho debug
//   mySerial.begin(9600);          // Bắt đầu SoftwareSerial với tốc độ 9600 baud
//   pinMode(LED, OUTPUT);
// }

// void loop() {
//   if (mySerial.available() > 0) {
//     String input = mySerial.readString(); // Đọc toàn bộ chuỗi dữ liệu
//     digitalWrite(LED, HIGH);
//     Serial.println(input);                // In dữ liệu nhận được ra Serial Monitor
//   }
// }