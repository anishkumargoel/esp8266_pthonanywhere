#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>

#define DHTPIN D1          // DHT11 sensor pin
#define DHTTYPE DHT11      // DHT11 sensor type

const char* ssid = "Lakshita24ghz"; // Your Wi-Fi network SSID
const char* password = "9318396455"; // Your Wi-Fi network password
const char* serverName = "https://app032823.pythonanywhere.com/api/send_data"; // Your HTTPS server address

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  delay(30000); // Wait for 30 seconds
  float temperature = dht.readTemperature(); // Read temperature value from DHT11 sensor
  float humidity = dht.readHumidity(); // Read humidity value from DHT11 sensor

  // Create JSON payload
  String payload = "{\"temp\":" + String(temperature) + ",\"humidity\":" + String(humidity) + "}";

  // Create HTTP client
  WiFiClientSecure client;
  client.setInsecure();

  // Create HTTPS request
  HTTPClient https;
  https.begin(client, serverName);

  // Add headers
  https.addHeader("Content-Type", "application/json");
  https.addHeader("X-API-Key", "my api key"); // Add X-API-Key header

  // Send HTTPS POST request
  int httpCode = https.POST(payload);

  // Check for response
  if (httpCode > 0) {
    Serial.println("Data sent successfully");
    Serial.println(httpCode);
    String response = https.getString();
    Serial.println(response);
  } else {
    Serial.println("Error sending data");
  }

  // Close HTTPS connection
  https.end();
}
