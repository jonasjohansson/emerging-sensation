#define SMOOTHSTEP(x) ((x) * (x) * (3 - 2 * (x)))
#define N 32.0

float lerp(float a, float b, float x){ 
  return a + x * (b - a);
}

class Particle {
	private:
		int flutterInterval;
		int length;
		unsigned long currentMillis;
		unsigned long previousMillis;
	public:
		int p;
		int last;
		int origin;
		int target;
		int index;
		int fade;
		bool attracts;
		CRGBPalette16 palette;
		CRGB color;
		void create(int p, int index, int len);
		void integrate();
		void attract();
		void draw();
		void flutter();
};

void Particle::create(int p, int index, int len){
	this->p = p;
	this->last = p;
	this->origin = p;
	this->index = index;
	this->target = p;
	this->attracts = false;
	this->currentMillis = 0;
	this->previousMillis = 0;
	this->color = CRGB::White;
	this->palette = buds_p[index];
	this->flutterInterval = random(6000,9000);
	this->length = len;
}

void Particle::attract(){
  // this->last = this->p;
  // this->p = lerp8by8(this->p, this->target, 8);
   // for (byte i = 0; i < N; i++) {
   //   float v = i / N;
   //   v = SMOOTHSTEP(v);
   //   v = v * v;
   //   this->p = ( this->last * v) + (this->target * (1 - v));
   // }

   this->p = lerp(this->p, this->target, 0.1);


   this->last = this->p;
}

void Particle::draw(){
	leds[this->index][this->last] += blend(leds[this->index][this->last],CRGB::Black,127);
	leds[this->index][this->p] += blend(leds[this->index][this->p],this->color,192); 
	// for (int i = 0; i < 11; i++){
	// 	int fade = plasma[i];
	// 	leds[this->index][this->p+i] += blend(leds[this->index][this->p+i],CRGB(127,255,255),fade); 
	// } 
	// if (this->attracts){
	// 	int index = sin8( (millis() / 1000 )) * 0.25
	//         + cos8( millis() / 5 + cos8(millis() / 5000)) * 0.125;
	// 	int fade = cos8(millis() / 200);
 //        leds[this->index][this->p] += ColorFromPalette(this->palette, index, fade, LINEARBLEND); 
 //    }
}

void Particle::flutter(){
	this->currentMillis = millis();
	if (this->currentMillis - this->previousMillis > this->flutterInterval){
		this->previousMillis = this->currentMillis;
		int len = LEDS_PER_STRIP[this->index];
		this->target = constrain(random(len)+random(-32,32),0,len);
	}
}