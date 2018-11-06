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
#define NUM_SENSORS 4
#define OUT_MIN 0
#define OUT_MAX 100

#define BRIGHTNESS 32

CRGB leds[NUM_STRIPS*NUM_LEDS];

const byte wingA[NUM_WINGS][2] = { {0,0}, {0,1}, {6,0}, {6,1} }; // x, y
const byte wingB[NUM_WINGS][2] = { {1,1}, {1,2}, {0,1}, {0,2} };
const byte wingC[NUM_WINGS][2] = { {2,0}, {2,1}, {1,0}, {1,1} };
const byte wingD[NUM_WINGS][2] = { {3,1}, {3,2}, {2,1}, {2,2} };
const byte wingE[NUM_WINGS][2] = { {4,0}, {4,1}, {3,0}, {3,1} };
const byte wingF[NUM_WINGS][2] = { {5,1}, {5,2}, {4,1}, {4,2} };
const byte wingG[NUM_WINGS][2] = { {6,0}, {6,1}, {5,0}, {5,1} };
const byte wingH[NUM_WINGS][2] = { {7,1}, {7,2}, {6,1}, {6,2} };

int sensors[NUM_SENSORS][4] = {
  {0,0,100,200}, // pin, value, min, max
  {1,0,100,200},
  {2,0,100,200},
  {3,0,100,200} };

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
  readSensors();
  colorise(wingA);
}
