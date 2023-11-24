#ifndef FRAGMENT
#define FRAGMENT

#include "Arduino.h"
#include "constMatrix.h"
#include "pixelUpdate.h"
#include "FastLED.h"
#include "vector"

using namespace std;

class Fragment
{
    protected:
        // animation
        int wait, fade;
        // color
        double hueIncrement;
        uint8_t hue, sat, bri;
    public:
        Fragment() {};
        virtual void setAnimationProperties(int wait=10, int fade=250, bool reverse=false, int length=0, int start=0);
        virtual void setColorProperties(uint8_t hue=0, uint8_t sat=0, uint8_t bri=255, double hueIncrement=0);
        virtual void nextFrame(unsigned long currentTime, vector<PixelUpdate> &matrixUpdate);
        virtual void resetTimer(unsigned long time);
        virtual ~Fragment() {};
};

#endif 
