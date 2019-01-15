  // DEFINE_GRADIENT_PALETTE( sky_14_gp ) {
  //   0, 40, 50, 192,
  //  68, 80, 0,  255,
  // 165,  44,  1,  144,
  // 255,   1,  1,  64};

DEFINE_GRADIENT_PALETTE( sky_14_gp ) {
    0, 94, 9, 192,
   128, 50, 0,  255,
  255,  84,  1,  144};

DEFINE_GRADIENT_PALETTE( sky_12_gp ) {
    0, 206, 78, 44,
   68, 167, 57,155,
  165,  92,  1, 37,
  255,   1,  1,  9};

DEFINE_GRADIENT_PALETTE( test ) {
    0, 	0, 	128, 65,
  128,  0,	128,255,
  255,  0, 	0, 	255};

DEFINE_GRADIENT_PALETTE( sky_39_gp ) {
    0, 247,255, 85,
   36, 255,248,  0,
  140,  77,  6,  1,
  255,  16,  1,  0};

DEFINE_GRADIENT_PALETTE( sky_15_gp ) {
    0,  27,161,233,
   90,   1,104,212,
  153,   1, 42,137,
  255,   1,  5, 38};
  // Gradient palette "peach_purple_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/neota/liht/tn/peach-purple.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 264 bytes of program space.

DEFINE_GRADIENT_PALETTE( peach_purple_gp ) {
    0, 0, 0,255,
  192, 0, 0, 64,
  230, 0, 0, 87,
  255, 0,184,160};


const TProgmemRGBGradientPalettePtr backgrounds_p[3] = {
  sky_14_gp,
  sky_12_gp,
  test
};

const TProgmemRGBGradientPalettePtr buds_p[3] = {
  peach_purple_gp,
  peach_purple_gp,
  peach_purple_gp
};

CRGB budCols[3] = {CRGB(0,255,255), CRGB(0,250,255), CRGB::Red};
