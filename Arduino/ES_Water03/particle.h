#define SMOOTHSTEP(x) ((x) * (x) * (3 - 2 * (x)))

#define ease8InOutCubic(x) == 3(x^i) - 2(x^3)
// #define SMOOTHERSTEP(x) ((x) * (x) * (x) * (x * (x * 6 - 15) + 10))
#define N 10.0

class Particle {
	private:
		int flutterInterval;
		int length;
		unsigned long currentMillis;
		unsigned long previousMillis;
	public:
		int id;
		int p;
		int pLast;
		int pOrigin;
		int pTarget;
		int ledIndex;
		CRGB color;
		void create(int id, int p, int ledIndex, int len);
		void integrate();
		void attract();
		void draw();
		void fall();
		void flutter();
		void setColor();
};

void Particle::create(int id, int p, int ledIndex, int len){
	this->id = id;
	this->p = p;
	this->pLast = p;
	this->pOrigin = p;
	this->pTarget = p;
	this->ledIndex = ledIndex;
	this->currentMillis = 0;
	this->previousMillis = 0;
	this->color = CRGB::Blue;
	this->flutterInterval = random(4000,6000);
	this->length = len;
}

void Particle::attract() {
	float pNew;
	float pLast = this->pLast;
	float pTarget = this->pTarget;

	// pNew = lerp8by8(pLast, pTarget, 127);
	for (byte i = 0; i < N; i++) {
		float v = i / N;
		v = SMOOTHSTEP(v);
		pNew = (pLast * v) + (pTarget * (1 - v));
	}

	this->pLast = this->p;
	this->p = (int)pNew;
}

void Particle::setColor(){
	this->color = OceanColors_p[random(16)];
}

void Particle::draw(){
	leds[this->ledIndex][this->pLast] += nblend(leds[this->ledIndex][this->pLast],CRGB::Black,255); 
	leds[this->ledIndex][this->p] += blend(leds[this->ledIndex][this->p],this->color,255); 
}

void Particle::flutter(){
	this->currentMillis = millis();
	if (this->currentMillis - this->previousMillis > this->flutterInterval){
		this->previousMillis = this->currentMillis;
		this->pTarget = random(this->length+32);
		Serial.println("FLUTTER!");
	}
}

void Particle::fall(){
	// if (this->pOrigin < 222){
	// 	this->pOrigin += 1;
	// } else {
	// 	this->pOrigin = 0;
	// }
}
