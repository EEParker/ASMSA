#include <Arduino.h>

#include <pins.h>
#include <wifi.h>
#include <mqtt.h>


void setup() {
  Serial.begin(115200);

  Serial.println("Setting up pins.");
  // put your setup code here, to run once:

  setupWifi();
  setupMqtt();
}

void loop() {
  // put your main code here, to run repeatedly:

  if (!WiFi.isConnected()) {
    setupWifi();
  }
  if (!client.connected()) {
    reconnectMqtt();
  }

  client.loop();

  long now = millis();
  if (!digitalRead(BTN_PIN) && now - lastMsg > 200) {
    lastMsg = now;

    Serial.println("Publish message: toggle [1]");
    client.publish("toggle", "1");
    client.publish("toggle1", "1");
    client.publish("toggle2", "1");
  }
}
