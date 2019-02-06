#ifndef REGION
#define REGION

#include "Arduino.h"
#include "pixelUpdate.h"
#include "FastLED.h"
#include "constRegions.h"
#include "constMatrix.h"

using namespace std;

class LedRegion
{
    protected:
        // animation
        int midiNote;
        int fade;
        // color
        double hueIncrement;
        uint8_t hue, sat, bri;
        LedUtils ledUtils;
    public:
        LedRegion(LedUtils ledUtils, int midiNote=0);
        virtual void setAnimationProperties(int midiNote, int fade=250);
        virtual void setColorProperties(uint8_t hue=0, uint8_t sat=0, uint8_t bri=255, double hueIncrement=0);
        virtual void nextFrame(vector<PixelUpdate> &matrixUpdate);
        virtual ~LedRegion() {};
};

#endif 
