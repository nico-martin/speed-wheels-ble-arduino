# Speed Wheels BLE Adruino

An Arduino Sketch that controls the wheels/motor (using the [DRV8871 Motor Driver](https://learn.adafruit.com/adafruit-drv8871-brushed-dc-motor-driver-breakout)) and the [12 LED NeoPixel Ring](https://www.bastelgarage.ch/neopixel-ring-12x-ws2812-rgb-led) using **Bluetooth Low Energy (BLE)**.

I had some problems to solve that I documented in a dev.to article:
[https://dev.to/nicomartin/neopixels-on-the-arduino-nano-rp2040-3po6](https://dev.to/nicomartin/neopixels-on-the-arduino-nano-rp2040-3po6)

## Circuit
![circuit design for an Arduino Nano RP2040, DRV8871 and NeoPixel](https://uploads.nico.dev/speed-wheels/arduino-nano-circuit-led.jpg)

## BLE Services
The Arduino exposes a Bluetooth Low Energy Server with to Services:

### Motor control
UUID: `c10e3e56-fdd3-11eb-9a03-0242ac130003`  
motorCharacteristic: `35a1022c-fdd3-11eb-9a03-0242ac130003` - BLERead | BLEWrite

Accepts two bytes between 0 and 200, each byte represents one wheel where the speed goes from 0 (full speed backward) to 100 (stop) to 200 (full speed forward).

### LED control
UUID: `90c554cb-1640-44d6-88ee-85a5eb8ace90`  
ledCharacteristic: `f601d5ac-c20b-4917-9cfc-28788d4454be` - BLERead | BLEWrite

A one-byte characteristic where you can set [one of seven LED-modes](https://github.com/nico-martin/speed-wheels-ble-arduino/blob/main/neopixel_functions.cpp).

## Remote Control
There is a second project for a browser-based remote control that uses the [WebBluetooth API](https://developer.mozilla.org/en-US/docs/Web/API/Web_Bluetooth_API) to communicate with the provided BLE server.

Demo: [https://speed-wheels.nico.dev/](https://speed-wheels.nico.dev/)  
Source: [https://github.com/nico-martin/speed-wheels-ble-ui](https://github.com/nico-martin/speed-wheels-ble-ui)
