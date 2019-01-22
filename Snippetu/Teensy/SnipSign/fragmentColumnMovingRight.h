#ifndef FRAGMENTCOLUMNMOVINGRIGHT
#define FRAGMENTCOLUMNMOVINGRIGHT

#include "fragment.h"

class ColumnMovingRight : public Fragment
{
    private:
        // shape
        int length, start, colCountLocal, currentCol, currentLed;
        LedUtils ledUtils;
        unsigned long time;
    public:
        ColumnMovingRight(LedUtils ledUtils, unsigned long time);
        void setAnimationProperties(int length=0, int start=0, int wait=10, int fade=250);
        void setColorProperties(uint8_t hue=0, uint8_t sat=0, uint8_t bri=255, double hueIncrement=0);
        void nextFrame(unsigned long currentTime, vector<PixelUpdate> &matrixUpdate, bool &animationFinished);
        void resetTimer(unsigned long time);
        String getValues();
};

#endif 