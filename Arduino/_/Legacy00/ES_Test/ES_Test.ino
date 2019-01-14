#include <Adafruit_NeoPixel.h>

#define PIN       6
#define NUMPIXELS 289
#define DELAY     10

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin(); // This initializes the NeoPixel library.
  strip.show();
}

void loop() {
  colorWipe(strip.Color(255, 0, 0), DELAY); // Red
  colorWipe(strip.Color(0, 255, 0), DELAY); // Green
  colorWipe(strip.Color(0, 0, 255), DELAY); // Blue
  colorWipe(strip.Color(255, 255, 255), DELAY); // Blue
}

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
