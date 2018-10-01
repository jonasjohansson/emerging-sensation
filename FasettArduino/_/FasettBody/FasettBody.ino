/*
 * Fasett Body configuration
 * 
 */
#include<FastLED.h>

#define DIGITAL_PINS 12
#define ANALOG_PINS 5

#define LED_PIN 6
#define NUM_LEDS 300
#define BRIGHTNESS 128

CRGB leds[NUM_LEDS];

byte analogValues[ANALOG_PINS];
byte lastAnalogValues[ANALOG_PINS];

byte digitalValues[DIGITAL_PINS];
byte lastDigitalValues[DIGITAL_PINS];

void setup(){
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL,LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  initDigitalPins(DIGITAL_PINS);
  turnOff();
}

void loop() {
  turnOn();
  readAnalogPins(ANALOG_PINS);
  readDigitalPins(DIGITAL_PINS);
}

void initDigitalPins(uint8_t pins){
	for (uint8_t i = 0; i < pins; i++){
    if (i == LED_PIN) return;
		pinMode(i, INPUT);
		//digitalValues[i] = 0;
		//lastDigitalValues[i] = 0;
	}
}

void readAnalogPins(uint8_t pins){
  for (uint8_t i = 0; i < pins; i++){
		analogValues[i] = analogRead(i);
		if (analogValues[i] != lastAnalogValues[i]){
			lastAnalogValues[i] = analogValues[i];
			Serial.print('a');
			Serial.print(i);
			Serial.print(' ');
			Serial.println(analogValues[i]);
		}
	}
}

void readDigitalPins(uint8_t pins){
  for (uint8_t i = 0; i < pins; i++){
    if (i == LED_PIN) return;
		digitalValues[i] = digitalRead(i);
		if (digitalValues[i] != lastDigitalValues[i]){
			lastDigitalValues[i] = digitalValues[i];
			Serial.print('d');
			Serial.print(i);
			Serial.print(' ');
			Serial.println(digitalValues[i]);
		}
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
