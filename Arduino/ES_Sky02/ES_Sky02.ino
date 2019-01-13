/*
 * https://github.com/FastLED/FastLED/wiki/Pixel-reference
 * OctoWS2811: 2,14,7,8,6,20,21,5
 * Teensy: 0,1,23,22,19,18,17
 * A,B,C,D,E,F,G,H: 144
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

DEFINE_GRADIENT_PALETTE(skyPalette1) {
  0,  	0,  0, 255,
  // 32,  	16,  64, 192,
  // 64,  	32,  128, 255,
  // 128,  64,  128, 255,
  255,  255,  255, 255
};

int skyMap[4][4][2][2] = {
	{ 						// top
		{ {6,3}, {5,3} }, 	// a
		{ {0,3}, {7,3} }, 	// b
		{ {2,3}, {1,3} }, 	// c
		{ {4,3}, {3,3} } 	// d
	},
	{
		{ {3,2}, {0,2} },
		{ {5,2}, {2,2} },
		{ {7,2}, {4,2} },
		{ {1,2}, {6,2} }
	},
	{
		{ {0,1}, {2,0} },
		{ {2,1}, {5,1} },
		{ {4,1}, {7,1} },
		{ {6,1}, {1,1} }
	},
	{
		{ {1,0}, {3,1} },
		{ {3,0}, {4,0} },
		{ {5,0}, {6,0} },
		{ {7,0}, {0,0} }
	}
};

// byte wingA[NUM_WINGS][2] = { {1,0}, {0,1}, {2,0}, {3,1} };
// byte wingB[NUM_WINGS][2] = { {3,0}, {2,1}, {5,1}, {4,0} };
// byte wingC[NUM_WINGS][2] = { {5,0}, {4,1}, {7,1}, {6,0} };
// byte wingD[NUM_WINGS][2] = { {7,0}, {6,1}, {1,1}, {0,0} };
// byte wingE[NUM_WINGS][2] = { {3,2}, {6,3}, {5,3}, {0,2} };
// byte wingF[NUM_WINGS][2] = { {5,2}, {0,3}, {7,3}, {2,2} };
// byte wingG[NUM_WINGS][2] = { {7,2}, {2,3}, {1,3}, {4,2} };
// byte wingH[NUM_WINGS][2] = { {1,2}, {4,3}, {3,3}, {6,2} };

float pins[NUM_SENSORS] = {17,18,19,22};
float sensor[NUM_SENSORS];
float sensorLast[NUM_SENSORS];

void setup(){
	skyPalette = skyPalette1;
	FastLED.addLeds<NEOPIXEL,6>(leds[0],NUM_LEDS);
	FastLED.addLeds<NEOPIXEL,20>(leds[1],NUM_LEDS);
	FastLED.addLeds<NEOPIXEL,21>(leds[2],NUM_LEDS);
	FastLED.addLeds<NEOPIXEL,5>(leds[3],NUM_LEDS);
	FastLED.addLeds<NEOPIXEL,2>(leds[4],NUM_LEDS);
	FastLED.addLeds<NEOPIXEL,14>(leds[5],NUM_LEDS);
	FastLED.addLeds<NEOPIXEL,7>(leds[6],NUM_LEDS);
	FastLED.addLeds<NEOPIXEL,8>(leds[7],NUM_LEDS);
	FastLED.clear();
	FastLED.show();
}

void loop(){

	for (byte i = 0; i < NUM_SENSORS; i++){
		readAdvanced(i,sensor[i],sensorLast[i],200,500);
	}

	all();
	single(2,1); // 3rd col, 2nd row

	FastLED.show();
}

void all(){
	int step = 0;
	for (byte i = 0; i < 4; i++){
		for (byte k = 0; k < 4; k++){
			for (byte l = 0; l < 2; l++){
				int pos = 0;
				for (byte j = 0; j < 12; j++) {
					pos = (step * 12) + (j * 3);
					byte x = skyMap[i][k][l][0];
					byte y = skyMap[i][k][l][1];
					uint8_t start = NUM_LEDS_PER_SIDE * y;
					uint8_t end = NUM_LEDS_PER_SIDE * (y + 1);
					byte a = start+j;
					byte b = start+23-j;
					byte c = start+24+j;
					int index = 255+cos8(255*(millis()/30+step));
					leds[x][a] = ColorFromPalette(skyPalette, beatsin16(pos,0,255),255,LINEARBLEND);
					pos++;
					leds[x][b] = ColorFromPalette(skyPalette, beatsin16(pos,0,255),255,LINEARBLEND);
					pos++;
					leds[x][c] = ColorFromPalette(skyPalette, beatsin16(pos,0,255),255,LINEARBLEND);
				}
			}
		}
		step++;
	}
}

void single(byte yi, byte xi){
	int step = 0;
	for (byte i = yi; i < yi+2; i++){
		for (byte l = 0; l < 2; l++){
			int pos = 0;
			for (byte j = 0; j < 12; j++) {
				pos = (step * 12) + (j * 3);
				byte x = skyMap[i][xi][l][0];
				byte y = skyMap[i][xi][l][1];
				uint8_t start = NUM_LEDS_PER_SIDE * y;
				uint8_t end = NUM_LEDS_PER_SIDE * (y + 1);
				byte a = start+j;
				byte b = start+23-j;
				byte c = start+24+j;
				leds[x][a] += nblend(leds[x][a],CRGB::Red,sensor[3]); 
				leds[x][b] += nblend(leds[x][b],CRGB::Red,sensor[3]); 
				leds[x][b] += nblend(leds[x][c],CRGB::Red,sensor[3]); 
			}
		}
		step++;
	}
}