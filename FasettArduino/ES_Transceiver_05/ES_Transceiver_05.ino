int a, b, al, bl;

void setup(){
  Serial.begin(115200);
}

void loop(){
  //rxtxA(23, a, al); // val, last, pin
  rxtxB(19, b, bl, 30, 120); // val, last, pin, min, max
  
  delay(10);
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

  //val = smooth(val);
  val = constrain(val,min,max);

  int diff = abs(val - last);
  if (diff > 0){
    int valMap = map(val,min,max,255,0);
    //s(pin,valMap);
  }
  int valLerp = lerp(last, val, 0.1);
  s(pin,valLerp);
  
  last = val;
}

void s(byte pin, int val){
  Serial.print(pin);
  Serial.print(' ');
  Serial.println(val);
}

float lerp(float a, float b, float x){ 
 return a + x * (b - a);
}
