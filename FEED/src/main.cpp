#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASS";

ESP8266WebServer server(80);
Servo feeder;

#define SERVO_PIN D4

// CORS support (IMPORTANT)
void sendOK() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "OK");
}

void handleFeed() {
  sendOK();
  feeder.write(90);
  delay(1500);
  feeder.write(0);
}

void setup() {
  Serial.begin(115200);
  feeder.attach(SERVO_PIN);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nESP8266 IP:");
  Serial.println(WiFi.localIP());

  server.on("/feed", handleFeed);
  server.begin();
}

void loop() {
  server.handleClient();
}
