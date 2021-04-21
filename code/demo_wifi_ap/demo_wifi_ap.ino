#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

#define AP_SSID "nulllab"
#define AP_PSW  "12341234"

WiFiClient WiFi_Client_Tmp;
const int SERVER_PORT = 80;
WiFiServer WiFi_Server(SERVER_PORT);
unsigned int UDPPort = 8787;      // local port to listen on
char packetBuffer[255]; //buffer to hold incoming packet
char  ReplyBuffer[] = "acknowledged";       // a string to send back
WiFiUDP Udp;

void setup() {
  Serial.begin ( 74880 );
  Serial.println("");
  Serial.println("===start===");
  // 设置内网
  IPAddress softLocal(192,168,128,1);   // 1 设置内网WIFI IP地址
  IPAddress softGateway(192,168,128,1);
  IPAddress softSubnet(255,255,255,0);
  WiFi.softAPConfig(softLocal, softGateway, softSubnet);
  
//  String apName = ("ESP8266_"+(String)ESP.getChipId());  // 2 设置WIFI名称
//  const char *softAPName = apName.c_str();
  
  WiFi.softAP(AP_SSID, AP_PSW);      // 3创建wifi  名称 +密码
//  WiFi.softAP(AP_SSID);
  Udp.begin(UDPPort);
  Serial.println();
  Serial.println("Started ap. Local ip: " + WiFi.localIP().toString());
  
  IPAddress myIP = WiFi.softAPIP();  // 4输出创建的WIFI IP地址
  Serial.print("AP IP address: ");      
  Serial.println(myIP);
  
  Serial.print("softAPName: ");  // 5输出WIFI 名称
  Serial.println(AP_SSID);
}

void loop() {
  Serial.println(WiFi.softAPgetStationNum());//获取当前连接到AP的数量
//  WiFi_Client_Tmp = WiFi_Server.available();
//  if(WiFi_Client_Tmp.connected()){
//    Serial.println("client connected");
//    WiFi_Client_Tmp.setNoDelay(true);
//    
    // if there's data available, read a packet
    int packetSize = Udp.parsePacket();
    if (packetSize) {
      Serial.print("Received packet of size ");
      Serial.println(packetSize);
      Serial.print("From ");
      IPAddress remoteIp = Udp.remoteIP();
      Serial.print(remoteIp);
      Serial.print(", port ");
      Serial.println(Udp.remotePort());
      
      // read the packet into packetBufffer
      int len = Udp.read(packetBuffer, 255);
      if (len > 0) {
        packetBuffer[len] = 0;
      }
      Serial.println("Contents:");
      Serial.println(packetBuffer);
      // send a reply, to the IP address and port that sent us the packet we received
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
      Udp.write(ReplyBuffer);
      Udp.endPacket();
    }
//  }
}
