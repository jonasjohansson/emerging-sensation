#define USE_OCTOWS2811
#include<OctoWS2811.h>
#include<FastLED.h>
#include "helpers.h"

FASTLED_USING_NAMESPACE

// Pin layouts on the teensy 3:
// OctoWS2811: 2,14,7,8,6,20,21,5

#define DATA_PIN    3
//#define CLK_PIN   4
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS_PER_STRIP 13
#define NUM_STRIPS 8
int NUM_LEDS = NUM_STRIPS * NUM_LEDS_PER_STRIP;

CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];

#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120

byte stripmap[9]={0,1,3,5,6,8,9,11,12};

byte sensorPin = 4;

void setup() {
  delay(1000); // 1 second delay for recovery
  LEDS.addLeds<OCTOWS2811>(leds, NUM_LEDS_PER_STRIP);
  FastLED.setBrightness(BRIGHTNESS);
  pinMode(sensorPin, INPUT);
}

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
  
void loop()
{

  
  
  ravePlasma(0); // Run ravePlasma on strip 0
  
  if(digitalRead(sensorPin))
    theaterChase(0, CRGB(255,0,0),127); // overlay theatre chase
  
  
  
  
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

 
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  
}


void ravePlasma(int y) {

    unsigned long m = millis();
    uint16_t t = fastCosineCalc((22 * m)/(500+y*27));  //time displacement - fiddle with these til it looks good...
    uint16_t t2 = fastCosineCalc((15 * m)/(710+y*11)); 
    uint16_t t3 = fastCosineCalc((18 * m)/(930-y*21));

      for (uint8_t x = 0; x < sizeof(stripmap); x++) {

        uint8_t r = fastCosineCalc(((x << 3) + (t >> 1) + fastCosineCalc((t2 + (y << 3)))));
        uint8_t g = fastCosineCalc(((y << 3) + t + fastCosineCalc(((t3 >> 2) + (x << 3)))));
        uint8_t b = fastCosineCalc(((y << 3) + t2 + fastCosineCalc((t + x + (g >> 2)))));

        //uncomment the following to enable gamma correction

        r=pgm_read_byte_near(linear+r);  
        g=pgm_read_byte_near(linear+g);
        b=pgm_read_byte_near(linear+b);
        setPixel(y,x, CRGB(r,g,b));
      }
}

void setAll(int y, CRGB c) {
  for (int x=0; x<NUM_LEDS_PER_STRIP; x++) {
      setPixel(y,x,c);
  }
  LEDS.show();
}

void test() {
  for (int x=0; x<NUM_LEDS_PER_STRIP; x++) {
    for (int y=0; y<NUM_STRIPS; y++) {
      setPixel(y,x,CRGB::Red);
    }
      LEDS.show();
      delay(100);
  }
  for (int x=0; x<NUM_LEDS_PER_STRIP; x++) {
    for (int y=0; y<NUM_STRIPS; y++) {
      setPixel(y,x,CRGB::Green);
    }
      LEDS.show();
      delay(100);
  }
  for (int x=0; x<NUM_LEDS_PER_STRIP; x++) {
    for (int y=0; y<NUM_STRIPS; y++) {
      setPixel(y,x,CRGB::Blue);
    }
      LEDS.show();
      delay(100);
  }
}

void rainbow(int y)
{
  // FastLED's built-in rainbow generator... will not be using mapping...
  fill_rainbow( leds+y*NUM_LEDS_PER_STRIP, NUM_LEDS, gHue, 7);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 1);
  for(int y=0;y<NUM_STRIPS;y++) {
    int pos = beatsin16(13,0,sizeof(stripmap));
    addPixel(y,pos,CHSV( gHue, 255, 192));
  }
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for(int y=0;y<NUM_STRIPS;y++) {
    for( int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
      setPixel(y,i,ColorFromPalette(palette, gHue+(i*2)+(y*4), beat-gHue+(i*10)+(y+20)));
    }
  }
}



void theaterChase(int y,CRGB c,int alpha) {
   int q=(millis()/50)%3;
  for (uint8_t x = 0; x < sizeof(stripmap) ; x++) {
    if((x+q)%3==0)
      mixPixel(y,x, c,alpha);
    else {
      mixPixel(y,x, CRGB::Black,alpha);
    }
  }
}


