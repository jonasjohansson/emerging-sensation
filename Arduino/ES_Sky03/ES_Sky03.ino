/*
   https://github.com/FastLED/FastLED/wiki/Pixel-reference
   OctoWS2811: 2,14,7,8,6,20,21,5
   Teensy: 0,1,23,22,19,18,17
   A,B,C,D,E,F,G,H: 144
*/

#include<FastLED.h>

#define NUM_SENSORS 4
#define NUM_STRIPS 8
#define NUM_LEDS 144
#define NUM_LEDS_PER_SIDE 36
#define NUM_WINGS 4

CRGB leds[NUM_STRIPS][NUM_LEDS];
CRGB col;
CRGBPalette16 skyPalette;

float speed;

DEFINE_GRADIENT_PALETTE(skyPalette1) {
  0,		0,  	0, 		0,
  32, 	192,  	64, 	192,
  64,  	192,  140, 	255,
  128,  92,  80, 	255,
  255,  192,  44, 	255
};

int skyMap[4][4][2][2] = {
  { // top
    { {6, 3}, {5, 3} }, 	// a
    { {0, 3}, {7, 3} }, 	// b
    { {2, 3}, {1, 3} }, 	// c
    { {4, 3}, {3, 3} } 	// d
  },
  {
    { {3, 2}, {0, 2} },
    { {5, 2}, {2, 2} },
    { {7, 2}, {4, 2} },
    { {1, 2}, {6, 2} }
  },
  {
    { {0, 1}, {3, 1} },
    { {2, 1}, {5, 1} },
    { {4, 1}, {7, 1} },
    { {6, 1}, {1, 1} }
  },
  {
    { {1, 0}, {2, 0} },
    { {3, 0}, {4, 0} },
    { {5, 0}, {6, 0} },
    { {7, 0}, {0, 0} }
  }
};

int skyMap2[4][8][36][2];
int skyMap3[8][4][36][2];

float pins[NUM_SENSORS] = {18, 22, 17, 19};
float sensor[NUM_SENSORS];
float sensorLast[NUM_SENSORS];
float sensorRaw[NUM_SENSORS];

void setup() {
  FastLED.addLeds<NEOPIXEL, 6>(leds[0], NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, 20>(leds[1], NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, 21>(leds[2], NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, 5>(leds[3], NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, 2>(leds[4], NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, 14>(leds[5], NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, 7>(leds[6], NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, 8>(leds[7], NUM_LEDS);
  FastLED.clear();
  FastLED.show();

  skyPalette = skyPalette1;

  for (byte i = 0; i < 4; i++) {
    for (byte k = 0; k < 4; k++) {
      for (byte l = 0; l < 2; l++) {
        for (byte j = 0; j < 12; j++) {
          byte strip = skyMap[i][k][l][0];
          byte y = skyMap[i][k][l][1];
          int p = (j * 3);
          uint8_t start = NUM_LEDS_PER_SIDE * y;
          byte a = start + j;
          byte b = start + 23 - j;
          byte c = start + 24 + j;
          skyMap2[y][k * 2 + l][p][0] = strip;
          skyMap2[y][k * 2 + l][p][1] = a;
          p++;
          skyMap2[y][k * 2 + l][p][0] = strip;
          skyMap2[y][k * 2 + l][p][1] = b;
          p++;
          skyMap2[y][k * 2 + l][p][0] = strip;
          skyMap2[y][k * 2 + l][p][1] = c;
        }
      }
    }
  }
}

void checkPixels() {
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 8; x++) {
      for (int p = 0; p < 36 ; p++) {
        leds[skyMap2[y][x][p][0]][skyMap2[y][x][p][1]] = CRGB::White;
        FastLED.show();
      }
    }
  }
}

void checkPart(int y, int x) {
  for (int p = 0; p < 36 ; p++) {
    leds[skyMap2[y][x][p][0]][skyMap2[y][x][p][1]] = CRGB::White;
  }
  FastLED.show();
  FastLED.delay(300);
  for (int p = 0; p < 36 ; p++) {
    leds[skyMap2[y][x][p][0]][skyMap2[y][x][p][1]] = CRGB::Black;
  }
}

void checkParts() {
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 8; x++) {
      checkPart(y, x);
    }
  }
}

void loop() {

  speed = 0;
  for (byte i = 0; i < NUM_SENSORS; i++) {
    readAdvanced(i, sensor[i], sensorLast[i], 200, 500);
    speed += sensor[i] / 1024;
  }

  skyFull();
  skyHoles();
  FastLED.show();
}

void setPixel(int y, int x, int p, CRGB color) {
  leds[skyMap2[y][x][p][0]][skyMap2[y][x][p][1]] = color;
}

void skyFull() {
  for (byte y = 0; y < 4; y++) {
    for (byte x = 0; x < 8; x++) {
      for (byte p = 0; p < 36; p++) {
        int index = (y * 36 + p) * 150 / 144
                    + cos8( (y * 36 + p) + millis() / (20 * speed) ) * 1 / 2
                    + cos8( (y * 36 + p) * 12 + (millis() / 5 + cos8(millis() / 5000)) ) / 4;
        int fade = cos8(millis() / (y * 36 + p));
        setPixel(y, x, p, ColorFromPalette(skyPalette, index, 255, LINEARBLEND));
      }
    }
  }
}

void skyHoles() {

  for (int x = 0; x < 8; x++) {
  	int sensorIndex = floor(x/2);

  	Serial.println(sensorIndex);
  	int fade = 255-sensor[sensorIndex];
    for (int y = 0; y < 2; y++) {
      for (int p = 0; p < 36; p++) {
        CRGB color = nblend(leds[skyMap2[y][x][p][0]][skyMap2[y][x][p][1]], CRGB::Red, fade);
        setPixel(y,x,p,color);
      }
    }
  }
}