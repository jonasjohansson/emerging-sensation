/*
 * 
 * https://github.com/FastLED/FastLED/wiki/Basic-usage
 * OctoWS2811: 2,14,7,8,6,20,21,5
 */
 
#include<FastLED.h>

#define SENSOR_PINS 12

#define DATA_PIN 14
#define NUM_LEDS 21
#define BRIGHTNESS 96

byte touches[SENSOR_PINS];
byte lastTouches[SENSOR_PINS];

CRGB leds[NUM_LEDS];

void setup(){
  Serial.begin(115200);

  delay(1000);
  
  FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
  
  for (uint8_t i = 0; i < SENSOR_PINS; i++){
    pinMode(i, INPUT);
    touches[i] = 0;
    lastTouches[i] = 0;
  }
}

void loop() {
  for (uint8_t i = 0; i < SENSOR_PINS; i++){
    touches[i] = digitalRead(i);
    if (touches[i] != lastTouches[i]){
      lastTouches[i] = touches[i];
      Serial.print(i);
      Serial.print(' ');
      Serial.println(touches[i]);
    }
  }
  if (touches[5] == 1){
    turnOn();
  } else {
    turnOff();
  }
}

void turnOn() {
  for (int i = 0; i < NUM_LEDS; i++) {   
    leds[i] = CRGB::Blue;
    FastLED.show();
  }
}

void turnOff() {
  FastLED.clear();
  FastLED.show();
}

