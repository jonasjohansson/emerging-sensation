  DEFINE_GRADIENT_PALETTE( sky_14_gp ) {
    0, 164, 78, 192,
   68, 128, 57,  92,
  165,  44,  1,  96,
  255,   1,  1,  64};

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
    0,   1,  0,  1,
  192, 123, 24, 64,
  230, 194, 87, 87,
  255, 255,184,160};


const TProgmemRGBGradientPalettePtr gGradientPalettes[3] = {
	sky_12_gp,
	sky_12_gp,
	test
};

CRGBPalette16 buds_p = peach_purple_gp;
