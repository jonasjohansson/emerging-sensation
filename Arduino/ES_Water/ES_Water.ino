/*
 * https://github.com/FastLED/FastLED/wiki/Pixel-reference
 * A: 300
 * B: 318
 * C: 315 
 */

#include<FastLED.h>

CRGB leds[3][318];

uint8_t gHue = 0; 

void setup(){
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL,0>(leds[0],300);
  FastLED.addLeds<NEOPIXEL,1>(leds[1],318);
  FastLED.addLeds<NEOPIXEL,2>(leds[2],315);
  FastLED.clear();
}

void loop(){
  //setColorRange(0,0,300,255,0,0);
  //setColorRange(1,0,318,0,255,0);
  //setColorRange(2,0,315,0,0,255);
  fill_rainbow( leds[0], 300, gHue, 0);
  fill_rainbow( leds[1], 318, gHue, 1);
  fill_rainbow( leds[2], 315, gHue, 2);
  FastLED.show();
  EVERY_N_MILLISECONDS(20) { gHue++; }
}
