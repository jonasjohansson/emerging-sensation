void setColor(uint8_t i, uint8_t r, uint8_t g, uint8_t b){
  uint8_t steps = lights[i][1];
  uint8_t inc = lights[i][2];
  for (uint8_t j = 0; j < steps; j+=inc){
    uint8_t index = lights[i][0] + j;
    leds[index] = CRGB(r, g, b);
    FastLED.show();
  }
}

void setColorAll(uint8_t r, uint8_t g, uint8_t b){
  for (uint8_t i = 0; i < NUM_PARTS; i++){
    setColor(i,r,g,b);
  }
}

void resetLights(){
  FastLED.clear();
  FastLED.show();
}
