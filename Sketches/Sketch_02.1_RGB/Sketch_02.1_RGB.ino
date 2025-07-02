/*
* @ File:   Sketch_02.1_RGB.ino
* @ Author: [Zhentao Lin]
* @ Date:   [2025-06-11]
*/

#include <Arduino.h>
#define RED_PIN 22
#define GREEN_PIN 16
#define BLUE_PIN 17

void rgbInit(void) {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void setRGB(bool redLevel, bool greenLevel, bool blueLevel) {
  digitalWrite(RED_PIN, !redLevel);
  digitalWrite(GREEN_PIN, !greenLevel);
  digitalWrite(BLUE_PIN, !blueLevel);
}

void setup() {
  rgbInit();
}

void loop() {
  setRGB(1, 0, 0);
  delay(500);
  setRGB(0, 1, 0);
  delay(500);
  setRGB(0, 0, 1);
  delay(500);
  setRGB(0, 0, 0);
  delay(500);
}
