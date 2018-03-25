//#include <CapacitiveSensor.h>

//CapacitiveSensor   capsense = CapacitiveSensor(18,23);        // second one is the sensor pin

#define NUMREAD 5
long readings[NUMREAD];
byte currReading=0;


// PIXLES
#define USE_OCTOWS2811
#include<OctoWS2811.h>
#include<FastLED.h>

#define NUM_LEDS_PER_STRIP 78
#define NUM_STRIPS 8

CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];
int NUM_LEDS=NUM_STRIPS * NUM_LEDS_PER_STRIP;

// END PIXELS

// IR REMOTE //

#include <IRremote.h>

int RECV_PIN = 19;
IRrecv irrecv(RECV_PIN);
decode_results results;
#define POWER 0x10EFD827 
#define A 0x10EFF807 
#define B 0x10EF7887
#define C 0x10EF58A7
#define UP 0x10EFA05F
#define DOWN 0x10EF00FF
#define LEFT 0x10EF10EF
#define RIGHT 0x10EF807F
#define SELECT 0x10EF20DF

// END IR REMOTE //


// SENSOR FILTER

#include <Filters.h>
float filterFrequency = 0.2;
FilterOnePole lowpassFilter( LOWPASS, filterFrequency );   

// END SENSOR FILTER


#define DROP_Y 6
#define DROP_X 8

byte wingmap[78];
byte wingmap2[65];

byte dropMap[6][8]= {{7,7,12,12,23,25,33,31},
                   {3,3,11,11,22,22,29,32},
                   {4,8,8,13,21,21,27,34},
                   {5,6,16,16,26,26,30,30},
                   {9,10,10,14,40,40,28,28},
                   {0,0,18,18,24,24,24,24}}; 
byte dropColor[3][6] {{180,170,155,150,130,120}, // first row is hue, second is saturation
                      {255,200,150,140,110,20},
                      {255,195,156,130,130,91}};


bool calibrateMin = false, calibrateMax = false;
long calibrateSum = 0;
long calibrateCount = 0;
long calibrateEnd = 0;

uint8_t gHue = 0; // rotating "base color" used by many of the patterns
int sensorValue;
float fSensorValue;
float charger, charger2;
byte explodeHue, explodeSat, explodeVar;
long chargerTimer, charger2Timer;
bool chargerTrigger, charger2Trigger;

long timeCode = 0, timeCode2=0;

int minSense=4200;
int maxSense=7000;

char sensorPins[4] = {17,18,19,22};

#define CHARGERMUL 0.11
#define CHARGERFADE 8
#define CHARGERMUL2 0.12
#define CHARGERFADE2 8
#define CHARGERTIMER 3000
#define CHARGER2TIMER 2000

int temp=0;

long autoCalTimer = 0;


void setup()                    
{
  randomSeed(analogRead(0));
  
   LEDS.addLeds<OCTOWS2811>(leds, NUM_LEDS_PER_STRIP);
   LEDS.setBrightness(255);

//   capsense.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(9600);
//   capsense.set_CS_Timeout_Millis(1000);

  for(int i=0;i<4;i++) {
    pinMode(sensorPins[i], INPUT);
  }


   irrecv.enableIRIn(); // Start the receiver

   for(int i=0;i<78;i++) {
    if(i%2)
      wingmap[i]=77-i/2;
    else
      wingmap[i]=i/2;
   }
   for(int i=0;i<65;i++) {
    if(i%2)
      wingmap2[i]=64-i/2;
    else
      wingmap2[i]=i/2;
   }

   newExplode();
  
}


void loop()                    
{
temp=millis()/200;
//    long last = addRead(capsense.capacitiveSensor(5));
//  long avg =  getAvg();

/*  long last = capsense.capacitiveSensor(5);

/*
  if(calibrateMax || calibrateMin) {
    calibrateSum += last;
    calibrateCount++;
    if(timeCode > calibrateEnd) {
      if(calibrateMin) {
        minSense=calibrateSum*1.1/calibrateCount;
        calibrateMin=false;
        Serial.print("New minSense: ");
        Serial.println(minSense);
      }
      if(calibrateMax) {
        maxSense=calibrateSum/calibrateCount;
        calibrateMax=false;
        Serial.print("New maxSense: ");
        Serial.println(maxSense);
      }
      calibrateSum=0;
      calibrateCount=0;
    }
  }
*/
/*
  lowpassFilter.input( last );
  long avg = lowpassFilter.output();
  sensorValue = constrain(map(avg,minSense,maxSense,0,255),0,255);
  fSensorValue = (float)(constrain(avg,minSense,maxSense)-minSense)/(float)(maxSense-minSense);
  
//  charger = constrain(charger+(sensorValue*CHARGERMUL),0,1023);
  charger = constrain(charger+(constrain(sensorValue-10,0,255)*CHARGERMUL),0,1023);
//  if(chargerTimer<millis());
  charger2 = constrain(charger2+(constrain(sensorValue-140,0,255)*CHARGERMUL2),0,1023);
*/


//
// Här är koden som reglerar känsligheten på 1,2,3, eller 4 touchar.
//

  
  int sensorCount=0;
  for(int i=0;i<4;i++) {
    sensorCount += digitalRead(sensorPins[i]);
  }
  sensorValue=0;
  switch(sensorCount) {
    case 1:
      sensorValue=105;
      break;
    case 2:
      sensorValue=133;
      break;
    case 3:
      sensorValue=145;
      break;
    case 4:
      sensorValue=160;
      break;
  }

  charger = constrain(charger+(sensorValue*CHARGERMUL),0,1023);
  charger2 = constrain(charger2+(constrain((sensorValue-50),0,255)*CHARGERMUL2),0,1023);


  Serial.print(sensorCount); 
  Serial.print("\t");
  Serial.print(sensorValue); 
  Serial.print("\t");
  Serial.print(charger); 
  Serial.print("\t");
  Serial.print(charger2); 
  Serial.println();

/*
    Serial.print(minSense);                  // print sensor output 1
    Serial.print("\t");                    // tab character for debug windown spacing   

    Serial.print(maxSense);                  // print sensor output 1
    Serial.print("\t");                    // tab character for debug windown spacing   

    Serial.print(last);                  // print sensor output 1
    Serial.print("\t");                    // tab character for debug windown spacing   
    Serial.print(avg);                  // print sensor output 1

    Serial.print("\t");                    // tab character for debug windown spacing
    Serial.print(sensorValue);                  // print sensor output 1

    Serial.print("\t");                    // tab character for debug windown spacing
    Serial.print(fSensorValue);                  // print sensor output 1

    Serial.print("\t");                    // tab character for debug windown spacing
    Serial.print(charger);                  // print sensor output 1

    Serial.print("\t");                    // tab character for debug windown spacing
    Serial.print(charger2);                  // print sensor output 1

    Serial.print("\t");                    // tab character for debug windown spacing
    Serial.print(chargerTrigger);                  // print sensor output 1

    Serial.print("\t");                    // tab character for debug windown spacing
    Serial.print(charger2Trigger);                  // print sensor output 1

    Serial.print("\t");                    // tab character for debug windown spacing
    Serial.print(temp);                  // print sensor output 1


    Serial.println();
*/

    int framelength=millis()-timeCode;
    timeCode += framelength+(float)framelength*charger/1023; 
    framelength=millis()-timeCode2;
    timeCode2 += framelength+(float)2*framelength*fSensorValue; 

  if(charger<512)
    chargerTimer=millis()+CHARGERTIMER;
    
  if(charger2>1000) {
    charger2Trigger=true;
  }
  else if(charger2<720) {
    if(charger2Trigger) {
        charger2Trigger=false;
        charger2Timer=millis()+CHARGER2TIMER;
        charger=0;
        charger2=0;
    }
  }
  if(charger2<500)
    newExplode();


/*
fSensorValue=0;
sensorValue=0;
charger=0;
charger2=0;
*/

  dropDefault();
  wingsDefault();

  dropOverlay();

if(!charger2Trigger)
  theaterChase2(CRGB(255, 0, 0),CRGB(255,50,0),constrain(map(charger2,200,700,0,255),0,255));

    wingsOverlay2();
    dropOverlay2();
  
/**/
  LEDS.show();
  delay(2);
  

if (irrecv.decode(&results)) 
  {
    if (results.value == A) 
    {
      if(!calibrateMin) {
        Serial.print("Calibrating Minimum...");
        calibrateMin=true;
        calibrateEnd=millis()+3000;
      }
    }
    if (results.value == B) 
    {
      if(!calibrateMin) {
        Serial.print("Calibrating Maximum...");
        calibrateMax=true;
        calibrateEnd=millis()+3000;
      }
    }
    if (results.value == C) 
    {
      photoOp();
      LEDS.show();
      delay(30000);
    }

    if (results.value == UP) 
    {
      maxSense+=200;
      Serial.print("maxSense: ");
      Serial.println(maxSense);
    }
     if (results.value == DOWN) 
    {
      maxSense-=200;
      Serial.print("maxSense: ");
      Serial.println(maxSense);
    }
     if (results.value == RIGHT) 
    {
      minSense+=200;
      Serial.print("minSense: ");
      Serial.println(minSense);
    }
     if (results.value == LEFT) 
    {
      minSense-=200;
      Serial.print("minSense: ");
      Serial.println(minSense);
    }
    irrecv.resume();
  }
/**/
gHue++;
  charger = constrain(charger-CHARGERFADE,0,1023);
  charger2 = constrain(charger2-CHARGERFADE2,0,1023);

/*
  if(sensorValue == 0 && charger == 0 && charger2 == 0) {
    if(autoCalTimer) {
      if(autoCalTimer<millis()) {
        capsense.reset_CS_AutoCal();
        autoCalTimer=0;
      }
    }
    else
      autoCalTimer=millis()+3000;
  }
*/
}



