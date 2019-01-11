/*
   https://github.com/FastLED/FastLED/wiki/Pixel-reference
   A: 222 (6x25 + 1x27 + 3x15)
   B: 213 (7x24 + 3x15)
   C: 300 (10x24 + 4x15)
*/

#include<FastLED.h>
#include "global.h"

int b1, b2, b3, b1l, b2l, b3l;
CRGB leds[3][300];

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL, 0>(leds[0], 222);
  FastLED.addLeds<NEOPIXEL, 1>(leds[1], 213);
  FastLED.addLeds<NEOPIXEL, 2>(leds[2], 300);
  FastLED.clear();
}

void loop() {
  waterB();
  readSimple(3, b1, b1l);
  readSimple(4, b2, b2l);
  readSimple(5, b3, b3l);
}

void waterB(){
  
  for (byte i = 0; i < WB_NUM_STEMS; i++){
    int index = WB_STEMS[i];
    int start = WB_MAP[index][0];
    int end = start+WB_MAP[index][1];
    for (byte j = start; j < end; j++){
      leds[1][j] = CRGB::Red;
    }
  }
  
  for (byte i = 0; i < WB_NUM_BRANCHES; i++){
    int index = WB_BRANCHES[i];
    int start = WB_MAP[index][0];
    int end = start+WB_MAP[index][1];
    for (byte j = start; j < end; j++){
      leds[1][j] = CRGB::Green;
    }
  }
  
  for (byte i = 0; i < WB_NUM_BUDS; i++){
    int index = WB_BUDS[i];
    int start = WB_MAP[index][0];
    int end = start+WB_MAP[index][1];
    for (byte j = start; j < end; j++){
      leds[1][j] = CRGB::Blue;
    }
  }
  
  FastLED.show();
  
}
