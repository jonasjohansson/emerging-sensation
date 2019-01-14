void readSimple(byte pin, int &val, int &last){
  val = analogRead(pin);
  
  val = (val > 512) ? 1 : 0;

  if (val == last) return;

  s(pin,val);
  //c(pin,val,random(0,255),random(0,255),random(0,255));
  
  last = val;
}

void c(byte pin, byte val, byte r, byte g, byte b){
  Serial.print("W"+String(pin));
  Serial.print(' ');
  Serial.println(String(r)+' '+String(g)+' '+String(b));
}

void s(byte pin, int val){
  Serial.print("W"+String(pin));
  Serial.print(' ');
  Serial.println(val);
}

void p(int val){
  Serial.print(val);
  Serial.print("  ");
}

void pl(){
  Serial.println();
}
