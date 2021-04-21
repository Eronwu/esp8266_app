/*
 * reference from document :
 * https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/soft-access-point-examples.html
 * https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/examples/WiFiAccessPoint/WiFiAccessPoint.ino
 * 
 */
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define AP_SSID "nulllab"
#define AP_PSWD "12341234"

int station_num = 0;

ESP8266WebServer server(8080);

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
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  if (station_num != WiFi.softAPgetStationNum()) {
    station_num = WiFi.softAPgetStationNum();
    Serial.printf("WiFi Stations connected num change = %d\n", station_num);
  }
  
//  delay(3000);
}

void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected</h1>");
}
