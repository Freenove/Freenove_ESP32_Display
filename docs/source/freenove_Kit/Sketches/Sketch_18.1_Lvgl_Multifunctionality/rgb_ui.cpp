#include "rgb_ui.h"

lvgl_rgb_ui guider_rgb_ui;
static int red_pin;
static int green_pin;
static int blue_pin;
void rgb_init(int red, int green, int blue) {
  red_pin = red;
  green_pin = green;
  blue_pin = blue;
  ledcAttachChannel(red_pin, 1000, 8, 0);
  ledcAttachChannel(green_pin, 1000, 8, 1);
  ledcAttachChannel(blue_pin, 1000, 8, 2);
}
void rgb_set_color(int red_value, int green_value, int blue_value) {
  ledcWrite(red_pin, 255 - red_value);
  ledcWrite(green_pin, 255 - green_value);
  ledcWrite(blue_pin, 255 - blue_value);
}
static void rgb_imgbtn_home_event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  switch (code) {
    case LV_EVENT_CLICKED:
      {
        Serial.println("Clicked the logo button.");
      }
      break;
    case LV_EVENT_RELEASED:
      {
        Serial.println("Released the logo button.");
        if (!lv_obj_is_valid(guider_main_ui.main))
          setup_scr_main(&guider_main_ui);
        lv_scr_load(guider_main_ui.main);
        lv_obj_del(guider_rgb_ui.rgb);
      }
      break;
    default:
      break;
  }
}
static void slider_event_cb(lv_event_t *e) {
  LV_UNUSED(e);
  int color_red = lv_slider_get_value(guider_rgb_ui.rgb_slider_red);
  int color_green = lv_slider_get_value(guider_rgb_ui.rgb_slider_green);
  int color_blue = lv_slider_get_value(guider_rgb_ui.rgb_slider_blue);

  lv_label_set_text_fmt(guider_rgb_ui.rgb_label_red,  "red:%6d", color_red);
  lv_label_set_text_fmt(guider_rgb_ui.rgb_label_green,"green:%6d", color_green);
  lv_label_set_text_fmt(guider_rgb_ui.rgb_label_blue, "blue:%6d", color_blue);

  rgb_set_color(color_red, color_green, color_blue);
}

//Parameter configuration function on the rgb screen
void setup_scr_rgb(lvgl_rgb_ui *ui) {
  //Write codes picture
  ui->rgb = lv_obj_create(NULL);
  lv_coord_t screen_width = lv_obj_get_width(ui->rgb);
  lv_coord_t screen_height = lv_obj_get_height(ui->rgb);

  static lv_style_t bg_style;
  lv_style_init(&bg_style);
  lv_style_set_bg_color(&bg_style, lv_color_hex(0xffffff));
  lv_obj_add_style(ui->rgb, &bg_style, LV_PART_MAIN);

  lv_img_home_init();
  ui->rgb_home = lv_imgbtn_create(ui->rgb);
  lv_obj_remove_style_all(ui->rgb_home);
  lv_obj_set_size(ui->rgb_home, 80, 80);
  lv_img_set_src(ui->rgb_home, &img_home);
  lv_obj_align(ui->rgb_home, LV_ALIGN_TOP_MID, 0, (screen_height-172)/6);

  static lv_style_t style_pr;              //Apply for a style
  lv_style_init(&style_pr);                //Initialize it
  lv_style_set_translate_y(&style_pr, 5);  //Style: Every time you trigger, move down 5 pixels
  lv_obj_add_style(ui->rgb_home, &style_pr, LV_STATE_PRESSED);

  ui->rgb_btn_red = lv_btn_create(ui->rgb);
  lv_obj_remove_style_all(ui->rgb_btn_red);
  lv_obj_set_size(ui->rgb_btn_red, (screen_width-40), 20);
  lv_obj_align_to(ui->rgb_btn_red, ui->rgb_home, LV_ALIGN_OUT_BOTTOM_MID, 0, (screen_height-172)/6);
  ui->rgb_label_red = lv_label_create(ui->rgb_btn_red);
  lv_obj_center(ui->rgb_label_red);
  static lv_style_t style_red;
  lv_style_init(&style_red);
  lv_style_set_border_width(&style_red, 2);
  lv_style_set_border_color(&style_red, lv_palette_main(LV_PALETTE_RED));
  lv_obj_add_style(ui->rgb_btn_red, &style_red, LV_PART_MAIN);
  
  ui->rgb_btn_green = lv_btn_create(ui->rgb);
  lv_obj_remove_style_all(ui->rgb_btn_green);
  lv_obj_set_size(ui->rgb_btn_green, (screen_width-40), 20);
  lv_obj_align_to(ui->rgb_btn_green, ui->rgb_btn_red, LV_ALIGN_OUT_BOTTOM_MID, 0, 1);
  ui->rgb_label_green = lv_label_create(ui->rgb_btn_green);
  lv_obj_center(ui->rgb_label_green);
  static lv_style_t style_green;
  lv_style_init(&style_green);
  lv_style_set_border_width(&style_green, 2);
  lv_style_set_border_color(&style_green, lv_palette_main(LV_PALETTE_GREEN));
  lv_obj_add_style(ui->rgb_btn_green, &style_green, LV_PART_MAIN);

  ui->rgb_btn_blue = lv_btn_create(ui->rgb);
  lv_obj_remove_style_all(ui->rgb_btn_blue);
  lv_obj_set_size(ui->rgb_btn_blue, (screen_width-40), 20);
  lv_obj_align_to(ui->rgb_btn_blue, ui->rgb_btn_green, LV_ALIGN_OUT_BOTTOM_MID, 0, 1);
  ui->rgb_label_blue = lv_label_create(ui->rgb_btn_blue);
  lv_obj_center(ui->rgb_label_blue);
  static lv_style_t style_blue;
  lv_style_init(&style_blue);
  lv_style_set_border_width(&style_blue, 2);
  lv_style_set_border_color(&style_blue, lv_palette_main(LV_PALETTE_BLUE));
  lv_obj_add_style(ui->rgb_btn_blue, &style_blue, LV_PART_MAIN);

  ui->rgb_slider_red = lv_slider_create(ui->rgb);
  lv_slider_set_range(ui->rgb_slider_red, 0, 255);
  lv_slider_set_value(ui->rgb_slider_red, LV_OPA_0, LV_ANIM_OFF);
  lv_obj_set_size(ui->rgb_slider_red, (screen_width-40), 10);
  lv_obj_set_style_bg_color(ui->rgb_slider_red, lv_palette_main(LV_PALETTE_RED), LV_PART_KNOB);
  lv_obj_set_style_bg_color(ui->rgb_slider_red, lv_palette_main(LV_PALETTE_RED), LV_PART_INDICATOR);
  lv_obj_add_event_cb(ui->rgb_slider_red, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_align_to(ui->rgb_slider_red, ui->rgb_btn_blue, LV_ALIGN_OUT_BOTTOM_MID, 0, (screen_height-172)/6);

  ui->rgb_slider_green = lv_slider_create(ui->rgb);
  lv_slider_set_range(ui->rgb_slider_green, 0, 255);
  lv_slider_set_value(ui->rgb_slider_green, LV_OPA_0, LV_ANIM_OFF);
  lv_obj_set_size(ui->rgb_slider_green, (screen_width-40), 10);
  lv_obj_set_style_bg_color(ui->rgb_slider_green, lv_palette_main(LV_PALETTE_GREEN), LV_PART_KNOB);
  lv_obj_set_style_bg_color(ui->rgb_slider_green, lv_palette_main(LV_PALETTE_GREEN), LV_PART_INDICATOR);
  lv_obj_add_event_cb(ui->rgb_slider_green, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_align_to(ui->rgb_slider_green, ui->rgb_slider_red, LV_ALIGN_OUT_BOTTOM_MID, 0, (screen_height-172)/6);

  ui->rgb_slider_blue = lv_slider_create(ui->rgb);
  lv_slider_set_range(ui->rgb_slider_blue, 0, 255);
  lv_slider_set_value(ui->rgb_slider_blue, LV_OPA_0, LV_ANIM_OFF);
  lv_obj_set_size(ui->rgb_slider_blue, (screen_width-40), 10);
  lv_obj_set_style_bg_color(ui->rgb_slider_blue, lv_palette_main(LV_PALETTE_BLUE), LV_PART_KNOB);
  lv_obj_set_style_bg_color(ui->rgb_slider_blue, lv_palette_main(LV_PALETTE_BLUE), LV_PART_INDICATOR);
  lv_obj_add_event_cb(ui->rgb_slider_blue, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_align_to(ui->rgb_slider_blue, ui->rgb_slider_green, LV_ALIGN_OUT_BOTTOM_MID, 0, (screen_height-172)/6);

  lv_event_send(ui->rgb_slider_red, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_add_event_cb(ui->rgb_home, rgb_imgbtn_home_event_handler, LV_EVENT_ALL, NULL);
}
