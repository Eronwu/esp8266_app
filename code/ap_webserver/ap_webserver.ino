/*
 * reference from document :
 * https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/soft-access-point-examples.html
 * https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/examples/WiFiAccessPoint/WiFiAccessPoint.ino
 * 
 */
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "webpage_src.h"

#define AP_SSID "nulllab"
#define AP_PSWD "12341234"

int station_num = 0;

ESP8266WebServer server(80);
const int led = LED_BUILTIN;

void setup() {
  Serial.begin(74880);
  Serial.println();
  Serial.print("Setting soft-AP ... ");
  
  boolean ap_enable = WiFi.softAP(AP_SSID, AP_PSWD);
  if (ap_enable == true) {
    Serial.println("Ready");
  } else {
    Serial.println("Failed!");
  }
  
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  server.on("/", handleRoot);
  server.on("/postplain/", handlePlain);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  if (station_num != WiFi.softAPgetStationNum()) {
    station_num = WiFi.softAPgetStationNum();
    Serial.print("WiFi Stations connected num =");
    Serial.println(station_num);
  }
  
//  delay(3000);
}

void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/html", postForms);
  digitalWrite(led, 0);
}

void handlePlain() {
  String inputData;
  if (server.method() != HTTP_POST) {
    digitalWrite(led, 1);
    inputData = "Method Not Allowed";
    server.send(405, "text/plain", "Method Not Allowed");
    digitalWrite(led, 0);
  } else {
    digitalWrite(led, 1);
    inputData = server.arg("plain");
    server.send(200, "text/plain", "POST body was:\n" + inputData);
    digitalWrite(led, 0);
  }
    Serial.println(inputData);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}
