/*
   https://github.com/FastLED/FastLED/wiki/Pixel-reference
*/

#include<FastLED.h>

#define NUM_SENSORS 5
#define NUM_STRIPS 26
#define NUM_LEDS 289
#define NUM_BLOBS 5
#define NUM_TENTACLES 9

CRGB leds[NUM_LEDS];

char sensorPins[5] = {19, 18, 17, 23, 22};
char sensorVals[5];
unsigned long sensorTime[5];
char sensorStage[5]={1,1,1,1,1};

#define SENSOR_TIMEOUT 2000

#define TENTACLE_FADE 5000;

uint8_t gHue = 0; // rotating "base color" used by many of the patterns

int a, b, c, d, e;
int al, bl, cl, dl, el;

const int blobData[5][4] = {
  {2, 206, 194, 12},
  {2, 237, 264, 14},
  {1, 100, 0, 10 },
  {2, 31, 15, 16},
  {1, 79, 0, 10}
};

float blobBrightness[5]= {0.8,0.8,1,0.8,1};
int blobTempo[5]={16,17,20,12,13};

const int blobTimes[4] {
  4000, // on
  4000, // fadeout
  3000, // black
  2000 // fadein
};

/*
  { 79, 20, 2 },  // 6 small ball 2 inside
  { 99, 20, 2 },  // 7 small ball 3 inside
*/

int tentacleData[9][4] {
  {0, 70, 9, 1},
  {9, 278, 6, 0},
  {62, 141, 8, 1},
  {119, 156, 9, 1},
  {128, 149, 7, 0},
  {135, 183, 6, 1},
  {165, 284, 5, 1},
  {170, 189, 5, 0},
  {175, 229, 8, 0}
};
float tentacleBrightness[9] { 1.2,1.5,2,.7,1,1,1,1,2 };

int tentacleJumps[5][5][3];

TBlendType    currentBlending;
CRGBPalette16 redyellow;
CRGBPalette16 yellowwhite;
CRGBPalette16 redyellowmagenta;
CRGBPalette16 tentacledark;
CRGBPalette16 lightningcolor;

DEFINE_GRADIENT_PALETTE( redyellow1 ) {
  0,  255,  0, 0,
  15,  255,  0, 0,
  127,  128,  128, 0,
  240,  255,  0, 0,
  255,  255,  0, 0
};

DEFINE_GRADIENT_PALETTE( yellowwhite1 ) {
  0,  130,  40, 0,
  127,  80,  60, 20,
  255,  130,  50, 0
};

DEFINE_GRADIENT_PALETTE( redyellowmagenta1 ) {
  0,  255,  0, 0,
  64,  127,  127, 0,
  128, 255,0,0,
  192,  255,  0, 90,
  255,  255,  0, 0
};

DEFINE_GRADIENT_PALETTE( tentacledark1 ) {
  0,  100, 0, 20,
  32,20,0,0,
  64, 120,0,0,
  128,100,0,30,
  160,0,0,0,
  192, 60,0,40,
  255,  100, 0, 20
};
DEFINE_GRADIENT_PALETTE( lightningcolor1 ) {
  0,  255,  10, 0,
  50, 255 , 50,0,
  100,  255,  0, 40,
  150,  30,  0, 70,
  200, 130,80,80,
  255, 255,255,255
};


void s(byte pin, int val){
  Serial.print("B"+String(pin));
  Serial.print(' ');
  Serial.println(val);
}

class Tentacle {
  public:
    void init(int start1, int start2, int len, int inverse) {
      this->len = len;
      for (int i = 0; i < len; i++) {
        this->pixels[0][i] = i + start1;
        if (inverse)
          this->pixels[1][i] = start2 + len - 1 - i;
        else
          this->pixels[1][i] = i + start2;
      }

    };

    void count() {
      for (int i = 0; i < this->len; i++) {
        leds[this->pixels[0][i]] = CRGB::Red;
        FastLED.show();
        FastLED.delay(50);
        leds[this->pixels[0][i]] = CRGB::Black;
        leds[this->pixels[1][i]] = CRGB::Blue;
        FastLED.show();
        FastLED.delay(50);
        leds[this->pixels[1][i]] = CRGB::Black;
      }
    };

    void offEffect() {
      this->fadeToBlackBy(1);
      for (int i = 0; i < len; i++) {
        leds[pixels[0][i]] += ColorFromPalette(tentacledark, beat8( 7)+i*10, beatsin8( 7,0,60*this->brightness,0,i*28) );
        leds[pixels[1][i]] += ColorFromPalette(tentacledark, beat8( 10)+127+i*10, beatsin8( 7,0,60*this->brightness,0,i*28+28) );
      }
      renderStars();
    };

    void renderStars() {
      if(random(0,1000)>995) {
        stars[random(0,1)][random(0,len)]=ColorFromPalette(redyellow, random(0,255),255);
      }
      
      for(int i=0;i<len;i++) {
        stars[0][i].fadeToBlackBy(1);
        stars[1][i].fadeToBlackBy(1);
        leds[pixels[0][i]]|=stars[0][i];
        leds[pixels[1][i]]|=stars[1][i];
      }
    }
    
    void lightning(int fade) {
      fadeToBlackBy(20);
      byte index = 0+(len-5)*15;
      for( int i = 0; i < 4; i++) {
        leds[pixels[0][beatsin16(i*3+len,0,len)]] |= ColorFromPalette(lightningcolor,index, fade);
        leds[pixels[1][beatsin16(i*4+len,0,len)]] |= ColorFromPalette(lightningcolor,index, fade);
        index += 35;
      }
    }

    void fadeToBlackBy(int by) {
      for (int i = 0; i < len; i++) {
        leds[pixels[0][i]]=255*leds[this->pixels[0][i]]/(255-by);
        leds[pixels[1][i]]=255*leds[this->pixels[0][i]]/(255-by);
      }

    }
    
    void show() {
      switch(state) {
        case 0:
          this->offEffect();
          break;
        case 1:
          this->lightning(255);
          break;
        case 2:
          if(millis() > this->endTime) {
            this->state=0;
            break;
          }
          int fade = (float)255*(this->endTime-millis())/TENTACLE_FADE;
          this->lightning(fade);
          break;
      }

    }

    
    unsigned long endTime;
    CRGB stars[2][9];
    int state=0;
    int tempo;
    int type;
    int len;
    int id;
    float brightness;

  private:
    int pixels[2][9];
};


class Blob {
  public:
    void init(int type, int inStart, int outStart, int len) {
      this->type = type;
      this->len = len;
      for (int i = 0; i < len; i++) {
        this->pixels[0][i] = i * 2 + inStart;
        if (type == 2)
          this->pixels[1][i] = i + outStart;
      }
    };
    void test() {
      leds[pixels[0][0]] = CRGB::Red;
      leds[pixels[0][len - 1]] = CRGB::Green;
      if (this->type == 2) {
        leds[pixels[1][0]] = CRGB::Blue;
        leds[pixels[1][len - 1]] = CRGB::Yellow;

      }
    };

    void setAll( CRGB color ) {
      for (int i = 0; i < len; i++) {
        leds[pixels[0][i]] = color;
        leds[pixels[1][i]] = color;
      }
    }

    void offEffect( byte fade) {
      for (int i = 0; i < len; i++) {
        leds[pixels[0][i]] = ColorFromPalette(redyellow, beatsin8( tempo, 0, 255), (float)fade*brightness,LINEARBLEND);
        if (type == 2)
          leds[pixels[1][i]] = ColorFromPalette(yellowwhite,  beatsin8( tempo - 12, 0, 255), (float)fade*brightness,LINEARBLEND);
      }
    };

    void onEffect(byte fade) {
      for (int i = 0; i < len; i++) {
          int index = 192*beatsin8( tempo-10 , 0, 255)/255+cos8(255*(millis()/30+i)/len)/4;
          leds[pixels[0][i]] = ColorFromPalette(redyellowmagenta, index,beatsin8( 85+tempo*2, 0, fade,0,40),LINEARBLEND);
        if (type == 2)
          leds[pixels[1][i]] = ColorFromPalette(redyellowmagenta,index,beatsin8( 50+tempo*2, 0, fade,0,120),LINEARBLEND);
          
      }
    };
    void show() {
      float fade;
      switch(state) {
        case 0:
          this->offEffect(255);
          break;
        case 1:               // on
          if(millis() > this->endTime) {
            this->state++;
            this->endTime=millis()+blobTimes[1];
            break;
          }
          this->onEffect(255);
          break;
        case 2:               // fadeout
          if(millis() > this->endTime) {
            this->state++;
            this->endTime=millis()+blobTimes[2];
            break;
          }
          fade = (float)255*(this->endTime-millis())/blobTimes[1];
          this->onEffect((byte)fade);
          break;
        case 3:               // black
          if(millis() > this->endTime) {
            this->state++;
            this->endTime=millis()+blobTimes[3];
            break;
          }
          this->setAll(CRGB::Black);
          break;
        case 4:               // fadein
          if(millis() > this->endTime) {
            this->state=0;
            break;
          }
          fade = (float)255*(this->endTime-millis())/blobTimes[3];
          this->offEffect((byte) 255-fade);
          break;

        
      }

    };

    unsigned long endTime;
    int state=0;
    int tempo;
    int type;
    int len;
    int id;
    float brightness;

  private:
    int pixels[2][16];

};


Blob blobs[5];
Tentacle tentacles[9];


void setup() {
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, 7>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.show();

  redyellow = redyellow1;
  yellowwhite = yellowwhite1;
  redyellowmagenta = redyellowmagenta1;
  tentacledark = tentacledark1;
  lightningcolor = lightningcolor1;
  currentBlending = LINEARBLEND;


  for (int i = 0; i < NUM_SENSORS; i++) {
    pinMode(sensorPins[i], INPUT);
  }
  for (int i = 0; i < NUM_TENTACLES; i++) {
    tentacles[i].init(tentacleData[i][0], tentacleData[i][1], tentacleData[i][2], tentacleData[i][3]);
    tentacles[i].brightness = tentacleBrightness[i];
    tentacles[i].id=i;

  }

  for (int i = 0; i < NUM_BLOBS; i++) {
    for (int j = 0; j < NUM_BLOBS; j++) {
      for (int k = 0; k < 3; k++) {
        tentacleJumps[i][j][k] = 10;
      }
    }
  }

  tentacleJumps[0][1][0] = 8;
  tentacleJumps[0][2][0] = 8;
  tentacleJumps[0][2][1] = 3;
  tentacleJumps[0][3][0] = 8;
  tentacleJumps[0][3][1] = 3;
//  tentacleJumps[0][3][2] = 4;
  tentacleJumps[0][4][0] = 7;
  tentacleJumps[0][4][1] = 5;
  tentacleJumps[0][4][2] = 2;

  tentacleJumps[1][2][0] = 6;
  tentacleJumps[1][3][0] = 1;
  tentacleJumps[1][4][0] = 4;
  tentacleJumps[1][4][1] = 2;

  tentacleJumps[2][3][0] = 4;
  tentacleJumps[2][4][0] = 4;
  tentacleJumps[2][4][1] = 2;

  tentacleJumps[3][4][0] = 0;

  for (int i = 0; i < NUM_BLOBS; i++) {
    blobs[i].init(blobData[i][0], blobData[i][1], blobData[i][2], blobData[i][3]);
    blobs[i].brightness = blobBrightness[i];
    blobs[i].tempo = blobTempo[i];
    blobs[i].id=i;
    s(i,1);
  }

}
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))


/*
EffectList = void (Blob::*currentEffect)() =  &Blob::offEffect;
Blob::EffectsList currentEffects = { blob[0].offAnim };
*/

void loop() {

  for(int i=0;i<NUM_SENSORS;i++) {
    sensorVals[i]=digitalRead(sensorPins[i]);
    if(sensorVals[i] && (millis() > sensorTime[i])) {
      sensorTime[i] = millis() + SENSOR_TIMEOUT;
      sensorStage[i]++;
      if(sensorStage[i]>4)
        sensorStage[i]=1;
      blobs[i].endTime = millis()+ blobTimes[0];
      blobs[i].state=1;
      s(i,sensorStage[i]);
    }
  }
  for(int i=0;i<NUM_TENTACLES;i++) {
    if(tentacles[i].state==1) {
      tentacles[i].state=2;
      tentacles[i].endTime=millis()+ TENTACLE_FADE;
    }
  }
  for(int i=0;i<NUM_BLOBS;i++) {
    for(int j=i+1;j<NUM_BLOBS;j++) {
      if(blobs[i].state==1 && blobs[j].state==1) {
        for(int k=0;k<3;k++) {
          if(tentacleJumps[i][j][k]<10) {
            tentacles[tentacleJumps[i][j][k]].state=1;
          }
        }
      }
    }
  }
  
  for(int i=0;i<NUM_BLOBS;i++)
    blobs[i].show();
  for(int i=0;i<NUM_TENTACLES;i++) {
    tentacles[i].show();
  }
/*  for (int i = 0; i < 9; i++)
    tentacles[i].count();*/
      FastLED.show();
      FastLED.delay(10);
                               // unomment this for photo op
/*
  EVERY_N_SECONDS (11) {
    FastLED.delay(10000);
  }
  */

  
  EVERY_N_MILLISECONDS( 20 ) {
    gHue++;  // slowly cycle the "base color" through the rainbow
  }

}

void hello() {

}
