#define SMOOTHSTEP(x) ((x) * (x) * (3 - 2 * (x)))
#define N 8.0
#define THRESH 20

void readAdvanced(byte index, float &val, float &oldVal, float min, float max){
  float newVal = analogRead(pins[index]);
  newVal = map(newVal,min,max,0,255);
  newVal = constrain(newVal,0,255);

  for (byte i = 0; i < N; i++) {
    float v = i / N;
    v = SMOOTHSTEP(v);
    val = (oldVal * v) + (newVal * (1 - v));
  }

  //if (abs(newVal - oldVal) > THRESH){
  if (newVal != oldVal){
    s(index,val);
  }

  oldVal = val;
}

void s(byte pin, int val){
  Serial.print("S"+String(pin));
  Serial.print(' ');
  Serial.println(val);
}
