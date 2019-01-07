/*
 * https://github.com/FastLED/FastLED/wiki/Pixel-reference
 * OctoWS2811: 2,14,7,8,6,20,21,5
 * Teensy: 0,1,23,22,19,18,17
 * A,B,C,D,E,F,G,H: 144
 */

#include<FastLED.h>

#define NUM_STRIPS 8
#define NUM_LEDS 144
#define NUM_LEDS_PER_SIDE 36
#define NUM_WINGS 4

CRGB leds[NUM_STRIPS][NUM_LEDS];

byte wingA[NUM_WINGS][2] = { {1,0}, {0,1}, {3,1}, {2,0} };
byte wingB[NUM_WINGS][2] = { {3,0}, {2,1}, {5,1}, {4,0} };
byte wingC[NUM_WINGS][2] = { {5,0}, {4,1}, {7,1}, {6,0} };
byte wingD[NUM_WINGS][2] = { {7,0}, {6,1}, {1,1}, {0,0} };
byte wingE[NUM_WINGS][2] = { {3,2}, {6,3}, {5,3}, {0,2} };
byte wingF[NUM_WINGS][2] = { {5,2}, {0,3}, {7,3}, {2,2} };
byte wingG[NUM_WINGS][2] = { {7,2}, {2,3}, {1,3}, {4,2} };
byte wingH[NUM_WINGS][2] = { {1,2}, {4,3}, {3,3}, {6,2} };

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
  colorise(wingA,CRGB::Red);
  colorise(wingB,CRGB::Green);
  colorise(wingC,CRGB::Blue);
  colorise(wingD,CRGB::Yellow);
  colorise(wingE,CRGB::Red);
  colorise(wingF,CRGB::Green);
  colorise(wingG,CRGB::Blue);
  colorise(wingH,CRGB::Yellow);
}
