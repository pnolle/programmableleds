#ifndef FRAGMENT
#define FRAGMENT

#include "Arduino.h"
#include "const.h"
#include "pixelUpdate.h"
#include <FastLED.h>
#include <StandardCplusplus.h>
#include "vector"

class Fragment
{
    protected:
        // animation
        int wait, fade;
        // color
        double hue, hueIncrement;
        int sat, bri;
    public:
        Fragment() {};
        virtual void setAnimationProperties(int length=0, int start=0, int wait=10, int fade=250);
        virtual void setColorProperties(double hue=0, int sat=0, int bri=255, double hueIncrement=0);
        virtual std::vector<PixelUpdate> nextFrame(unsigned long currentTime);
        virtual void resetTimer(unsigned long time);
        virtual ~Fragment() {};
};

#endif 