/*
 * 
 * Fasett Body configuration
 * 
 */
 
#include<FastLED.h>

#define NUM_LEDS 289
#define NUM_PARTS 26
#define LED_PIN 6
#define BRIGHTNESS 128

CRGB leds[NUM_LEDS];

int lights[NUM_PARTS][3] = {
  { 0, 9, 1 },
  { 9, 6, 1 },
  { 15, 16, 1 }, // large ball 1 outside
  { 31, 31, 2 }, // large ball 1 inside
  { 62, 8, 1 },
  { 70, 9, 1 },
  { 79, 20, 2 }, // small ball 2 inside
  { 99, 20, 2 }, // small ball 3 inside
  { 119, 9, 1 },
  { 128, 7, 1 },
  { 135, 6, 1 },
  { 141, 8, 1 },
  { 149, 7, 1 },
  { 156, 9, 1 },
  { 165, 5, 1 },
  { 170, 5, 1 },
  { 175, 8, 1 },
  { 183, 6, 1 },
  { 189, 5, 1 },
  { 194, 12, 1 },
  { 206, 23, 2 }, // large ball 4 outside
  { 229, 8, 1 }, // large ball 4 inside
  { 237, 27, 1 },
  { 264, 14, 1 }, // large ball 5 inside
  { 278, 6, 1 }, // large ball 5 outside
  { 284, 5, 1 }
};

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL,LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  resetLights();
  setColorAll(0,255,0);
  setColor(2,255,0,0);
  setColor(3,0,0,255);
}

void loop(){
}
