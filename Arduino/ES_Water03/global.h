/*
   https://github.com/FastLED/FastLED/wiki/Pixel-reference
   A: 222 (6x25 + 1x27 + 3x15)
   B: 213 (7x24 + 3x uu15)
   C: 300 (10x24 + 4x15)
*/

#define NUM_SENSORS 10
#define NUM_LEDS 300
#define NUM_STRIPS 3
#define NUM_PARTICLES 60

#define WA_NUM_PARTS 10
#define WB_NUM_PARTS 10
#define WC_NUM_PARTS 14

int LEDS_PER_STRIP[NUM_STRIPS] = {222, 213, 300};
int SENSORS_PER_STRIP[NUM_STRIPS] = {3, 3, 4};

int WA_MAP[WA_NUM_PARTS][2] = {
  {0, 24},    // 0, stem 1
  {24, 24},   // 1, stem 2
  {48, 15},   // 2, bud 1
  {63, 24},   // 3, stem 3
  {87, 24},   // 4, branch 1
  {111, 15},  // 5, bud2
  {126, 24},  // 6, branch 2
  {150, 15},  // 7, bud 3
  {165, 27},  // 8, branch 3
  {192, 24},  // 9, branch 4
};

int WB_MAP[WB_NUM_PARTS][2] = {
  {0, 24},    // 0, stem 1
  {24, 24},   // 1, stem 2
  {48, 15},   // 2, bud 1
  {63, 24},   // 3, stem 3
  {87, 24},   // 4, branch 1
  {111, 15},  // 5, bud2
  {126, 24},  // 6, branch 2
  {150, 15},  // 7, bud 3
  {165, 24},  // 8, branch 3
  {189, 24},  // 9, branch 4
};

int WC_MAP[WC_NUM_PARTS][2] = {
  {0, 24},    // 0, stem 1
  {24, 24},   // 1, stem 2
  {48, 15},   // 2, bud 1
  {63, 15},   // 3, stem 3
  {87, 24},   // 4, branch 1
  {111, 24},  // 5, bud2
  {126, 24},  // 6, branch 2
  {150, 15},  // 7, bud 3
  {165, 24},  // 8, branch 3
  {189, 24},  // 9, branch 4
  {213, 15},  // 10, branch 4
  {228, 24},  // 11, branch 4
  {252, 24},  // 12, branch 4
  {276, 24},  // 13, branch 4
};

int BUDS_PER_STRIP[NUM_STRIPS] = { 3, 3, 4 };
int BUDS[NUM_STRIPS][4] = {
  { 48, 111, 150 },
  { 48, 150, 111 },
  { 48, 63, 150, 213 }
};
