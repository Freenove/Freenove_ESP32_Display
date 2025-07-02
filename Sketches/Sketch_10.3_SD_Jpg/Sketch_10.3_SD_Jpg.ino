/*
* @ File:   Sketch_10.3_SD_Jpg.ino
* @ Author: [Zhentao Lin]
* @ Date:   [2025-06-19]
*/

#include <TJpg_Decoder.h>  // JPEG decoder library
#include <TFT_eSPI.h>  // TFT display library
TFT_eSPI tft = TFT_eSPI();

#define SD_VSPI_SS 5     // SD card chip select pin
#define SD_VSPI_MOSI 23  // SD card SPI MOSI pin
#define SD_VSPI_MISO 19  // SD card SPI MISO pin
#define SD_VSPI_SCK 18   // SD card SPI SCK pin
SPIClass* vspi = NULL;   // VSPI

bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap) {
  if (y >= tft.height()) return 0;
  tft.pushImage(x, y, w, h, bitmap);
  return 1;
}

void setup() {
  Serial.begin(115200);
  Serial.println("\n\n Testing TJpg_Decoder library");
  tft.begin();
  // tft.setRotation(1);
  vspi = new SPIClass(VSPI);
  vspi->begin(SD_VSPI_SCK, SD_VSPI_MISO, SD_VSPI_MOSI, SD_VSPI_SS);
  if (!SD.begin(SD_VSPI_SS, *vspi, 1000000)) {
    Serial.println(F("SD.begin failed!"));
    while (1) delay(0);
  }
  Serial.println("\r\nInitialisation done.");
  tft.setTextColor(0xFFFF, 0x0000);
  tft.fillScreen(TFT_BLACK);
  TJpgDec.setJpgScale(1);
  tft.setSwapBytes(true); 
  TJpgDec.setCallback(tft_output);
}

void loop() {
  uint32_t t = millis();
  uint16_t w = 0, h = 0;
  TJpgDec.getSdJpgSize(&w, &h, "/flower.jpg");
  Serial.print("Width = ");
  Serial.print(w);
  Serial.print(", height = ");
  Serial.println(h);
  TJpgDec.drawSdJpg(0, 0, "/flower.jpg");
  t = millis() - t;
  Serial.print(t);
  Serial.println(" ms");
  delay(2000);
}