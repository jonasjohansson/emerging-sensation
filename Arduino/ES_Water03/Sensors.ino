void readSimple(byte pin, int &val){
  int newVal = analogRead(pin);

  newVal = (newVal > 512) ? 1 : 0;

  if (newVal != val){
    s(pin,newVal);
    if (newVal == 1) newTarget(pin);
  }
  
  val = newVal;
}

// void c(byte pin, byte val, byte r, byte g, byte b){
//   Serial.print("W"+String(pin));
//   Serial.print(' ');
//   Serial.println(String(r)+' '+String(g)+' '+String(b));
// }

void s(byte pin, int val){
  Serial.print("W"+String(pin));
  Serial.print(' ');
  Serial.println(val);
}