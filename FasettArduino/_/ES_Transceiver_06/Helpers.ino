const int numReadings = 4;

int readings[numReadings] = {0,0,0,0};
int readIndex = 0;
int total = 0;
int average = 0;

int smooth(int val) {

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
