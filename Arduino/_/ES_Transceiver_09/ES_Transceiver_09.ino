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

#define NUM_LEDS 213
#define BRIGHTNESS 255
#define DEBUG false

CRGB leds[2][NUM_LEDS];

int a, b, c, d, e, f;
float ax, bx, cx, dx, ex, fx;
float al, bl, cl, dl, el, fl;

void setup(){
  Serial.begin(BAUD);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.addLeds<NEOPIXEL,11>(leds[0],NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,12>(leds[1],NUM_LEDS);
  FastLED.clear();
  FastLED.show();
  setColorRange(255,0,0,0,NUM_LEDS,0);
  setColorRange(255,0,0,0,NUM_LEDS,1);
}

void loop(){
  if (DEBUG) return;
  
  readSimple(0, ax, al);
  readSimple(1, bx, bl);
  readSimple(2, cx, cl);
  readSimple(3, dx, dl);
  readSimple(4, ex, el);
  readSimple(5, fx, fl);
  //readAdvanced(23, cx, cl, 100, 300);

  a = (int)ax;
  a = map(a,0,1,0,255);
  
  b = (int)bx;
  b = map(b,0,1,0,255);
  
  c = (int)cx;
  c = map(c,0,1,0,255);

  setColorRange(a,b,c,0,NUM_LEDS,0);

  d = (int)dx;
  d = map(d,0,1,0,255);
  
  e = (int)ex;
  e = map(e,0,1,0,255);
  
  f = (int)fx;
  f = map(f,0,1,0,255);
  
  setColorRange(d,e,0,0,NUM_LEDS,1);
  
  delay(10);
}
