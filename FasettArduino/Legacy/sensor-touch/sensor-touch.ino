#define SENSOR_PIN 4

byte lastTouch = 0;

void setup(){
  Serial.begin(115200);
  pinMode(SENSOR_PIN, INPUT);
}

void loop() {
  byte newTouch = digitalRead(SENSOR_PIN) * 127;
  if (newTouch != lastTouch) {
    lastTouch = newTouch;
    Serial.println(newTouch);
  }
}
