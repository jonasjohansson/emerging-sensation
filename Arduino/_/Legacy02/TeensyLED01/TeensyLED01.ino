#include<OctoWS2811.h>
#include<FastLED.h>

#define USE_OCTOWS2811

FASTLED_USING_NAMESPACE

#define DATA_PIN    3
#define LED_TYPE    WS2811s
#define COLOR_ORDER GRB
#define NUM_LEDS_PER_STRIP 13
#define NUM_STRIPS 8

int NUM_LEDS = NUM_STRIPS * NUM_LEDS_PER_STRIP;

#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120

void setup() {
  FastLED.setBrightness(BRIGHTNESS);
}

void loop(){
  FastLED.show();  
  FastLED.delay(1000/FRAMES_PER_SECOND); 
}
