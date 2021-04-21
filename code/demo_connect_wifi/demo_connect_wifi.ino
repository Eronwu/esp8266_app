// Import required libraries
#include <ESP8266WiFi.h>

// WiFi parameters
const char* ssid = "ChinaNet-js7M";
const char* password = "12345678";

void setup(void)
{
  // Start Serial
  Serial.begin(74880);
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Print the IP address
  Serial.println(WiFi.localIP());
}
       
void loop() {
}
