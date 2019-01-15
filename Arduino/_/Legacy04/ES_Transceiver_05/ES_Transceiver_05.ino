#define SMOOTHSTEP(x) ((x) * (x) * (3 - 2 * (x)))
#define N 10.0

int a, b, al, bl;

void setup(){
  Serial.begin(115200);
}

void loop(){
  //readSimple(23, a, al);
  readAdvanced(23, b, bl, 30, 120);
  
  delay(10);
}

void readSimple(byte pin, int &val, int &last){
  val = analogRead(pin);
  val = (val > 512) ? 1 : 0;
  if (val != last){
    s(pin,val);
    last = val;
  }
}


void readAdvanced(byte pin, int &val, int &last, int min, int max){
  int temp = analogRead(pin);
  temp = constrain(temp,min,max);
  temp = smooth(temp);

  if (temp == last) return;

  s(pin,val);

  int diff = abs(val - last);
  if (diff > 3){
    val = map(val,min,max,255,0);
    s(pin,val);
  }
  
  float v;
  
  for (int i = 0; i < N; i++){
    v = i / N;
    v = SMOOTHSTEP(v);
    val = (last * v) + (temp * (1 - v));
    //s(pin,temp);
    Serial.println(val);
  }
  
  last = temp;
}

void s(byte pin, int val){
  Serial.print(pin);
  Serial.print(' ');
  Serial.println(val);
}

float lerp(float a, float b, float x){ 
 return a + x * (b - a);
}
