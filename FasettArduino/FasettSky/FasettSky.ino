#include<FastLED.h>

/*
 * 
 * Fasett Sky configuration
 * 4 x Proximity
 * 1500mm from center to edge
 * 
 */
 
#define NUM_STRIPS 8
#define NUM_LEDS_PER_STRIP 144
#define NUM_LEDS_PER_SIDE 36
#define NUM_WINGS 4

#define LED_PIN_A 2
#define LED_PIN_B 14
#define LED_PIN_C 7
#define LED_PIN_D 8
#define LED_PIN_E 6
#define LED_PIN_F 20
#define LED_PIN_G 21
#define LED_PIN_H 5

#define BRIGHTNESS 32

CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];

byte wingA[NUM_WINGS][2] = { {0,0}, {4,1}, {7,0}, {3,1} };
byte wingB[NUM_WINGS][2] = { {1,0}, {5,1}, {4,0}, {0,1} };
byte wingC[NUM_WINGS][2] = { {2,0}, {6,1}, {5,0}, {1,1} };
 byte wingD[NUM_WINGS][2] = { {3,0}, {7,1}, {6,0}, {2,1} };

void setup() {
  Serial.begin(115200);
  FastLED.setBrightness(BRIGHTNESS);
  //FastLED.addLeds<NEOPIXEL,LED_PIN_A>(leds[0], NUM_LEDS_PER_STRIP);
  //FastLED.addLeds<NEOPIXEL,LED_PIN_B>(leds[1], NUM_LEDS_PER_STRIP);
  //FastLED.addLeds<NEOPIXEL,LED_PIN_C>(leds[2], NUM_LEDS_PER_STRIP);
  //FastLED.addLeds<NEOPIXEL,LED_PIN_D>(leds[3], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL,LED_PIN_E>(leds[4], NUM_LEDS_PER_STRIP);
  //FastLED.addLeds<NEOPIXEL,LED_PIN_F>(leds[5], NUM_LEDS_PER_STRIP);
  //FastLED.addLeds<NEOPIXEL,LED_PIN_G>(leds[6], NUM_LEDS_PER_STRIP);
  //FastLED.addLeds<NEOPIXEL,LED_PIN_H>(leds[7], NUM_LEDS_PER_STRIP);
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
      leds[x][j] = CRGB(255,255,255);
    }
  }
  FastLED.show();
}
