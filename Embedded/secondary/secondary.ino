/* 웹을 통한 릴레이 무선제어 secondary */
/* ATmega328P(arduino nano) */
#include <SoftwareSerial.h>

SoftwareSerial HC12(9, 10);

void setup() {
  Serial.begin(115200);
  HC12.begin(9600);

  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);

  Serial.println("Primary");
}

void loop() {
  String input = "";
  while (HC12.available()) {
    input += (char) HC12.read();
    Serial.println(input);
    delay(1);
  }

  if (input != "") {
    Serial.println(input);
    if (input == "on") {
      digitalWrite(5, LOW);
    }
    else if (input == "off") {
      digitalWrite(5, HIGH);
    }
    input = "";
  }
}
