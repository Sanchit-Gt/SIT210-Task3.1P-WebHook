#include <WiFiNINA.h>
#include <ThingSpeak.h>
#define IR_SENSOR_PIN 4   // Connecting the IR sensor pin

#define WIFI_SSID "sanchit_pvt"  //hotspot ssid
#define WIFI_PASS "12345679" //hotspot password

#define CHANNEL_ID 2252430  //thingspeak channel id
#define API_KEY "4OH8FHVYWLY8VQKZ"  //thingspeak api key

WiFiClient wifiClient;

void setup() {
  Serial.begin(9600);

  pinMode(IR_SENSOR_PIN, INPUT);  // Setting IR sensor pin as input
  pinMode(LED_BUILTIN, OUTPUT);    // Setting LED pin as output

  connectToWiFi();                 // Connecting to WiFi network
  ThingSpeak.begin(wifiClient);    // Initializing ThingSpeak client
}

void loop() {
  int irState = digitalRead(IR_SENSOR_PIN);  // Reading IR sensor state

  sendDataToThingSpeak(irState);             // Sending data to ThingSpeak

  delay(10000);  // Waiting for a short interval before the next iteration
}

void connectToWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);  // Connecting to WiFi network

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void sendDataToThingSpeak(int irState) {
  ThingSpeak.setField(1, irState);  // Setting ThingSpeak field with IR sensor state

  int responseCode = ThingSpeak.writeFields(CHANNEL_ID, API_KEY);  // Sending data to ThingSpeak

  if (responseCode == 200) {
    Serial.println("Data sent to ThingSpeak");
    digitalWrite(LED_BUILTIN, HIGH);   // Turning on the LED briefly
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);    // Turning off the LED
  } else {
    Serial.println("Error sending data to ThingSpeak");
  }
}

