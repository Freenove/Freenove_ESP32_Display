/*
* @ File:   Sketch_07.1_Play_MP3_SD_by_DAC.ino
* @ Author: [Zhentao Lin]
* @ Date:   [2025-06-14]
*/

#include <Arduino.h>
#include <WiFi.h>
#include "AudioFileSourceSD.h"
#include "AudioFileSourceID3.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"

#define AUDIO_EN 4
#define SD_VSPI_SS 5
#define SD_VSPI_MOSI 23
#define SD_VSPI_MISO 19
#define SD_VSPI_SCK 18

AudioFileSourceSD *file;
AudioFileSourceID3 *id3;
AudioOutputI2S *out;
AudioGeneratorMP3 *mp3;

SPIClass *vspi = NULL;

void playMP3(char *filename) {
  file = new AudioFileSourceSD(filename);
  id3 = new AudioFileSourceID3(file);
  out = new AudioOutputI2S(0, 1);
  out->SetGain(1);
  mp3 = new AudioGeneratorMP3();
  mp3->begin(id3, out);
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  WiFi.mode(WIFI_OFF);
  pinMode(AUDIO_EN, OUTPUT);
  digitalWrite(AUDIO_EN, LOW);
  delay(500);
  vspi = new SPIClass(VSPI);
  vspi->begin(SD_VSPI_SCK, SD_VSPI_MISO, SD_VSPI_MOSI, SD_VSPI_SS);
  if (!SD.begin(SD_VSPI_SS, *vspi)) {
    Serial.println(F("SD.begin failed!"));
    while (1) delay(1);
  }
  playMP3("/Olsen-Banden.mp3");
}

void loop() {
  while (mp3->isRunning()) {
    if (!mp3->loop()) mp3->stop();
  }
}