#ifndef FRAGMENTCOLUMNMOVINGRIGHT
#define FRAGMENTCOLUMNMOVINGRIGHT

#include "fragment.h"

class ColumnMovingRight : public Fragment
{
    private:
        int matrix, length, start;
    public:
        ColumnMovingRight(int matrix, int length, int start);
        void setAnimationProperties(int wait, int fade);
        void setColorProperties(double hue, double hueIncrement, int sat, int bri);
        void nextFrame();
};

#endif 