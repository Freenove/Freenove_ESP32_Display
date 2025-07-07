#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "Arduino.h"
#include "lvgl.h"

#include <TFT_eSPI.h> // TFT display library

//Select TFT Direction (0-3). Don't modify it. Modifying it may cause an lvgl picture exception.
#define TFT_DIRECTION 0   

class Display
{
private:

public:
    void init();
    void routine();
};

#endif
