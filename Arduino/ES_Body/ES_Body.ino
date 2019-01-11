/*
   https://github.com/FastLED/FastLED/wiki/Pixel-reference
*/

#include<FastLED.h>

#include "blob.h"

#define NUM_SENSORS 5
#define NUM_STRIPS 26
#define NUM_LEDS 289
#define NUM_BLOBS 5
#define NUM_TENTACLES 9

CRGB leds[NUM_LEDS];

char sensorPins[5] = {19, 18, 17, 23, 22};
char sensorVals[5];
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

int a, b, c, d, e;
int al, bl, cl, dl, el;

int blobData[5][4] = {
  {2, 206, 194, 12},
  {2, 237, 264, 14},
  {1, 100, 0, 10 },
  {2, 31, 15, 16},
  {1, 79, 0, 10}
};

#define BLOB_TIMEOUT 5000
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
  0,  130,  50, 0,
  127,  80,  70, 20,
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
  0,  0,  0, 0,
  110, 0,0,0,
  120,  0,  0, 255,
  128,  130,  130, 255,
  140, 0,0,0,
  255, 0,0,0
};

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
      for (int i = 0; i < len; i++) {
        leds[this->pixels[0][i]] = ColorFromPalette(tentacledark, beat8( 7)+i*10, beatsin8( 7,0,60*this->brightness,0,i*28) );
        leds[this->pixels[1][i]] = ColorFromPalette(tentacledark, beat8( 10)+127+i*10, beatsin8( 7,0,60*this->brightness,0,i*28+28) );
      }
    };

    void lightning() {
      this->fadeToBlackBy(20);
      byte dothue = 230;
      for( int i = 0; i < 4; i++) {
        leds[this->pixels[0][beatsin16(i*5+10,0,this->len)]] |= CHSV(dothue, 255, 255);
        leds[this->pixels[1][beatsin16(i*6+8,0,this->len)]] |= CHSV(dothue, 255, 255);
        dothue += 16;
      }
    }

    void fadeToBlackBy(int by) {
      for (int i = 0; i < len; i++) {
        leds[this->pixels[0][i]]=255*leds[this->pixels[0][i]]/(255-20);
        leds[this->pixels[1][i]]=255*leds[this->pixels[0][i]]/(255-20);
      }

    }
    
    void show() {
      (*this.*currentEffect)();

    }

    
    unsigned long endTime;
    int tempo;
    int type;
    int len;
    int id;
    float brightness;
    void (Tentacle::*currentEffect)() =  &Tentacle::offEffect;

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
      leds[this->pixels[0][0]] = CRGB::Red;
      leds[this->pixels[0][len - 1]] = CRGB::Green;
      if (this->type == 2) {
        leds[this->pixels[1][0]] = CRGB::Blue;
        leds[this->pixels[1][len - 1]] = CRGB::Yellow;

      }
    };

    void offEffect() {
      for (int i = 0; i < len; i++) {
        leds[this->pixels[0][i]] = ColorFromPalette(redyellow, beatsin8( tempo, 0, 255), 255);
        if (this->type == 2)
          leds[this->pixels[1][i]] = ColorFromPalette(yellowwhite,  beatsin8( tempo - 12, 0, 255), 255);
      }
    };

    void onEffect() {
      for (int i = 0; i < len; i++) {
          int index = 192*beatsin8( tempo-10 , 0, 255)/255+cos8(255*(millis()/30+i)/len)/4;
          leds[this->pixels[0][i]] = ColorFromPalette(redyellowmagenta, index,beatsin8( 35, 0, 255,0,40));
        if (this->type == 2)
          leds[this->pixels[1][i]] = ColorFromPalette(redyellowmagenta,index,beatsin8( 35, 0, 255,0,120));
          
      }
      if(millis() > this->endTime) {
        this->node=false;
        this->currentEffect=&Blob::offEffect;
      }
    };
    void show() {
      (*this.*currentEffect)();

    }

    unsigned long endTime;
    int tempo;
    int type;
    int len;
    int id;
    bool node=false;
    void (Blob::*currentEffect)() =  &Blob::offEffect;

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
  tentacleJumps[0][1][1] = 6;
  tentacleJumps[0][2][0] = 8;
  tentacleJumps[0][2][1] = 3;
  tentacleJumps[0][3][0] = 8;
  tentacleJumps[0][3][1] = 3;
  tentacleJumps[0][3][2] = 4;
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
    blobs[i].id=i;
  }
  blobs[0].tempo = 16;
  blobs[1].tempo = 19;
  blobs[2].tempo = 15;
  blobs[3].tempo = 14;
  blobs[4].tempo = 12;

//  blobs[0].currentEffect= &Blob::offEffect;
}
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void (Blob::*currentEffects[5])() =  {&Blob::offEffect, &Blob::offEffect, &Blob::offEffect, &Blob::offEffect, &Blob::offEffect};

/*
EffectList = void (Blob::*currentEffect)() =  &Blob::offEffect;
Blob::EffectsList currentEffects = { blob[0].offAnim };
*/

void loop() {
  for(int i=0;i<NUM_SENSORS;i++) {
    sensorVals[i]=digitalRead(sensorPins[i]);
    if(sensorVals[i]) {
      blobs[i].endTime = millis()+ BLOB_TIMEOUT;
      blobs[i].node=true;
      blobs[i].currentEffect = &Blob::onEffect;
    }
  }
  for(int i=0;i<NUM_BLOBS;i++) {
    for(int j=i+1;j<NUM_BLOBS;j++) {
      for(int k=0;k<3;k++) {
        if(blobs[i].node && blobs[j].node) {
          if(tentacleJumps[i][j][k]<10) {
            tentacles[tentacleJumps[i][j][k]].currentEffect = &Tentacle::lightning;
          }
        }
        else {
          tentacles[tentacleJumps[i][j][k]].currentEffect = &Tentacle::offEffect;
        }
      }
    }
  }
  
  for(int i=0;i<NUM_BLOBS;i++)
    blobs[i].show();
  for(int i=0;i<NUM_TENTACLES;i++)
    tentacles[i].show();
    
//   (blobs[0].penis)();
//    for(int i=0;i<5;i++)
//        blobs[i].offEffect();
//  for (int i = 0; i < 9; i++)
//    tentacles[i].count();
      FastLED.show();
      FastLED.delay(10);

  EVERY_N_MILLISECONDS( 20 ) {
    gHue++;  // slowly cycle the "base color" through the rainbow
  }

}

void hello() {

}
