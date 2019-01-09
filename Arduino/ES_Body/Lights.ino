void setColorRange(byte index, int startIndex, int endIndex, byte r, byte g, byte b){
  for (int i = startIndex; i < endIndex; i++){
    leds[index][i].setRGB(r,g,b);
  }
  FastLED.show();
}

void setColor(byte i, byte r, byte g, byte b){
  uint8_t steps = lights[i][1];
  uint8_t inc = lights[i][2];
  for (uint8_t j = 0; j < steps; j+=inc){
    int k = lights[i][0] + j;
    leds[k].setRGB(r, g, b);
  }
  FastLED.show();
}

void cycleHSV(){
  static uint8_t hue = 0;
  FastLED.showColor(CHSV(hue++, 255, 255)); 
  delay(10);
}
