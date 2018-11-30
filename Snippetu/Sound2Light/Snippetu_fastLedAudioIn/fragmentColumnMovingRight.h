#ifndef FRAGMENTCOLUMNMOVINGRIGHT
#define FRAGMENTCOLUMNMOVINGRIGHT

#include "fragment.h"
#include "const.h"
#include <FastLED.h>

class ColumnMovingRight : public Fragment
{
    private:
        // shape
        int length, start, colCountLocal, ledCount, currentCol, currentLed;
        LedUtils ledUtils;
    public:
        ColumnMovingRight(int length, int start, LedUtils ledUtils);
        bool nextFrame(CRGB crgbledstrip[]);
};

#endif 