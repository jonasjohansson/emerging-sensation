#define SMOOTHSTEP(x) ((x) * (x) * (3 - 2 * (x)))
#define N 4.0

int a, b, al, bl;

void setup(){
  Serial.begin(115200);
}

void loop(){
  //readSimple(23, a, al);
  readAdvanced(23, b, bl, 30, 320);
  
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


  if (abs(temp - val) > 10){
    
    for (int i = 0; i < N; i++){
      float v = i / N;
      v = SMOOTHSTEP(v);
      val = (last * v) + (temp * (1 - v));
    }

    //val = lerp(val,temp,0.1);
    
    Serial.println(val);
    last = val;

  }
  
}

void s(byte pin, int val){
  Serial.print(pin);
  Serial.print(' ');
  Serial.println(val);
}

float lerp(float a, float b, float x){ 
 return a + x * (b - a);
}
