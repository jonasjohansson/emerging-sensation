/*
 * https://github.com/FastLED/FastLED/wiki/Pixel-reference
 * A: 222 (6x25 + 1x27 + 3x15)
 * B: 213 (7x24 + 3x15)
 * C: 300 (10x24 + 4x15)
 */

#include<FastLED.h>

CRGB leds[3][300];

int a1,a2,a3,a1l,a2l,a3l;
int b1,b2,b3,b1l,b2l,b3l;
int c1,c2,c3,c4,c1l,c2l,c3l,c4l;

void setup(){
  FastLED.setBrightness(128);
  FastLED.addLeds<NEOPIXEL,0>(leds[0],222);
  FastLED.addLeds<NEOPIXEL,1>(leds[1],213);
  FastLED.addLeds<NEOPIXEL,2>(leds[2],300);
  FastLED.clear();
  FastLED.show();
}

void loop(){
  readSimple(0,a1,a1l);
  readSimple(1,a2,a2l);
  readSimple(2,a3,a3l);
  readSimple(3,b1,b1l);
  readSimple(4,b2,b2l);
  readSimple(5,b3,b3l);
  readSimple(6,c1,c1l);
  readSimple(7,c2,c2l);
  readSimple(8,c3,c3l);
  readSimple(9,c4,c4l);

  if (c4 == 1) {
    c1 *= 0.5;
    c2 *= 0.5;
    c3 *= 0.5;
  }

  setColorRange(0,0,222,a1*255,a2*255,a3*255);
  setColorRange(1,0,213,b1*255,b2*255,b3*255);
  setColorRange(2,0,300,c1*255,c2*255,c3*255);
  
  FastLED.show();
  
  delay(10);
}
