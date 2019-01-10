/*
 * https://github.com/FastLED/FastLED/wiki/Pixel-reference
 */

#include<FastLED.h>

#define NUM_SENSORS 5
#define NUM_STRIPS 26
#define NUM_LEDS 289

CRGB leds[NUM_LEDS];

int a,b,c,d,e;
int al,bl,cl,dl,el;

int lights[NUM_STRIPS][3] = {
  { 0, 9, 1 },    // 0
  { 9, 6, 1 },    // 1
  { 15, 16, 1 },  // 2 large ball 1 outside
  { 31, 31, 2 },  // 3 large ball 1 inside
  { 62, 8, 1 },   // 4
  { 70, 9, 1 },   // 5
  { 79, 20, 2 },  // 6 small ball 2 inside
  { 99, 20, 2 },  // 7 small ball 3 inside
  { 119, 9, 1 },  // 8
  { 128, 7, 1 },  // 9
  { 135, 6, 1 },  // 10
  { 141, 8, 1 },  // 11
  { 149, 7, 1 },  // 12
  { 156, 9, 1 },  // 13
  { 165, 5, 1 },  // 14
  { 170, 5, 1 },  // 15
  { 175, 8, 1 },  // 16
  { 183, 6, 1 },  // 17
  { 189, 5, 1 },  // 18
  { 194, 12, 1 }, // 19 large ball 4 outside
  { 206, 23, 2 }, // 20 large ball 4 inside
  { 229, 8, 1 },  // 21
  { 237, 27, 2 }, // 22 large ball 5 inside
  { 264, 14, 1 }, // 23 large ball 5 outside
  { 278, 6, 1 },  // 24 
  { 284, 5, 1 },  // 25
};

void setup(){
  FastLED.addLeds<NEOPIXEL,7>(leds,NUM_LEDS);
  FastLED.clear();
  FastLED.show();
}

void loop(){

  readSimple(0,a,al);
  readSimple(1,b,bl);
  readSimple(2,c,cl);
  readSimple(3,d,dl);
  readSimple(4,e,el);

  delay(10);
}
