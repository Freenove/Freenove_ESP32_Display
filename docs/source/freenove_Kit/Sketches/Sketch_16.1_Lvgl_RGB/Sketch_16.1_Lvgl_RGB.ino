/*
* @ File:   Sketch_16.1_LVGL_RGB.ino
* @ Author: [Zhentao Lin]
* @ Date:   [2025-06-23]
*/

#include "display.h"
#include "rgb_ui.h"

#define RED_PIN 22
#define GREEN_PIN 16
#define BLUE_PIN 17

Display screen;
void setup() {
  Serial.begin(115200);

  /*** Init screen ***/
  screen.init();

  /***  Print lvgl version ***/
  String LVGL_Arduino = "Hello Arduino! ";
  LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();
  Serial.println(LVGL_Arduino);
  Serial.println("I am LVGL_Arduino");
  Serial.println("Setup done");

  /*** The custom code ***/
  rgb_init(RED_PIN, GREEN_PIN, BLUE_PIN);
  rgb_set_color(0, 0, 0);
  setup_scr_rgb(&guider_rgb_ui);
  lv_scr_load(guider_rgb_ui.rgb);
}

void loop() {
  screen.routine();
  delay(5);
}