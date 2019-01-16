#define SMOOTHSTEP(x) ((x) * (x) * (3 - 2 * (x)))
#define N 12.0

void readAdvanced(byte index, float &val, float &oldVal, float min, float max){
  float newVal = analogRead(pins[index]);
  newVal = map(newVal,min,max,0,255);
  newVal = constrain(newVal,0,255);

  for (byte i = 0; i < N; i++) {
    float v = i / N;
    v = SMOOTHSTEP(v);
    val = (oldVal * v) + (newVal * (1 - v));
  }

  int diff = abs(floor(val) - floor(oldVal));
  if (diff > 1){
    // re-mapping, look here Gustaf
    int mapped = map(val,24,222,0,255);
    mapped = constrain(mapped,0,255);
    s(index,mapped);
    //s(index,val);
  }

  oldVal = val;
}

void s(byte pin, int val){
  if (isCalibrating) return;
  Serial.print("S"+String(pin));
  Serial.print(' ');
  Serial.println(val);
}
