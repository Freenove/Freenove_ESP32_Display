/*
* @ File:   Sketch_02.2_PWM_RGB.ino
* @ Author: [Zhentao Lin]
* @ Date:   [2025-06-11]
*/

#include <Arduino.h>

#define RED_PIN 22
#define GREEN_PIN 16
#define BLUE_PIN 17
#define LEDC_RESOLUTION 8
#define LEDC_FREQ 2000
#define LEDC_RED_CHANNEL 0
#define LEDC_GREEN_CHANNEL 1
#define LEDC_BLUE_CHANNEL 2

#define PWM_BRIGHTNESS 255
#define DELAY_TIME 2

void pwmInit(void) {
  ledcAttachChannel(RED_PIN, LEDC_FREQ, LEDC_RESOLUTION, LEDC_RED_CHANNEL);
  ledcAttachChannel(GREEN_PIN, LEDC_FREQ, LEDC_RESOLUTION, LEDC_GREEN_CHANNEL);
  ledcAttachChannel(BLUE_PIN, LEDC_FREQ, LEDC_RESOLUTION, LEDC_BLUE_CHANNEL);
}

void setPwm(int redValue, int greenValue, int blueValue) {
  ledcWrite(RED_PIN, 255 - redValue);
  ledcWrite(GREEN_PIN, 255 - greenValue);
  ledcWrite(BLUE_PIN, 255 - blueValue);
}

void setup() {
  pwmInit();
}

void loop() {
  for (int i = 0; i <= PWM_BRIGHTNESS; i++) {
    setPwm(i, 0, 0);
    delay(DELAY_TIME);
  }
  for (int i = PWM_BRIGHTNESS; i >= 0; i--) {
    setPwm(i, 0, 0);
    delay(DELAY_TIME);
  }

  for (int i = 0; i <= PWM_BRIGHTNESS; i++) {
    setPwm(0, i, 0);
    delay(DELAY_TIME);
  }
  for (int i = PWM_BRIGHTNESS; i >= 0; i--) {
    setPwm(0, i, 0);
    delay(DELAY_TIME);
  }

  for (int i = 0; i <= PWM_BRIGHTNESS; i++) {
    setPwm(0, 0, i);
    delay(DELAY_TIME);
  }
  for (int i = PWM_BRIGHTNESS; i >= 0; i--) {
    setPwm(0, 0, i);
    delay(DELAY_TIME);
  }
}
