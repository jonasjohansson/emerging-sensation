/*
 * 
 * https://github.com/FastLED/FastLED/wiki/Basic-usage
 * 
 */

#include<FastLED.h>

#define DATA_PIN 13
#define NUM_LEDS 21
#define BRIGHTNESS 96

CRGB leds[NUM_LEDS];

void setup() {
  delay(1000);
  FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
}

void loop() {
  for (int i = 0; i < NUM_LEDS; i++) {   
    leds[i] = CRGB::Blue;
    FastLED.show();
  }
}

