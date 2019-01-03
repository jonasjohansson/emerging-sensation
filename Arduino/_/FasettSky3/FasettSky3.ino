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
#define DEBUG

#define BRIGHTNESS 32

CRGB leds[NUM_STRIPS][NUM_LEDS];

static byte wingA[NUM_WINGS][2] = { {0,0}, {0,1}, {6,0}, {6,1} }; // x, y
static byte wingB[NUM_WINGS][2] = { {1,1}, {1,2}, {0,1}, {0,2} };
static byte wingC[NUM_WINGS][2] = { {2,0}, {2,1}, {1,0}, {1,1} };
static byte wingD[NUM_WINGS][2] = { {3,1}, {3,2}, {2,1}, {2,2} };
static byte wingE[NUM_WINGS][2] = { {4,0}, {4,1}, {3,0}, {3,1} };
static byte wingF[NUM_WINGS][2] = { {5,1}, {5,2}, {4,1}, {4,2} };
static byte wingG[NUM_WINGS][2] = { {6,0}, {6,1}, {5,0}, {5,1} };
static byte wingH[NUM_WINGS][2] = { {7,1}, {7,2}, {6,1}, {6,2} };

int sensors[NUM_SENSORS][4] = {
  {17,0,100,200}, // pin, value, min, max
  {18,0,100,200},
  {19,0,100,200},
  {22,0,100,200} };

void setup() {
  #ifdef DEBUG
    Serial.begin(115200);
  #endif
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.addLeds<NEOPIXEL,2>(leds[0], NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,14>(leds[1], NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,7>(leds[2], NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,8>(leds[3], NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,6>(leds[4], NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,20>(leds[5], NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,21>(leds[6], NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,5>(leds[7], NUM_LEDS);
  resetLights();
}

void loop(){
  //readSensors();
  colorise(wingG,255,0,0);
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
    #ifdef DEBUG
      Serial.print("Sensor (");
      Serial.print(i);
      Serial.print("): ");
      Serial.println(val);
    #endif
  }
}

void colorise(byte wing[][2], byte r, byte g, byte b){
  for (byte i = 0; i < NUM_WINGS; i++){
    byte x = wing[i][0];
    byte y = wing[i][1];
    int _start = NUM_LEDS_PER_SIDE * y;
    int _end = NUM_LEDS_PER_SIDE * (y + 1);
    for (uint8_t j = _start; j < _end; j++){
      #ifdef DEBUG
        Serial.print("X (Wing): ");
        Serial.print(x);
        Serial.print("  ");
        Serial.print("Y: ");
        Serial.print(y);
        Serial.print("  ");
        Serial.print("LED: ");
        Serial.println(j);
      #endif
      leds[x][j] = CRGB(r,g,b);
    }
  }
  FastLED.show();
}

void resetLights(){
  FastLED.clear();
  FastLED.show();
}
