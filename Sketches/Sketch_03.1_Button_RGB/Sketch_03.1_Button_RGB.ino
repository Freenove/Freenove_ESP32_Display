/*
* @ File:   Sketch_03.1_Button_RGB.ino
* @ Author: [Zhentao Lin]
* @ Date:   [2025-06-13]
*/

#include <Arduino.h>
#define RED_PIN 22
#define GREEN_PIN 16
#define BLUE_PIN 17
#define KEY_PIN 0

static unsigned int keyCount = 0;
static unsigned int lastKeyCount = 1;

void buttonInit(void) {
  pinMode(KEY_PIN, INPUT_PULLUP);
}

bool readButton(void) {
  return digitalRead(KEY_PIN);
}

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

void switchRGB(int value) {
  int colorIndex = value % 4;
  switch (colorIndex) {
    case 1:
      setRGB(1, 0, 0);
      break;
    case 2:
      setRGB(0, 1, 0);
      break;
    case 3:
      setRGB(0, 0, 1);
      break;
    default:
      setRGB(0, 0, 0);
      break;
  }
}

void setup() {
  rgbInit();
  buttonInit();
  Serial.println("ESP32 initialization completed!");
}

void loop() {
  if (readButton() == 0) {
    delay(20);
    if (readButton() == 0) {
      keyCount++;
      while (!readButton());
    }
  }
  if (keyCount != lastKeyCount) {
    switchRGB(keyCount);
    lastKeyCount = keyCount;
  }
}
