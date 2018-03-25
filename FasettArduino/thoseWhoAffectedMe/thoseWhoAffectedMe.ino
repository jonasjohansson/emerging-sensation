/*

  Required Connections
  --------------------
    led strip 0 = Orange / Orange White
    led strip 1 = Blue / Blue White
    led strip 2 = Green / Green White
    led strip 3 = Brown / Brown White

    sensorPin[0] = Brown
    sensorPin[1] = Brown White
    sensorPin[2] = Green
    sensorPin[3] = Green White
    sensorPin[4] = Blue
    sensorPin[5] = Blue White
    sensorPin[6] = Orange
    sensorPin[7] = Orange White


*/

#include <OctoWS2811.h>

#define STRIPLEN 140  // all of the following params need to be adjusted for screen size
#define NUMSTRIPS 8  // LED_LAYOUT assumed 0 if NUMSTRIPS > 8

#define Color(r, g, b) (((r) << 16) | ((g) << 8) | (b))

DMAMEM int displayMemory[STRIPLEN*6];
int drawingMemory[STRIPLEN*6];
const int config = WS2811_GRB | WS2811_800kHz;
OctoWS2811 leds(STRIPLEN, displayMemory, drawingMemory, config);

//
// Pixel stuff
// 
int numpixels[4]={126,108,135,114};
int deadpixels[4]={125,108,333,333};

int availablePixels[4][STRIPLEN];
int pixelArray[4][STRIPLEN];

//
// Animation settings
//
unsigned long starttime;


int animColor[4];
int animState[4];
uint animTimer[4];
int animPos[4];
uint plasmaTimer[4];
int plasmaState[4]={1,1,1,1};
int raveState;

uint32_t starpixels[4][STRIPLEN];

//
// Sensor stuff
// 

#define NUMSENSORS 8
int sensorValue[NUMSENSORS];
int sensorState[NUMSENSORS]={1,1,1,1,1,1,1,1};
uint sensorTimer[NUMSENSORS];
uint32_t sensorColor[NUMSENSORS];
int sensorPos[NUMSENSORS][2]={{0,8},{0,26},
                           {1,9},{1,28},
                           {2,9},{2,28},
                           {3,8},{3,25}};
int sensorPins[8]={3,0,1,19,22,23,18,17};
int sensorThreshold=10;

#define OFF 0
#define ON 1
#define FADEIN 2
#define FADEOUT 3
#define GLITTER 4
#define RAVE1 5
#define RAVE2 6
#define RAVE3 7
#define RAVE4 8

//
// Effect helpers
//
//#define NUMCOLORS 300
//int rainbowColors[NUMCOLORS];


//
// ===== SETTINGS ======
// Change these!
// 

#define NUMCOLORS 10

uint32_t colorList[]={Color(0,255,140),Color(0,140,255),
                    Color(130,255,0),Color(255,255,0),
                    Color(0,230,60),Color(255,60,0),
                    Color(40,40,255),Color(150,0,255),
                    Color(255,100,130),Color(255,127,0)};



/*
uint32_t colorList[]={};
*/

int animFadeIn=2000;
int animLength=6000;
int animGlitter=3000;
int animFadeOut=3000;
int plasmaTimout=1000;
int plasmaFadeIn=5000;
int sensorTimeout=10500;
int sensorFadeIn=2500;
int raveLength1=1000;
int raveLength2=9000;
int raveLength3=3000;
int raveLength4=6000;
float fadeAmount=.9999999;
float probMultiply=1;
int touchTimeout=10000;
int touchTimer=millis()+touchTimeout;


int raveTotal=raveLength1+raveLength2+raveLength3+raveLength4;

void setup() {

  Serial.begin(9600);


  // 
  // Setting up pixels
  //
  for(int y=0;y<4;y++) {
    int partlength=numpixels[y]/3;
    
    int count=0;
    for(int i=0;i<numpixels[y];i++) {
      if(i!=deadpixels[y]) {
        availablePixels[y][count]=i;
        count++;
      }
    }
    numpixels[y]=count;

    for(int i=0;i<partlength;i++) {
      pixelArray[y][i*3]=availablePixels[y][i];
    }
    for(int i=0;i<partlength;i++) {
      pixelArray[y][i*3+1]=availablePixels[y][partlength*2-i-1];
    }
    for(int i=0;i<partlength;i++) {
      pixelArray[y][i*3+2]=availablePixels[y][i+partlength*2];
    } 



  }
    // special exception for wing2
//      numpixels[2]--;
    
    // end
    

  leds.begin();
  
  // 
  // Setting starting colors
  //
  for(int i=0;i<NUMSENSORS;i++) {
    sensorColor[i]=colorList[i];
  }
/*  
  // 
  // Creating rainbow array
  //
  for (int i=0; i<NUMCOLORS; i++) {
    int hue = (360*i)/NUMCOLORS;
    int saturation = 100;
    int lightness =20;
    // pre-compute the 180 rainbow colors
    rainbowColors[i] = makeColor(hue, saturation, lightness);
  }
  */
  // 
  // Setting up sensor pins
  //
  for(int i=0;i<8;i++) {
    pinMode(sensorPins[i], INPUT);
  }
  
}


void loop() {
  starttime=millis();


  // 
  // Default plasma function
  //

  for(int y=0;y<4;y++) {
    defaultPlasma(y, 0, numpixels[y],255);
  }

  // 
  // Draw sensors
  //

  for(int i=0;i<NUMSENSORS;i++) {
    if(sensorState[i]==OFF) {
      if(millis()>sensorTimer[i]) {
        sensorState[i]=FADEIN;
        sensorTimer[i]=millis()+sensorFadeIn;
      }
    }
    if(sensorState[i]==FADEIN) {
      if(millis()>sensorTimer[i]) {
        sensorState[i]=ON;
      } else {
        int alpha=255-((255*(sensorTimer[i]-millis()))/sensorFadeIn);
      sensorPlasma(sensorPos[i][0], sensorPos[i][1]-3,sensorPos[i][1]-3, sensorColor[i],alpha/2);
      sensorPlasma(sensorPos[i][0], sensorPos[i][1]-2,sensorPos[i][1]+2, sensorColor[i],alpha);
      sensorPlasma(sensorPos[i][0], sensorPos[i][1]+3,sensorPos[i][1]+3, sensorColor[i],alpha/2);
      }
    }
    if(sensorState[i]==ON) {
      sensorPlasma(sensorPos[i][0], sensorPos[i][1]-3,sensorPos[i][1]-3, sensorColor[i],127);
      sensorPlasma(sensorPos[i][0], sensorPos[i][1]-2,sensorPos[i][1]+2, sensorColor[i],255);
      sensorPlasma(sensorPos[i][0], sensorPos[i][1]+3,sensorPos[i][1]+3, sensorColor[i],127); 
    }
  }
  
  // 
  // Draw active animations
  //
  
  
  
  for(int y=0;y<4;y++) {
    if(animState[y]==FADEIN) {
      if(millis()>animTimer[y]) {
        animState[y]=ON;
        animTimer[y]=millis()+animLength;
        if(raveState==ON) {
          if(animState[0]==ON && animState[1]==ON && animState[2]==ON && animState[3]==ON) {
            for(int a=0;a<4;a++) {
              animState[a]=RAVE1;
              animTimer[a]=millis()+raveLength1;
              sensorTimer[a*2]=millis()+raveTotal;
              sensorTimer[a*2+1]=millis()+raveTotal;
            }
          }
        }
      } else {
        int maxlen=numpixels[y]-animPos[y];
        int len=maxlen-((maxlen*(animTimer[y]-millis()))/animFadeIn);
        forwardPlasma(y, max(0,animPos[y]-len), min(animPos[y]+len,STRIPLEN), animColor[y],255);
      }
    }
    if(animState[y]==ON) {
      if(millis()>animTimer[y]) {
        animState[y]=GLITTER;
        animTimer[y]=millis()+animGlitter;
      } else {
        int alpha=((255*(animTimer[y]-millis()))/animLength);
        forwardPlasma(y, 0, numpixels[y], animColor[y],alpha);
        int prob=probMultiply*fastCosineCalc(127-(127*(animTimer[y]-millis()))/animLength);
        stars(y,prob,fadeAmount, animColor[y]);
      }
    }
    if(animState[y]==GLITTER) {
      if(millis()>animTimer[y]) {
        animState[y]=FADEOUT;
        animTimer[y]=millis()+animFadeOut;
      } else {
        int prob=probMultiply*fastCosineCalc(255-(127*(animTimer[y]-millis()))/animLength);
        stars(y,prob,fadeAmount, animColor[y]);
//        delay(10);
      }
    }
    if(animState[y]==FADEOUT) {
      if(millis()>animTimer[y]) {
        animState[y]=OFF;
      } else {
        starsFade(y,fadeAmount);
        starsShow(y);
//        delay(10);
      }
    }
    if(animState[y]==RAVE1) {
      if(millis()>animTimer[y]) {
        animState[y]=RAVE2;
        animTimer[y]=millis()+raveLength2;
      } else {
        int alpha=255-((255*(animTimer[y]-millis()))/raveLength1);
        forwardPlasma(y, 0, numpixels[y], animColor[y],255);
        ravePlasma(y,alpha);
      }
    }
    if(animState[y]==RAVE2) {
      if(millis()>animTimer[y]) {
        animState[y]=RAVE3;
        animTimer[y]=millis()+raveLength3;
      } else {
        int alpha=255-((255*(animTimer[y]-millis()))/raveLength2);
        ravePlasma(y,255);
        theaterChaseRainbow(y,0,numpixels[y],alpha);
      }
    }
    if(animState[y]==RAVE3) {
      if(millis()>animTimer[y]) {
        animState[y]=RAVE4;
        animTimer[y]=millis()+raveLength4;
      } else {
        theaterChaseRainbow(y,0,numpixels[y],255);
      }
    }
    if(animState[y]==RAVE4) {
      if(millis()>animTimer[y]) {
        animState[y]=OFF;
      } else {
        int alpha=((255*(animTimer[y]-millis()))/raveLength4);
        theaterChaseRainbow(y,0,numpixels[y],alpha);
      }
    }

  }
  leds.show();

/*  */
  //
  // Reading sensors
  //

  for(int i=0;i<NUMSENSORS;i++) {
    if(digitalRead(sensorPins[i]) && (sensorState[i] == ON )) {
      sensorValue[i]++;

      Serial.print("Sensor ");
      Serial.print(i);
      Serial.println(" triggered.");
    }
    else {
      sensorValue[i]=0;
    }
    if(sensorValue[i]>sensorThreshold) {
      touchTimer=millis()+touchTimeout;
      int y=sensorPos[i][0];

      animState[y]=FADEIN;
      animTimer[y]=millis()+animFadeIn;
      animColor[y]=sensorColor[i];
      animPos[y]=sensorPos[i][1];

      sensorState[y*2]=OFF;
      sensorTimer[y*2]=millis()+sensorTimeout;
      sensorColor[y*2]=colorList[random(0,NUMCOLORS)];
      sensorState[y*2+1]=OFF;                    // Turning off neighboring pixel
      sensorTimer[y*2+1]=millis()+sensorTimeout;
      sensorColor[y*2+1]=colorList[random(0,NUMCOLORS)];

      starsReset(y);

/*
Serial.print("sensor i:");
Serial.print(i);
Serial.print(" sensorColor: r=");
Serial.print((sensorColor[i]& 0xFF0000)>>16);
Serial.print(" g=");
Serial.print((sensorColor[i]& 0x00FF00)>>8);
Serial.print(" b=");
Serial.println((sensorColor[i]& 0x0000FF));
Serial.print("anim y:");
Serial.print(y);
Serial.print(" animColor: r=");
Serial.print((animColor[y]& 0xFF0000)>>16);
Serial.print(" g=");
Serial.print((animColor[y]& 0x00FF00)>>8);
Serial.print(" b=");
Serial.println((animColor[y]& 0x0000FF));
*/
      
      if(animState[0]==FADEIN && animState[1]==FADEIN && animState[2]==FADEIN && animState[3]==FADEIN) {
        raveState=ON;
      }
    }
  }

//
// DEBUG STUFF
//
/*
Serial.print("Update frequency:");
Serial.println(1000/(millis()-starttime));
*/
/*
Serial.print("Sensors:");
for(int i=0;i<NUMSENSORS;i++) {
  switch(sensorState[i]) {
    case OFF:
      Serial.print("\tOFF");
      break;
    case ON:
      Serial.print("\tON");
      break;
    case FADEIN:
      Serial.print("\tFADEIN");
      break;
  }
}
Serial.println();

Serial.print("Animations:");
for(int i=0;i<4;i++) {
  switch(animState[i]) {
    case OFF:
      Serial.print("\tOFF");
      break;
    case ON:
      Serial.print("\tON");
      break;
    case FADEIN:
      Serial.print("\tFADEIN");
      break;
    case FADEOUT:
      Serial.print("\tFADEOUT");
      break;
    case RAVE1:
      Serial.print("\tRAVE1");
      break;
    case RAVE2:
      Serial.print("\tRAVE2");
      break;
    case RAVE3:
      Serial.print("\tRAVE3");
      break;
    case RAVE4:
      Serial.print("\tRAVE4");
      break;
  }
}
Serial.println();
*/
/**/
  /* 
  for(int y=0; y<4;y++) {
        Serial.print(y);
    Serial.print(": ");
    for(int i=0;i<numpixels[y];i++) {
      Serial.print(pixelArray[y][i]);
      Serial.print(",");
    }
    Serial.println();

  }
*/


}


