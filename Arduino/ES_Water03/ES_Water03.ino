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
#define PARTICLES_COUNT 40

CRGB waLeds[WA_NUM_LEDS];
CRGB wbLeds[WB_NUM_LEDS];
CRGB wcLeds[WC_NUM_LEDS];

#include "particle.h"

int touches[NUM_SENSORS];
int touchesLast[NUM_SENSORS];
int targets[3];

int target;
int hue = 0;
int currentPaletteIndex = 0;

Particle particles[PARTICLES_COUNT];

int a,b,c;
int al,bl,cl;

void setup() {
	FastLED.addLeds<NEOPIXEL, 3>(waLeds, WA_NUM_LEDS);
	FastLED.addLeds<NEOPIXEL, 4>(wbLeds, WB_NUM_LEDS);
	FastLED.addLeds<NEOPIXEL, 2>(wcLeds, WC_NUM_LEDS);
	FastLED.clear();
	// createParticles(PARTICLES_COUNT);
}

void loop() {
	readSimple(3,a,al);
	// readSimple(4,b,bl);
	// readSimple(4,c,cl);
	// waterB();
}

void waterB(){
	
 //  uint8_t starthue = beatsin8(5, 0, 255);
 //  uint8_t endhue = beatsin8(7, 0, 255);
 //  starthue = map(starthue,0,255,128,164);
 //  endhue = map(endhue,0,255,128,192);

 //  if (starthue < endhue) {
 //    fill_gradient(waLeds, WB_NUM_LEDS, CHSV(starthue,255,128), CHSV(endhue,255,128), FORWARD_HUES);
 //    fill_gradient(wbLeds, WB_NUM_LEDS, CHSV(starthue,255,128), CHSV(endhue,255,128), FORWARD_HUES);
 //    fill_gradient(wcLeds, WB_NUM_LEDS, CHSV(starthue,255,128), CHSV(endhue,255,128), FORWARD_HUES);
	// } else {
 //    fill_gradient(waLeds, WB_NUM_LEDS, CHSV(starthue,255,128), CHSV(endhue,255,128), BACKWARD_HUES);
 //    fill_gradient(wbLeds, WB_NUM_LEDS, CHSV(starthue,255,128), CHSV(endhue,255,128), BACKWARD_HUES);
 //    fill_gradient(wcLeds, WB_NUM_LEDS, CHSV(starthue,255,128), CHSV(endhue,255,128), BACKWARD_HUES);
 //  }

	// for (byte i = 0; i < WB_NUM_BUDS; i++){
	//   int index = WB_BUDS[i];
	//   int start = WB_MAP[index][0];
	//   int end = start+WB_MAP[index][1];
	//   for (byte j = start; j < end; j++){
	//     wbLeds[j] = OceanColors_p[0];
	//     // wbLeds[j] = OceanColors_p[currentPaletteIndex];
	//   }
	// }
	
	// for (int i = 0; i < PARTICLES_COUNT; i++) {
	// 	if (b1 or b2 or b3){
	// 		particles[i].pTarget = target;
	// 	} else {
	// 		particles[i].flutter();
	// 	}
	// 	particles[i].attract();
	// 	particles[i].draw();
	// }

	FastLED.show();
}

// void newTarget(int pin){
// 	target[0] = WA_MAP[WA_BUDS[pin]];
// 	target[1] = WB_MAP[WB_BUDS[pin]];
// 	target[2] = WC_MAP[WC_BUDS[pin]];
// 	currentPaletteIndex = random(16);
// }

// void createParticles(int count){
// 	for (int i = 0; i < count; i++) {
// 		Particle p;
// 		int rand = random(WB_NUM_LEDS);
// 		p.create(i,rand,WB_NUM_LEDS);
// 		particles[i] = p;
// 	}
// }