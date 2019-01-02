#define THRESH 3

int a, b, c;
int al, bl, cl;

void setup(){
  Serial.begin(115200);
}

void loop(){

  rxtx_d(a, al, 17);

  rxtx_a(b, bl, 23, 30, 80);
  
}

void rxtx_d(int &val, int &last, int pin){
  val = digitalRead(pin);
  if (val != last){
    last = val;
    s(pin,val);
  }
}

void rxtx_a(int &val, int &last, int pin, int min, int max, bool flag){
  val = analogRead(pin);
  if (flag)
    val = smooth(val);
  int diff = abs(val - last);
  if (diff > THRESH){
    last = val;
    if (flag){
      val = constrain(val,min,max);
      val = map(val,min,max,255,0);
    }
    s(pin,val);
  }
}

void s(byte index, byte val){
  Serial.print(String(index)+' ');
  Serial.println(val);
}
