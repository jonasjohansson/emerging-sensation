/*
 * https://github.com/FastLED/FastLED/wiki/Pixel-reference
 * OctoWS2811: 2,14,7,8,6,20,21,5
 * Teensy: 0,1,23,22,19,18,17
 * A,B,C,D,E,F,G,H: 144
 */

#include<FastLED.h>

#define SMOOTHSTEP(x) ((x) * (x) * (3 - 2 * (x)))
#define N 10.0
#define NUM_LEDS 144

CRGB leds[8][NUM_LEDS];

uint8_t gHue = 0; 

float val,oldVal,newVal;

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
  
  for (int i = 0; i < 8; i++){
    fill_rainbow( leds[i], NUM_LEDS, gHue, i);
  }

  newVal = analogRead(19);
  //newVal = smooth(newVal);

  for (byte i = 0; i < N; i++) {
    float v = i / N;
    v = SMOOTHSTEP(v);
    val = (oldVal * v) + (newVal * (1 - v));
  }

  byte a = map(val,200,500,255,32);
  a = constrain(a,32,255);

  //Serial.println(val);

  a = gammaCorrect(a);

  setColorRange(1,0,36,a,a,a);
  setColorRange(2,36,72,a,a,a);
  setColorRange(3,36,72,a,a,a);
  setColorRange(4,0,36,a,a,a);
  
  oldVal = val;

  EVERY_N_MILLISECONDS(20) { gHue++; }
  
  FastLED.show();
}
