#include "music_ui.h"
#include "driver_sdspi.h"
#include "AudioFileSourceSD.h"
#include "AudioFileSourceID3.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"
#include "lv_img.h"

#define MUSIC_FOLDER "/Music"
lvgl_music_ui guider_music_ui;

int music_index_num = 0;
int music_play_state = 0;

AudioFileSourceSD *file;
AudioFileSourceID3 *id3;
AudioOutputI2S *out;
AudioGeneratorMP3 *mp3;

void music_dac_init(void) { 
  file = new AudioFileSourceSD();
  id3 = new AudioFileSourceID3(file);
  out = new AudioOutputI2S(0, 1);
  mp3 = new AudioGeneratorMP3();
}

void music_load_mp3(const char *name) {
  char buf_music_path[255] = { 0 };
  memset(buf_music_path, 0, sizeof(buf_music_path));
  strcat(buf_music_path, MUSIC_FOLDER);
  strcat(buf_music_path, "/");
  strcat(buf_music_path, name);
  file->open(buf_music_path);
  mp3->begin(id3, out);
}

void music_stop(void) {
  mp3->stop();
}
bool music_is_running(void) {
  return mp3->isRunning();
}
bool music_loop(void) {
  return mp3->loop();
}
void music_set_volume(int volume) {
  float music_volume = (float)(volume / 10.0);
  out->SetGain(music_volume);
}

void music_set_label_text(const char *text) {
  char buf[256];
  if (text != NULL) {
    lv_snprintf(buf, sizeof(buf), "%s", text);
    lv_label_set_text(guider_music_ui.music_label, buf);
  } else
    lv_label_set_text(guider_music_ui.music_label, "Can't find mp3.");
}
void music_set_imgbtn_state(bool is_play) {
  if (is_play) {
    lv_img_set_src(guider_music_ui.music_imgbtn_play, &img_playing);
  } else {
    lv_img_set_src(guider_music_ui.music_imgbtn_play, &img_pause);
  }
}

static void music_imgbtn_home_event_handler(lv_event_t *e) {
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
      }
      break;
    default:
      break;
  }
}

static void music_imgbtn_left_event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  switch (code) {
    case LV_EVENT_CLICKED:
      {
        Serial.println("Clicked the left button.");
      }
      break;
    case LV_EVENT_RELEASED:
      {
        Serial.println("Play the previous song.");
        music_index_num--;
        if (music_index_num < 0)
          music_index_num = read_file_num(MUSIC_FOLDER) - 1;
        music_set_imgbtn_state(true);
        String music_name = get_file_name_by_index(MUSIC_FOLDER, music_index_num);
        music_set_label_text(music_name.c_str());
        music_stop();
        music_load_mp3(music_name.c_str());
      }
      break;
    default:
      break;
  }
}

static void music_imgbtn_right_event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  switch (code) {
    case LV_EVENT_CLICKED:
      {
        Serial.println("Clicked the right button.");
      }
      break;
    case LV_EVENT_RELEASED:
      {
        Serial.println("Play the next song.");
        music_index_num++;
        if (music_index_num >= read_file_num(MUSIC_FOLDER))
          music_index_num = 0;
        music_set_imgbtn_state(true);
        String music_name = get_file_name_by_index(MUSIC_FOLDER, music_index_num);
        music_set_label_text(music_name.c_str());
        music_stop();
        music_load_mp3(music_name.c_str());
      }
      break;
    default:
      break;
  }
}

static void music_imgbtn_play_event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  switch (code) {
    case LV_EVENT_CLICKED:
      {
        Serial.println("Clicked the play button.");
      }
      break;
    case LV_EVENT_RELEASED:
      {
        Serial.println("Released the play button.");
        if (music_play_state == 0) {
          music_play_state = 1;
          music_set_imgbtn_state(music_play_state);
          String music_name = get_file_name_by_index(MUSIC_FOLDER, music_index_num);
          music_set_label_text(music_name.c_str());
          music_stop();
          music_load_mp3(music_name.c_str());
        } else {
          music_play_state = 0;
          music_set_imgbtn_state(music_play_state);
          music_stop();
        }
      }
      break;
    default:
      break;
  }
}

static void music_slider_change_event_handler(lv_event_t *e) {
  lv_obj_t *slider = lv_event_get_target(e);
  char buf[16];
  int volume = (int)lv_slider_get_value(slider);
  music_set_volume(volume);
  lv_snprintf(buf, sizeof(buf), "Volume: %d", volume);
  lv_label_set_text(guider_music_ui.music_slider_label, buf);
}

void music_timer_event_handler(lv_timer_t *timer) {
  if (music_is_running()) {
    if (!music_loop()) {
      music_stop();
    }
  } else {
    if (music_play_state == 1) {
      music_play_state = 0;
      music_set_imgbtn_state(music_play_state);
    }
  }
}

void setup_scr_music(lvgl_music_ui *ui) {
  music_dac_init();
  ui->music = lv_obj_create(NULL);
  lv_coord_t screen_width = lv_obj_get_width(ui->music);    // Get screen width
  lv_coord_t screen_height = lv_obj_get_height(ui->music);  // Get screen height

  static lv_style_t bg_style;
  lv_style_init(&bg_style);
  lv_style_set_bg_color(&bg_style, lv_color_hex(0xffffff));
  lv_obj_add_style(ui->music, &bg_style, LV_PART_MAIN);

  lv_img_home_init();
  lv_img_left_init();
  lv_img_right_init();
  lv_img_pause_init();
  lv_img_playing_init();

  static lv_style_t style_pr;
  lv_style_init(&style_pr);
  lv_style_set_translate_y(&style_pr, 5);

  ui->music_imgbtn_home = lv_imgbtn_create(ui->music);
  lv_obj_set_size(ui->music_imgbtn_home, 80, 80);
  lv_img_set_src(ui->music_imgbtn_home, &img_home);
  lv_obj_add_style(ui->music_imgbtn_home, &style_pr, LV_STATE_PRESSED);
  lv_obj_align(ui->music_imgbtn_home, LV_ALIGN_TOP_MID, 0, (screen_height - 180) / 6);

  ui->music_slider_label = lv_label_create(ui->music);
  lv_obj_set_size(ui->music_slider_label, (screen_width - 20), 10);
  lv_obj_set_style_text_align(ui->music_slider_label, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_align_to(ui->music_slider_label, ui->music_imgbtn_home, LV_ALIGN_OUT_BOTTOM_MID, 0, (screen_height - 180) / 6);

  ui->music_slider_valume = lv_slider_create(ui->music);
  lv_obj_set_size(ui->music_slider_valume, (screen_width - 20), 10);
  lv_slider_set_mode(ui->music_slider_valume, LV_SLIDER_MODE_NORMAL);
  lv_slider_set_range(ui->music_slider_valume, 0, 39);
  lv_slider_set_value(ui->music_slider_valume, 10, LV_ANIM_OFF);
  lv_obj_align_to(ui->music_slider_valume, ui->music_slider_label, LV_ALIGN_OUT_BOTTOM_MID, 0, (screen_height - 180) / 6);

  ui->music_label = lv_label_create(ui->music);
  lv_obj_set_size(ui->music_label, (screen_width - 20), 20);
  //lv_label_set_long_mode(ui->music_label, LV_LABEL_LONG_SCROLL_CIRCULAR);
  lv_obj_set_style_text_align(ui->music_label, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_align_to(ui->music_label, ui->music_slider_valume, LV_ALIGN_OUT_BOTTOM_MID, 0, (screen_height - 180) / 6);

  ui->music_imgbtn_play = lv_imgbtn_create(ui->music);
  lv_obj_set_size(ui->music_imgbtn_play, 60, 60);
  lv_img_set_src(ui->music_imgbtn_play, &img_pause);
  lv_obj_add_style(ui->music_imgbtn_play, &style_pr, LV_STATE_PRESSED);
  lv_obj_align_to(ui->music_imgbtn_play, ui->music_label, LV_ALIGN_OUT_BOTTOM_MID, 0, (screen_height - 180) / 6);

  ui->music_imgbtn_left = lv_imgbtn_create(ui->music);
  lv_obj_set_size(ui->music_imgbtn_left, 60, 60);
  lv_img_set_src(ui->music_imgbtn_left, &img_left);
  lv_obj_add_style(ui->music_imgbtn_left, &style_pr, LV_STATE_PRESSED);
  lv_obj_align_to(ui->music_imgbtn_left, ui->music_imgbtn_play, LV_ALIGN_OUT_LEFT_MID, -((screen_width - 180) / 4), 0);

  ui->music_imgbtn_right = lv_imgbtn_create(ui->music);
  lv_obj_set_size(ui->music_imgbtn_right, 60, 60);
  lv_img_set_src(ui->music_imgbtn_right, &img_right);
  lv_obj_add_style(ui->music_imgbtn_right, &style_pr, LV_STATE_PRESSED);
  lv_obj_align_to(ui->music_imgbtn_right, ui->music_imgbtn_play, LV_ALIGN_OUT_RIGHT_MID, ((screen_width - 180) / 4), 0);

  if (read_file_num(MUSIC_FOLDER) > 0) {
    String file_name = get_file_name_by_index(MUSIC_FOLDER, music_index_num);
    music_set_label_text(file_name.c_str());
    char buf_music_path[255] = { 0 };
    memset(buf_music_path, 0, sizeof(buf_music_path));
    strcat(buf_music_path, MUSIC_FOLDER);
    strcat(buf_music_path, "/");
    strcat(buf_music_path, file_name.c_str());
    music_load_mp3(buf_music_path);
    music_play_state = 0;
  } else {
    Serial.printf("SD card has no files!\r\n");
  }
  int volume = (int)lv_slider_get_value(ui->music_slider_valume);
  char buf_music_volume[50];
  music_set_volume(volume);
  lv_snprintf(buf_music_volume, sizeof(buf_music_volume), "Volume:%d", volume);
  lv_label_set_text(guider_music_ui.music_slider_label, buf_music_volume);

  lv_obj_add_event_cb(ui->music_imgbtn_home, music_imgbtn_home_event_handler, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui->music_imgbtn_left, music_imgbtn_left_event_handler, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui->music_imgbtn_right, music_imgbtn_right_event_handler, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui->music_imgbtn_play, music_imgbtn_play_event_handler, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui->music_slider_valume, music_slider_change_event_handler, LV_EVENT_VALUE_CHANGED, NULL);

  ui->music_timer = lv_timer_create(music_timer_event_handler, 1, NULL);
}
