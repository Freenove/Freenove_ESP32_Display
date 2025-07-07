/*
* @ File:   Sketch_14.1_LVGL_Picture.ino
* @ Author: [Zhentao Lin]
* @ Date:   [2025-06-23]
*/

#include "display.h"
#include "driver_sdspi.h"
#include "picture_ui.h"

Display screen;

#define SD_SCK   18
#define SD_MISO  19
#define SD_MOSI  23
#define SD_CS    5

void setup(){
    /* prepare for possible serial debug */
    Serial.begin( 115200 );

   /*** Init drivers ***/
    sdspi_init(SD_SCK, SD_MISO, SD_MOSI, SD_CS);       //Initialize the SD module
    screen.init();

    String LVGL_Arduino = "Hello Arduino! ";
    LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();
    Serial.println( LVGL_Arduino );
    Serial.println( "I am LVGL_Arduino" );
    
    setup_scr_picture(&guider_picture_ui);
    lv_scr_load(guider_picture_ui.picture);

    Serial.println( "Setup done" );
}

void loop(){
    screen.routine(); /* let the GUI do its work */
    delay( 5 );
}