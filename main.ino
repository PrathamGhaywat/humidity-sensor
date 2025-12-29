#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_SHT4x.h>

const char* WIFI_SSID = "wifi_name";
const char* WIFI_PASS = "wifi_password";

WebServer server(80);
Adafruit_SHT4x sht4;

void handleRoot() {
  String html =
    "<!DOCTYPE html><html lang='en'>"
    "<head>"
    "<meta charset='UTF-8'>"
    "<title>ESP32 SHT41</title>"
    "<style>"
    "body { font-family: Arial; text-align: center; margin: 50px; background: #f0f0f0; }"
    "h1 { color: #333; }"
    "button { padding: 12px 24px; font-size: 16px; cursor: pointer; background: #4CAF50; color: white; border: none; border-radius: 5px; }"
    "button:hover { background: #45a049; }"
    "#readings { margin-top: 20px; font-size: 18px; }"
    "</style>"
    "</head><body>"
    "<h1>ESP32 SHT41 Sensor</h1>"
    "<button onclick='fetchReadings()'>Fetch Readings</button>"
    "<div id='readings'></div>"
    "<script>"
    "function fetchReadings() {"
      "fetch('/readings')"
      ".then(response => response.text())"
      ".then(data => document.getElementById('readings').innerHTML = data);"
    "}"
    "</script>"
    "</body></html>";

  server.send(200, "text/html", html);
}

void handleReadings() {
  sensors_event_t hum, temp;
  sht4.getEvent(&hum, &temp);

  String readings =
    "Temperature: " + String(temp.temperature, 2) + " °C<br>" +
    "Humidity: " + String(hum.relative_humidity, 2) + " %";

  server.send(200, "text/html", readings);
}

void connectWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.print("ESP32 IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Wire.begin(4, 5); // SDA, SCL
  if (!sht4.begin()) {
    Serial.println("SHT41 not detected");
    while (1);
  }

  connectWiFi();

  server.on("/", handleRoot);
  server.on("/readings", handleReadings);

  server.begin();
  Serial.println("server started, go to ip to see the page");
}

void loop() {
  server.handleClient();
}
