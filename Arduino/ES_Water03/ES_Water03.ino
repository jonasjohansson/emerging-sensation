#include<FastLED.h>

#include "math.h"
#include "global.h"
#include "palettes.h"

CRGB leds[3][NUM_LEDS];

#include "particle.h"

#define BRIGHTNESS 140
#define CALIBRATION_DELAY 5000
#define TOUCH_DELAY 300

Particle particles[NUM_STRIPS][NUM_PARTICLES];

int sensorValues[NUM_STRIPS][NUM_SENSORS];
int targetValues[NUM_STRIPS];
long sensorTimers[NUM_SENSORS];

boolean isCalibrating = true;

void setup() {
  Serial.println("Emerging Sensation: Water.");
  Serial.println("Initiating calibration…");
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.addLeds<NEOPIXEL, 3>(leds[0], LEDS_PER_STRIP[0]);
  FastLED.addLeds<NEOPIXEL, 4>(leds[1], LEDS_PER_STRIP[1]);
  FastLED.addLeds<NEOPIXEL, 2>(leds[2], LEDS_PER_STRIP[2]);
  FastLED.clear();
  createParticles();
}

void loop() {

  // for each sensor
  int pin = 0;
  for (int i = 0; i < NUM_STRIPS; i++) {
    for (int j = 0; j < SENSORS_PER_STRIP[i]; j++) {
      readSimple(pin, sensorValues[i][j]);
      pin++;
    }
  }

  calibrate();

  // for each strip
  for (int i = 0; i < NUM_STRIPS; i++) {

    // get the strip palette
    CRGBPalette16 bg_p( backgrounds_p[i] );

    int p = i * LEDS_PER_STRIP[i];
    // background
    for (int j = 0; j < LEDS_PER_STRIP[i]; j++) {
      int index = cos8( millis() / 200 + (p + j));
      CRGB color = ColorFromPalette(bg_p, index, 255, LINEARBLEND);
      leds[i][j] = color;
    }

    int sensorTotal = 0;
    // for each particle
    for (int j = 0; j < NUM_PARTICLES; j++) {

      // for each sensor
      for (int k = 0; k < SENSORS_PER_STRIP[i]; k++) {

        // if the sensor value
        if (sensorValues[i][k] > 0) {
          sensorTotal += 1;
        }
      }

      // if any sensor is touched
      if (sensorTotal != 0) {
        int dir = (random(2) == 1) ? 1 : -1;
        int target = targetValues[i] + (dir * random(7, 15));
        particles[i][j].target = targetValues[i];
        particles[i][j].attracts = true;
      } else {
        particles[i][j].target = particles[i][j].origin;
        particles[i][j].flutter();
        particles[i][j].attracts = false;
      }
      particles[i][j].attract();
      particles[i][j].draw();
    }

    // for each bud
    for (int j = 0; j < BUDS_PER_STRIP[i]; j++) {
      int p = BUDS[i][j];
      for (int k = 0; k < 15; k++) {
        int fade = sin8(millis() / (200 / sensorTotal)) * 0.5
            + sin8( (p * (i + j)) + millis() / 10 ) * 0.5;
          leds[i][p+k] = blend(budCols[i],CRGB::Black,fade);
          //leds[i][p+k] = blend(leds[i][p+k],budCols[i],fade);
      }
    }

    // fade out to prevent flicker
//    if (i == 2){
//      int p = i * LEDS_PER_STRIP[i];
//      for (int j = 0; j < LEDS_PER_STRIP[i]; j++) {
//        leds[i][j].fadeLightBy(96);
//      }
//    }
  }

  FastLED.show();
}

void newTarget(int pin) {
  if (pin < 3) {
    targetValues[0] = BUDS[0][pin] + 7;
  } else if (pin < 6) {
    targetValues[1] = BUDS[1][pin - 3] + 7;
  } else if (pin < 10) {
    targetValues[2] = BUDS[2][pin - 6] + 7;
  }
}

void createParticles() {
  for (int i = 0; i < NUM_STRIPS; i++) {
    for (int j = 0; j < NUM_PARTICLES; j++) {
      Particle p;
      int r = random(LEDS_PER_STRIP[i]);
      p.create(r, i, backgrounds_p[i], LEDS_PER_STRIP[i]);
      particles[i][j] = p;
    }
  }
}

void calibrate() {
  if (isCalibrating && millis() > CALIBRATION_DELAY) {
    isCalibrating = false;
    Serial.println("Complete!");
  }
  return;
}

void checkAll(){
  for (int i = 0; i < NUM_STRIPS; i++) {
    for (int j = 0; j < LEDS_PER_STRIP[i]; j++) {
      leds[i][j] = CRGB(128,128,128);
      FastLED.show();
    }
  }
}
