/*
  IoT Club - ISTC Workshop
  Controlling LED with MQTT

  This code demonstrates how to control the state of an LED connected 
  to the ESP32 based on messages received from a specific MQTT topic.
*/

#include <WiFi.h>
#include <PubSubClient.h>

// Update these with your Wi-Fi credentials
const char* ssid = "Node";
const char* password = "12345678";

// MQTT Broker settings
const char* mqtt_server = "192.168.1.100";
const int mqtt_port = 1883;

// Topic for controlling the LED
const char* ledTopic = "esp32/led";
const char* ledBrightnessTopic = "esp32/led/brightness";

// Pins for the LED and push button
const int ledPin = 2; // Change this to the actual pin connected to the LED
const int pushButton =27; // Change this to the actual pin connected to the push button

// Initialize the WiFi and MQTT clients
bool ledStatus = LOW;
int brightness = 255;


WiFiClient espClient;
PubSubClient client(espClient);
/**
 * Function to establish connection to MQTT server.
 *
 * @return void
 *
 * @throws None
 */
void connectToMQTT() {
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("Connected to MQTT Broker!");
      client.subscribe(ledTopic);
      client.subscribe(ledBrightnessTopic);

    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

// Callback function for received MQTT messages
void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  Serial.println(message);

if (topic == ledBrightnessTopic) {
  brightness = message.toInt();
  analogWrite(ledPin, brightness);
  return;
}
  // Control the LED based on the message
 
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(pushButton, INPUT_PULLUP);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  connectToMQTT();
  
}

/**
 * Function to continuously check the connection status, 
 * and reconnect to MQTT if not connected. 
 */
void loop() {
  if (!client.connected()) {
    connectToMQTT();
  }  
  
  client.loop();

  delay(200);
}


