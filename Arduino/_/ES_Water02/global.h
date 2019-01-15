#define NUM_LEDS 300
#define NUM_STEMS 3
#define NUM_BRANCHES 3
#define NUM_BUDS 3

#define WB_NUM_PARTS 10
#define WB_NUM_STEMS 3
#define WB_NUM_BRANCHES 4
#define WB_NUM_BUDS 3

int WB_MAP[WB_NUM_PARTS][2] = {
  {0,24},     // 0, stem 1
  {24,24},    // 1, stem 2
  {48,15},    // 2, bud 1
  {63,24},    // 3, stem 3    
  {87,24},    // 4, branch 1
  {111,15},   // 5, bud2
  {126,24},   // 6, branch 2
  {150,15},   // 7, bud 3
  {165,24},   // 8, branch 3
  {189,24},   // 9, branch 4
};

int WB_STEMS[WB_NUM_STEMS]= { 0,1,3 };
int WB_BRANCHES[WB_NUM_BRANCHES] = { 4,6,8,9  };
int WB_BUDS[WB_NUM_BUDS] = { 2,7,5 };
int WB_TREE[WB_NUM_STEMS+WB_NUM_BRANCHES] = { 0,1,4,6,3,8,9 };
