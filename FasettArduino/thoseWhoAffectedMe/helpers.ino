inline uint8_t fastCosineCalc( uint16_t preWrapVal)
{
  uint8_t wrapVal = (preWrapVal % 255);
  if (wrapVal<0) wrapVal=255+wrapVal;
  return (pgm_read_byte_near(cos_wave+wrapVal)); 
}


void setPixel(int y, int x, int c) {
  leds.setPixel((y+4)*STRIPLEN+pixelArray[y][x],c);
}


void mixPixel(int y, int x, uint32_t color,int alpha) {
  setPixel(y,x,colorMix(getPixel(y,x),color,alpha));
}
void addPixel(int y, int x, uint32_t color) {
  setPixel(y,x,colorAdd(getPixel(y,x),color));
}

uint32_t getPixel(int y, int x) {
  return leds.getPixel((y+4)*STRIPLEN+pixelArray[y][x]);
}


uint32_t colorMix(uint32_t color1, uint32_t color2, int alpha) {
  int r,r1,r2,g,g1,g2,b,b1,b2;
  r1=(color1 & 0xFF0000)>>16;
  g1=(color1 & 0x00FF00)>>8;
  b1=(color1 & 0x0000FF);
  r2=(color2 & 0xFF0000)>>16;
  g2=(color2 & 0x00FF00)>>8;
  b2=(color2 & 0x0000FF);
  r=(r1*(255-alpha))>>8 | (r2*alpha)>>8;
  g=(g1*(255-alpha))>>8 | (g2*alpha)>>8;
  b=(b1*(255-alpha))>>8 | (b2*alpha)>>8;

/*
  r=(r1*(255-alpha))/255 | (r2*alpha)/255;
  g=(g1*(255-alpha))/255 | (g2*alpha)/255;
  b=(b1*(255-alpha))/255 | (b2*alpha)/255;
  */
  return Color(r,g,b);
}

uint32_t colorAdd(uint32_t color1, uint32_t color2) {
  int r,r1,r2,g,g1,g2,b,b1,b2;
  r1=(color1 & 0xFF0000)>>16;
  g1=(color1 & 0x00FF00)>>8;
  b1=(color1 & 0x0000FF);
  r2=(color2 & 0xFF0000)>>16;
  g2=(color2 & 0x00FF00)>>8;
  b2=(color2 & 0x0000FF);
  r=r1|r2;
  g=g1|g2;
  b=b1|b2;

/*
  r=(r1*(255-alpha))/255 | (r2*alpha)/255;
  g=(g1*(255-alpha))/255 | (g2*alpha)/255;
  b=(b1*(255-alpha))/255 | (b2*alpha)/255;
  */
  return Color(r,g,b);
}

int colorBlend(uint32_t color1, uint32_t color2) {
  int r,r1,r2,g,g1,g2,b,b1,b2;
  r1=(color1 & 0xFF0000)>>16;
  g1=(color1 & 0x00FF00)>>8;
  b1=(color1 & 0x0000FF);
  r2=(color2 & 0xFF0000)>>16;
  g2=(color2 & 0x00FF00)>>8;
  b2=(color2 & 0x0000FF);
//  r=((r2-r1)*s)+r1;
//  g=((g2-g1)*s)+g1;
//  b=((b2-b1)*s)+b1;
  r=r1 | r2;
  g=g1 | g2;
  b=b1 | b2;
  return Color(r,g,b);
}

uint32_t colorFade(uint32_t color, int fade) {
  uint8_t r,g,b;
    r=(color >> 16);
    g=(color >>  8);
    b=(color);
    r=(uint8_t)r*(long)fade/255L;
    g=(uint8_t)g*(long)fade/255L;
    b=(uint8_t)b*(long)fade/255L;
  return Color(r,g,b);
//  return strip.Color(linear[r],linear[g],linear[b]);
}

uint32_t colorFadeLin(uint32_t color, int fade) {
  uint8_t r,g,b;
    r=(color >> 16);
    g=(color >>  8);
    b=(color);
    r=(uint8_t)r*(long)fade/255L;
    g=(uint8_t)g*(long)fade/255L;
    b=(uint8_t)b*(long)fade/255L;
  return Color(linear[r],linear[g],linear[b]);
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

bool in_array(int needle, int haystack[]) {
  for(uint i=0;i<sizeof(haystack);i++) {
    if(haystack[i]==needle)
      return true;
  }
  return false;
}


int colorMultiply(int x, int y) {
        int xb = (x) & 0xFF;
        int yb = (y) & 0xFF;
        int b = (xb * yb) / 255;

        int xg = (x >> 8) & 0xFF;
        int yg = (y >> 8) & 0xFF;
        int g = (xg * yg) / 255;

        int xr = (x >> 16) & 0xFF;
        int yr = (y >> 16) & 0xFF;
        int r = (xr * yr) / 255;


        return (b) | (g << 8) | (r << 16);
    }


void fadeAll(int y, float fadeSpeed) {
  int color, r,g,b;
  for(int x=0;x<numpixels[y];x++) {
    color=getPixel(y,x);
    r=(color & 0xFF0000)>>16;
    g=(color & 0x00FF00)>>8;
    b=(color & 0x0000FF);
    setPixel(y,x,Color((int)(r*fadeSpeed),(int)(g*fadeSpeed),(int)(b*fadeSpeed)));
  }
}

/// Helper functions
/*
void setPixel(int num, uint32_t color) {
  strip.setPixelColor(num,color);
}

void setPixel(int s, int num, uint32_t color) {
    strip.setPixelColor(s*STRIPLEN+num,color);
}

uint32_t getPixel(int n) {
  return strip.getPixelColor(n);
}

uint32_t getPixel(int s, int num) {
    strip.getPixelColor(s*STRIPLEN+num);
}

void addPixel(int num, uint32_t color) {
  strip.setPixelColor(num,colorBlend(getPixel(num),color,.5));
}


void moveAll() {
  for(int i=0;i<NUMSTRIPS;i++) {
    for(int x=STRIPLEN-1; x > 0 ; x--) {
      setPixel(i,x,getPixel(i,x-1));
    }
  }
}


void fadeAll(float fadeSpeed) {
  uint32_t color;
  uint8_t r,g,b;
  for(int x=0;x<strip.numPixels();x++) {
    color=getPixel(x);
    r=(color >> 16);
    g=(color >>  8);
    b=(color);
    setPixel(x,strip.Color(r*fadeSpeed,g*fadeSpeed,b*fadeSpeed));
  }
}

void setAll(uint32_t color) {
  for(int i=0;i<strip.numPixels();i++)
    setPixel(i,color);
}




uint32_t colorBlend(uint32_t color1, uint32_t color2) {
  int r,r1,r2,g,g1,g2,b,b1,b2;
  r1=(color1 & 0xFF0000)>>16;
  g1=(color1 & 0x00FF00)>>8;
  b1=(color1 & 0x0000FF);
  r2=(color2 & 0xFF0000)>>16;
  g2=(color2 & 0x00FF00)>>8;
  b2=(color2 & 0x0000FF);
//  r=((r2-r1)*s)+r1;
//  g=((g2-g1)*s)+g1;
//  b=((b2-b1)*s)+b1;
  r=r1 | r2;
  g=g1 | g2;
  b=b1 | b2;
  return strip.Color(r,g,b);
}

uint32_t colorBlend(uint32_t color1, uint32_t color2, float s) {
  int r,r1,r2,g,g1,g2,b,b1,b2;
  r1=(color1 & 0xFF0000)>>16;
  g1=(color1 & 0x00FF00)>>8;
  b1=(color1 & 0x0000FF);
  r2=(color2 & 0xFF0000)>>16;
  g2=(color2 & 0x00FF00)>>8;
  b2=(color2 & 0x0000FF);
  r=((r2-r1)*s)+r1;
  g=((g2-g1)*s)+g1;
  b=((b2-b1)*s)+b1;
  return strip.Color(r,g,b);
}

uint32_t randomColor() {
      switch(random(0,5)) {
        case 0:
          return strip.Color(255,0,0);
        case 1:
          return strip.Color(255,255,0);
        case 2:
          return strip.Color(0,255,0);
        case 3:
          return strip.Color(0,255,255);
        case 4:
          return strip.Color(0,0,255);
        case 5:
          return strip.Color(255,0,255);
      }        

}
*/
