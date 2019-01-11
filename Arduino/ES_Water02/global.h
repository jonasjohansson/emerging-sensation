#define NUM_LEDS 300
#define NUM_STEMS 3
#define NUM_BRANCHES 3
#define NUM_BUDS 3

#define WB_NUM_PARTS 10
#define WB_NUM_STEMS 2
#define WB_NUM_BRANCHES 5
#define WB_NUM_BUDS 3

int WB_MAP[WB_NUM_PARTS][2] = {
  {0,24},     // 0, stem 1
  {24,48},    // 1, branch 1
  {48,63},    // 2, bud 1
  {63,87},    // 3, stem 2    
  {120,144},  // 4, branch 2
  {168,192},  // 5, branch 3
  {192,216},  // 6, branch 4
  {216,216},  // 7, branch 5
  {216,216},  // 8, bud 3
};

int WB_STEMS[WB_NUM_STEMS]= { 0,3 };
int WB_BRANCHES[WB_NUM_BRANCHES] = { 1,4,5,6 };
int WB_BUDS[WB_NUM_BUDS] = { 2,7,8 };
