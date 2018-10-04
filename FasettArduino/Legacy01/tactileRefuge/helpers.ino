
long addRead(long reading) {
  //Serial.println(reading);
  readings[currReading]=reading;
  currReading++;
  if(currReading==NUMREAD)
    currReading=0;
  return reading;
}

long getAvg() {
  long sum;
  for(int i=0;i<NUMREAD;i++) {
//    Serial.print(readings[i]);
//    Serial.print(" ");
    sum+=readings[i];
  }
//  Serial.println();
  return sum/NUMREAD;
}

CRGB getPixel(int y, int x) {
  return leds[y*NUM_LEDS_PER_STRIP+wingmapper(y,x)];
}
void setPixel(int y, int x, CRGB color) {
  leds[y*NUM_LEDS_PER_STRIP+wingmapper(y,x)]=color;
}
void addPixel(int y, int x, CRGB color) {
  leds[y*NUM_LEDS_PER_STRIP+wingmapper(y,x)]+=color;
}
void orPixel(int y, int x, CRGB color) {
  leds[y*NUM_LEDS_PER_STRIP+wingmapper(y,x)]|=color;
}
void mixPixel(int y, int x, CRGB color,int alpha) {
  setPixel(y,x,colorMix(getPixel(y,x),color,alpha));
}

int wingmapper(int y, int x) {
  if(y==1|| y==4)
    if(x<65)
      return wingmap2[x];
    else
      return 65;
  else
    return wingmap[x];

}

void dropPixel(int y, int x, CRGB color) {
  leds[dropMap[y][x]]=color;
}
CRGB dropGetPixel(int y, int x) {
  return leds[dropMap[y][x]];
}
void dropMixPixel(int y, int x, CRGB color,int alpha) {
  dropPixel(y,x,colorMix(dropGetPixel(y,x),color,alpha));
}

CRGB colorMix(CRGB color1, CRGB color2, int alpha) {
  CRGB output;
  output.r=(color1.r*(255-alpha))/255 + (color2.r*alpha)/255;
  output.g=(color1.g*(255-alpha))/255 + (color2.g*alpha)/255;
  output.b=(color1.b*(255-alpha))/255 + (color2.b*alpha)/255;
/*
  output.r=(color1.r*(255-alpha))>>8 | (color2.r*alpha)>>8;
  output.g=(color1.g*(255-alpha))>>8 | (color2.g*alpha)>>8;
  output.b=(color1.b*(255-alpha))>>8 | (color2.b*alpha)>>8;
  */
/*
  Serial.print("r1:");
  Serial.print(color1.r);
  Serial.print(" r2:");
  Serial.print(color2.r);
  Serial.print(" rout:");
  Serial.println(output.r);
  Serial.print("g1:");
  Serial.print(color1.g);
  Serial.print(" g2:");
  Serial.print(color2.g);
  Serial.print(" gout:");
  Serial.println(output.g);
  Serial.print("b1:");
  Serial.print(color1.b);
  Serial.print(" b2:");
  Serial.print(color2.b);
  Serial.print(" bout:");
  Serial.println(output.b);
*/
/*
  r=(r1*(255-alpha))/255 | (r2*alpha)/255;
  g=(g1*(255-alpha))/255 | (g2*alpha)/255;
  b=(b1*(255-alpha))/255 | (b2*alpha)/255;
  */
  return output;
}


//Byte val 2PI Cosine Wave, offset by 1 PI 
//supports fast trig calcs and smooth LED fading/pulsing.
uint8_t const cos_wave[256] PROGMEM =  
{0,0,0,0,1,1,1,2,2,3,4,5,6,6,8,9,10,11,12,14,15,17,18,20,22,23,25,27,29,31,33,35,38,40,42,
45,47,49,52,54,57,60,62,65,68,71,73,76,79,82,85,88,91,94,97,100,103,106,109,113,116,119,
122,125,128,131,135,138,141,144,147,150,153,156,159,162,165,168,171,174,177,180,183,186,
189,191,194,197,199,202,204,207,209,212,214,216,218,221,223,225,227,229,231,232,234,236,
238,239,241,242,243,245,246,247,248,249,250,251,252,252,253,253,254,254,255,255,255,255,
255,255,255,255,254,254,253,253,252,252,251,250,249,248,247,246,245,243,242,241,239,238,
236,234,232,231,229,227,225,223,221,218,216,214,212,209,207,204,202,199,197,194,191,189,
186,183,180,177,174,171,168,165,162,159,156,153,150,147,144,141,138,135,131,128,125,122,
119,116,113,109,106,103,100,97,94,91,88,85,82,79,76,73,71,68,65,62,60,57,54,52,49,47,45,
42,40,38,35,33,31,29,27,25,23,22,20,18,17,15,14,12,11,10,9,8,6,6,5,4,3,2,2,1,1,1,0,0,0,0
};

inline uint8_t fastCosineCalc( uint16_t preWrapVal)
{
  uint8_t wrapVal = (preWrapVal % 255);
  if (wrapVal<0) wrapVal=255+wrapVal;
  return (pgm_read_byte_near(cos_wave+wrapVal)); 
}



