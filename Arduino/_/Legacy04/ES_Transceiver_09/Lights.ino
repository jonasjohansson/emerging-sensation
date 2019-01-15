void setColorRange(byte r, byte g, byte b, int startIndex, int endIndex, byte index){
  for (int i = startIndex; i < endIndex; i++){
    leds[index][i].setRGB(r,g,b);
  }
  FastLED.show();
}
