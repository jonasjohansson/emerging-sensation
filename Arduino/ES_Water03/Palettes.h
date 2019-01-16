DEFINE_GRADIENT_PALETTE( white_p) {
    0, 255, 255, 255,
  255, 255, 255, 255};
    
DEFINE_GRADIENT_PALETTE( a_p ) {
    0, 96, 30, 0,
   128, 128, 40,  0,
  255,  96,  50,  0};

DEFINE_GRADIENT_PALETTE( b_p ) {
    0, 206, 78, 44,
   68, 167, 57,155,
  165,  92,  1, 37,
  255,   1,  1,  9};

DEFINE_GRADIENT_PALETTE( c_p ) {
    0, 	0, 	128, 65,
  128,  0,	128,255,
  255,  0, 	0, 	255};

const TProgmemRGBGradientPalettePtr backgrounds_p[3] = {
  a_p,
  b_p,
  c_p
};

CRGB budCols[3] = {CRGB(0,0,255), CRGB(0,255,0), CRGB(255,0,0)};
