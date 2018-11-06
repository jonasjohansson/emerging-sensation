

void readSensors(){
  for (uint8_t i = 0; i < NUM_SENSORS; i++){
    int pin = sensors[i][0];
    int in_min = sensors[i][2];
    int in_max = sensors[i][3];
    int out_min = sensors[i][2];
    int out_max = sensors[i][3];
    int val = analogRead(sensors[i]);
    val = constrain(val,in_min,in_max);
    val = map(val,in_min,in_max,OUT_MIN,OUT_MAX);
    sensors[i][1] = val;
  }
}

void colorise(byte wing[][2]){
  for (uint8_t i = 0; i < NUM_WINGS; i++){
    byte x = wing[i][0];
    byte y = wing[i][1];
    uint8_t start = NUM_LEDS_PER_SIDE * y;
    uint8_t end = NUM_LEDS_PER_SIDE * (y + 1);
    for (uint8_t j = start; j < end; j++){
      FastLED[x][j] = CRGB(255,255,255);
    }
  }
  FastLED.show();
}
