#define THRESH 3

int al, bl, cl;

void setup(){
  Serial.begin(115200);
}

void loop(){

  int a = r(23);

  // diff
  int adiff = abs(a - al);
  if (adiff > THRESH){
    al = a;
    // filter
    a = f(a,30,120); 
    // send
    s(0,a);
  }
}

int r(int pin){
  int val = analogRead(pin);
  return smooth(val);
}

int f(int val, int min, int max){
  val = constrain(val,min,max);
  val = map(val,min,max,255,0);
  return val;
}

void s(byte index, byte val){
  Serial.print(String(index)+' ');
  Serial.println(val);
}
