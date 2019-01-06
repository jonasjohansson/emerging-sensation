/*
 * https://github.com/FastLED/FastLED/wiki/Pixel-reference
 * OctoWS2811: 2,14,7,8,6,20,21,5
 * Teensy: 0,1,23,22,19,18,17
 * A,B,C,D,E,F,G,H: 144
 */

#include<FastLED.h>

#define NUM_LEDS 144

CRGB leds[8][NUM_LEDS];
CRGB col = CRGB(255,255,255);

#define NUM_STRIPS 8
#define NUM_LEDS_PER_STRIP 144
#define NUM_LEDS_PER_SIDE 36
#define NUM_WINGS 4

byte wingA[NUM_WINGS][2] = { {2,1}, {3,0}, {4,0}, {5,1} };
byte wingB[NUM_WINGS][2] = { {6,1}, {7,0}, {0,0}, {0,1} };
byte wingC[NUM_WINGS][2] = { {2,3}, {3,2}, {4,2}, {5,3} };
byte wingD[NUM_WINGS][2] = { {6,3}, {7,2}, {0,2}, {1,3} };

byte wingE[NUM_WINGS][2] = { {0,1}, {1,0}, {2,0}, {3,1} };
byte wingF[NUM_WINGS][2] = { {4,1}, {5,0}, {6,0}, {7,1} };
byte wingG[NUM_WINGS][2] = { {0,3}, {1,2}, {2,2}, {3,3} };
byte wingH[NUM_WINGS][2] = { {4,3}, {5,2}, {6,2}, {7,3} };

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

  // 0x0, 1x1, 2x1, 3x0s
//  setColorRange(2,36,72,255,0,0);
//  setColorRange(3,0,36,255,0,0);
//  setColorRange(4,0,36,255,0,0);
//  setColorRange(5,36,72,255,0,0);
//  
//  setColorRange(2,72,72,255,0,0);
//  setColorRange(3,0,36,255,0,0);
//  setColorRange(4,0,36,255,0,0);
//  setColorRange(5,36,72,255,0,0);
//  
//  setColorRange(6,36,72,0,255,0);
//  setColorRange(7,0,36,0,255,0);
//  setColorRange(0,0,36,0,255,0);
//  setColorRange(1,36,72,0,255,0);
//  
//  
//  setColorRange(6,36,72,0,255,0);
//  setColorRange(7,0,36,0,255,0);
//  setColorRange(0,0,36,0,255,0);
//  setColorRange(1,36,72,0,255,0);

  colorise(wingA,255,0,0);
  colorise(wingB,0,255,0);
  colorise(wingC,0,0,255);
  colorise(wingD,255,128,0);
  colorise(wingE,0,255,128);
  colorise(wingF,128,0,255);
  colorise(wingG,255,0,128);
  colorise(wingH,128,255,0);
}

void colorise(byte wing[][2], byte r, byte g, byte b){
  for (uint8_t i = 0; i < NUM_WINGS; i++){
    byte x = wing[i][0];
    byte y = wing[i][1];
    uint8_t start = NUM_LEDS_PER_SIDE * y;
    uint8_t end = NUM_LEDS_PER_SIDE * (y + 1);
    for(uint8_t j = 0; j < 12; j++) {
      leds[x][start+j] = CRGB(r,g,b);
      leds[x][start+23-j] = CRGB(r,g,b);
      leds[x][start+24+j] = CRGB(r,g,b);
      FastLED.show();
    }
  }
}

void test(){
  for (int i = 0; i < 8; i++){
    for (int j = 0; j < NUM_LEDS; j++){
      leds[i][j].setRGB(255,255,255);
      FastLED.show();
    }
  }
}
