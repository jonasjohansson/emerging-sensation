/*
 * https://github.com/FastLED/FastLED/wiki/Pixel-reference
 */

#include<FastLED.h>

#define NUM_LEDS 289

CRGB leds[1][NUM_LEDS];

uint8_t gHue = 0;

void setup(){
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL,5>(leds[0],NUM_LEDS);  
}

void loop(){
  int val = analogRead(0);
  
  Serial.println(val);
  
  if (val == 1023){
    gHue = 0;
  }
  
  fill_rainbow( leds[0], NUM_LEDS, gHue, 0);
  EVERY_N_MILLISECONDS(20) { gHue++; }

  FastLED.show();
}
