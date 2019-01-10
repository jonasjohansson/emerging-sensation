/*
 * https://github.com/FastLED/FastLED/wiki/Pixel-reference
 * A: 222 (6x25 + 1x27 + 3x15)
 * B: 213 (7x24 + 3x15)
 * C: 300 (10x24 + 4x15)
 */

#include<FastLED.h>

#define NUM_PARTICLES 200
#define PIN_A 8
#define PIN_B 10
#define PIN_C 12

CRGB leds[3][300];

uint8_t gHue = 0;


int a1,a2,a3,a1l,a2l,a3l;
int b1,b2,b3,b1l,b2l,b3l;
int c1,c2,c3,c4,c1l,c2l,c3l,c4l;

byte r,g,b;

void setup(){
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL,PIN_A>(leds[0],222);
  FastLED.addLeds<NEOPIXEL,PIN_B>(leds[1],213);
  FastLED.addLeds<NEOPIXEL,PIN_C>(leds[2],300);
  FastLED.clear();
  FastLED.show();
  Serial.println("Calibrating…");
  delay(5000);
  Serial.println("Calibration done!");
}

void loop(){

  int a = analogRead(A0);
  int b = analogRead(A1);
  int c = analogRead(A2);
  int d = analogRead(A3);
  int e = analogRead(A4);
  int f = analogRead(A5);
  int g = analogRead(A6);
  int h = analogRead(A7);
  int i = analogRead(A8);
  int j = analogRead(A9);

  a = (a > 512) ? 1 : 0;
  b = (b > 512) ? 1 : 0;
  c = (c > 512) ? 1 : 0;
  d = (d > 512) ? 1 : 0;
  e = (e > 512) ? 1 : 0;
  f = (f > 512) ? 1 : 0;
  g = (g > 512) ? 1 : 0;
  h = (h > 512) ? 1 : 0;
  i = (i > 512) ? 1 : 0;
  j = (j > 512) ? 1 : 0;

  p(a);
  p(b);
  p(c);
  p(d);
  p(e);
  p(f);
  p(g);
  p(h);
  p(i);
  p(j);
  
  pl();
  
  for (int k = 0; k < 222; k++){
    leds[0][k] = CRGB( (byte)a*255, (byte)b*255, (byte)c*255 );
  }
  
  for (int k = 0; k < 213; k++){
    leds[1][k] = CRGB( (byte)d*255, (byte)e*255, (byte)f*255 );
  }
  
  for (int k = 0; k < 300; k++){
    leds[2][k] = CRGB( (byte)g*255, (byte)h*255, (byte)i*255 );
  }
  
  FastLED.show();
}

void p(int val){
  Serial.print(val);
  Serial.print("  ");
}

void pl() { Serial.println(); }
