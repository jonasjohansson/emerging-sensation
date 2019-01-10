
#define DAMPING 0.899

class Particle {
  private:
    int x;
    int y;
    int oldX;
    int oldY;
    int originX;
    int originY;
  public:
    void init(int x, int y);
    void integrate();
    void attract(int x, int y);
    void draw();
};


Particle::init(int x, int y){
//Particle::Particle(){
  this->x = this->oldX = this->originX = x;
  this->x = this->oldX = this->originY = y;
  return;
}

Particle::integrate(){
  int velocityX = (this->x - this->oldX) * DAMPING;
  int velocityY = (this->y - this->oldY) * DAMPING;
  this->oldX = this->x;
  this->oldY = this->y;
  this->x += velocityX;
  this->y += velocityY;
}

Particle::attract(int x, int y){
  int dx = x - this->x;
  int dy = y = this->y;
  int distance = sqrt(dx * dx + dy * dy);
  this->x += dx / distance;
  this->y += dy / distance;
}

Particle::draw(){
  // turn pixels on/off
}
