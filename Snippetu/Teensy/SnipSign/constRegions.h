#ifndef CONSTREGIONS
#define CONSTREGIONS

#include "ledUtils.h"
#include "vector"

using namespace std;

// SnipSign
// Glossary:
// 0: [array length (n)]
// 1-n: [startPx][lengthPx][color]

const unsigned int blinders[][3] = {
  {2},
  {44, 8, 0xffffff},
  {97, 8, 0xffffff}
};
const unsigned int snippet[][3] = {
  {2},
  {53, 30, 0xe71709},
  {124, 15, 0xf6a46a}
};
const unsigned int upper[][3] = {
  {4},
  {29, 15, 0xacdfe5},
  {138, 12, 0x171f8a},
  {83, 15, 0x171f8a},
  {104, 18, 0xacdfe5}
};
const unsigned int laser[][3] = {
  {1},
  {1, 28, 0xe71709}
};
#endif 
