/*
   https://github.com/FastLED/FastLED/wiki/Pixel-reference
   OctoWS2811: 2,14,7,8,6,20,21,5
   Teensy: 0,1,23,22,19,18,17
   A,B,C,D,E,F,G,H: 144
*/

#include<FastLED.h>
#include "Palettes.h"
#include "Math.h"

#define NUM_SENSORS 4
#define NUM_STRIPS 8
#define NUM_LEDS 144
#define NUM_LEDS_PER_SIDE 36
#define NUM_WINGS 4
#define SENSOR_MIN 150
#define SENSOR_MAX 460

CRGB leds[NUM_STRIPS][NUM_LEDS];
CRGB col;

unsigned long timer = 0;
unsigned long lastFrame = 0;
unsigned long thisFrame = 0;
unsigned long frameLength;

unsigned long holeTimer[4];

boolean isCalibrating = true;

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

int pins[NUM_SENSORS] = {18, 22, 17, 19};
float fSensor[NUM_SENSORS];
byte sensor[NUM_SENSORS];
byte sensorLastSend[NUM_SENSORS];
float sensorTot;

float fSensorLast[NUM_SENSORS] = {255,255,255,255};
float sensorRaw[NUM_SENSORS];

float raveFade;
int raveTrigger = 100;

void setup() {
  Serial.begin(9600);
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

void setPixel(int y, int x, int p, CRGB color) {
  leds[skyMap2[y][x][p][0]][skyMap2[y][x][p][1]] = color;
}

CRGB * getPixel(int y, int x, int p) {
  return &leds[skyMap2[y][x][p][0]][skyMap2[y][x][p][1]];
}

void skyFull() {
  for (byte y = 0; y < 4; y++) {
    for (byte x = 0; x < 8; x++) {
      for (byte p = 0; p < 36; p++) {
        int index = constrain( (y * 36 + p + (255 - sensor[x / 2]) / 8-16) * 192 / 144
                               + cos8( (y * 36 + p) + timer / 50 )/8
                                + cos8( (y * 36 + p) * 12 - (timer / 5 + cos8(timer / 5000)) )/8, 0, 240);
        int fade =  255 - sensor[x/2]*3/4;
        CRGB color = ColorFromPalette(fullPal, index, fade, LINEARBLEND);
        int iwhite = gamma8[cos8( (y * 36 + p) * 21 - timer / 7)/2+cos8( (y * 36 + p) * 33 - timer / 5)/2];
        CRGB white = CRGB(iwhite, iwhite, iwhite);
        setPixel(y, x, p,  color + white);
      }
    }
  }
}

void skyRave() {
  for (byte y = 0; y < 4; y++) {
    for (byte x = 0; x < 8; x++) {
      for (byte p = 0; p < 36; p++) {
        int r = gamma8[cos8( -(y * 36 + p) + cos8( 3 + (y * 36 + p) * beatsin16(5) / 2048) / 3)];
        int g = gamma8[cos8( (y * 36 + p) * 12 - timer / 4) / 2];
        int b = gamma8[cos8( (y * 36 + p) + sin8( 5 + (y * 36 + p) * beatsin16(8) / 3072) / 2 + timer / 4)];
        CRGB *pixel = getPixel(y, x, p);
        CRGB color = CRGB(r, g, b);
        *pixel = nblend(*pixel, color, raveFade / 4);
      }
    }
  }
}

void skyHoles() {
  int tracelen = 4;
  int ntraces = 11;
  int dist = 144 / ntraces;;
  for (int h = 0; h < 4; h++) {
    if (sensor[h] < 230) {
      for (int n = 0; n < ntraces; n++) {
        int step = (holeTimer[h] / 32) % 144;
        for (int t = 0; t < tracelen; t++) {
          int s = (step + t + dist * n) % 144;
          int p, y, x;
          if (s < 36) {
            p = s;
            x = h * 2 + 1;
            y = 0;
          } else if (s < 72) {
            p = s - 36;
            x = h * 2 + 1;
            y = 1;
          } else if (s < 108) {
            p = 107 - s;
            x = h * 2;
            y = 1;
          } else {
            p = 143 - s;
            x = h * 2;
            y = 0;
          }
          /*Serial.print(x);
            Serial.print("\t");
            Serial.print(y);
            Serial.print("\t");
            Serial.print(p);
            Serial.println("\t");*/
          int index = 255 - t * 30;
          CRGB *pixel = getPixel(y, x, p);
          *pixel = blend(*pixel, ColorFromPalette(spinPal, index, 255), constrain(map(sensor[h],255,180,0,255 ),0,255));
/*          CRGB *pixel = getPixel(y, h * 2 + 1, p);
          *pixel = nblend(*pixel, ColorFromPalette(spinPal, index, 255), 127 - sensor[h] / 2);
          CRGB *pixel2 = getPixel(y, h * 2, p);
          *pixel2 = nblend(*pixel, ColorFromPalette(spinPal, index, 255), 127 - sensor[h] / 2);
*/        }
      }
    }
  }
}

/*  for (int x = 0; x < 8; x++) {
  	int sensorIndex = floor(x/2);
    for (int y = 0; y < 2; y++) {
      for (int p = 0; p < 36; p++) {
        CRGB *pixel = getPixel(y,x,p);

  //        int index=cos8( -(y * 36 + p) * 12 + (millis() / 5 + cos8(millis() / 5000)) ) ;
  //        CRGB newColor = ColorFromPalette(ravePal, index, 255-sensor[sensorIndex], LINEARBLEND);

         pixel = nblend(*pixel,newColor ,255);


  //        Serial.print(*pixel->saturation);
  /*        CRGB color = nblend(leds[skyMap2[y][x][p][0]][skyMap2[y][x][p][1]], CRGB::Black, 255-sensor[sensorIndex]);
        int index = (y * 36 + p) * 150 / 144
                    + sin8( (y * 36 + p) + millis() / 10 ) * 0.25
                    + cos8( (y * 36 + p) * 12 + (millis() / 5 + cos8(millis() / 5000)) ) * 0.125;
        int fade = cos8(millis() / (y * 36 + p));
        color += ColorFromPalette(ravePal, index, 255-sensor[sensorIndex], LINEARBLEND);
        setPixel(y,x,p,color);*/
/*      }
    }
  }
  }*/

void loop() {
  lastFrame = thisFrame;
  thisFrame = millis();
  frameLength = thisFrame - lastFrame;
  sensorTot = 0;
  for (byte i = 0; i < NUM_SENSORS; i++) {
    readAdvanced(i, fSensor[i], fSensorLast[i], sensorLastSend[i], SENSOR_MIN, SENSOR_MAX);
    sensor[i]=round(fSensor[i]);

    timer += frameLength / 8 + frameLength / NUM_SENSORS * (255 - sensor[i]) / 128;
    holeTimer[i] += frameLength / 8 + frameLength * (255 - sensor[i]) / 256;
    sensorTot += sensor[1];
  }

  // calibration code
  if (isCalibrating && millis() > 5000) {
    isCalibrating = false;
    Serial.println("Sky calibration complete!");
  }
  
  raveFade = constrain(raveFade - frameLength / 2, 0, 1023);
  if (sensor[0] < 120 && sensor[1] < 120 && sensor[2] < 120 && sensor[3] < 120) {
    raveFade = constrain(raveFade + frameLength * (480 - sensorTot) / 200, 0, 1023);
  }

  skyFull();
  if (raveFade) {
    skyRave();
  }
//  FastLED.clear ();
  skyHoles();
  FastLED.show();
}
