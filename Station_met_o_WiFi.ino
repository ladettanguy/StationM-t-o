//code relatif à l'ESP
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

// Code propore au DHT11
#include <DHT.h>
#define DHT11_PIN D4
#define DHT11_TYPE DHT11

DHT dht(DHT11_PIN, DHT11_TYPE);

const char* ssid = "RPi-AP";
const char* password = "raspberry";



#include <ESP8266WebServer.h>
ESP8266WebServer server(80);
String html = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);
  Serial.println("Starting...");


  WiFi.begin(ssid,password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("connecté à ");
  Serial.print(ssid);
  Serial.print(" r: ");
  Serial.println(WiFi.localIP());

  html += "<html><head><title>Station météo</title>";
  html += "<meta charset=\"utf-8\" />\n";
  html += "</head><body>ESP8266</body></html>";

  server.on("/", []() {
    server.send(200, "text/html", html);

  });
  server.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Température : ");
  Serial.println(dht.readTemperature ());
   Serial.print("Humidité : ");
  Serial.println(dht.readHumidity ());
  delay(1000);
  server.handleClient();

}
