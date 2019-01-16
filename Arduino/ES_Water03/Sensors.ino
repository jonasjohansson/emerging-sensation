void readSimple(byte pin, int &val){
  int newVal = analogRead(pin);

  newVal = (newVal > 512) ? 1 : 0;

  if (millis() - sensorTimers[pin] > 1000){
    if (newVal != val){
      s(pin,newVal);
      if (newVal == 1) {
        c(pin,random(255),random(255),random(255));
        newTarget(pin);
      }
      val = newVal;
    }
    sensorTimers[pin] = millis();
  }

}

void c(byte pin, byte r, byte g, byte b){
  if (isCalibrating) return;
  Serial.print("W"+String(pin));
  Serial.print(' ');
  Serial.println(String(r)+' '+String(g)+' '+String(b));
}

void s(byte pin, int val){
  if (isCalibrating) return;
  Serial.print("W"+String(pin));
  Serial.print(' ');
  Serial.println(val);
}
