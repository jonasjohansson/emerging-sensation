void readSimple(byte pin, int &val, int &last){
  val = analogRead(pin);
  //val = smooth(val);

  s(pin,val);
  
  val = (val > 128) ? 1 : 0;

  if (val == last) return;
  
  last = val;
}

void s(byte pin, int val){
  Serial.print(pin);
  Serial.print(' ');
  Serial.println(val);
}
