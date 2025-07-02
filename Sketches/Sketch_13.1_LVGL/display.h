#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "Arduino.h"
#include "lvgl.h"

#include <TFT_eSPI.h> // TFT display library


#define TFT_DIRECTION 0   //Select TFT Direction (0 - 3)


class Display
{
private:

public:
    void init();
    void routine();
};

#endif
