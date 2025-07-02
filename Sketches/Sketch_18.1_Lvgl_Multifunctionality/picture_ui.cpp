#include "picture_ui.h"
#include "driver_sdspi.h"

#define PICTURE_FOLDER "/Picture"
lvgl_picture_ui guider_picture_ui;  // picture ui structure
int picture_index = 0;
int picture_width = 240;

static void picture_imgbtn_left_event_handler(lv_event_t *event) {
  lv_event_code_t code = lv_event_get_code(event);
  if (code == LV_EVENT_PRESSED) {
    Serial.println("Picture Btn Left Pressed!");
  } else if (code == LV_EVENT_RELEASED) {
    Serial.println("Picture Btn Left Released!");
    char buf_picture_name[256] = {""};
    if(picture_width==240)
    {
      strcat(buf_picture_name, PICTURE_FOLDER);
      strcat(buf_picture_name, "/Picture_240x240");
    }
    else if(picture_width==320)
    {
      strcat(buf_picture_name, PICTURE_FOLDER);
      strcat(buf_picture_name, "/Picture_320x320");
    }
    picture_index--;
    if (picture_index < 0) {
      int sd_picture_count = read_file_num(buf_picture_name);
      picture_index = sd_picture_count - 1;
    }
    String file_name = get_file_name_by_index(buf_picture_name, picture_index);
    picture_imgbtn_display(file_name.c_str());
  }
  lv_event_stop_bubbling(event);
}

static void picture_imgbtn_right_event_handler(lv_event_t *event) {
  lv_event_code_t code = lv_event_get_code(event);
  if (code == LV_EVENT_PRESSED) {
    Serial.println("Picture Btn Right Pressed!");
  } else if (code == LV_EVENT_RELEASED) {
    Serial.println("Picture Btn Right Released!");
    picture_index++;
    char buf_picture_name[256] = {""};
    if(picture_width==240)
    {
      strcat(buf_picture_name, PICTURE_FOLDER);
      strcat(buf_picture_name, "/Picture_240x240");
    }
    else if(picture_width==320)
    {
      strcat(buf_picture_name, PICTURE_FOLDER);
      strcat(buf_picture_name, "/Picture_320x320");
    }
    int sd_picture_count = read_file_num(buf_picture_name);
    if (picture_index >= sd_picture_count) {
      picture_index = 0;
    }
    String file_name = get_file_name_by_index(buf_picture_name, picture_index);
    picture_imgbtn_display(file_name.c_str());
  }
  lv_event_stop_bubbling(event);
}

static void picture_imgbtn_home_event_handler(lv_event_t *e) {
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
        lv_obj_del(guider_picture_ui.picture);
      }
      break;
    default:
      break;
  }
}

// Parameter configuration function on the picture screen
void setup_scr_picture(lvgl_picture_ui *ui) {
  // Create a scrollable container
  ui->picture = lv_obj_create(NULL);
  lv_coord_t screen_width = lv_obj_get_width(ui->picture);    // Get screen width
  lv_coord_t screen_height = lv_obj_get_height(ui->picture);  // Get screen height
  lv_obj_set_size(ui->picture, screen_width, screen_height);
  picture_width = screen_width;

  static lv_style_t bg_style;
  lv_style_init(&bg_style);
  lv_style_set_bg_color(&bg_style, lv_color_hex(0xffffff));
  lv_obj_add_style(ui->picture, &bg_style, LV_PART_MAIN);

    /*Init the pressed style*/
  static lv_style_t style_pr;              // Apply for a style
  lv_style_init(&style_pr);                // Initialize it
  lv_style_set_translate_y(&style_pr, 5);  // Style: Every time you trigger, move down 5 pixels

  lv_img_home_init();
  lv_img_left_init();
  lv_img_right_init();

  // Write codes picture_img_show
  ui->picture_img_show = lv_img_create(ui->picture);
  lv_obj_set_size(ui->picture_img_show, screen_width, screen_width);  // Set the actual size of the image
  lv_obj_align(ui->picture_img_show, LV_ALIGN_TOP_MID, 0, 0);
  static lv_style_t style_border;
  lv_style_init(&style_border);
  lv_style_set_border_width(&style_border, 1);
  lv_style_set_border_color(&style_border, lv_color_hex(0x000000));
  lv_obj_add_style(ui->picture_img_show, &style_border, LV_PART_MAIN);

  ui->picture_imgbtn_home = lv_imgbtn_create(ui->picture);
  lv_obj_set_size(ui->picture_imgbtn_home, 80, 80);
  lv_obj_align_to(ui->picture_imgbtn_home, ui->picture_img_show, LV_ALIGN_OUT_BOTTOM_MID, 0, (screen_height-screen_width-80)/2);
  lv_img_set_src(ui->picture_imgbtn_home, &img_home);
  lv_obj_add_style(ui->picture_imgbtn_home, &style_pr, LV_STATE_PRESSED);
  lv_obj_move_foreground(ui->picture_imgbtn_home);

  ui->picture_imgbtn_left = lv_imgbtn_create(ui->picture);
  lv_obj_set_size(ui->picture_imgbtn_left, 60, 60);
  lv_obj_align_to(ui->picture_imgbtn_left, ui->picture_imgbtn_home, LV_ALIGN_OUT_LEFT_MID, -(screen_width-200)/4, 0);
  lv_img_set_src(ui->picture_imgbtn_left, &img_left);
  lv_obj_add_style(ui->picture_imgbtn_left, &style_pr, LV_STATE_PRESSED);
  lv_obj_move_foreground(ui->picture_imgbtn_left);

  ui->picture_imgbtn_right = lv_imgbtn_create(ui->picture);
  lv_obj_set_size(ui->picture_imgbtn_right, 60, 60);
  lv_obj_align_to(ui->picture_imgbtn_right, ui->picture_imgbtn_home, LV_ALIGN_OUT_RIGHT_MID, (screen_width-200)/4, 0);
  lv_img_set_src(ui->picture_imgbtn_right, &img_right);
  lv_obj_add_style(ui->picture_imgbtn_right, &style_pr, LV_STATE_PRESSED);
  lv_obj_move_foreground(ui->picture_imgbtn_right);

  lv_obj_add_event_cb(ui->picture_imgbtn_home, picture_imgbtn_home_event_handler, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui->picture_imgbtn_left, picture_imgbtn_left_event_handler, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui->picture_imgbtn_right, picture_imgbtn_right_event_handler, LV_EVENT_ALL, NULL);
  
  char buf_picture_name[256] = {""};
  if(picture_width==240)
  {
    strcat(buf_picture_name, PICTURE_FOLDER);
    strcat(buf_picture_name, "/Picture_240x240");
  }
  else if(picture_width==320)
  {
    strcat(buf_picture_name, PICTURE_FOLDER);
    strcat(buf_picture_name, "/Picture_320x320");
  }
  if (read_file_num(buf_picture_name) >= 0) {
    String file_name = get_file_name_by_index(buf_picture_name, picture_index);
    picture_imgbtn_display(file_name.c_str());
  } else {
    Serial.printf("SD card has no files!\r\n");
  }
}

//Read the image file and display it
void picture_imgbtn_display(const char *name) {
  if (name != NULL) {
    char buf_picture_name[256] = { "S:" };
    strcat(buf_picture_name, PICTURE_FOLDER);
    if(picture_width==240)
      strcat(buf_picture_name, "/Picture_240x240/");
    else if(picture_width==320)
      strcat(buf_picture_name, "/Picture_320x320/");
    strcat(buf_picture_name, name);
    Serial.printf("%s\n", buf_picture_name);
    lv_img_header_t header;
    lv_res_t res = lv_img_decoder_get_info(buf_picture_name, &header);
    if (res == LV_RES_OK) {
      Serial.printf("Image size: %dx%d cf:%d\n", header.w, header.h, header.cf);
      switch(header.cf)
      { 
        case LV_IMG_CF_TRUE_COLOR:              /**< Color format and depth should match with LV_COLOR settings*/
          Serial.println("Image format: LV_IMG_CF_TRUE_COLOR");
          break;
        case LV_IMG_CF_RAW:                     /**< Contains the file as it is. Needs custom decoder function*/
        case LV_IMG_CF_RAW_ALPHA:               /**< Contains the file as it is. The image has alpha. Needs custom decoder function*/
        case LV_IMG_CF_RAW_CHROMA_KEYED:        /**< Contains the file as it is. The image is chroma keyed. Needs custom decoder function*/          
        case LV_IMG_CF_TRUE_COLOR_ALPHA:        /**< Same as `LV_IMG_CF_TRUE_COLOR` but every pixel has an alpha byte*/
        case LV_IMG_CF_TRUE_COLOR_CHROMA_KEYED: /**< Same as `LV_IMG_CF_TRUE_COLOR` but LV_COLOR_TRANSP pixels will be transparent*/
        case LV_IMG_CF_INDEXED_1BIT:            /**< Can have 2 different colors in a palette (can't be chroma keyed)*/
        case LV_IMG_CF_INDEXED_2BIT:            /**< Can have 4 different colors in a palette (can't be chroma keyed)*/
        case LV_IMG_CF_INDEXED_4BIT:            /**< Can have 16 different colors in a palette (can't be chroma keyed)*/
        case LV_IMG_CF_INDEXED_8BIT:            /**< Can have 256 different colors in a palette (can't be chroma keyed)*/
        case LV_IMG_CF_ALPHA_1BIT:              /**< Can have one color and it can be drawn or not*/
        case LV_IMG_CF_ALPHA_2BIT:              /**< Can have one color but 4 different alpha value*/
        case LV_IMG_CF_ALPHA_4BIT:              /**< Can have one color but 16 different alpha value*/
        case LV_IMG_CF_ALPHA_8BIT:              /**< Can have one color but 256 different alpha value*/
        case LV_IMG_CF_RGB888:
        case LV_IMG_CF_RGBA8888:
        case LV_IMG_CF_RGBX8888:
        case LV_IMG_CF_RGB565:
        case LV_IMG_CF_RGBA5658:
        case LV_IMG_CF_RGB565A8:
        case LV_IMG_CF_UNKNOWN:
          Serial.println("Image format error! Please use the tool to convert the image to the correct format."); 
          break;
      }
    }
    lv_img_set_src(guider_picture_ui.picture_img_show, buf_picture_name);
  } else {
    lv_img_set_src(guider_picture_ui.picture_img_show, LV_SYMBOL_DUMMY "The picture folder has no files.");
  }
}
