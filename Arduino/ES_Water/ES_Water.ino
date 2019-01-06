/*
 * https://github.com/FastLED/FastLED/wiki/Pixel-reference
 * A: 222 (6x25 + 1x27 + 3x15)
 * B: 213 (7x24 + 3x15)
 * C: 300 (10x24 + 4x15)
 */

#include<FastLED.h>

CRGB leds[3][300];

uint8_t gHue = 0;

void setup(){
  //Serial.begin(115200);
  FastLED.setBrightness(192);
  FastLED.addLeds<NEOPIXEL,0>(leds[0],222);
  FastLED.addLeds<NEOPIXEL,2>(leds[1],213);
  FastLED.addLeds<NEOPIXEL,4>(leds[2],300);
  FastLED.clear();
  FastLED.show();
}

void loop(){
  //setColorRange(0,0,222,255,255,255);
  //setColorRange(1,0,213,255,255,255);
  //setColorRange(2,0,150,255,255,255);
  //setColorRange(2,150,300,255,255,255);
  fill_rainbow( leds[0], 222, gHue, 0);
  fill_rainbow( leds[1], 213, gHue, 1);
  fill_rainbow( leds[2], 300, gHue, 2);
  FastLED.show();
  EVERY_N_MILLISECONDS(20) { gHue++; }
}
