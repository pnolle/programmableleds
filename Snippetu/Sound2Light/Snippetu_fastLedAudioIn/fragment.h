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
        virtual void setAnimationProperties(int wait, int fade);
        virtual void setColorProperties(double hue, int sat, int bri, double hueIncrement=0);
        virtual std::vector<PixelUpdate> nextFrame();
        virtual ~Fragment() {};
};

#endif 