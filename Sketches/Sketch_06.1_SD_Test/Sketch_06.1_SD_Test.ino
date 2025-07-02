/*
* @ File:   Sketch_06.1_SD_Test.ino
* @ Author: [Zhentao Lin]
* @ Date:   [2025-06-14]
*/

#include "sd_read_write.h"
#include "SPI.h"

#define SD_VSPI_SS 5
#define SD_VSPI_SCK 18
#define SD_VSPI_MISO 19
#define SD_VSPI_MOSI 23

SPIClass spi(VSPI);

void setup() {
  Serial.begin(115200);
  spi.begin(SD_VSPI_SCK, SD_VSPI_MISO, SD_VSPI_MOSI, SD_VSPI_SS);
  if (!SD.begin(SD_VSPI_SS, spi)) {
    Serial.println(F("SD.begin failed!"));
    while (1) delay(1);
  }
  Serial.println("\r\nInitialisation done.");
  uint8_t cardType = SD.cardType();
  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }

  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);

  listDir(SD, "/", 0);

  createDir(SD, "/mydir");
  listDir(SD, "/", 0);

  removeDir(SD, "/mydir");
  listDir(SD, "/", 2);

  writeFile(SD, "/hello.txt", "Hello ");
  appendFile(SD, "/hello.txt", "World!\n");
  readFile(SD, "/hello.txt");

  deleteFile(SD, "/foo.txt");
  renameFile(SD, "/hello.txt", "/foo.txt");
  readFile(SD, "/foo.txt");

  testFileIO(SD, "/test.txt");

  Serial.printf("Total space: %lluMB\r\n", SD.totalBytes() / (1024 * 1024));
  Serial.printf("Used space: %lluMB\r\n", SD.usedBytes() / (1024 * 1024));
}

void loop() {
  delay(10000);
}