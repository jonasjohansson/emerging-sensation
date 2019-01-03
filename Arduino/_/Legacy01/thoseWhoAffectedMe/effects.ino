

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


uint8_t const linear[256] PROGMEM =
{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,3,3,3,3,3,
4,4,4,4,4,5,5,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,10,10,10,11,11,12,12,12,13,13,14,14,14,15,15,
16,16,17,17,18,18,19,19,20,20,21,21,22,23,23,24,24,25,26,26,27,28,28,29,30,30,31,32,32,33,
34,35,35,36,37,38,39,39,40,41,42,43,44,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,
61,62,63,64,65,66,67,68,70,71,72,73,74,75,77,78,79,80,82,83,84,85,87,89,91,92,93,95,96,98,
99,100,101,102,105,106,108,109,111,112,114,115,117,118,120,121,123,125,126,128,130,131,133,
135,136,138,140,142,143,145,147,149,151,152,154,156,158,160,162,164,165,167,169,171,173,175,
177,179,181,183,185,187,190,192,194,196,198,200,202,204,207,209,211,213,216,218,220,222,225,
227,229,232,234,236,239,241,244,246,249,251,253,254,255
};

unsigned long frameCount=25500;  // arbitrary seed to calculate the three time displacement variables t,t2,t3

void defaultPlasma(int y,int from, int to, int alpha) {
    frameCount=starttime;
    uint16_t t = fastCosineCalc((7 * frameCount)/(150+y*11));  //time displacement - fiddle with these til it looks good...
    uint16_t t2 = fastCosineCalc((5 * frameCount)/(210-y*17)); 
    uint16_t t3 = fastCosineCalc((8 * frameCount)/(230-y*21));

      for (uint8_t x = from; x < to ; x++) {

        //Calculate 3 seperate plasma waves, one for each color channel
/*        uint8_t r = fastCosineCalc(((x << 3) + (t >> 1) + fastCosineCalc((t2 + (y << 3)))))/16+20;// /6+50;
        uint8_t g = fastCosineCalc(((y << 3) + t + fastCosineCalc(((t3 >> 2) + (x << 3)))))/16+20;// /6+50;
        uint8_t b = fastCosineCalc(((y << 3) + t2 + fastCosineCalc((t + x + (g >> 2)))))/16+20;// /6+50;
*/
        uint8_t r = fastCosineCalc(((x << 3) + (t >> 1) + fastCosineCalc((t2 + (y << 3)))))/4+40;
        uint8_t g = fastCosineCalc(((y << 3) + t + fastCosineCalc(((t3 >> 2) + (x << 3)))))/4+40;
        uint8_t b = fastCosineCalc(((y << 3) + t2 + fastCosineCalc((t + x + (g >> 2)))))/4+40;

        r=(r*alpha)/255;
        g=(g*alpha)/255;
        b=(b*alpha)/255;
        
        setPixel(y,x, ((r << 16) | (g << 8) | b));
//        addPixel(y,x, ((r << 16) | (g << 8) | b));
      }

}

void sensorPlasma(int y,int from, int to, int color,int alpha) {
    frameCount=starttime;
    uint16_t t = fastCosineCalc((7 * frameCount)/(150+y*11));  //time displacement - fiddle with these til it looks good...
    uint16_t t2 = fastCosineCalc((5 * frameCount)/(210-y*17)); 
    uint16_t t3 = fastCosineCalc((8 * frameCount)/(230-y*21));


 int r1=(color & 0xFF0000)>>16;
 int g1=(color & 0x00FF00)>>8;
 int b1=(color & 0x0000FF);

      for (uint8_t x = from; x <= to ; x++) {
        uint8_t r = fastCosineCalc(((x << 3) + (t >> 1) + fastCosineCalc((t2 + (y << 3)))))/3;// /6+50;
        uint8_t g = fastCosineCalc(((y << 3) + t + fastCosineCalc(((t3 >> 2) + (x << 3)))))/3;// /6+50;
        uint8_t b = fastCosineCalc(((y << 3) + t2 + fastCosineCalc((t + x + (g >> 2)))))/3;// /6+50;

        
/*     
        uint8_t r = fastCosineCalc(((x << 3) + (t >> 1) + fastCosineCalc((t2 + (y << 3)))))/2;
        uint8_t g = fastCosineCalc(((y << 3) + t + fastCosineCalc(((t3 >> 2) + (x << 3)))))/2;
        uint8_t b = fastCosineCalc(((y << 3) + t2 + fastCosineCalc((t + x + (g >> 2)))))/2;
*/
        r = (r | r1);
        g = (g | g1);
        b = (b | b1);

        //uncomment the following to enable gamma correction

        r=pgm_read_byte_near(linear+r);  
        g=pgm_read_byte_near(linear+g);
        b=pgm_read_byte_near(linear+b);

        mixPixel(y,x, ((r << 16) | (g << 8) | b),alpha);
      }

}


void forwardPlasma(int y,int from, int to, int color, int alpha) {
    frameCount=starttime;
    uint16_t t = frameCount/9;  //time displacement - fiddle with these til it looks good...
    uint16_t t2 =frameCount/7;
    uint16_t t3 = frameCount/11;


 int r1=(color & 0xFF0000)>>16;
 int g1=(color & 0x00FF00)>>8;
 int b1=(color & 0x0000FF);
 
      for (uint8_t x = from; x < to ; x++) {

        uint8_t r = fastCosineCalc(((x << 2)  -t3 + fastCosineCalc((-t2 + (x << 2)))))/2;
        uint8_t g = fastCosineCalc(((x << 1)- t + fastCosineCalc((-t3 + (x << 2)))))/2;
        uint8_t b = fastCosineCalc(((x << 2) - t2 + fastCosineCalc((-t  + (x << 1)))))/2;

        r = (r | r1);
        g = (g | g1);
        b = (b | b1);

/*        r=(r*alpha)/255;
        g=(g*alpha)/255;
        b=(b*alpha)/255;
*/
        //uncomment the following to enable gamma correction

        r=pgm_read_byte_near(linear+r);  
        g=pgm_read_byte_near(linear+g);
        b=pgm_read_byte_near(linear+b);

        mixPixel(y,x, ((r << 16) | (g << 8) | b),alpha);
      }

}



void ravePlasma(int y,int alpha) {
    frameCount++ ; 
    uint16_t t = fastCosineCalc((42 * frameCount)/(500+y*27));  //time displacement - fiddle with these til it looks good...
    uint16_t t2 = fastCosineCalc((35 * frameCount)/(710+y*11)); 
    uint16_t t3 = fastCosineCalc((38 * frameCount)/(930-y*21));

      for (uint8_t x = 0; x < numpixels[y] ; x++) {
/*
        //Calculate 3 seperate plasma waves, one for each color channel
        uint8_t r = fastCosineCalc(((x << 3) + (t >> 1) + fastCosineCalc((t2 + (y << 3)))))/6+63;
        uint8_t g = fastCosineCalc(((y << 3) + t + fastCosineCalc(((t3 >> 2) + (x << 3)))))/6+63;
        uint8_t b = fastCosineCalc(((y << 3) + t2 + fastCosineCalc((t + x + (g >> 2)))))/6+63;
/**/

        uint8_t r = fastCosineCalc(((x << 3) + (t >> 1) + fastCosineCalc((t2 + (y << 3)))));
        uint8_t g = fastCosineCalc(((y << 3) + t + fastCosineCalc(((t3 >> 2) + (x << 3)))));
        uint8_t b = fastCosineCalc(((y << 3) + t2 + fastCosineCalc((t + x + (g >> 2)))));
/**/

        //uncomment the following to enable gamma correction

        r=pgm_read_byte_near(linear+r);  
        g=pgm_read_byte_near(linear+g);
        b=pgm_read_byte_near(linear+b);
        mixPixel(y,x, ((r << 16) | (g << 8) | b),alpha);
      }

}

void theaterChaseRainbow(int y, int from, int to, int alpha) {
  int j=(millis()/100)%256;
  int q=(millis()/50)%3;
  for (uint8_t x = from; x < to ; x++) {
    if((x+q)%3==0)
      mixPixel(y,x, Wheel( 64*y +(x+j*8) % 255),alpha);
    else {
      mixPixel(y,x, 0,alpha);
    }
  }    
}
/*
void colorWipe(int color, int wait)
{
  for (int y=0; y < 4; y++) {
    for (int x=0; x < numpixels[y]; x++) {
      setPixel(y,x, color);
      leds.show();
      delay(wait);
    }
  }
}
*/
/*
void rainbow(int phaseShift, int cycleTime)
{
  int color, wait;

  wait = cycleTime * 1000 / STRIPLEN;
  for (color=NUMCOLORS; color > -1; color-=1) {
    digitalWrite(1, HIGH);
    for (int y=0; y < 4; y++) {
      for (int x=0; x < numpixels[y]; x++) {
        int index = (color + x + y*phaseShift/2) % NUMCOLORS;
        setPixel(y,x, rainbowColors[index]);
      }
    }
    leds.show();;
    delay(wait);
  }
}
*/

/*
void stars(int y, int probability, float fadeSpeed, int color) {
  while(probability>0) {
    if(random(0,100)<probability) {
      setPixel(y, random(0,STRIPLEN),color);
    }
    probability-=100;
  }
//  fadeAll(y,fadeSpeed);
}
*/

void stars(int y, int probability, float fadeSpeed, int color) {
  while(probability>0) {
    if(random(0,100)<probability) {
      starpixels[y][random(0,STRIPLEN)]=color;
    }
    probability-=100;
  }
  starsFade(y,fadeSpeed);
  starsShow(y);
}

void starsReset(int y) {
  for(int x=0;x<numpixels[y];y++) {
    starpixels[y][x]=0;//getPixel(y,x);
  }
}
void starsGet(int y) {
  for(int x=0;x<numpixels[y];y++) {
    starpixels[y][x]=getPixel(y,x);
  }
}

void starsShow(int y) {
  for(int x=0;x<numpixels[y];x++) {
    addPixel(y,x,starpixels[y][x]);
  }
}

void starsFade(int y, float fadeSpeed) {
  int color, r,g,b;
  for(int x=0;x<numpixels[y];x++) {
    color=starpixels[y][x];
    r=(color & 0xFF0000)>>16;
    g=(color & 0x00FF00)>>8;
    b=(color & 0x0000FF);

    r=(int)(r*fadeSpeed);
    g=(int)(g*fadeSpeed);
    b=(int)(b*fadeSpeed);
    starpixels[y][x]=(b) | (g << 8) | (r << 16);
  }
}



