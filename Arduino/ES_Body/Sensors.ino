void readSimple(byte pin, int &val, int &last){
  val = analogRead(pin);
  
  val = (val > 512) ? 1 : 0;

  if (val == last) return;

  s(pin,val);
  
  last = val;
}

void s(byte pin, int val){
  Serial.print(pin);
  Serial.print(' ');
  Serial.println(val);
}
