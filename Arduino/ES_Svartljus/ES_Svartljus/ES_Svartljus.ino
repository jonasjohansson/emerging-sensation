#include <FastLED.h>

#define NUM_LEDS_SHORT 100
#define NUM_LEDS_LONG 200
#define NUM_LEDS 300

CRGB leds[NUM_LEDS];

int svartMap[300];

void setup() {
  FastLED.setBrightness(192);
  FastLED.addLeds<NEOPIXEL, 13>(leds, 0, NUM_LEDS_SHORT);
  FastLED.addLeds<NEOPIXEL, 12>(leds, 0, NUM_LEDS_LONG);
  FastLED.clear();
  FastLED.show();
  int p = 0;
  for (int i = NUM_LEDS_SHORT; i > 0; i--) {
    svartMap[p] = i;
    p++;
  }
  for (int i = 0; i < NUM_LEDS_LONG; i++) {
    svartMap[p] = i;
    p++;
  }
}

int counter = 0;

void loop() {

  leds[counter] = CRGB::White;
  FastLED.show();
  FastLED.delay(10);
  leds[counter] = CRGB::Black;
  
  EVERY_N_MILLISECONDS(10){
    counter++; 
    if (counter < NUM_LEDS){
      counter++;
    } else {
      counter = 0;
    }
  }
}
