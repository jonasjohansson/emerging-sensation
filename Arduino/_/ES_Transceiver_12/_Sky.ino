#define SMOOTHSTEP(x) ((x) * (x) * (3 - 2 * (x)))
#define N 10.0
#define NUM_LEDS 144
#define BRIGHTNESS 255

CRGB leds[8][NUM_LEDS];
void _setup(){


  FastLED.setBrightness(BRIGHTNESS);
  FastLED.addLeds<NEOPIXEL,6>(leds[0],NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,20>(leds[1],NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,21>(leds[2],NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,5>(leds[3],NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,2>(leds[4],NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,14>(leds[5],NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,7>(leds[6],NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,8>(leds[7],NUM_LEDS);
}

void sky(){
  float newVal = analogRead(19);
  newVal = smooth(newVal);

  for (byte i = 0; i < N; i++) {
    float v = i / N;
    v = SMOOTHSTEP(v);
    val = (oldVal * v) + (newVal * (1 - v));
  }
    Serial.println(val);

  oldVal = val;

}
