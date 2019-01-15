#include<FastLED.h>
#include "global.h"
#include "palettes.h"

CRGB leds[3][NUM_LEDS];

#include "particle.h"

Particle particles[NUM_STRIPS][NUM_PARTICLES];

int sensorValues[NUM_STRIPS][NUM_SENSORS];
int targetValues[NUM_STRIPS];

void setup() {
	FastLED.setBrightness(228);
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
		CRGBPalette16 gTargetPalette( gGradientPalettes[i] );

		// background
		for (int j = 0; j < LEDS_PER_STRIP[i]; j++){
			int index = (i * j) * 72 / 144
				+ sin8( (i + j) + millis() / 100 ) * 0.25;
			CRGB color = ColorFromPalette(gTargetPalette, index, 255, LINEARBLEND);
			leds[i][j] = color;
		}

		// for each particle
		for (int j = 0; j < NUM_PARTICLES; j++) {
			int sensorTotal = 0;

			// for each sensor
			for (int k = 0; k < SENSORS_PER_STRIP[i]; k++){

				// if the sensor value 
				if (sensorValues[i][k] == 1){
					// targetValues[i][k] = BUDS[i][k];
				}
				sensorTotal += sensorValues[i][k];
			}
			
			// if any sensor is touched
			if (sensorTotal != 0){
				particles[i][j].target = targetValues[i]+random(7);
				particles[i][j].attracts = true;
			} else {
				// particles[i][j].target = particles[i][j].origin;
				particles[i][j].flutter();
				particles[i][j].attracts = false;
			}
			particles[i][j].attract();
			particles[i][j].draw();
		}

		// for each bud
		for (int j = 0; j < BUDS_PER_STRIP[i]; j++){
			int p = BUDS[i][j];
			for (int k = 0; k < 15; k++){
				int index = sin8( (millis() / 1000 ) * 0.25
			        + cos8( millis() / 5 + cos8(millis() / 5000)) ) * 0.125;
				int fade = 128 + cos8(millis() / 2000)*0.5;
				CRGB color = ColorFromPalette(buds_p, index, fade, LINEARBLEND);
				leds[i][p+k] += color;
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