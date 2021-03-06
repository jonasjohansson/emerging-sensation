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
   25, 255,146,  4,
   63, 224,255,255,
  101,  46,114,226,
  127,   6, 40,127,
  191,   1,  3, 17,
  255,   1,  1,  4};

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

CRGBPalette16 myPal = sky_05_gp;
CRGBPalette16 ravePal = Fuschia_7_gp;
