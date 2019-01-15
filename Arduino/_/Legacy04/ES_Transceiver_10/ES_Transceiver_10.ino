/*
 * https://github.com/FastLED/FastLED/wiki/Pixel-reference
 * OctoWS2811: 2,14,7,8,6,20,21,5
 * Teensy: 0,1,23,22,19,18,17
*/

#if defined(TEENSYDUINO)
  #define BAUD 115200
#else
  #define BAUD 9600
#endif

#include<FastLED.h>

#define NUM_LEDS 144
#define BRIGHTNESS 255
#define DEBUG true

CRGB leds[4][NUM_LEDS];

int a1, a2, a3, a4, b1, b2, b3, c1, c2, c3;
float a1x, a2x, a3x, a4x, b1x, b2x, b3x, c1x, c2x, c3x;
float a1l, a2l, a3l, a4l, b1l, b2l, b3l, c1l, c2l, c3l;

void setup(){
  Serial.begin(BAUD);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.addLeds<NEOPIXEL,6>(leds[0],NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,20>(leds[1],NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,21>(leds[2],NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,5>(leds[3],NUM_LEDS);
  FastLED.clear();
  FastLED.show();
  
  setColorRange(0,0,NUM_LEDS,255,0,0);
  setColorRange(1,0,NUM_LEDS,0,255,0);
  setColorRange(2,0,NUM_LEDS,0,0,255);
  setColorRange(3,0,NUM_LEDS,0,255,255);
}

void loop(){
  if (DEBUG) return;
  
  readSimple(0, a1x, a1l);
  readSimple(1, a2x, a2l);
  readSimple(2, a3x, a3l);
  readSimple(3, a4x, a4l);
  readSimple(4, b1x, b1l);
  readSimple(5, b2x, b2l);
  readSimple(6, b3x, b3l);
  readSimple(7, c1x, c1l);
  readSimple(8, c2x, c2l);
  readSimple(9, c3x, c3l);

  a1 = map((int)a1x,0,1,0,255);
  a2 = map((int)a2x,0,1,0,255);
  a3 = map((int)a3x,0,1,0,255);
  a4 = map((int)a4x,0,1,0,255);
  
  setColorRange(0,0,NUM_LEDS,a1,a2,a3);
  
  b1 = map((int)b1x,0,1,0,255);
  b2 = map((int)b2x,0,1,0,255);
  b3 = map((int)b3x,0,1,0,255);
  
  setColorRange(0,0,NUM_LEDS,b1,b2,b3);
  
  c1 = map((int)c1x,0,1,0,255);
  c2 = map((int)c2x,0,1,0,255);
  c3 = map((int)c3x,0,1,0,255);
  
  setColorRange(0,0,NUM_LEDS,c1,c2,c3);
  
  delay(10);
}

void readAdvancedAll(){
  readAdvanced(
}
