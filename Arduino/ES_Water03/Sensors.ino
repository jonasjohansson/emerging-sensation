void readSimple(byte pin, int &val){
  int newVal = analogRead(pin);

  if (isCalibrating) return;
  
  newVal = (newVal > 512) ? 1 : 0;

  if (millis() - sensorTimers[pin] > TOUCH_DELAY){
    if (newVal != val){
      s(pin,newVal);
      if (newVal == 1) {
        newTarget(pin);
        c(pin,random(255),random(255),random(255));
      }
      val = newVal;
    }
    sensorTimers[pin] = millis();
  }
}

void c(byte pin, byte r, byte g, byte b){
  Serial.print("W"+String(pin));
  Serial.print(' ');
  Serial.println(String(r)+' '+String(g)+' '+String(b));
}

void s(byte pin, int val){
  Serial.print("W"+String(pin));
  Serial.print(' ');
  Serial.println(val);
}
