/*
 * 
 * Fasett Body configuration
 * 
 */
 
#include<FastLED.h>
//#include <Adafruit_NeoPixel.h>

#define NUM_LEDS 289
#define NUM_PARTS 26
#define LED_PIN 6
#define BRIGHTNESS 32

CRGB leds[NUM_LEDS];
//Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

int lights[NUM_PARTS][3] = {
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
void setup() {
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL,LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  //setColorAll(0,0,0);
  setColor(2,255,0,0);
  setColor(3,0,0,255);
  setColor(6,255,0,0);
  setColor(7,255,0,0);
  setColor(19,255,0,0);
  setColor(20,0,0,255);
  setColor(22,0,255,0);
  setColor(23,255,0,0);
}

void loop(){
}
