#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>

const char *ssid = "Archer C7";       // tên WiFi muốn kết nối, chỉ kết nối được WiFi 2.4G
const char *password = "0987718868";  // mật khẩu WiFI

const char *indexPage = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
  <head>
    <title>ESP8266</title>
    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
  </head>

  <body>
    <h1>Hi, am ESP8266</h1>
  </body>
</html>

)rawliteral";

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;

void handleIndex() {
  httpServer.send(200, "text/html", indexPage);
}

void setup(void) {
  Serial.begin(115200);

  Serial.println();
  Serial.println();
  Serial.println("ESP8266 booting");

  Serial.print("WiFi connecting");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("connected");
  Serial.println("IP address " + WiFi.localIP().toString());

  httpServer.on("/", handleIndex);

  httpUpdater.setup(&httpServer, "/update");
  httpServer.begin();

  Serial.println("Boot success");
}

void loop(void) {
  httpServer.handleClient();
}