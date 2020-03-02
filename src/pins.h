#include <Arduino.h>

#define LED_PIN 2
#define LED1_PIN 14
#define LED2_PIN 12

#define BTN_PIN 13
#define PWR_PIN 15

void setupPins() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);

  // turn on power to ports
  pinMode(PWR_PIN, OUTPUT);
  digitalWrite(PWR_PIN, HIGH);

  pinMode(BTN_PIN, INPUT_PULLUP);
}