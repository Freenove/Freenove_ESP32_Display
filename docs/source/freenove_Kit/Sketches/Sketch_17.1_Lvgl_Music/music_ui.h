#ifndef __MUSIC_H
#define __MUSIC_H

#include "lvgl.h"
#include "Arduino.h"

typedef struct lvgl_music
{
	lv_obj_t *music;
	lv_obj_t *music_imgbtn_home;
	lv_obj_t *music_imgbtn_left;
	lv_obj_t *music_imgbtn_play;
	lv_obj_t *music_imgbtn_right;
	lv_obj_t *music_label;
	lv_obj_t *music_slider_valume;
	lv_obj_t *music_slider_label;
	lv_timer_t *music_timer;
} lvgl_music_ui;

extern lvgl_music_ui guider_music_ui;	 // music ui structure

void music_set_label_text(const char *text); // Set the label display content
void setup_scr_music(lvgl_music_ui *ui); // Parameter configuration function on the music screen

void music_set_volume(int volume);	   // Set the volume: 0-21
void music_dac_init(void);             // DAC initialization
void music_load_mp3(const char *name); // load the mp3
void music_stop(void);				   // Stop the music
bool music_is_running(void);		   // Whether the music is running
bool music_loop(void);				   // Non-blocking audio execution function

#endif
