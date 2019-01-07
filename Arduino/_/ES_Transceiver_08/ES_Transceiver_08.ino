float a, b, al, bl;

void setup(){
  Serial.begin(115200);
}

void loop(){
  //readSimple(23, a, al);
  readAdvanced(23, b, bl, 40, 360);
  
  delay(10);
}
