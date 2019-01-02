#define SMOOTHSTEP(x) ((x) * (x) * (3 - 2 * (x)))
#define N 10.0

void readSimple(byte pin, float &val, float &last){
  val = analogRead(pin);
  val = (val > 512) ? 1 : 0;

  if (val == last) return;
  
  s(pin,val);
  last = val;
}

void readAdvanced(byte pin, float &val, float &last, float min, float max){
  float temp = analogRead(pin);
  temp = constrain(temp,min,max);
  temp = map(temp,min,max,255,0);
  temp = smooth(temp);

  if (abs(temp - last) < 2) return;

  for (byte i = 0; i < N; i++) {
    float v = i / N;
    v = SMOOTHSTEP(v);
    //v = v*v;
    val = (last * v) + (temp * (1 - v));
  }
  
  s(pin,val);
  last = val;
}

void s(byte pin, int val){
  //Serial.print(pin);
  //Serial.print(' ');
  Serial.println(val);
}
