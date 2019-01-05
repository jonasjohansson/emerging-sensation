/*
 * https://github.com/FastLED/FastLED/wiki/Pixel-reference
 * OctoWS2811: 2,14,7,8,6,20,21,5
 * Teensy: 0,1,23,22,19,18,17
 * A,B,C,D,E,F,G,H: 144
 */

#include<FastLED.h>

#define NUM_LEDS 144

CRGB leds[8][NUM_LEDS];

uint8_t gHue = 0; 

void setup(){
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL,6>(leds[0],NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,20>(leds[1],NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,21>(leds[2],NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,5>(leds[3],NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,2>(leds[4],NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,14>(leds[5],NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,7>(leds[6],NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,8>(leds[7],NUM_LEDS);
  FastLED.clear();
}

void loop(){
  for (int i = 0; i < 8; i++){
    fill_rainbow( leds[i], NUM_LEDS, gHue, i);
  }
  FastLED.show();
  EVERY_N_MILLISECONDS(20) { gHue++; }
}
