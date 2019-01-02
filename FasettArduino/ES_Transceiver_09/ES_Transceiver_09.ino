/*
 * https://github.com/FastLED/FastLED/wiki/Pixel-reference
 * 
 */

#include<FastLED.h>

#define NUM_LEDS 200
#define LED_PIN 6
#define BRIGHTNESS 255

CRGB leds[NUM_LEDS];

int a, b;
float ax, bx, al, bl;

void setup(){
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL, LED_PIN >(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );
  FastLED.clear();
  FastLED.show();
}

void loop(){
  //readSimple(23, ax, al);
  readAdvanced(23, bx, bl, 100, 300);

  b = (int)bx;
  
  setColorRange(b,0,0,0,NUM_LEDS);
  
  delay(1);
}
