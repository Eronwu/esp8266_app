#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WebServer.h>


ESP8266WiFiMulti WiFiMulti;//建立ESP8266WiFiMulti对象，对象名称为WiFiMulti
ESP8266WebServer esp8266_server(80);//建立ESP8266WebServer对象，对象名称是“esp8266_server”
                                  //括号中的数字是网络服务器响应http请求的端口号
                                  //网络服务器http端口号为80，因此这里使用80为端口号

void setup() 
{
    Serial.begin(74880);
    WiFiMulti.addAP("vivo","QiFei159874");//这条指令就是告诉ESP8266下面会告诉你多个WiFi网络名称和密码
    WiFiMulti.addAP("ChinaNet-js7M","12345678");//注意这里的双引号要加上，没加报错
    WiFiMulti.addAP("vivo2","QIFEI159874");
   
    Serial.println("start WiFi connect");

    int i=0;
    while(WiFiMulti.run()!=WL_CONNECTED)//WiFiMulti.run()和WiFi.Status()功能一样，都是用来表示当前WiFi连接的状态
    {
        delay(1000);
        Serial.print(".");
    }
    
    Serial.println('\n');
    Serial.print("连接到");
    Serial.println(WiFi.SSID());
    Serial.print("IP Address:  ");
    Serial.println(WiFi.localIP());//ESP8266的IP地址

    /*-------------”启动网络服务功能“程序部分开始------------*/
    esp8266_server.begin();//启动网络服务器
//    esp8266_server.on("/",handleRoot);//on函数的作用就是提供页面服务，告诉MCU通过那个函数访问这个界面“/”页面，就是主页，通过handleRoot函数处理该页面
    esp8266_server.on("/",HTTP_GET,handleRoot);//on函数的作用就是提供页面服务，告诉MCU通过那个函数访问这个界面“/”页面，就是主页，通过handleRoot函数处理该页面
    esp8266_server.on("/LED",HTTP_POST,handleLED);//设置处理LED控制请求的函数“handleLED”
    esp8266_server.onNotFound(handleNotFound);//当请求页面不存在时，通过该函数处理
    //----启动网路服务功能部分结束
    Serial.println("HTTP esp8266_server Started");//告知用户ESP8266网络服务功能已经启动
}

void loop() 
{
  esp8266_server.handleClient();//处理HTTP服务器访问
    

}
void handleRoot()
{               /*服务器响应状态码200（找到信息了），text/plain，表示告诉浏览器接下来要返送信息内容的是一段纯文本信息，信息内容就是Hello from ESP8266                                     */
//    esp8266_server.send(200,"text/plain","Hello from ESP8266");//nodeMCU将调用
  esp8266_server.send(200, "text/html", "<form action=\"/LED\" method=\"POST\"><input type=\"submit\" value=\"Toggle LED\"></form>");//nodeMCU将调用html内容，这是一个按钮
}

void handleLED()
{
//    digitalWrite(LED,!digitalRead(LED));//改变LED的状态
  Serial.println("change led");
    esp8266_server.sendHeader("Location","/");//跳转回页面根目录
    esp8266_server.send(303);//发送HTTP相应代码303 跳转到另一个界面}
}

void handleNotFound()//当浏览器访问页面不存在时，通过该函数处理
{                       /*服务器响应状态码404（未找到浏览器需要的信息），text/plain，表示告诉浏览器接下来要返送信息内容的是一段纯文本信息，信息内容就是404 Not found*/
    esp8266_server.send(404,"text/plain","404 Not found");
}
