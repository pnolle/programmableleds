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


// const unsigned int regionU[] {253,252,251,240,241,242,177,176,175,174,173,239,243,250,178,204,205,206,207,238,249,179,203,208,237,244,248,180,202,209,236,245,247,181,201,210,235,246,182,200,197,211,183,199,198,196,212,234,184,195,213,233,185,194,214,232,186,193,215,231,187,192,216,230,188,189,190,191,217,229,218,228,219,227,220,226,221,225,224,223,222};

// const unsigned int ledRegions[23][] {
//   {253,252,251,240,241,242,177,176,175,174,173,239,243,250,178,204,205,206,207,238,249,179,203,208,237,244,248,180,202,209,236,245,247,181,201,210,235,246,182,200,197,211,183,199,198,196,212,234,184,195,213,233,185,194,214,232,186,193,215,231,187,192,216,230,188,189,190,191,217,229,218,228,219,227,220,226,221,225,224,223,222},
//   {253,252,251,240,241,242,177,176,175,174,173,239,243,250,178,204,205,206,207,238,249,179,203,208,237,244,248,180,202,209,236,245,247,181,201,210,235,246,182,200,197,211,183,199,198,196,212,234,184,195,213,233,185,194,214,232,186,193,215,231,187,192,216,230,188,189,190,191,217,229,218,228,219,227,220,226,221,225,224,223,222},
//   {253,252,251,240,241,242,177,176,175,174,173,239,243,250,178,204,205,206,207,238,249,179,203,208,237,244,248,180,202,209,236,245,247,181,201,210,235,246,182,200,197,211,183,199,198,196,212,234,184,195,213,233,185,194,214,232,186,193,215,231,187,192,216,230,188,189,190,191,217,229,218,228,219,227,220,226,221,225,224,223,222},
//   {253,252,251,240,241,242,177,176,175,174,173,239,243,250,178,204,205,206,207,238,249,179,203,208,237,244,248,180,202,209,236,245,247,181,201,210,235,246,182,200,197,211,183,199,198,196,212,234,184,195,213,233,185,194,214,232,186,193,215,231,187,192,216,230,188,189,190,191,217,229,218,228,219,227,220,226,221,225,224,223,222},
//   {253,252,251,240,241,242,177,176,175,174,173,239,243,250,178,204,205,206,207,238,249,179,203,208,237,244,248,180,202,209,236,245,247,181,201,210,235,246,182,200,197,211,183,199,198,196,212,234,184,195,213,233,185,194,214,232,186,193,215,231,187,192,216,230,188,189,190,191,217,229,218,228,219,227,220,226,221,225,224,223,222},
//   {253,252,251,240,241,242,177,176,175,174,173,239,243,250,178,204,205,206,207,238,249,179,203,208,237,244,248,180,202,209,236,245,247,181,201,210,235,246,182,200,197,211,183,199,198,196,212,234,184,195,213,233,185,194,214,232,186,193,215,231,187,192,216,230,188,189,190,191,217,229,218,228,219,227,220,226,221,225,224,223,222},
//   {253,252,251,240,241,242,177,176,175,174,173,239,243,250,178,204,205,206,207,238,249,179,203,208,237,244,248,180,202,209,236,245,247,181,201,210,235,246,182,200,197,211,183,199,198,196,212,234,184,195,213,233,185,194,214,232,186,193,215,231,187,192,216,230,188,189,190,191,217,229,218,228,219,227,220,226,221,225,224,223,222},
//   {253,252,251,240,241,242,177,176,175,174,173,239,243,250,178,204,205,206,207,238,249,179,203,208,237,244,248,180,202,209,236,245,247,181,201,210,235,246,182,200,197,211,183,199,198,196,212,234,184,195,213,233,185,194,214,232,186,193,215,231,187,192,216,230,188,189,190,191,217,229,218,228,219,227,220,226,221,225,224,223,222},
//   {253,252,251,240,241,242,177,176,175,174,173,239,243,250,178,204,205,206,207,238,249,179,203,208,237,244,248,180,202,209,236,245,247,181,201,210,235,246,182,200,197,211,183,199,198,196,212,234,184,195,213,233,185,194,214,232,186,193,215,231,187,192,216,230,188,189,190,191,217,229,218,228,219,227,220,226,221,225,224,223,222},
// /* 10 */  {253,252,251,240,241,242,177,176,175,174,173,239,243,250,178,204,205,206,207,238,249,179,203,208,237,244,248,180,202,209,236,245,247,181,201,210,235,246,182,200,197,211,183,199,198,196,212,234,184,195,213,233,185,194,214,232,186,193,215,231,187,192,216,230,188,189,190,191,217,229,218,228,219,227,220,226,221,225,224,223,222}
// };

#endif 