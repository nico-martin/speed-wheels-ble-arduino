#include <Adafruit_NeoPixel.h>
#include "neopixel_functions.h"

unsigned long prevBleSearchMillis = 0;
unsigned int bleSearchLedI = 0;
int currentRingMode = 0;
unsigned long prevSevenBlinkMillis = 0;

/**
 * Ring Modes
 * 0 = off
 * 1 = bleSearch
 * 2 = full circle white 
 * 3 = left half white
 * 4 = right half white
 * 5 = even white dimmed
 * 6 = odd white dimmed
 * 7 = odd red blink
 * 8 = party (random color per led every 50 ms?)
 */

#define LED_PIN 15
#define LED_COUNT 12

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setupStrip() {
  strip.begin();
  strip.show(); 
  strip.setBrightness(50);
}

void neopixelPolling() {  
  switch(currentRingMode) {
    case 0: 
      for(int i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
      }
      break;

    case 1:
      unsigned long currentBleSearchMillis = millis();
      if(currentBleSearchMillis - prevBleSearchMillis >= 50) {
        prevBleSearchMillis = currentBleSearchMillis;
        for(int i=0; i<strip.numPixels(); i++) {
          if(i == bleSearchLedI){
            strip.setPixelColor(i, strip.Color(0, 0, 255));
          } else {
            strip.setPixelColor(i, strip.Color(0, 0, 0));
          }
        }
        bleSearchLedI++;
        if(bleSearchLedI >= strip.numPixels()) {
          bleSearchLedI = 0;
        }
      }
      break;
    case 2:
      for(int i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(255, 255, 255));
      }
      break;
    case 3:
      for(int i=0; i<strip.numPixels(); i++) {
        if(i >= strip.numPixels() / 2) {
          strip.setPixelColor(i, strip.Color(255, 255, 255));
        } else {
          strip.setPixelColor(i, strip.Color(0,0,0));
        }
      }
      break;
    case 4:
      for(int i=0; i<strip.numPixels(); i++) {
        if(i <= strip.numPixels() / 2) {
          strip.setPixelColor(i, strip.Color(255, 255, 255));
        } else {
          strip.setPixelColor(i, strip.Color(0, 0, 0));
        }
      }
      break;
    case 5:
      for(int i=0; i<strip.numPixels(); i++) {
        if(i % 2 == 0) {
          strip.setPixelColor(i, strip.Color(50, 50, 50));
        } else {
          strip.setPixelColor(i, strip.Color(0, 0, 0));
        }
      }
      break;
    case 6:
      for(int i=0; i<strip.numPixels(); i++) {
        if(i % 2 != 0) {
          strip.setPixelColor(i, strip.Color(50, 50, 50));
        } else {
          strip.setPixelColor(i, strip.Color(0, 0, 0));
        }
      }
      break;
    case 7:
      unsigned long currentSevenBlinkMillis = millis();
      if(currentSevenBlinkMillis - prevSevenBlinkMillis >= 50) {
        prevSevenBlinkMillis = currentSevenBlinkMillis;
        for(int i=0; i<strip.numPixels(); i++) {
          if(i % 2 != 0) {
            strip.setPixelColor(i, strip.Color(255, 0, 0));
          } else {
            strip.setPixelColor(i, strip.Color(0, 0, 0));
          }
        }
      }
      break;
    default:
      for(int i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
      }
  }
  strip.show();
}

void setRingMode(int mode) {
  currentRingMode = mode;
}
