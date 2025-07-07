/*
* @ File:   Sketch_08.2_BLE_RGB.ino
* @ Author: [Zhentao Lin]
* @ Date:   [2025-06-14]
*/

#include "BLEDevice.h"
#include "BLEServer.h"
#include "BLEUtils.h"
#include "BLE2902.h"
#include "String.h"

BLECharacteristic *pCharacteristic;
bool deviceConnected = false;
uint8_t txValue = 0;
long lastMsg = 0;
String rxload = "Test\n";

#define SERVICE_UUID "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

#define RED_PIN 22
#define GREEN_PIN 16
#define BLUE_PIN 17

void rgbInit(void) {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void setRGB(bool redLevel, bool greenLevel, bool blueLevel) {
  digitalWrite(RED_PIN, !redLevel);
  digitalWrite(GREEN_PIN, !greenLevel);
  digitalWrite(BLUE_PIN, !blueLevel);
}

class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer *pServer) {
    deviceConnected = true;
  };
  void onDisconnect(BLEServer *pServer) {
    deviceConnected = false;
  }
};

class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    String rxValue = pCharacteristic->getValue();
    if (rxValue.length() > 0) {
      rxload = "";
      for (int i = 0; i < rxValue.length(); i++) {
        rxload += (char)rxValue[i];
      }
    }
  }
};

void setupBLE(String BLEName) {
  const char *ble_name = BLEName.c_str();
  BLEDevice::init(ble_name);
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_TX, BLECharacteristic::PROPERTY_NOTIFY);
  pCharacteristic->addDescriptor(new BLE2902());
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_RX, BLECharacteristic::PROPERTY_WRITE);
  pCharacteristic->setCallbacks(new MyCallbacks());
  pService->start();
  pServer->getAdvertising()->start();
  Serial.println("Waiting a client connection to notify...");
}

void setup() {
  Serial.begin(115200);
  rgbInit();
  setRGB(0, 0, 0);
  setupBLE("ESP32_BLE");
}

void loop() {
  long now = millis();
  if (now - lastMsg > 100) {
    if (deviceConnected && rxload.length() > 0) {
      Serial.println(rxload);
      if (strncmp(rxload.c_str(), "red_on", 6) == 0) {
        setRGB(1, 0, 0);
      } else if (strncmp(rxload.c_str(), "red_off", 7) == 0) {
        setRGB(0, 0, 0);
      } else if (strncmp(rxload.c_str(), "green_on", 8) == 0) {
        setRGB(0, 1, 0);
      } else if (strncmp(rxload.c_str(), "green_off", 9) == 0) {
        setRGB(0, 0, 0);
      } else if (strncmp(rxload.c_str(), "blue_on", 7) == 0) {
        setRGB(0, 0, 1);
      } else if (strncmp(rxload.c_str(), "blue_off", 8) == 0) {
        setRGB(0, 0, 0);
      }
      rxload = "";
    }
    if (Serial.available() > 0) {
      String str = Serial.readString();
      const char *newValue = str.c_str();
      pCharacteristic->setValue(newValue);
      pCharacteristic->notify();
    }
    lastMsg = now;
  }
}
