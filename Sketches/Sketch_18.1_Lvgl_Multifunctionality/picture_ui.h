#ifndef __PICTURE_UI_H
#define __PICTURE_UI_H

#include "public.h"

typedef struct lvgl_picture
{
	lv_obj_t *picture;
	lv_obj_t *picture_img_show;
	lv_obj_t *picture_imgbtn_left;
	lv_obj_t *picture_imgbtn_right;
	lv_obj_t *picture_imgbtn_home;
}lvgl_picture_ui;

extern lvgl_picture_ui guider_picture_ui;    //picture ui structure 

void setup_scr_picture(lvgl_picture_ui *ui); //Parameter configuration function on the picture screen
void picture_imgbtn_display(const char *name);     //Read the image file and display it









#endif
