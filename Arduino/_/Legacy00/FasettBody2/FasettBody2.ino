/*
 * 
 * Fasett Body
 * 
 */

#include<FastLED.h>

#define DIGITAL_PINS 12
#define ANALOG_PINS 5

byte analogValues[ANALOG_PINS];
byte lastAnalogValues[ANALOG_PINS];

byte digitalValues[DIGITAL_PINS];
byte lastDigitalValues[DIGITAL_PINS];
 
#define BRIGHTNESS 32

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL,LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  initDigitalPins(DIGITAL_PINS);
  resetLights();
}

void loop(){
}
