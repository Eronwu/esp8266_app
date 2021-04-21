

// 需要一个一键将web页面加上反斜杠符号的翻译工具
// https://www.sojson.com/yasuo.html 转义工具（但看起来好像有错）
const String postForms = "<html>\
  <head>\
    <title>ESP8266 Web Server text POSER</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>POST plain text to ESP8266</h1><br>\
    <form method=\"post\" enctype=\"text/plain\" action=\"/postplain/\">\
      <input type=\"text\" name=\'{ \"\' value=\'\" }\'><br>\<br>\
      <input type=\"submit\" value=\"Submit\">\
    </form>\
  </body>\
</html>";
