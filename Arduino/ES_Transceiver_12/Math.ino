const int numReadings = 10;

int readings[numReadings];
int readIndex = 0;
int total = 0;
int average = 0;
bool first = true;

int smooth(int val) {

  if (first){
    first = false;
    for (byte i = 0; i < numReadings; i++) readings[i] = 0;
  }

  total = total - readings[readIndex];
  readings[readIndex] = val;
  total = total + readings[readIndex];
  readIndex = readIndex + 1;
  
  if (readIndex >= numReadings)
    readIndex = 0;

  average = total / numReadings;

  return average;

  delay(1);
}

double mapf(double val, double in_min, double in_max, double out_min, double out_max) {
  return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float lerp(float a, float b, float x){ 
  return a + x * (b - a);
}
