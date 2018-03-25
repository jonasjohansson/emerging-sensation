uint8_t const linear[256] PROGMEM =
{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,3,3,3,3,3,
4,4,4,4,4,5,5,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,10,10,10,11,11,12,12,12,13,13,14,14,14,15,15,
16,16,17,17,18,18,19,19,20,20,21,21,22,23,23,24,24,25,26,26,27,28,28,29,30,30,31,32,32,33,
34,35,35,36,37,38,39,39,40,41,42,43,44,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,
61,62,63,64,65,66,67,68,70,71,72,73,74,75,77,78,79,80,82,83,84,85,87,89,91,92,93,95,96,98,
99,100,101,102,105,106,108,109,111,112,114,115,117,118,120,121,123,125,126,128,130,131,133,
135,136,138,140,142,143,145,147,149,151,152,154,156,158,160,162,164,165,167,169,171,173,175,
177,179,181,183,185,187,190,192,194,196,198,200,202,204,207,209,211,213,216,218,220,222,225,
227,229,232,234,236,239,241,244,246,249,251,252,253,254
};

void wingsDefault () {
  unsigned long m = timeCode;
  for (int y=1; y<7; y++) {
    for (int x=0; x<NUM_LEDS_PER_STRIP; x++) {
      CRGB color;
      
//      byte index = 185 + cubicwave8(y+m/32+cubicwave8(m/16+cubicwave8(y*3)+cubicwave8(x*5))/4)/8 + cubicwave8(x*8+m/8+cubicwave8(x));
      byte index = 135 + cubicwave8(y*m/128+cubicwave8(m/64+cubicwave8(y*3))/4)/8 + (float)cubicwave8(x+m/64+cubicwave8(m/64))*(0.2+fSensorValue*.8);
      byte brightness = sin8(x*8+cubicwave8(m/32+cubicwave8(x*7))+(cubicwave8(cubicwave8(m/32+y*8)/16)/4));
      color = CHSV(index,255,brightness);//constrain(brightness*(fSensorValue*.3+.7),0,255));
      setPixel(y,x,color);
    }
  }
}


void wingsOverlay2 () {
  unsigned long m = timeCode;
  for (int y=1; y<7; y++) {
    for (int x=0; x<NUM_LEDS_PER_STRIP; x++) {
      CRGB color;
      byte index = explodeHue + (cubicwave8(y+cubicwave8(cubicwave8(y*3))/4)/2 + cubicwave8(x*4+cubicwave8(x))/4)*explodeVar/255;
      byte brightness= 255;
      color = CHSV(index,explodeSat,brightness);
//      setPixel(y,x,color);
      mixPixel(y,x,color,constrain(map(charger2,940,1020,0,255),0,255));

    }
  }
}

void dropDefault () {
  unsigned long m = timeCode;
  for (int y=0; y<DROP_Y; y++) {
    for (int x=0; x<DROP_X; x++) {
      CRGB color;
      byte index = dropColor[0][y] - cubicwave8(y+m/32+cubicwave8(m/16+cubicwave8(y*3)+cubicwave8(x*5))/4)/8 + cubicwave8(x*8+m/8+cubicwave8(x))/8;
      byte brightness = dropColor[2][y]*(sin8(x*18+cubicwave8(m/32+cubicwave8(x*18))+(cubicwave8(cubicwave8(m/32+y*8)/16)/4-8)))/255;
      color = CHSV(index,dropColor[1][y],brightness);
      dropPixel(y,x,color);

    }
  }
}

void dropOverlay () {
  unsigned long m = timeCode;
  int test;
  for (int y=0; y<DROP_Y; y++) {
    for (int x=0; x<DROP_X; x++) {
      CRGB color;
      byte index = 16 - charger/32 - cubicwave8(y*m/32+cubicwave8(m/32+cubicwave8(y*3))/4)/8 + cubicwave8(x*8+m/2+cubicwave8(x))/16;
      byte brightness = cubicwave8(x*18+cubicwave8(m/64+cubicwave8(x*18))+y*(cubicwave8(cubicwave8(m/64+y*8)/16)/4-8))*(1024-charger)/1024
                        + cubicwave8(x*18+cubicwave8(m/8+cubicwave8(x*18))+(cubicwave8(cubicwave8(m/24+y*8)/13)+y*m/32))*(charger)/1024;
      color = CHSV(index,255,brightness);
      if(sensorValue)
        dropMixPixel(y,x,color,constrain(sensorValue/2+map(charger,0,1023,0,255),0,255));
        
//      dropMixPixel(y,x,color,map(sensorValue/2,0,127,0,255));
    }
  }
}

void dropOverlay2 () {
  unsigned long m = timeCode;
  for (int y=0; y<DROP_Y; y++) {
    for (int x=0; x<DROP_X; x++) {
      CRGB color;
      byte index = explodeHue + (cubicwave8(y+cubicwave8(cubicwave8(y*3))/4)/2 + cubicwave8(x*4+cubicwave8(x))/4)*explodeVar/255;

      byte brightness= 255;
      color = CHSV(index,explodeSat,brightness);
//      dropPixel(y,x,color);    
      dropMixPixel(y,x,color,constrain(map(charger2,800,1000,0,255),0,255));
    }
  }
}

void photoOp () {
  unsigned long m = 12986;
  for (int y=1; y<7; y++) {
    for (int x=0; x<NUM_LEDS_PER_STRIP; x++) {
      CRGB color;
      
//      byte index = 185 + cubicwave8(y+m/32+cubicwave8(m/16+cubicwave8(y*3)+cubicwave8(x*5))/4)/8 + cubicwave8(x*8+m/8+cubicwave8(x));
      byte index = 135 + cubicwave8(y*m/128+cubicwave8(m/64+cubicwave8(y*3))/4)/8 + cubicwave8(x+m/64+cubicwave8(m/64));
      byte brightness = sin8(x*8+cubicwave8(m/32+cubicwave8(x*7))+(cubicwave8(cubicwave8(m/32+y*8)/16)/4));
      color = CHSV(index,255,brightness);
      setPixel(y,x,color);
    }
  }
  for (int y=0; y<DROP_Y; y++) {
    for (int x=0; x<DROP_X; x++) {
      CRGB color=CHSV(30,160,255);
      dropPixel(y,x,color);
    }
  }
}


unsigned long frameCount=25500;  // arbitrary seed to calculate the three time displacement variables t,t2,t3

void ravePlasma(int y) {

    frameCount++ ; 
    uint16_t t = fastCosineCalc((42 * frameCount)/(500+y*27));  //time displacement - fiddle with these til it looks good...
    uint16_t t2 = fastCosineCalc((35 * frameCount)/(710+y*11)); 
    uint16_t t3 = fastCosineCalc((38 * frameCount)/(930-y*21));

      for (uint8_t x = 0; x < NUM_LEDS_PER_STRIP; x++) {

        uint8_t r = fastCosineCalc(((x << 3) + (t >> 1) + fastCosineCalc((t2 + (y << 3)))));
        uint8_t g = fastCosineCalc(((y << 3) + t + fastCosineCalc(((t3 >> 2) + (x << 3)))));
        uint8_t b = fastCosineCalc(((y << 3) + t2 + fastCosineCalc((t + x + (g >> 2)))));

        //uncomment the following to enable gamma correction

        r=pgm_read_byte_near(linear+r);  
        g=pgm_read_byte_near(linear+g);
        b=pgm_read_byte_near(linear+b);
        setPixel(y,x, CRGB(r,g,b));
      }

}


void setAll(CHSV c) {
  for (int x=0; x<NUM_LEDS_PER_STRIP; x++) {
    for (int y=0; y<NUM_STRIPS; y++) {
      setPixel(y,x,c);
    }
  }
  LEDS.show();
}

void test() {
  for (int x=0; x<NUM_LEDS_PER_STRIP; x++) {
    if(x<48)
      dropPixel(x/6,x%6,CRGB::Red);
    for (int y=1; y<NUM_STRIPS; y++) {
      setPixel(y,x,CRGB::Red);
    }
      LEDS.show();
      delay(100);
  }
  for (int x=0; x<NUM_LEDS_PER_STRIP; x++) {
    if(x<48)
      dropPixel(x/6,x%6,CRGB::Green);
    for (int y=1; y<NUM_STRIPS; y++) {
      setPixel(y,x,CRGB::Green);
    }
      LEDS.show();
      delay(100);
  }
  for (int x=0; x<NUM_LEDS_PER_STRIP; x++) {
    if(x<48)
      dropPixel(x/6,x%6,CRGB::Blue);
    for (int y=1; y<NUM_STRIPS; y++) {
      setPixel(y,x,CRGB::Blue);
    }
      LEDS.show();
      delay(100);
  }
}

void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

void confetti() 
{
  fadeToBlackBy( leds, NUM_LEDS, 1);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 1);
  for(int y=0;y<NUM_STRIPS;y++) {
    int pos = beatsin16(13,0,NUM_LEDS_PER_STRIP);
    addPixel(y,pos,CHSV( gHue, 255, 192));
  }
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for(int y=0;y<NUM_STRIPS;y++) {
    for( int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
      setPixel(y,i,ColorFromPalette(palette, gHue+(i*2)+(y*4), beat-gHue+(i*10)+(y+20)));
    }
  }
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for(int y=0;y<NUM_STRIPS;y++) {
    for( int i = 0; i < 8; i++) {
      orPixel(y,beatsin16(i+7+y,0,NUM_LEDS_PER_STRIP),CHSV(dothue, 200, 255));
      dothue += 32;
    }
  }
}


void theaterChase(CRGB c,int alpha) {
  int j=(millis()/100)%256;
  int q=(millis()/50)%3;
  for(int y=1;y<7;y++)
  for (uint8_t x = 0; x < NUM_LEDS_PER_STRIP ; x++) {
    if((x+q)%3==0)
      mixPixel(y,x, c,alpha);
    else {
      mixPixel(y,x, CRGB::Black,alpha);
    }
  }    
}


void theaterChase2(CRGB c,CRGB c2,int alpha) {
  int j=(millis()/100)%256;
  int q=(millis()/50)%6;
  for(int y=1;y<7;y++)
  for (uint8_t x = 0; x < NUM_LEDS_PER_STRIP ; x++) {
    if((x+q)%6==0) {
      mixPixel(y,x, c,alpha);
    } else if((x+q)%6==3) {
      mixPixel(y,x, c2,alpha);
    } else {
      mixPixel(y,x, CRGB::Black,alpha);
    }
  }    
}

void newExplode() {
    switch(random(0,5)) {
      case 0:
        explodeHue = 85;
        explodeSat = 255;
        explodeVar = 127;
        break;
      case 1: 
        explodeHue = 210;
        explodeSat = 255;
        explodeVar = 127;
        break;
      case 2: 
        explodeHue = 0;
        explodeSat = 180;
        explodeVar = 0;
        break;
      case 3: 
        explodeHue = 160;
        explodeSat = 140;
        explodeVar = 127;
        break;
      case 4:
        explodeHue = 150;
        explodeSat = 255;
        explodeVar = 60;
        break;
      case 5:
        explodeHue = 0;
        explodeSat = 255;
        explodeVar = 40;
        break;
    }
  }
