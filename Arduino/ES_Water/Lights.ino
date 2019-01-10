void setColorRange(byte index, int startIndex, int endIndex, byte r, byte g, byte b){
  for (int i = startIndex; i < endIndex; i++){
    leds[index][i] = CRGB::Red;
  }
}
