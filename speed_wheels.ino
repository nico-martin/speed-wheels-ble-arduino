#include <ArduinoBLE.h>
#include "neopixel_functions.h"
#include "motor_functions.h"

BLEService motorControlService("c10e3e56-fdd3-11eb-9a03-0242ac130003");
BLECharacteristic motorCharacteristic(
  "35a1022c-fdd3-11eb-9a03-0242ac130003",
  BLERead | BLEWrite,
  2
);

BLEService ledControlService("90c554cb-1640-44d6-88ee-85a5eb8ace90");
BLEByteCharacteristic ledCharacteristic(
  "f601d5ac-c20b-4917-9cfc-28788d4454be",
  BLERead | BLEWrite
);

void setup() {
  Serial.println("starting..");

  if (!BLE.begin()) {
    Serial.println("starting BLE module failed!");
    while (1);
  }

  BLE.setLocalName("SpeedWheels");

  BLE.setAdvertisedService(motorControlService);
  motorControlService.addCharacteristic(motorCharacteristic);
  BLE.addService(motorControlService);

  BLE.setAdvertisedService(ledControlService);
  ledControlService.addCharacteristic(ledCharacteristic);
  BLE.addService(ledControlService);

  BLE.setEventHandler(BLEConnected, blePeripheralConnectHandler);
  BLE.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);

  motorCharacteristic.setEventHandler(BLEWritten, motorCharacteristicWritten);
  motorCharacteristic.writeValue((word) 0x0000);

  ledCharacteristic.setEventHandler(BLEWritten, ledCharacteristicWritten);
  ledCharacteristic.writeValue((word) 0x00);

  setupMotor();
  setupStrip();
  BLE.advertise();
  Serial.println("'SpeedWheels' is now active..");
  setRingMode(1);
}

void loop() {
  BLE.poll();
  neopixelPolling();
  delay(50);
}

void blePeripheralConnectHandler(BLEDevice central) {
  Serial.print("Connected event, central: ");
  Serial.println(central.address());
  setRingMode(0);
}

void blePeripheralDisconnectHandler(BLEDevice central) {
  Serial.print("Disconnected event, central: ");
  Serial.println(central.address());
  setRingMode(1);
}

void motorCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic) {
  word data;
  motorCharacteristic.readValue(data);
  moveLeftWheel((data >> (8*0)) & 0xff);
  moveRightWheel((data >> (8*1)) & 0xff);
}

void ledCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic) {
  word data;
  ledCharacteristic.readValue(data);
  setRingMode((data >> (8*0)) & 0xff);
}
