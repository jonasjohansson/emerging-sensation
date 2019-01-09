/*
 * https://github.com/FastLED/FastLED/wiki/Pixel-reference
 * A: 222 (6x25 + 1x27 + 3x15)
 * B: 213 (7x24 + 3x15)
 * C: 300 (10x24 + 4x15)
 */

#include<FastLED.h>
#include "Particle.h"

#define NUM_PARTICLES 200

CRGB leds[3][300];

uint8_t gHue = 0;

int a1,a2,a3,a1l,a2l,a3l;
int b1,b2,b3,b1l,b2l,b3l;
int c1,c2,c3,c4,c1l,c2l,c3l,c4l;

Particle particles[NUM_PARTICLES];

void setup(){
  FastLED.setBrightness(192);
  FastLED.addLeds<NEOPIXEL,0>(leds[0],222);
  FastLED.addLeds<NEOPIXEL,2>(leds[1],213);
  FastLED.addLeds<NEOPIXEL,4>(leds[2],300);
  FastLED.clear();
  FastLED.show();
  for (int i = 0; i < NUM_PARTICLES; i++){
    Particle p;
    p.init(0,0);
    particles[i] = p;
  }
}

void loop(){

  readSimple(6,c1,c1l);
  readSimple(7,c2,c2l);
  readSimple(8,c3,c3l);
  readSimple(9,c4,c4l);

  byte r = c1*255;
  byte g = c2*255;
  byte b = c3*255;

  if (c1){
    gHue = 0;
  }
  if (c2){
    gHue = 64;
  }
  if (c3){
    gHue = 128;
  }
  if (c4){
    gHue = 192;
  }
  
  //setColorRange(1,0,213,255,255,255);
  //setColorRange(2,0,150,255,255,255);
  //setColorRange(2,150,300,255,255,255);
  fill_rainbow( leds[0], 222, gHue, 0);
  fill_rainbow( leds[1], 213, gHue, 0);
  fill_rainbow( leds[2], 300, gHue, 0);
  FastLED.show();
  EVERY_N_MILLISECONDS(20) { gHue++; }
}
