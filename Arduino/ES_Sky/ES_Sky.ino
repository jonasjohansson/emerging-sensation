/*
 * https://github.com/FastLED/FastLED/wiki/Pixel-reference
 * OctoWS2811: 2,14,7,8,6,20,21,5
 * Teensy: 0,1,23,22,19,18,17
 * A,B,C,D,E,F,G,H: 144
 */

#include<FastLED.h>

#define NUM_STRIPS 8
#define NUM_LEDS 144
#define NUM_LEDS_PER_SIDE 36
#define NUM_WINGS 4

CRGB leds[NUM_STRIPS][NUM_LEDS];
CRGB col;

float a,b,c,d;
float ax,bx,cx,dx;
float al,bl,cl,dl;

CRGBPalette16 sunset;

DEFINE_GRADIENT_PALETTE(sunset1) {
  0,  	0,  0, 255,
  // 32,  	16,  64, 192,
  // 64,  	32,  128, 255,
  // 128,  64,  128, 255,
  255,  255,  255, 255
};
TBlendType    currentBlending;
// int skyMap[8][4][2] = {
// 	{ {1,0}, {0,1}, {2,0}, {3,1} },
// 	{ {3,0}, {2,1}, {5,1}, {4,0} },
// 	{ {5,0}, {4,1}, {7,1}, {6,0} },
// 	{ {7,0}, {6,1}, {1,1}, {0,0} },
// 	{ {3,2}, {6,3}, {5,3}, {0,2} },
// 	{ {5,2}, {0,3}, {7,3}, {2,2} },
// 	{ {7,2}, {2,3}, {1,3}, {4,2} },
// 	{ {1,2}, {4,3}, {3,3}, {6,2} }
// };


int skyMap[8][4][2] = {
	{ {1,0}, {0,1}, {2,0}, {3,1} },
	{ {3,0}, {2,1}, {5,1}, {4,0} },
	{ {5,0}, {4,1}, {7,1}, {6,0} },
	{ {7,0}, {6,1}, {1,1}, {0,0} },
	{ {3,2}, {6,3}, {5,3}, {0,2} },
	{ {5,2}, {0,3}, {7,3}, {2,2} },
	{ {7,2}, {2,3}, {1,3}, {4,2} },
	{ {1,2}, {4,3}, {3,3}, {6,2} }
};

int skyMapx[8][4][2] = {
	{ {0,1}, {2,0}, {1,0}, {3,1} },
	{ {2,1}, {5,1}, {3,0}, {4,0} },
	{ {4,1}, {7,1}, {5,0}, {6,0} },
	{ {6,1}, {1,1}, {7,0}, {0,0} },
	{ {6,3}, {5,3}, {3,2}, {0,2} },
	{ {0,3}, {7,3}, {5,2}, {2,2} },
	{ {2,3}, {1,3}, {7,2}, {4,2} },
	{ {4,3}, {3,3}, {1,2}, {6,2} }
};

int skyMapMega[4][4][2][2] = {
	{ { {6,3}, {5,3} },
		{ {0,3}, {7,3} },
		{ {2,3}, {1,3} },
		{ {4,3}, {3,3} } },
	{ { {3,2}, {0,2} },
		{ {5,2}, {2,2} },
		{ {7,2}, {4,2} },
		{ {1,2}, {6,2} } },
	{ { {0,1}, {2,0} },
		{ {2,1}, {5,1} },
		{ {4,1}, {7,1} },
		{ {6,1}, {1,1} } },
	{ { {1,0}, {3,1} },
		{ {3,0}, {4,0} },
		{ {5,0}, {6,0} },
		{ {7,0}, {0,0} } }
};

int skyMap1[4][2][2] = {
	{ {6,3}, {5,3} },
	{ {0,3}, {7,3} },
	{ {2,3}, {1,3} },
	{ {4,3}, {3,3} }
};
int skyMap2[4][2][2] = {
	{ {3,2}, {0,2} },
	{ {5,2}, {2,2} },
	{ {7,2}, {4,2} },
	{ {1,2}, {6,2} }
};

int skyMap3[4][2][2] = {
	{ {0,1}, {2,0} },
	{ {2,1}, {5,1} },
	{ {4,1}, {7,1} },
	{ {6,1}, {1,1} }
};

int skyMap4[4][2][2] = {
	{ {1,0}, {3,1} },
	{ {3,0}, {4,0} },
	{ {5,0}, {6,0} },
	{ {7,0}, {0,0} }
};

int skyLine1[4][2] = {
	{7,3},
	{2,2},
	{5,1},
	{4,0}
};


int skyLines[4][4][2] = {
	{ {7,3}, {2,2}, {5,1}, {4,0} },
	{ {1,3}, {4,2}, {7,1}, {6,0} },
	{ {3,3}, {6,2}, {1,1}, {0,0} },
	{ {5,3}, {0,2}, {2,0}, {3,1} },
};

byte wingA[NUM_WINGS][2] = { {1,0}, {0,1}, {2,0}, {3,1} };
byte wingB[NUM_WINGS][2] = { {3,0}, {2,1}, {5,1}, {4,0} };
byte wingC[NUM_WINGS][2] = { {5,0}, {4,1}, {7,1}, {6,0} };
byte wingD[NUM_WINGS][2] = { {7,0}, {6,1}, {1,1}, {0,0} };
byte wingE[NUM_WINGS][2] = { {3,2}, {6,3}, {5,3}, {0,2} };
byte wingF[NUM_WINGS][2] = { {5,2}, {0,3}, {7,3}, {2,2} };
byte wingG[NUM_WINGS][2] = { {7,2}, {2,3}, {1,3}, {4,2} };
byte wingH[NUM_WINGS][2] = { {1,2}, {4,3}, {3,3}, {6,2} };



void setup(){
	sunset = sunset1;
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
uint8_t colorIndex = 0;
int position = 0;
int gHue = 0;
void loop(){
	//a = readAdvanced(17,ax,al,200,500);
	//b = readAdvanced(18,bx,bl,200,500);
	//c = readAdvanced(19,cx,cl,200,500);
	// d = readAdvanced(22,dx,dl,200,500);

	// d = map(d,200,500,255,0);

	// colorise(wingB, CRGB(d,d,d));
	// colorise(wingB, CRGB::Red);
	// col = OceanColors_p[random(16)];
	// col = ColorFromPalette(sunset, beat8(20), 255);
		// for (byte j = 0; j < 12; j++) {
	// for (byte j = 12; j > 0; j--) {

	// 	for (byte i = 0; i < 8; i++){

	// 		byte x = skyMap[i][1][0];
	// 		byte y = skyMap[i][1][1];
	// 		byte x2 = skyMap[i][2][0];
	// 		byte y2 = skyMap[i][2][1];

	// 		uint8_t start = NUM_LEDS_PER_SIDE * y;
	// 		uint8_t end = NUM_LEDS_PER_SIDE * (y + 1);
	// 		uint8_t start2 = NUM_LEDS_PER_SIDE * y2;
	// 		uint8_t end2 = NUM_LEDS_PER_SIDE * (y2 + 1);

	// 	  byte a = start+j;
	// 	  byte b = start+24-j;
	// 	  byte c = start+22+j;

	// 	  CRGB color = CRGB(255,255,255);
			
	// 	  leds[x][a] = color;
	// 	  leds[x][b] = color;
	// 	  leds[x][c] = color;
			
	// 	  a = start2+j;
	// 	  b = start2+24-j;
	// 	  c = start2+22+j;
			
	// 	  leds[x2][a] = color;
	// 	  leds[x2][b] = color;
	// 	  leds[x2][c] = color;
	// 	}
	// 	  FastLED.show();
	// 	// colorLine(x,y,x2,y2);
	// }

	// for (byte i = 0; i < 4; i++){
	// 	for (byte j = 12; j > 0; j--) {
	// 		for (byte k = 0; k < 4; k++){
	// 			for (byte l = 0; l < 2; l++){
	// 				byte x = skyMapMega[i][k][l][0];
	// 				byte y = skyMapMega[i][k][l][1];
	// 				uint8_t start = NUM_LEDS_PER_SIDE * y;
	// 				uint8_t end = NUM_LEDS_PER_SIDE * (y + 1);
	// 				byte a = start+j;
	// 				byte b = start+24-j;
	// 				byte c = start+22+j;
	// 				leds[x][a] = ColorFromPalette( HeatColors_p, colorIndex, 255, LINEARBLEND);
	// 				leds[x][b] = ColorFromPalette( HeatColors_p, colorIndex, 255, LINEARBLEND);
	// 				leds[x][c] = ColorFromPalette( HeatColors_p, colorIndex, 255, LINEARBLEND);
	// 			}
	// 		}
	// 				colorIndex += 30; 
	// 		FastLED.show();
	// 	}
	// }

		int inc  = 0;
	for (byte i = 0; i < 4; i++){
		for (byte k = 0; k < 4; k++){
			for (byte l = 0; l < 2; l++){
			int pos = 0;
				for (byte j = 0; j < 12; j++) {
					// t++;
					pos = (inc * 12) + (j * 3);
					Serial.print(pos);
					Serial.print("	");
					Serial.print(pos + 1);
					Serial.print("	");
					Serial.println(pos + 2);
					byte x = skyMapMega[i][k][l][0];
					byte y = skyMapMega[i][k][l][1];
					uint8_t start = NUM_LEDS_PER_SIDE * y;
					uint8_t end = NUM_LEDS_PER_SIDE * (y + 1);
					byte a = start+j;
					byte b = start+23-j;
					byte c = start+24+j;
					int index = 255+cos8(255*(millis()/30+inc));
	//   		uint8_t beat = beatsin8( 120, 64, 255);
				leds[x][a] = ColorFromPalette(sunset, beatsin16(pos,0,255),255,LINEARBLEND);
	// 			
					// leds[x][a] = ColorFromPalette( sunset, gHue+(l*t),255, LINEARBLEND);
					// leds[x][a] = ColorFromPalette( sunset, gHue+(i*j),255, LINEARBLEND);
					leds[x][b] = ColorFromPalette(sunset, beatsin16(pos+1,0,255),255,LINEARBLEND);
					leds[x][c] = ColorFromPalette(sunset, beatsin16(pos+2,0,255),255,LINEARBLEND);
				}
			}
		}
			inc++;
	}

	byte x = 2;
	byte y = 2;
	uint8_t start = NUM_LEDS_PER_SIDE * y;
	uint8_t end = NUM_LEDS_PER_SIDE * (y + 1);
	// uint8_t start2 = NUM_LEDS_PER_SIDE * y2;
	// uint8_t end2 = NUM_LEDS_PER_SIDE * (y2 + 1);
	// for (byte j = 0; j < 12; j++) {
	int pos = 0;
	// for (byte j = 12; j > 0; j--) {
	// 	pos++;
	// 	byte a = start+j;
	// 	byte b = start+24-j;
	// 	byte c = start+22+j;
	// 	int col = cos8(255);
	// 	CRGB color = CRGB(255,255,col);
	// 	int index = 192*beatsin8( 30-10 , 0, 255);
	// 	// ColorFromPalette(sunset,j,cos8(255*(millis()/36+(ledOffset*72)+j)/72),LINEARBLEND);
	// 	leds[x][a] = ColorFromPalette(sunset, 0,beatsin16(gHue+pos,0,255),LINEARBLEND);
	// 	leds[x][b] = leds[x][a];
	// 	leds[x][c] = leds[x][a];

	// 	// a = start2+j;
	// 	// b = start2+24-j;
	// 	// c = start2+22+j;
	// 	// leds[x2][a] = color;
	// 	// leds[x2][b] = color;
	// 	// leds[x2][c] = color;
	// }

	// for (byte k = 0;k < 4; k++){
	// 	int inc = 0;
	// 	for (byte i = 0; i < 4; i++){
	// 		inc++;
	// 		int pos = 0;
	// 		// for (byte j = 12; j > 0; j--) {
	// 		for (byte j = 0; j < 12; j++) {
	// 			pos = inc * j;
	// 			byte x = skyLines[k][i][0];
	// 			byte y = skyLines[k][i][1];
	// 			uint8_t start = NUM_LEDS_PER_SIDE * y;
	// 			uint8_t end = NUM_LEDS_PER_SIDE * (y + 1);
	// 			byte a = start+j;
	// 			byte b = start+23-j;
	// 			byte c = start+24+j;
	// 			int index = beatsin16((i*j)*3+10,0,255);
	// 			// int index = beatsin16((i*j)+44,0,255);
	// 			index = 255+cos8(255*(millis()/30+pos));
	//   		uint8_t beat = beatsin8( 120, 64, 255);
	// 			leds[x][a] = ColorFromPalette(sunset, index,beatsin16(gHue+pos,0,255),LINEARBLEND);
	// 			// leds[x][a] = ColorFromPalette( sunset, gHue+(i*t),255, LINEARBLEND);
	// 			// leds[x][a] = CRGB(index,0,0);
	// 			leds[x][b] = ColorFromPalette(sunset, index,beatsin16(gHue+pos++,0,255),LINEARBLEND);
	// 			leds[x][c] = ColorFromPalette(sunset, index,beatsin16(gHue+pos++,0,255),LINEARBLEND);
	// 		}
	// 	}
	// }
		FastLED.show();
  // EVERY_N_MILLISECONDS( 10 ) { gHue++; }
  gHue++; 

	// for (byte i = 5; i < 6; i++){
	// 	byte x = skyMap[i][1][0];
	// 	byte y = skyMap[i][1][1];
	// 	byte x2 = skyMap[i][2][0];
	// 	byte y2 = skyMap[i][2][1];
	// 	Serial.println(x);
	// 	Serial.println(y);
	// 	Serial.println(x2);
	// 	Serial.println(y2);
	// 	colorLine(x,y,x2,y2);
	// }

	// for (byte i = 5; i < 6; i++){
	// 	byte x = skyMap[i][0][0];
	// 	byte y = skyMap[i][0][1];
	// 	byte x2 = skyMap[i][3][0];
	// 	byte y2 = skyMap[i][3][1];
	// 	Serial.println(x);
	// 	Serial.println(y);
	// 	Serial.println(x2);
	// 	Serial.println(y2);
	// 	colorLine(x,y,x2,y2);
	// }

	// for (byte i = 1; i < 2; i++){
	// 	byte x = skyMap[i][1][0];
	// 	byte y = skyMap[i][1][1];
	// 	byte x2 = skyMap[i][2][0];
	// 	byte y2 = skyMap[i][2][1];
	// 	Serial.println(x);
	// 	Serial.println(y);
	// 	Serial.println(x2);
	// 	Serial.println(y2);
	// 	colorLine(x,y,x2,y2);
	// }

	// for (byte i = 1; i < 2; i++){
	// 	byte x = skyMap[i][0][0];
	// 	byte y = skyMap[i][0][1];
	// 	byte x2 = skyMap[i][3][0];
	// 	byte y2 = skyMap[i][3][1];
	// 	Serial.println(x);
	// 	Serial.println(y);
	// 	Serial.println(x2);
	// 	Serial.println(y2);
	// 	colorLine(x,y,x2,y2);
	// }

	// colorLine(0,3,7,3);
	// colorLine(5,2,2,2);

	// for (byte i = 0; i < 8; i++){
	// 	byte x = skyMap[i][0];
	// 	byte y = skyMap[i][1];
	// 	byte x2 = skyMap[i][2];
	// 	byte y2 = skyMap[i][3];
	//   uint8_t start = NUM_LEDS_PER_SIDE * y;
	//   uint8_t end = NUM_LEDS_PER_SIDE * (y + 1);
	//   uint8_t start2 = NUM_LEDS_PER_SIDE * y2;
	//   uint8_t end2 = NUM_LEDS_PER_SIDE * (y2 + 1);
	//   for (byte j = 12; j > 0; j--) {
	//     byte a = start+j;
	//     byte b = start+24-j;
	//     byte c = start+22+j;
	//     CRGB color = CRGB(255,255,255);
	//     leds[x][a] = color;
	//     leds[x][b] = color;
	//     leds[x][c] = color;
	//     a = start2+j;
	//     b = start2+24-j;
	//     c = start2+22+j;
	//     leds[x2][a] = color;
	//     leds[x2][b] = color;
	//     leds[x2][c] = color;
	//     FastLED.show();
	//   }

	// }

	// colorLine2(2,1);
	// colorLine(4,0);

	// for (int i = 0; i < NUM_STRIPS; i++){
	//   fill_gradient(leds[0], NUM_LEDS, CHSV(100,255,255), CHSV(160,255,255), FORWARD_HUES);
	//   fill_gradient(leds[1], NUM_LEDS, CHSV(90,255,255), CHSV(140,255,255), FORWARD_HUES);
	//   fill_gradient(leds[2], NUM_LEDS, CHSV(110,255,255), CHSV(150,255,255), FORWARD_HUES);
	//   fill_gradient(leds[3], NUM_LEDS, CHSV(110,255,255), CHSV(150,255,255), FORWARD_HUES);
	//   fill_gradient(leds[4], NUM_LEDS, CHSV(110,255,255), CHSV(150,255,255), FORWARD_HUES);
	//   fill_gradient(leds[5], NUM_LEDS, CHSV(110,255,255), CHSV(150,255,255), FORWARD_HUES);
	//   fill_gradient(leds[6], NUM_LEDS, CHSV(110,255,255), CHSV(150,255,255), FORWARD_HUES);
	//   fill_gradient(leds[7], NUM_LEDS, CHSV(110,255,255), CHSV(150,255,255), FORWARD_HUES);
	// }
	// FastLED.show();
	
	// delay(10);
}

// void colorLine(byte x, byte y, byte x2, byte y2){
void colorLinex(byte x, byte y){
	uint8_t start = NUM_LEDS_PER_SIDE * y;
	uint8_t end = NUM_LEDS_PER_SIDE * (y + 1);
	// uint8_t start2 = NUM_LEDS_PER_SIDE * y2;
	// uint8_t end2 = NUM_LEDS_PER_SIDE * (y2 + 1);
	// for (byte j = 0; j < 12; j++) {
	for (byte j = 12; j > 0; j--) {
		byte a = start+j;
		byte b = start+24-j;
		byte c = start+22+j;
		int col = cos8(255);
		CRGB color = CRGB(255,255,col);
		// ColorFromPalette(sunset,j,cos8(255*(millis()/36+(ledOffset*72)+j)/72),LINEARBLEND);
		leds[x][a] = color;
		leds[x][b] = color;
		leds[x][c] = color;
		// a = start2+j;
		// b = start2+24-j;
		// c = start2+22+j;
		// leds[x2][a] = color;
		// leds[x2][b] = color;
		// leds[x2][c] = color;
		FastLED.show();
	}
}
void colorLine(byte x, byte y, byte x2, byte y2){
// void colorLine(byte x, byte y){
	uint8_t start = NUM_LEDS_PER_SIDE * y;
	uint8_t end = NUM_LEDS_PER_SIDE * (y + 1);
	uint8_t start2 = NUM_LEDS_PER_SIDE * y2;
	uint8_t end2 = NUM_LEDS_PER_SIDE * (y2 + 1);
	// for (byte j = 0; j < 12; j++) {
	for (byte j = 12; j > 0; j--) {
		byte a = start+j;
		byte b = start+24-j;
		byte c = start+22+j;
		int col = cos8(255*(millis()/36));
		CRGB color = CRGB(255,255,col);
		// ColorFromPalette(sunset,j,cos8(255*(millis()/36+(ledOffset*72)+j)/72),LINEARBLEND);
		leds[x][a] = color;
		leds[x][b] = color;
		leds[x][c] = color;
		a = start2+j;
		b = start2+24-j;
		c = start2+22+j;
		leds[x2][a] = color;
		leds[x2][b] = color;
		leds[x2][c] = color;
		FastLED.show();
	}
}

void colorLine2(byte x, byte y, byte x2, byte y2){
	uint8_t start = NUM_LEDS_PER_SIDE * y;
	uint8_t end = NUM_LEDS_PER_SIDE * (y + 1);
	uint8_t start2 = NUM_LEDS_PER_SIDE * y2;
	uint8_t end2 = NUM_LEDS_PER_SIDE * (y2 + 1);
	for (byte j = 0; j < 12; j++) {
		byte a = start+j;
		byte b = start+23-j;
		byte c = start+24+j;
		leds[x][a] = col;
		leds[x][b] = col;
		leds[x][c] = col;
		a = start2+j;
		b = start2+23-j;
		c = start2+24+j;
		leds[x2][a] = col;
		leds[x2][b] = col;
		leds[x2][c] = col;
		FastLED.show();
	}
}

CRGB Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return CRGB(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return CRGB(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return CRGB(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

