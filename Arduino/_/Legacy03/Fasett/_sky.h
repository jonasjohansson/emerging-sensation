#define NUM_LEDS 144
#define NUM_PARTS 36
#define LED_PIN 6

/*
 * 
 * Fasett Sky configuration
 * 4 x Proximity
 * 1500mm from center to edge
 * 
 */
 
int lights[NUM_PARTS][3] = {
	{ 0, 35, 1 },     // a1
	{ 35, 36, 1 },    // a2
	{ 71, 36, 1 },    // a3
	{ 107, 36, 1 },   // a4
  { 143, 36, 1 },   // b1
  { 179, 36, 1 },   // b2
  { 215, 36, 1 },   // b3
  { 251, 36, 1 },   // b4
  { 287, 36, 1 },   // c1
  { 323, 36, 1 },   // c2
  { 359, 36, 1 },   // c3
  { 395, 36, 1 },   // c4
  { 431, 36, 1 },   // d1
  { 467, 36, 1 },   // d2
  { 503, 36, 1 },   // d3
  { 539, 36, 1 },   // d4
  { 575, 36, 1 },   // e1
  { 647, 36, 1 },   // e2
  { 683, 36, 1 },   // e3
  { 719, 36, 1 },   // e4
  { 755, 36, 1 },   // f1
  { 791, 36, 1 },   // f2
  { 827, 36, 1 },   // f3
  { 863, 36, 1 },   // f4
  { 899, 36, 1 },   // g1
  { 935, 36, 1 },   // g2
  { 971, 36, 1 },   // g3
  { 1007, 36, 1 },  // g4
};
