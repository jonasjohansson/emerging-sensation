void setColor(uint8_t i, uint8_t r, uint8_t g, uint8_t b){
  uint8_t steps = lights[i][1];
  uint8_t inc = lights[i][2];
  for (uint8_t j = 0; j < steps; j+=inc){
    int k = lights[i][0] + j;
    leds[k] = CRGB(r, g, b);
  }
  FastLED.show();
}

void setColorAll(uint8_t r, uint8_t g, uint8_t b){
  for (uint8_t i = 0; i < NUM_PARTS; i++){
    setColor(i,r,g,b);
  }
}

void blink(uint8_t i, uint8_t num, uint8_t wait){
  for (uint8_t j = 0; j < num; j++){
    setColor(i,255,255,255);
    delay(wait);
    setColor(i,0,0,0);
    delay(wait);
  }
}

void cycleHSV(){
  static uint8_t hue = 0;
  FastLED.showColor(CHSV(hue++, 255, 255)); 
  delay(10);
}

void resetLights(){
  FastLED.clear();
  FastLED.show();
}
