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
byte wingB[NUM_WINGS][2] = { {4,1}, {5,0}, {6,0}, {7,1} };
byte wingC[NUM_WINGS][2] = { {6,1}, {7,0}, {0,0}, {0,1} };
byte wingD[NUM_WINGS][2] = { {0,1}, {1,0}, {2,0}, {3,1} };

byte wingE[NUM_WINGS][2] = { {2,3}, {3,2}, {4,2}, {5,3} };
byte wingF[NUM_WINGS][2] = { {4,3}, {5,2}, {6,2}, {7,3} };
byte wingG[NUM_WINGS][2] = { {6,3}, {7,2}, {0,2}, {1,3} };
byte wingH[NUM_WINGS][2] = { {0,3}, {1,2}, {2,2}, {3,3} };

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
  colorise(wingB,CRGB::Orange);
  colorise(wingC,CRGB::Yellow);
  colorise(wingD,CRGB::Green);
  colorise(wingE,CRGB::Cyan);
  colorise(wingF,CRGB::Blue);
  colorise(wingG,CRGB::Violet);
  colorise(wingH,CRGB::White);
}

void colorise(byte wing[][2], CRGB c){
  for (uint8_t i = 0; i < NUM_WINGS; i++){
    byte x = wing[i][0];
    byte y = wing[i][1];
    uint8_t start = NUM_LEDS_PER_SIDE * y;
    uint8_t end = NUM_LEDS_PER_SIDE * (y + 1);
    for(uint8_t j = 0; j < 12; j++) {
      leds[x][start+j] = c;
      leds[x][start+23-j] = c;
      leds[x][start+24+j] = c;
    }
  }
  FastLED.show();
}