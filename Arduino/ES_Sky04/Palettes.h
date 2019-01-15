// Gradient palette "purplefly_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/rc/tn/purplefly.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 16 bytes of program space.

DEFINE_GRADIENT_PALETTE( purplefly_gp ) {
    0,   0,  0,  0,
   63, 239,  0,122,
  191, 252,255, 78,
  255,   0,  0,  0};

// Gradient palette "sky_05_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/rafi/tn/sky-05.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE( sky_05_gp ) {
    0, 252, 61,  2,
   35, 255,146,  4,
   63, 224,255,255,
  121,  46,114,226,
  147,   30, 40,255,
  201,   1,  3, 255,
  255,   1,  1,  255};

DEFINE_GRADIENT_PALETTE( spin_gp ) {
    0, 255, 0, 0,
150,255,255,0,
255,255,255,255};

// Gradient palette "Fuschia_7_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ds/fuschia/tn/Fuschia-7.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE( Fuschia_7_gp ) {
    0,  43,  3,153,
   63, 100,  4,103,
  127, 188,  5, 66,
  191, 161, 11,115,
  255, 135, 20,182};


DEFINE_GRADIENT_PALETTE(skyPalette) {
  0,		0,  	0, 		0,
  32, 	192,  64, 	192,
  64,  	255,  0, 0,
  128,  255,  80, 0,
  255,  255,  44, 0
};

DEFINE_GRADIENT_PALETTE(ravePalette) {
  0,    255,    0,    0,
  85,   0,  255,   0,
  170,   0,  0, 255,
  255,  255,  0, 0
};

CRGBPalette16 fullPal = sky_05_gp;
CRGBPalette16 ravePal = ravePalette;
CRGBPalette16 spinPal = spin_gp;
