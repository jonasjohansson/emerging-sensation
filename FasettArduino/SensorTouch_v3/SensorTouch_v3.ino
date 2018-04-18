#define PINS 5

byte touches[PINS];
byte lastTouches[PINS];

void setup(){
  Serial.begin(115200);
  for (uint8_t i = 0; i < PINS; i++){
    pinMode(i, INPUT);
    touches[i] = 0;
    lastTouches[i] = 0;
  }
}

void loop() {
  for (uint8_t i = 0; i < PINS; i++){
    touches[i] = digitalRead(i);
    if (touches[i] != lastTouches[i]){
      lastTouches[i] = touches[i];
      Serial.print(i);
      Serial.print(' ');
      Serial.println(touches[i]);
    }
  }
}
