#include<FastLED.h>

#include "math.h"
#include "global.h"
#include "palettes.h"

CRGB leds[3][NUM_LEDS];

#include "particle.h"

Particle particles[NUM_STRIPS][NUM_PARTICLES];

int sensorValues[NUM_STRIPS][NUM_SENSORS];
int targetValues[NUM_STRIPS];
int disco[NUM_STRIPS];

void setup() {
	FastLED.setBrightness(144);
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
		for (int j = 0; j < SENSORS_PER_STRIP[i]; j++){
			readSimple(pin, sensorValues[i][j]);
			pin++;
		}
	}

	// for each strip
	for (int i = 0; i < NUM_STRIPS; i++){
		
		// get the strip palette
		CRGBPalette16 bg_p( backgrounds_p[i] );

		int p = i * LEDS_PER_STRIP[i];
		// background
		for (int j = 0; j < LEDS_PER_STRIP[i]; j++){
	        int index = sin8( millis() / 20 + p++);
			
			CRGB color = ColorFromPalette(bg_p, index, 255, LINEARBLEND);
			leds[i][j] = color;
		}

		int sensorTotal = 0;
		// for each particle
		for (int j = 0; j < NUM_PARTICLES; j++) {

			// for each sensor
			for (int k = 0; k < SENSORS_PER_STRIP[i]; k++){

				// if the sensor value 
				if (sensorValues[i][k] > 0){
					sensorTotal += 1;
				}
			}
			
			// if any sensor is touched
			if (sensorTotal != 0){
				int dir = (random(2) == 1) ? 1 : -1;
				int target = targetValues[i] + (dir * random(7,15));
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

		// get the bud palette
		CRGBPalette16 bud_p( buds_p[i] );
		
		// for each bud
		for (int j = 0; j < BUDS_PER_STRIP[i]; j++){
			int p = BUDS[i][j];
			for (int k = 0; k < 15; k++){
				leds[i][p+k] += nblend(leds[i][p+k],budCols[i],255);
				if (sensorTotal > 0){
					int fade = cos8(millis() / (250 / sensorTotal)) * 0.5
						+ sin8( (p * (i + j)) + millis() / 10 ) * 0.5;
					leds[i][p+k] += nblend(leds[i][p+k],CRGB::Black,224);
					leds[i][p+k] = blend(leds[i][p+k],CRGB::White,fade);
				}
			}
		}
	}

	FastLED.show();
}

void newTarget(int pin){
	if (pin < 3){
		targetValues[0] = BUDS[0][pin]+7;
	} else if (pin < 6){
		targetValues[1] = BUDS[1][pin-3]+7;
	} else if (pin < 10){
		targetValues[2] = BUDS[2][pin-6]+7;
	}
}

void createParticles(){
	for (int i = 0; i < NUM_STRIPS; i++){
		for (int j = 0; j < NUM_PARTICLES; j++){
			Particle p;
			int r = random(LEDS_PER_STRIP[i]);
			p.create(r,i,LEDS_PER_STRIP[i]);
			particles[i][j] = p;
		}
	}
}

void checkParts(){
	// for (int i = 0; i < 300; i++){
	// 	Serial.println(i);
	// 	leds[2][i] = CRGB::White;
	// 	FastLED.show();
	// 	FastLED.delay(100);
	// }
	for (int i = 24; i < 24+15; i++){
		leds[2][i] = CRGB::White;
		FastLED.delay(100);
	}
	for (int i = 63; i < 63+15; i++){
		leds[2][i] = CRGB::White;
		FastLED.delay(100);
	}
	for (int i = 150; i < 150+15; i++){
		leds[2][i] = CRGB::White;
		FastLED.delay(100);
	}
	for (int i = 213; i < 213+15; i++){
		leds[2][i] = CRGB::White;
		FastLED.delay(100);
	}
}