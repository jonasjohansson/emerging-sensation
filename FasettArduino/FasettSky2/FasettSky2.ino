#include<FastLED.h>

/*
 * 
 * Fasett Sky configuration
 * 4 x Proximity
 * 1500mm from center to edge
 * 
 */
 
#define NUM_STRIPS 8
#define NUM_LEDS 144
#define NUM_LEDS_PER_SIDE 36
#define NUM_WINGS 4

#define BRIGHTNESS 32

CRGB leds[NUM_STRIPS*NUM_LEDS];

const byte wingA[NUM_WINGS][2] = { {0,0}, {4,1}, {7,0}, {3,1} };
const byte wingB[NUM_WINGS][2] = { {1,0}, {5,1}, {4,0}, {0,1} };
const byte wingC[NUM_WINGS][2] = { {2,0}, {6,1}, {5,0}, {1,1} };
const byte wingD[NUM_WINGS][2] = { {3,0}, {7,1}, {6,0}, {2,1} };

void setup() {
  Serial.begin(115200);
  FastLED.setBrightness(BRIGHTNESS);
  //FastLED.addLeds<WS2812,2>(leds, NUM_LEDS);
  //FastLED.addLeds<WS2812,14>(leds, NUM_LEDS);
  //FastLED.addLeds<WS2812,7>(leds, NUM_LEDS);
  //FastLED.addLeds<WS2812,8>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812,6>(leds, NUM_LEDS);
  //FastLED.addLeds<WS2812,20>(leds, NUM_LEDS);
  //FastLED.addLeds<WS2812,21>(leds, NUM_LEDS);
  //FastLED.addLeds<WS2812,5>(leds, NUM_LEDS);
}

void loop(){
  colorise(wingA);
}

void colorise(byte wing[][2]){
  for (uint8_t i = 0; i < NUM_WINGS; i++){
    byte x = wing[i][0];
    byte y = wing[i][1];
    uint8_t start = NUM_LEDS_PER_SIDE * y;
    uint8_t end = NUM_LEDS_PER_SIDE * (y + 1);
    for (uint8_t j = start; j < end; j++){
      FastLED[x][j] = CRGB(255,255,255);
    }
  }
  FastLED.show();
}
