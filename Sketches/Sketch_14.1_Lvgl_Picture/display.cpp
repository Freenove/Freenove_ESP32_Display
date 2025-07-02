#include <stdint.h>
#include "display.h"

#if defined(FNK0103B_2P8_240x320_ST7789) || defined(FNK0103F_2P8_240x320_ILI9341)
  #ifndef _TFT_Touch_H
    #include "TFT_Touch.h"
    #if !defined(_TFT_Touch_H)
      #error "Please install TFT_Touch library before using this library!"
    #endif
  #endif
#define DOUT 39 /* Data out pin (T_DO) of touch screen */
#define DIN 32  /* Data in pin (T_DIN) of touch screen */
#define DCS 33  /* Chip select pin (T_CS) of touch screen */
#define DCLK 25 /* Clock pin (T_CLK) of touch screen */
#define TFT_SCREEN_WIDTH 240
#define TFT_SCREEN_HEIGHT 320
TFT_Touch touch = TFT_Touch(DCS, DCLK, DIN, DOUT);
#elif defined(FNK0103L_3P2_240x320_ST7789)
#define TFT_SCREEN_WIDTH 240
#define TFT_SCREEN_HEIGHT 320
#elif defined(FNK0103N_3P5_320x480_ST7796) || defined(FNK0103S_4P0_320x480_ST7796)
#define TFT_SCREEN_WIDTH 320
#define TFT_SCREEN_HEIGHT 480
#endif

static const uint16_t screenWidth = TFT_SCREEN_WIDTH;
static const uint16_t screenHeight = TFT_SCREEN_HEIGHT;
static const uint16_t screenHeightBuf = TFT_SCREEN_HEIGHT / 10;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t draw_buf1[screenWidth * screenHeightBuf];
//static lv_color_t draw_buf2[screenWidth * screenHeightBuf];

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char *buf) {
  Serial.printf(buf);
  Serial.flush();
}
#endif

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);
  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors((uint16_t *)&color_p->full, w * h, true);
  tft.endWrite();
  lv_disp_flush_ready(disp);
}

/*Read the touchpad*/
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {
  uint16_t touchX, touchY;
  bool touched;
#if defined(FNK0103B_2P8_240x320_ST7789) || defined(FNK0103F_2P8_240x320_ILI9341)
  touched = touch.Pressed();
  touchX = touch.X();
  touchY = touch.Y();
  if (!touched) {
    data->state = LV_INDEV_STATE_REL;
  } else {
    data->state = LV_INDEV_STATE_PR;
#if (TFT_DIRECTION == 0)
    data->point.x = tft.width() - touchY;
    data->point.y = touchX;
#elif (TFT_DIRECTION == 1)
    data->point.x = touchX;
    data->point.y = touchY;
#elif (TFT_DIRECTION == 2)
    data->point.x = touchY;
    data->point.y = tft.height() - touchX;
#elif (TFT_DIRECTION == 3)
    data->point.x = tft.width() - touchX;
    data->point.y = tft.height() - touchY;
#endif
    // Serial.print("Data x ");
    // Serial.print(data->point.x);
    // Serial.print("\tData y ");
    // Serial.println(data->point.y);
  }
#elif defined(FNK0103L_3P2_240x320_ST7789)
  touched = tft.getTouch(&touchX, &touchY, 600);
  if (!touched) {
    data->state = LV_INDEV_STATE_REL;
  } else {
    data->state = LV_INDEV_STATE_PR;
#if (TFT_DIRECTION == 0)
    data->point.x = touchX;
    data->point.y = touchY;
#elif (TFT_DIRECTION == 1)
    data->point.x = map(touchY, 0, tft.height(), 0, tft.width());
    data->point.y = map((tft.width() - touchX), 0, tft.width(), 0, tft.height());
#elif (TFT_DIRECTION == 2)
    data->point.x = tft.width() - touchX;
    data->point.y = tft.height() - touchY;
#elif (TFT_DIRECTION == 3)
    data->point.x = map((tft.height() - touchY), 0, tft.height(), 0, tft.width());
    data->point.y = map(touchX, 0, tft.width(), 0, tft.height());
#endif
    // Serial.print("Data x ");
    // Serial.print(data->point.x);
    // Serial.print("\tData y ");
    // Serial.println(data->point.y);
  }
#elif defined(FNK0103N_3P5_320x480_ST7796) || defined(FNK0103S_4P0_320x480_ST7796)
  touched = tft.getTouch(&touchX, &touchY, 600);
  if (!touched) {
    data->state = LV_INDEV_STATE_REL;
  } else {
    data->state = LV_INDEV_STATE_PR;
#if (TFT_DIRECTION == 0)
    data->point.x = tft.width() - touchX;
    data->point.y = touchY;
#elif (TFT_DIRECTION == 1)
    data->point.x = map(touchY, 0, tft.height(), 0, tft.width());
    data->point.y = map(touchX, 0, tft.width(), 0, tft.height());
#elif (TFT_DIRECTION == 2)
    data->point.x = touchX;
    data->point.y = tft.height() - touchY;
#elif (TFT_DIRECTION == 3)
    data->point.x = map((tft.height() - touchY), 0, tft.height(), 0, tft.width());
    data->point.y = map(tft.width() - touchX, 0, tft.width(), 0, tft.height());
#endif
    // Serial.print("Data x ");
    // Serial.print(data->point.x);
    // Serial.print("\tData y ");
    // Serial.println(data->point.y);
  }
#endif
}

void Display::init(void) {
#if defined(FNK0103B_2P8_240x320_ST7789) || defined(FNK0103F_2P8_240x320_ILI9341)
  touch.setCal(526, 3443, 750, 3377, screenHeight, screenWidth, 1);
#elif defined(FNK0103L_3P2_240x320_ST7789)
  uint16_t calData[5] = { 286, 3534, 283, 3600, 6 };
  tft.setTouch(calData);
#elif defined(FNK0103N_3P5_320x480_ST7796) || defined(FNK0103S_4P0_320x480_ST7796)
  uint16_t calData[5] = { 286, 3534, 283, 3600, 6 };
  tft.setTouch(calData);
#endif

#if LV_USE_LOG != 0
  lv_log_register_print_cb(my_print); /* register print function for debugging */
#endif
  tft.begin();                    /* TFT init */
  tft.setRotation(TFT_DIRECTION); /* Landscape orientation, flipped */

  lv_init();
  //lv_disp_draw_buf_init(&draw_buf, draw_buf1, draw_buf2, screenWidth * screenHeightBuf);
  lv_disp_draw_buf_init(&draw_buf, draw_buf1, NULL, screenWidth * screenHeightBuf);

  /*Initialize the display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  /*Change the following line to your display resolution*/
#if (TFT_DIRECTION % 2 == 0)
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
#else
  disp_drv.hor_res = screenHeight;
  disp_drv.ver_res = screenWidth;
#endif

  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  /*Initialize the (dummy) input device driver*/
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);
}

void Display::routine(void) {
  lv_task_handler();
}
