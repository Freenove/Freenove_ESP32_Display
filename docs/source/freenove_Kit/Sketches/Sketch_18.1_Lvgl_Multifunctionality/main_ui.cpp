
#include "main_ui.h"

lvgl_main_ui guider_main_ui;  // main ui structure

// Click the main interface picture button
static void main_imgbtn_picture_imgbtn_home_event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  switch (code) {
    case LV_EVENT_CLICKED:
      {
        Serial.println("Clicked the picture button.");
      }
      break;
    case LV_EVENT_RELEASED:
      {
        Serial.println("Released the picture button.");
        if (!lv_obj_is_valid(guider_picture_ui.picture))
          setup_scr_picture(&guider_picture_ui);
        lv_scr_load(guider_picture_ui.picture);
        lv_obj_del(guider_main_ui.main);
      }
      break;
  }
}

// Click the main interface timer button
static void main_imgbtn_timer_event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  switch (code) {
    case LV_EVENT_CLICKED:
      {
        Serial.println("Clicked the timer button.");
      }
      break;
    case LV_EVENT_RELEASED:
      {
        Serial.println("Released the timer button.");
        if (!lv_obj_is_valid(guider_chronograph_ui.chronograph))
          setup_scr_chronograph(&guider_chronograph_ui);
        lv_scr_load(guider_chronograph_ui.chronograph);
        lv_obj_del(guider_main_ui.main);
      }
      break;
  }
}

// Click the main interface music button
static void main_imgbtn_music_event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  switch (code) {
    case LV_EVENT_CLICKED:
      {
        Serial.println("Clicked the music button.");
      }
      break;
    case LV_EVENT_RELEASED:
      {
        Serial.println("Released the music button.");
        if (!lv_obj_is_valid(guider_music_ui.music))
          setup_scr_music(&guider_music_ui);
        lv_scr_load(guider_music_ui.music);
        lv_obj_del(guider_main_ui.main);
      }
      break;
  }
}

// Click the main interface led button
static void main_imgbtn_led_event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  switch (code) {
    case LV_EVENT_CLICKED:
      {
        Serial.println("Clicked the led button.");
      }
      break;
    case LV_EVENT_RELEASED:
      {
        Serial.println("Released the led button.");
        if (!lv_obj_is_valid(guider_rgb_ui.rgb))
          setup_scr_rgb(&guider_rgb_ui);
        lv_scr_load(guider_rgb_ui.rgb);
        lv_obj_del(guider_main_ui.main);
      }
      break;
  }
}

// Parameter configuration function on the main screen
void setup_scr_main(lvgl_main_ui *ui) {
  // Write codes main
  ui->main = lv_obj_create(NULL);
  lv_coord_t screen_width = lv_obj_get_width(ui->main);    // Get screen width
  lv_coord_t screen_height = lv_obj_get_height(ui->main);  // Get screen height

  static lv_style_t bg_style;
  lv_style_init(&bg_style);
  lv_style_set_bg_color(&bg_style, lv_color_hex(0xffffff));
  lv_obj_add_style(ui->main, &bg_style, LV_PART_MAIN);

  lv_img_freenove_init();
  lv_img_picture_init();
  lv_img_timer_init();
  lv_img_led_init();
  lv_img_music_init();

  /*Init the pressed style*/
  static lv_style_t style_pr;              // Apply for a style
  lv_style_init(&style_pr);                // Initialize it
  lv_style_set_translate_y(&style_pr, 5);  // Style: Every time you trigger, move down 5 pixels

  // Write codes main_imgbtn_logo
  ui->main_imgbtn_logo = lv_imgbtn_create(ui->main);
  lv_obj_set_size(ui->main_imgbtn_logo, 160, 90);
  lv_img_set_src(ui->main_imgbtn_logo, &img_freenove);
  //lv_obj_add_style(ui->main_imgbtn_logo, &style_pr, LV_STATE_PRESSED);  // Triggered when the button is pressed
  lv_obj_align(ui->main_imgbtn_logo, LV_ALIGN_TOP_MID, 0, (screen_height - 250) / 4);

  // Write codes main_imgbtn_picture
  ui->main_imgbtn_picture = lv_imgbtn_create(ui->main);
  lv_obj_set_size(ui->main_imgbtn_picture, 80, 80);
  lv_img_set_src(ui->main_imgbtn_picture, &img_picture);
  lv_obj_add_style(ui->main_imgbtn_picture, &style_pr, LV_STATE_PRESSED);  // Triggered when the button is pressed
  lv_obj_align_to(ui->main_imgbtn_picture, ui->main_imgbtn_logo, LV_ALIGN_OUT_BOTTOM_LEFT, -(screen_width - 160) / 8, (screen_height - 250) / 4);

  // Write codes main_imgbtn_timer
  ui->main_imgbtn_timer = lv_imgbtn_create(ui->main);
  lv_obj_set_size(ui->main_imgbtn_timer, 80, 80);
  lv_img_set_src(ui->main_imgbtn_timer, &img_timer);
  lv_obj_add_style(ui->main_imgbtn_timer, &style_pr, LV_STATE_PRESSED);  // Triggered when the button is pressed
  lv_obj_align_to(ui->main_imgbtn_timer, ui->main_imgbtn_logo, LV_ALIGN_OUT_BOTTOM_RIGHT, (screen_width - 160) / 8, (screen_height - 250) / 4);

  // Write codes main_imgbtn_music
  ui->main_imgbtn_music = lv_imgbtn_create(ui->main);
  lv_obj_set_size(ui->main_imgbtn_music, 80, 80);
  lv_img_set_src(ui->main_imgbtn_music, &img_music);
  lv_obj_add_style(ui->main_imgbtn_music, &style_pr, LV_STATE_PRESSED);  // Triggered when the button is pressed
  lv_obj_align_to(ui->main_imgbtn_music, ui->main_imgbtn_picture, LV_ALIGN_OUT_BOTTOM_MID, 0, (screen_height - 250) / 4);

  // Write codes main_imgbtn_led
  ui->main_imgbtn_led = lv_imgbtn_create(ui->main);
  lv_obj_set_size(ui->main_imgbtn_led, 80, 80);
  lv_img_set_src(ui->main_imgbtn_led, &img_led);
  lv_obj_add_style(ui->main_imgbtn_led, &style_pr, LV_STATE_PRESSED);  // Triggered when the button is pressed
  lv_obj_align_to(ui->main_imgbtn_led, ui->main_imgbtn_timer, LV_ALIGN_OUT_BOTTOM_MID, 0, (screen_height - 250) / 4);

  lv_obj_add_event_cb(ui->main_imgbtn_picture, main_imgbtn_picture_imgbtn_home_event_handler, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui->main_imgbtn_timer, main_imgbtn_timer_event_handler, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui->main_imgbtn_music, main_imgbtn_music_event_handler, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui->main_imgbtn_led, main_imgbtn_led_event_handler, LV_EVENT_ALL, NULL);
}