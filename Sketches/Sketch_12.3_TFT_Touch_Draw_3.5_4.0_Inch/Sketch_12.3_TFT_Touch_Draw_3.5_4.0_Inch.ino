/*
* @ File:   Sketch_12.3_TFT_Touch_Draw_3.5_4.0_Inch.ino
* @ Author: [Zhentao Lin]
* @ Date:   [2025-06-20]
*/

#include <TFT_eSPI.h>  // TFT display library

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 480

TFT_eSPI tft = TFT_eSPI(SCREEN_WIDTH, SCREEN_HEIGHT);

// Define coordinate variables
uint16_t x, y;
uint16_t last_x, last_y;

const uint8_t ColorPalette = 32;      // Height of the color palette area
const uint8_t BrushSize = 3;          // Brush thickness (radius)
const uint8_t LineSize = 7;           // Line thickness (radius)
const uint8_t color_num = 12;
int color = TFT_WHITE;

unsigned int colors[color_num] = { TFT_RED, TFT_PINK, TFT_GREEN, TFT_BLUE, TFT_OLIVE , TFT_CYAN, TFT_YELLOW, TFT_WHITE, TFT_MAGENTA, TFT_ORANGE, TFT_BLACK, TFT_SILVER};

void drawUI()
{
  // Draw color palette
  for (int i = 0; i < color_num; i++) {
    tft.fillRect(i * ColorPalette, 0, ColorPalette, ColorPalette, colors[i]);
  }



  // Draw clear screen button
  tft.setCursor(405 , 8, 2);
  tft.setTextColor(TFT_WHITE);
  tft.print("Clear");
  
  // Display current color
  tft.fillRect(450, 9, 12, 12, color);

  // Add palette border/outline
  tft.drawRect(0, 0, SCREEN_HEIGHT, ColorPalette, TFT_WHITE);
}

void setup() {
  Serial.begin(115200);
  tft.init();
  uint16_t calData[5] = { 303, 3458, 350, 3304, 7 };
  tft.setTouch(calData);
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  drawUI();
}

void loop() {
  bool pressed = tft.getTouch(&x, &y);

  if (pressed) {
    Serial.printf("x: %d, y: %d\r\n", x, y);
    
    /* Color palette area logic */
    if(y < ColorPalette + 3)
    {
      // Enter color selection area, stroke interrupted
      last_x = 0;
      last_y = 0;

      /* Determine stylus click area */
      // Clicked Clear button
      if(x >= ColorPalette * color_num)
      {
        tft.fillRect(0, ColorPalette, SCREEN_HEIGHT, SCREEN_WIDTH - ColorPalette, color);
      }
      // Clicked color palette
      else{
        // Calculate current color based on x-coordinate
        color = colors[x / ColorPalette];

        // Update display of current color
        tft.fillRect(450, 9, 12, 12, color);
      }
      delay(5);
      return;
    }

    /* Drawing logic */
    // Start of a new stroke
    if(last_x == 0 && last_y == 0)
    {
      // Record current position
      last_x = x;
      last_y = y;
    }

    // Draw a line between the previous position and current position
    tft.drawWideLine(last_x, last_y, x, y, LineSize, color, color);

    // Update coordinates
    last_x = x;
    last_y = y;
  }
  else{
    // Reset coordinates when stylus leaves the screen
    last_x = 0;
    last_y = 0;
  }
}