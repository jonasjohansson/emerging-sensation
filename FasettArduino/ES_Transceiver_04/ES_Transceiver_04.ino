int a, b, c;
int al, bl, cl;

void setup(){
  Serial.begin(115200);
}

void loop(){
  receiveTransmitSimple(a, al, 23); // val, last, pin
  receiveTransmitAdvanced(b, bl, 19, 30, 120); // val, last, pin, min, max
}

void receiveTransmitSimple(int &val, int &last, int pin){
  val = analogRead(pin);
  val = (val > 512) ? 1 : 0;
  if (val != last){
    last = val;
    s(pin,val);
  }
}

void receiveTransmitAdvanced(int &val, int &last, int pin, int min, int max){
  val = analogRead(pin);
  val = smooth(val);
  int diff = abs(val - last);
  if (diff > 3){
    last = val;
    val = constrain(val,min,max);
    val = map(val,min,max,1023,0);
    s(pin,val);
  }
}

void s(byte index, int val){
  Serial.print(index);
  Serial.print(' ');
  Serial.println(val);
}
