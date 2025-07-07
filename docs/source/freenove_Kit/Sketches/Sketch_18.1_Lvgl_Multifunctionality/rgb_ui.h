#ifndef __RGB_UI_H
#define __RGB_UI_H

#include "public.h"

typedef struct lvgl_rgb
{
	lv_obj_t *rgb;
  lv_obj_t *rgb_home;

  lv_obj_t *rgb_slider_red;
  lv_obj_t *rgb_slider_green;
  lv_obj_t *rgb_slider_blue;

  lv_obj_t *rgb_btn_red;
  lv_obj_t *rgb_btn_green;
  lv_obj_t *rgb_btn_blue;
  lv_obj_t *rgb_label_red;
  lv_obj_t *rgb_label_green;
  lv_obj_t *rgb_label_blue;
}lvgl_rgb_ui;

extern lvgl_rgb_ui guider_rgb_ui;    //rgb ui structure 

void rgb_init(int red, int green, int blue);
void rgb_set_color(int red_value, int green_value, int blue_value);
void setup_scr_rgb(lvgl_rgb_ui *ui); //Parameter configuration function on the rgb screen

#endif
