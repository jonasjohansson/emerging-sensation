#include<FastLED.h>

#define NUM_LEDS 60
#define LED_PIN 6
#define BRIGHTNESS 128

CRGB leds[NUM_LEDS];

class Light {
  public:
    virtual void create(int offset, int steps, int inc) {
      _offset = offset;
      _steps = steps;
      _inc = inc;
    }
    virtual void setColor(int r, int g, int b) {
      for (uint8_t i = 0; i < _steps; i+=_inc) {
        int index = _offset + i;
        leds[index] = CRGB(r, g, b);
        FastLED.show();
      }
   }
  private:
    int _offset;
    int _steps;
    int _inc;
};

Light *ball1;
Light *ball2;
Light *strip1;

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL,LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
  ball1 = new Light();
  ball1->create(16,16,1);
  ball2 = new Light();
  ball2->create(31,16,2);
  strip1 = new Light();
  strip1->create(0,9,1);
}

void loop(){
  strip1->setColor(0,255,0);
  ball1->setColor(255,0,0);
  ball2->setColor(0,0,255);
}
