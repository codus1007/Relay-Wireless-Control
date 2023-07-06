/* 웹을 통한 릴레이 무선제어 primary */
/* esp8266(lolin D1 mini lite) */
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

const char* ssid = "LeeF";
const char* password = "";

IPAddress ip (192, 168, 0, 50);
IPAddress gw (192, 168, 0, 1);
IPAddress subnet (255, 255, 255, 0);

WiFiServer server(80);

SoftwareSerial HC12(D6, D5);

void setup() {
  Serial.begin(115200);
  HC12.begin(9600);

  pinMode(D2, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.config (ip, gw, subnet);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
  Serial.println("Server started");
}

void loop() {
  while (Serial.available()) {
    HC12.write(Serial.read());
  }

  WiFiClient client = server.available();
  if (!client) return;

  client.setTimeout(5000);

  String request = client.readStringUntil('\r');
  Serial.println("request: ");
  Serial.println(request);

  if (request.indexOf("/off") != -1) {
    Serial.println("릴레이 OFF");
    HC12.write("off");
    digitalWrite(D2, HIGH);
    delay(200);
    digitalWrite(D2, LOW);
    delay(80);
    digitalWrite(D2, HIGH);
    delay(200);
    digitalWrite(D2, LOW);
    delay(100);
  }
  else if (request.indexOf("/on") != -1) {
    Serial.println("릴레이 ON");
    HC12.write("on");
    digitalWrite(D2, HIGH);
    delay(300);
    digitalWrite(D2, LOW);
    delay(100);
  }

  while (client.available()) {
    client.read();
  }
}
