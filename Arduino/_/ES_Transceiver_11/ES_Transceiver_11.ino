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
#define DEBUG false

CRGB leds[4][NUM_LEDS];

float a1, a2, a3, a4, b1, b2, b3, c1, c2, c3;
float a1x, a2x, a3x, a4x, b1x, b2x, b3x, c1x, c2x, c3x;
float a1l, a2l, a3l, a4l, b1l, b2l, b3l, c1l, c2l, c3l;

void setup(){
  Serial.begin(BAUD);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
}

void loop(){
  if (DEBUG) return;
  float test = readAdvanced(17,a1,0,1023);
  Serial.println(test);
}
