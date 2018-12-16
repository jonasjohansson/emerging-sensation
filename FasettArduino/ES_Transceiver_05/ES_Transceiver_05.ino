#include <FastLED.h>

#define smoothStep(x) ((x) * (x) * (3 - 2 * (x)))

int a, b, al, bl;
float v;
float X;

void setup(){
  Serial.begin(115200);
}

void loop(){
  //rxtxA(23, a, al); // val, last, pin
  //rxtxB(19, b, bl, 30, 120); // val, last, pin, min, max

  a = analogRead(19);
  a = smooth(a);

  //int n = lerp(al, a, 0.1);
  a = lerp8by8(al, a, 0.5);

  if (al != a) Serial.println(a);

  al = a;
}

void rxtxA(byte pin, int &val, int &last){
  val = analogRead(pin);
  val = (val > 512) ? 1 : 0;
  if (val != last){
    last = val;
    s(pin,val);
  }
}

void rxtxB(byte pin, int &val, int &last, int min, int max){
  val = analogRead(pin);
  val = smooth(val);
  int diff = abs(val - last);
  if (diff > 3){
    last = val;
    val = constrain(val,min,max);
    val = map(val,min,max,1023,0);
    //s(pin,val);
  }
}

void s(byte pin, int val){
  Serial.print(pin);
  Serial.print(' ');
  Serial.println(val);
}

float lerp(float a, float b, float x){ 
 return a + x * (b - a);
}
