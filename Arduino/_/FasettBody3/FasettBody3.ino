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
 
void setup() {
  Serial.begin(115200);
  initDigitalPins(DIGITAL_PINS);
}

void loop(){
  readAnalogPins(ANALOG_PINS);
  readDigitalPins(DIGITAL_PINS);
}
