#include<FastLED.h>

#define NUM_LEDS 60
#define LED_PIN 6
#define BRIGHTNESS 128

CRGB leds[NUM_LEDS];

class LightBall {
  public:
    int offset;
    int steps;
    int inc;
    virtual void create(int _offset, int _steps, int _inc) {
      offset = _offset;
      steps = _steps;
      inc = _inc;
    }
    virtual void setColor(int r, int g, int b) {
      Serial.println(offset);
      for (uint8_t i = 0; i < steps; i+=inc) {
        int index = offset + i;
        leds[index] = CRGB(r, g, b);
        FastLED.show();
      }
   }
};

LightBall *ball1;
LightBall *ball2;

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL,LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
  ball1 = new LightBall();
  ball1->create(16,16,1);
  ball1->setColor(255,0,0);
  ball2 = new LightBall();
  ball2->create(31,16,2);
  ball2->setColor(0,0,255);
}

void loop(){
}
