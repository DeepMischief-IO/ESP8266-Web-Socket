#include <ESP8266WiFi.h>
#include <SocketIoClient.h>

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";
const char* host = "your_server_ip"; // Replace with your server IP or domain
const int port = 3000;

WiFiClient wifiClient;
SocketIoClient SocketIoClient;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  if (SocketIoClient.disconnect(host, port)) {
    Serial.println("Connected to Socket.IO server");
  } else {
    Serial.println("Failed to connect to Socket.IO server");
  }

  SocketIoClient.on("response", [](const String& message) {
    Serial.println("Response from server: " + message);
  });

  SocketIoClient.emit("message", "Hello from ESP8266");
}

void loop() {
  SocketIoClient.loop();
}
