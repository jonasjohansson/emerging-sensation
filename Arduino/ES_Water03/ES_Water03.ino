/*
	 https://github.com/FastLED/FastLED/wiki/Pixel-reference
	 A: 222 (6x25 + 1x27 + 3x15)
	 B: 213 (7x24 + 3x15)
	 C: 300 (10x24 + 4x15)
*/

#include<FastLED.h>
#include "global.h"

#define NUM_SENSORS 10
#define WA_NUM_LEDS 222
#define WB_NUM_LEDS 213
#define WC_NUM_LEDS 300
#define PARTICLES_COUNT 120

CRGB leds[3][WC_NUM_LEDS];

#include "particle.h"

Particle particles[PARTICLES_COUNT];

int sensor[NUM_SENSORS];
int targets[3];
int target;

void setup() {
	FastLED.addLeds<NEOPIXEL, 3>(leds[0], WA_NUM_LEDS);
	FastLED.addLeds<NEOPIXEL, 4>(leds[1], WB_NUM_LEDS);
	FastLED.addLeds<NEOPIXEL, 2>(leds[2], WC_NUM_LEDS);
	FastLED.clear();
	createParticles(PARTICLES_COUNT/3);
}

void loop() {
  for (byte i = 0; i < NUM_SENSORS; i++) {
    readSimple(i, sensor[i]);
  }
  waterB();
 
  FastLED.show();
}

void waterB(){
	
	for (int i = 0; i < PARTICLES_COUNT; i++) {
		if (sensor[2] or sensor[3] or sensor[4]){
			particles[i].pTarget = target;
		} else {
			particles[i].flutter();
		}
		particles[i].attract();
		particles[i].draw();
	}

	FastLED.show();
}

void newTarget(int pin){
	// Serial.println(pin);
	// target[0] = WA_MAP[WA_BUDS[pin]];
	// target[2] = WC_MAP[WC_BUDS[pin]];
	target = WB_MAP[WB_BUDS[0]][0];
	// currentPaletteIndex = random(16);
}

void createParticles(int count){

	for (int i = 0; i < count; i++) {
		Particle p;
		int rand = random(WA_NUM_LEDS);
		p.create(i,rand,0,WA_NUM_LEDS);
		particles[i] = p;
	}

	for (int i = 0; i < count; i++) {
		Particle p;
		int rand = random(WB_NUM_LEDS);
		p.create(count+i,rand,1,WB_NUM_LEDS);
		particles[count+i] = p;
	}
	
	for (int i = 0; i < count; i++) {
		Particle p;
		int rand = random(WC_NUM_LEDS);
		p.create((2*count)+i,rand,2,WC_NUM_LEDS);
		particles[(2*count)+i] = p;
	}
}