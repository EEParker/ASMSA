#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <pins.h>

const char *mqtt_server = "10.0.60.1";

WiFiClient espClient;
PubSubClient client(espClient);

void messageRx(char* topic, byte* payload, unsigned int length);
void reconnectMqtt();

void setupMqtt() {
  client.setServer(mqtt_server, 1883);
  client.setCallback(messageRx);
}

void messageRx(char* topic, byte* payload, unsigned int length) {
    Serial.printf("Message arrived [%s]: ", topic);
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if (strcmp(topic, "toggle") == 0) {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  } else if (strcmp(topic, "toggle1") == 0) {
    digitalWrite(LED1_PIN, !digitalRead(LED1_PIN));
  } else if (strcmp(topic, "toggle2") == 0) {
    digitalWrite(LED2_PIN, !digitalRead(LED2_PIN));
  }
}

void reconnectMqtt() {
  // Loop until we're reconnected
  String clientId = "IOT" + WiFi.macAddress();
  while (!client.connected()) {

    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // ... and resubscribe
      client.subscribe("toggle");
      client.subscribe("toggle1");
      client.subscribe("toggle2");

    } else {
      Serial.print("failed..");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}