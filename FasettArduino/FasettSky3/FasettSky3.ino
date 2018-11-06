#include<FastLED.h>

/*
 * 
 * Fasett Sky
 * 4 x Distance
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

static byte wingA[NUM_WINGS][2] = { {0,0}, {0,1}, {6,0}, {6,1} }; // x, y
static byte wingB[NUM_WINGS][2] = { {1,1}, {1,2}, {0,1}, {0,2} };
static byte wingC[NUM_WINGS][2] = { {2,0}, {2,1}, {1,0}, {1,1} };
static byte wingD[NUM_WINGS][2] = { {3,1}, {3,2}, {2,1}, {2,2} };
static byte wingE[NUM_WINGS][2] = { {4,0}, {4,1}, {3,0}, {3,1} };
static byte wingF[NUM_WINGS][2] = { {5,1}, {5,2}, {4,1}, {4,2} };
static byte wingG[NUM_WINGS][2] = { {6,0}, {6,1}, {5,0}, {5,1} };
static byte wingH[NUM_WINGS][2] = { {7,1}, {7,2}, {6,1}, {6,2} };

int sensors[NUM_SENSORS][4] = {
  {0,0,100,200}, // pin, value, min, max
  {1,0,100,200},
  {2,0,100,200},
  {3,0,100,200} };

void setup() {
  Serial.begin(115200);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.addLeds<WS2812,2>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812,14>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812,7>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812,8>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812,6>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812,20>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812,21>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812,5>(leds, NUM_LEDS);
}

void loop(){
  readSensors();
  colorise(wingA);
}

void readSensors(){
  for (byte i = 0; i < NUM_SENSORS; i++){
    byte pin = sensors[i][0];
    int in_min = sensors[i][2];
    int in_max = sensors[i][3];
    int val = analogRead(pin);
    val = constrain(val,in_min,in_max);
    val = map(val,in_min,in_max,OUT_MIN,OUT_MAX);
    sensors[i][1] = val;
  }
}

void colorise(byte wing[][2]){
  for (byte i = 0; i < NUM_WINGS; i++){
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
