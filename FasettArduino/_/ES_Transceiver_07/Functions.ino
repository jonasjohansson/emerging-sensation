#define SMOOTHSTEP(x) ((x) * (x) * (3 - 2 * (x)))
#define N 8.0

void readSimple(byte pin, int &val, int &last){
  val = analogRead(pin);
  val = (val > 512) ? 1 : 0;

  if (val == last) return;
  
  s(pin,val);
  last = val;
}

int X = 0;

void readAdvanced(byte pin, int &val, int &last, int min, int max){
  int B = analogRead(pin);
  B = constrain(B,min,max);
  //temp = smooth(temp);

  Serial.println(B + String(" ") + last);
  //if (B == last) return;

  int A = val;
  //val = lerp(val,temp,0.1);
  
  float v;
  
  for (int i = 0; i < N; i++) {
    v = i / N;
    v = SMOOTHSTEP(v);
    val = (A * v) + (B * (1 - v));
  } 
  
  s(pin,val);
  last = val;

}

void s(byte pin, int val){
  //Serial.print(pin);
  //Serial.print(' ');
  Serial.println(val);
}

int smoothstep(int A, int B, float value) {
  int x = max(0, min(1, (value-A)/(B-A)));
  return x*x*(3 - 2*x);
};

int smoothstep2(int edge0, int edge1, float x) {
  // Scale, bias and saturate x to 0..1 range
  x = constrain((x - edge0) / (edge1 - edge0), 0.0, 1.0); 
  // Evaluate polynomial
  return x * x * (3 - 2 * x);
}
