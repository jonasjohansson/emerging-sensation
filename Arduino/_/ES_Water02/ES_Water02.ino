/*
   https://github.com/FastLED/FastLED/wiki/Pixel-reference
   A: 222 (6x25 + 1x27 + 3x15)
   B: 213 (7x24 + 3x15)
   C: 300 (10x24 + 4x15)
*/

#include<FastLED.h>
#include "global.h"

#define NUM_PARTICLES 100
#define DAMPING 0.2
#define SMOOTHSTEP(x) ((x) * (x) * (3 - 2 * (x)))
#define N 14.0

int b1, b2, b3, b1l, b2l, b3l;

uint8_t beat, mixer;
uint8_t paletteBeatsPerMinute = 10;

int attractPos;

CRGB waLeds[222];
CRGB wbLeds[222];
CRGB wcLeds[300];

class Particle {
  private:
  public:
    int x;
    int y;
    int oldX;
    int oldY;
    int originX;
    int originY;
    int color;
    int hue;
    int speed;
    int gravity;
    int brightness;
    int weight;
    int target;
    int id;
    long timeSince;
    long timer;
    void init(int x, int i);
    void integrate();
    void attract();
    void draw();
    void fall();
};

void Particle::init(int x, int i){
  this->x = x;
  this->id = i;
  this->originX = x;
  this->color = random(128);
  this->hue = random(255);
  this->speed = random(10);
  this->gravity = random(10);
  this->weight = random(10);
  this->brightness = 0;
  this->timer = millis();
  this->timeSince = 0;
  this->target = 0;
  Serial.print(x);
  Serial.println("  "+String(i));
}

void Particle::integrate() {
}

void Particle::attract() {
  //this->x = lerp(this->x, x, 0.05);
//  float temp;
//  float oldX = this->oldX;
//  float target = this->target;

  //this->oldX = this->x;

  this->x = lerp(this->x, target, 0.1);


  this->oldX = this->x;
//  for (byte i = 0; i < N; i++) {
//    float v = i / N;
//    v = SMOOTHSTEP(v);
//    temp = ( this->oldX * v) + (target * (1 - v));
//  }
  //this->x = (int)temp;
}

void Particle::draw(){
  wbLeds[this->oldX] += blend(wbLeds[this->oldX],CRGB::Black,127); 
 // wbLeds[this->x] += blend(wbLeds[this->x],CRGB::Blue,192); 
  wbLeds[this->x] += blend(wbLeds[this->x],CRGB(127,255,255),127); 
  //wbLeds[this->x] += blend(wbLeds[this->x],CHSV(127,this->hue,255),255); 
//  this->hue++;
//  wbLeds[this->x] = CHSV(128,255,sin8(255));
//    
//  if (random8() == 1) {
//    wbLeds[this->x] += CRGB::White;
//  }

    if (millis() - this->timeSince > 5000){
      //Serial.println("NEW PLACE TO GO!");
      this->timeSince = millis();
      //this->target = random(213);
    }
}

void Particle::fall(){
  if (this->originX < 222){
    this->originX += 1;
  } else {
    this->originX = 0;
  }
}

Particle particles[NUM_PARTICLES];

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, 3>(waLeds, 222);
  FastLED.addLeds<NEOPIXEL, 4>(wbLeds, 222);
  FastLED.addLeds<NEOPIXEL, 2>(wcLeds, 300);
  FastLED.clear();
  
  for (int i = 0; i < NUM_PARTICLES; i++) {
    Particle p;
    p.init(random(222),i);
    particles[i] = p;
  }
  
}

void loop() {
  readSimple(3, b1, b1l);
  readSimple(4, b2, b2l);
  readSimple(5, b3, b3l);
  waterB();
}

void addGlitter() {
}

void waterB(){
  
//  for (byte i = 0; i < WB_NUM_STEMS; i++){
//    int index = WB_STEMS[i];
//    int start = WB_MAP[index][0];
//    int end = start+WB_MAP[index][1];
//    for (byte j = start; j < end; j++){
//      wbLeds[j] = CRGB::Red;
//    }
//  }
//  
//  for (byte i = 0; i < WB_NUM_BRANCHES; i++){
//    int index = WB_BRANCHES[i];
//    int start = WB_MAP[index][0];
//    int end = start+WB_MAP[index][1];
//    for (byte j = start; j < end; j++){
//      wbLeds[j] = CRGB::Green;
//    }
//  }
//  
//  
//  for (byte i = 0; i < WB_NUM_STEMS+WB_NUM_BRANCHES; i++){
//    int index = WB_TREE[i];
//    int start = WB_MAP[index][0];
//    int end = start+WB_MAP[index][1];
//    for (byte j = start; j < end; j++){       
//    }
//  }
  
  fill_gradient(waLeds, 213, CHSV(111,255,255), CHSV(123,255,255), FORWARD_HUES);
  fill_gradient(wbLeds, 222, CHSV(90,255,128), CHSV(120,255,128), FORWARD_HUES);
  fill_gradient(wcLeds, 300, CHSV(110,255,255), CHSV(123,255,255), FORWARD_HUES);

  for (byte i = 0; i < WB_NUM_BUDS; i++){
    int index = WB_BUDS[i];
    int start = WB_MAP[index][0];
    int end = start+WB_MAP[index][1];
    for (byte j = start; j < end; j++){
      wbLeds[j] = CRGB(0,128,255);
    }
  }
  
  for (int i = 0; i < NUM_PARTICLES; i++) {
    if (b1 || b2 || b3){
      int mapIndex;
      
      if (b1) {
        mapIndex = WB_BUDS[0];
      }
      if (b2) {
        mapIndex = WB_BUDS[1];
      }
      if (b3) {
        mapIndex = WB_BUDS[2];
      }
      attractPos = WB_MAP[mapIndex][0];
     // particles[i].attract(attractPos);
      particles[i].target = attractPos+random(15);
    } else {
      particles[i].target = particles[i].originX;
      //particles[i].attract(particles[i].originX);
     //
      
    }
    particles[i].fall();
    particles[i].attract();
    particles[i].draw();
  }

  blur1d(wbLeds, 222, 127);
  FastLED.show();

}
