#include<FastLED.h>

#define BRIGHTNESS 32

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL,LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  resetLights();
  //setColorAll(128,128,128);
  //setColor(2,255,0,0);
  //setColor(3,0,0,255);
  //setColor(6,255,0,0);
  //setColor(7,255,0,0);
  //setColor(19,255,0,0);
  //setColor(20,0,0,255);
  //setColor(22,0,255,0);
  //setColor(23,255,0,0);
}

void loop(){
  for (uint8_t i = 0; i < NUM_PARTS; i++){
    blink(i,2,20);
  }
}
