#define SMOOTHSTEP(x) ((x) * (x) * (3 - 2 * (x)))
#define N 10.0
#define THRESH 4

float readAdvanced(byte index, float &val, float &last, float min, float max){
  float temp = analogRead(pins[index]);
  temp = map(temp,min,max,255,0);
  temp = constrain(temp,0,255);
  
  float change = abs(last - temp);

  if (change > THRESH){
    for (byte i = 0; i < N; i++) {
      float v = i / N;
      v = SMOOTHSTEP(v);
      val = (last * v) + (temp * (1 - v));
    }
    
    s(index,temp);

    last = val;
  }
  
  return val;
}

void s(byte pin, int val){
   if (pin == 1) pin = 0;
  Serial.print("S"+String(pin));
  Serial.print(' ');
  Serial.println(val);
}
