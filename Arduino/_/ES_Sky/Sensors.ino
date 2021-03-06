#define SMOOTHSTEP(x) ((x) * (x) * (3 - 2 * (x)))
#define N 10.0
#define THRESH 4

float readAdvanced(byte pin, float &val, float &last, float min, float max){
  float temp = analogRead(pin);
  
  float change = abs(last - temp);

  if (change > THRESH){
    for (byte i = 0; i < N; i++) {
      float v = i / N;
      v = SMOOTHSTEP(v);
      val = (last * v) + (temp * (1 - v));
    }
    int mapped = map(val,min,max,255,0);
    mapped = constrain(mapped,0,255);
    s(pin,mapped);
    last = val;
  }
  
  return val;
}

void s(byte pin, int val){
  switch (pin){
    case 17:
      pin = 0;
    break;
    case 18:
      pin = 1;
    break;
    case 19:
      pin = 2;
    break;
    case 22:
      pin = 3;
    break;
  }
  Serial.print("S"+String(pin));
  Serial.print(' ');
  Serial.println(val);
}
