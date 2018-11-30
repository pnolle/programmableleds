#ifndef FRAGMENTCOLUMNMOVINGRIGHT
#define FRAGMENTCOLUMNMOVINGRIGHT

#include "fragment.h"

class ColumnMovingRight : public Fragment
{
    private:
        // shape
        int length, start, colCountLocal, currentCol, currentLed;
        LedUtils ledUtils;
    public:
        ColumnMovingRight(int length, int start, LedUtils ledUtils);
        void setAnimationProperties(int wait=10, int fade=240);
        void setColorProperties(double hue=0, int sat=0, int bri=255, double hueIncrement=0);
        std::vector<PixelUpdate> nextFrame();
        String getValues();
};

#endif 