#define NUM_PINS 8

byte pins[NUM_PINS] = {2,14,7,8,6,20,21,5};

int al, bl, cl;

void setup(){
  
  for (byte i = 0; i < NUM_PINS; i++)
    pinMode(i, INPUT);
  
  Serial.begin(115200);
}

void loop(){

  // read
  int a = analogRead(2);
  int b = analogRead(14);
  int c = analogRead(7);
  
  // filter
  a = f(a,50,200);
  b = f(b,50,200);
  c = f(c,50,200);

  // send
  if (a != al){
    al = a;
    s(0,a);
  }

  if (b != bl){
    bl = b;
    s(1,b);
  }

  if (c != cl){
    cl = c;
    s(2,c);
  }
}

int f(int val, int min, int max){
  val = constrain(val,min,max);
  val = map(val,min,max,0,255);
  return val;
}

void s(byte index, byte val){
  Serial.print(index+' ');
  Serial.println(val);
}
