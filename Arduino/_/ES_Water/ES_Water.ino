/*
   https://github.com/FastLED/FastLED/wiki/Pixel-reference
   A: 222 (6x25 + 1x27 + 3x15)
   B: 213 (7x24 + 3x15)
   C: 300 (10x24 + 4x15)
*/

#include<FastLED.h>

#define NUM_PARTICLES 20

#define NUM_LEDS 300
CRGB leds[3][300];

int a1, a2, a3, a1l, a2l, a3l;
int b1, b2, b3, b1l, b2l, b3l;
int c1, c2, c3, c4, c1l, c2l, c3l, c4l;

#define DAMPING 0.999

class Particle {
  private:
    int leds;
  public:
    int x;
    int y;
    int oldX;
    int oldY;
    int originX;
    int originY;
    void init(int x, int y);
    void integrate();
    void attract(int x, int y);
};


void Particle::init(int x, int y) {
  //Particle::Particle(){
  this->x = this->oldX = this->originX = x;
  this->x = this->oldX = this->originY = y;
}

void Particle::integrate() {
  int velocityX = (this->x - this->oldX) * DAMPING;
  int velocityY = (this->y - this->oldY) * DAMPING;
  this->oldX = this->x;
  this->oldY = this->y;
  this->x += velocityX;
  this->y += velocityY;
}

void Particle::attract(int x, int y) {
  int dx = x - this->x;
  int dy = y = this->y;
  int distance = sqrt(dx * dx + dy * dy);
  this->x += dx / distance;
  this->y += dy / distance;
}


Particle particles[NUM_PARTICLES];

CHSV gradStartColor(0,0,255);  // Gradient start color.
CHSV gradEndColor(255,0,0);  // Gradient end color.
uint8_t gradStartPos = 0;  // Starting position of the gradient.
#define gradLength 8  // How many pixels (in total) is the grad from start to end.
int8_t gradDelta = 1;  // 1 or -1.  (Negative value reverses direction.)

// If you wanted to move your gradient 32 pixels in 120 seconds, then:
// 120sec / 32pixel = 3.75sec
// 3.75sec x 1000miliseconds/sec = 3750milliseconds
#define gradMoveDelay 10  // How fast to move the gradient (in Milliseconds)

CRGB grad[gradLength];  // A place to save the gradient colors. (Don't edit this)

int x = 0;
uint16_t gHue = 0;
uint8_t  gHueDelta = 3;

void setup() {
  Serial.begin(115200);
  FastLED.setBrightness(192);
  FastLED.addLeds<NEOPIXEL, 0>(leds[0], 222);
  FastLED.addLeds<NEOPIXEL, 1>(leds[1], 213);
  FastLED.addLeds<NEOPIXEL, 2>(leds[2], 300);
  FastLED.clear();



  createParticles();
  
  //fill the array that stores the gradient colors.
  fill_gradient(grad, gradStartPos, gradStartColor, gradStartPos+gradLength-1, gradEndColor, SHORTEST_HUES);

}

#define NUM_PETALS 10

int petals[NUM_PETALS][2] = { {48,18},{110,24},{128,18} };

void loop() {

  

  return;

  gHue += gHueDelta;
  gHue = gHue % 360;
  for (int i = 0; i < 300; i++) {
   // leds[1][i] = CRGB(gHue,100, 360);
  }
  //FastLED.show();

  for (int i = 0; i < 3; i++){
    int start = petals[i][0];
    int length = petals[i][1];
    for (int j = start; j < start+length; j++){
      //leds[1][j] = CRGB::Blue;
    //  FastLED.show();
    }
  }
  
  //fill_grad();
  //FastLED.show();  
  

  if (b1) x = 100;
  if (b2) x = 110;
  if (b3) x = 48;

  for (int i = 0; i < NUM_PARTICLES; i++) {
    particles[i].attract(x, 0);
    particles[i].integrate();
    leds[1][particles[i].x - 1] = CRGB::Black;
    leds[1][particles[i].x + 1] = CRGB::Black;
    leds[1][particles[i].x] = CRGB::White;
  }

  FastLED.show();

  readSimple(0, a1, a1l);
  readSimple(1, a2, a2l);
  readSimple(2, a3, a3l);
  readSimple(3, b1, b1l);
  readSimple(4, b2, b2l);
  readSimple(5, b3, b3l);
  readSimple(6, c1, c1l);
  readSimple(7, c2, c2l);
  readSimple(8, c3, c3l);
  readSimple(9, c4, c4l);

 return;

    EVERY_N_MILLISECONDS(gradMoveDelay) {
    uint8_t count = 0;
    for (uint8_t i = gradStartPos; i < gradStartPos+gradLength; i++) {
      leds[1][i % NUM_LEDS] = grad[count];
      count++;
    }
    FastLED.show();  // Display the pixels.
    FastLED.clear();  // Clear the strip to not leave behind lit pixels as grad moves.
    
    gradStartPos = gradStartPos + gradDelta;  // Update start position.
    if ( (gradStartPos > NUM_LEDS-1) || (gradStartPos < 0) ) {  // Check if outside NUM_LEDS range
      gradStartPos = gradStartPos % NUM_LEDS;  // Loop around as needed.
    }

  } //end EVERY_N gradMoveDelay
  
}

void fill_grad() {
  
  uint8_t starthue = beatsin8(5, 0, 255);
  uint8_t endhue = beatsin8(7, 0, 255);
  
  if (starthue < endhue) {
    fill_gradient(leds[1], 300, CHSV(starthue,255,255), CHSV(endhue,255,255), FORWARD_HUES);    // If we don't have this, the colour fill will flip around. 
  } else {
    fill_gradient(leds[1], 300, CHSV(starthue,255,255), CHSV(endhue,255,255), BACKWARD_HUES);
  }
}

void createParticles(){
  for (int i = 0; i < NUM_PARTICLES; i++) {
    Particle* p;
    p->init(random(300), 0);
    particles[i] = p;
    leds[1][p->x] = CRGB::White;
    FastLED.show();
  }
}
