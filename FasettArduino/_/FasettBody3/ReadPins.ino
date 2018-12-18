void initDigitalPins(uint8_t pins){
  for (uint8_t i = 0; i < pins; i++){
    pinMode(i, INPUT);
    //digitalValues[i] = 0;
    //lastDigitalValues[i] = 0;
  }
}

void readAnalogPins(uint8_t pins){
  for (uint8_t i = 0; i < pins; i++){
   analogValues[i] = analogRead(i);
    if (analogValues[i] != lastAnalogValues[i]){
      lastAnalogValues[i] = analogValues[i];
      Serial.print('a');
      Serial.print(i);
      Serial.print(' ');
      Serial.println(analogValues[i]);
    }
  }
}

void readDigitalPins(uint8_t pins){
  for (uint8_t i = 0; i < pins; i++){
    if (i == LED_PIN) return;
    digitalValues[i] = digitalRead(i);
    if (digitalValues[i] != lastDigitalValues[i]){
      lastDigitalValues[i] = digitalValues[i];
      Serial.print('d');
      Serial.print(i);
      Serial.print(' ');
      Serial.println(digitalValues[i]);
    }
  }
}
