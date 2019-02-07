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
//    private:
//        const uint16_t getColRegion();
    protected:
        // animation
        uint8_t midiNote;
        uint8_t channel;
        int fade;
        // color
        double hueIncrement;
        uint8_t hue, sat, bri;
        LedUtils ledUtils;
    public:
        LedRegion(LedUtils ledUtils, uint8_t midiNote=0, uint8_t channel=1);
        virtual void setAnimationProperties(uint8_t midiNote, uint8_t channel, int fade=250);
        virtual void setColorProperties(uint8_t hue=0, uint8_t sat=0, uint8_t bri=255, double hueIncrement=0);
        virtual void nextFrame(vector<PixelUpdate> &matrixUpdate);
        virtual ~LedRegion() {};
};

#endif 
