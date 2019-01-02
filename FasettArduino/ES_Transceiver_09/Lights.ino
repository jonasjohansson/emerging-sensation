void setColorRange(byte r, byte g, byte b, int startIndex, int endIndex){
  for (int i = startIndex; i < endIndex; i++){
    leds[i].setRGB(r,g,b);
  }
  FastLED.show();
}
