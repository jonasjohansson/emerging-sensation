/*
 * 
 * OctoWS2811: 2,14,7,8,6,20,21,5
 * 
 */

#define NUM_PINS 8
#define MIN 50
#define MAX 200

byte pins[NUM_PINS] = {2,14,7,8,6,20,21,5};
byte values[NUM_PINS];
byte lastValues[NUM_PINS];

void setup(){
  
  for (byte i = 0; i < NUM_PINS; i++)
    pinMode(i, INPUT);
  
  Serial.begin(115200);
}

void loop() {

  // read
  int a = analogRead(2);
  int b = analogRead(14);
  int c = analogRead(7);

  // filter
  a = f(a);
  b = f(b);
  c = f(c);

  // send
  s(0,a);
  s(1,b);
  s(2,c);
}

int f(int val){
  val = constrain(val,MIN,MAX);
  val = map(val,MIN,MAX,0,255);
  return val;
}

void s(byte index, byte val){
  Serial.print(index);
  Serial.print(' ');
  Serial.println(val);
}

void r(){
  for (byte i = 0; i < NUM_PINS; i++){
    values[i] = analogRead(i);
    if (values[i] != lastValues[i]){
      lastValues[i] = values[i];
      s(i,values[i]);
    }
  }
}
