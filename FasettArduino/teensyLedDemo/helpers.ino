int stripmapper(int x) {
    return stripmap[x];
}

CRGB getPixel(int y, int x) {
  return leds[y*NUM_LEDS_PER_STRIP+stripmapper(x)];
}
void setPixel(int y, int x, CRGB color) {
  leds[y*NUM_LEDS_PER_STRIP+stripmapper(x)]=color;
}
void addPixel(int y, int x, CRGB color) {
  leds[y*NUM_LEDS_PER_STRIP+stripmapper(x)]+=color;
}
void orPixel(int y, int x, CRGB color) {
  leds[y*NUM_LEDS_PER_STRIP+stripmapper(x)]|=color;
}
void mixPixel(int y, int x, CRGB color,int alpha) {
  setPixel(y,x,colorMix(getPixel(y,x),color,alpha));
}


CRGB colorMix(CRGB color1, CRGB color2, int alpha) {
  CRGB output;
  output.r=(color1.r*(255-alpha))/255 + (color2.r*alpha)/255;
  output.g=(color1.g*(255-alpha))/255 + (color2.g*alpha)/255;
  output.b=(color1.b*(255-alpha))/255 + (color2.b*alpha)/255;
  return output;
}


inline uint8_t fastCosineCalc( uint16_t preWrapVal)
{
  uint8_t wrapVal = (preWrapVal % 255);
  if (wrapVal<0) wrapVal=255+wrapVal;
  return (pgm_read_byte_near(cos_wave+wrapVal)); 
}



