#define SMOOTHSTEP(x) ((x) * (x) * (3 - 2 * (x)))
#define N 6.0

void readAdvanced(byte index, float &val, float &oldVal, byte &lastSend, float min, float max){
  float newVal = analogRead(pins[index]);
/*
  Serial.print("raw reading: ");
  Serial.println(newVal);
  */
  newVal =  constrain(map(newVal,min,max,0,255),0,255);

/*
  Serial.print("reading: ");
  Serial.println(newVal);
  */

  for (byte i = 0; i < N; i++) {
    float v = (float)i / N;
    v = SMOOTHSTEP(v);
    val = (oldVal * v) + (newVal * (1 - v));
  }
/*
  Serial.print("val: ");
  Serial.println(val);
*/
  // re-mapping, look here Jonas
  int mapped = map(val,20,150,0,255);
  mapped = constrain(mapped,0,255);

/*
Serial.print("mapped: ");
Serial.println(mapped);
*/
 
  int diff = abs( mapped -  lastSend);
  
  if (diff > 1){
    s(index,mapped);
    //s(index,val);
  }

  lastSend = mapped;
  oldVal = val;
}

void s(byte pin, int val){
  if (isCalibrating) return;
  Serial.print("S"+String(pin));
  Serial.print(' ');
  Serial.println(val);
}
