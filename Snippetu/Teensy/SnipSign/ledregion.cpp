#include "ledregion.h"

LedRegion::LedRegion(LedUtils ledUtils) : 
	ledUtils(ledUtils) {

    setColorProperties();
}

void LedRegion::setColorProperties(uint8_t hue, uint8_t sat, uint8_t bri, double hueIncrement) {
    this->hue = hue;
    this->sat = sat;
    this->bri = bri;
    this->hueIncrement = hueIncrement;
}

void LedRegion::setAnimationProperties(int midiNote, int fade) {
    this->midiNote = midiNote;
    this->fade = fade;
}

void LedRegion::nextFrame(vector<PixelUpdate> &matrixUpdate) {
    vector<int> regionU {240,241,242,239,243,204,205,206,207,238,203,208,237,244,209,236,245,247,210,235,246,211,183,196,212,234,184,195,213,233,185,194,214,232,186,193,215,231,187,192,216,230,188,189,190,191,217,229,218,228,219,227,220,226,221,225,224,223,222};
    vector<int> regionP {170,364,365,366,367,368,369,370,169,371,168,372,373,167,374,143,166,144,165,145,164,149,148,147,146,163,150,162,150,161,160,151,159,152,158,157,153,156,155,154};
    vector<int> regionNull {0};

    vector<int> &regionByNote = regionNull;
    if (this->midiNote == 10) {
        regionByNote = regionP;
    }
    else if (this->midiNote == 11) {
        regionByNote = regionP;
    }
    // switch(this->midiNote) {
    //     case 10:
    //         regionByNote = regionU;
    //         break;
    //     case 11:
    //         regionByNote = regionP;
    //         break;
    // }

    for (vector<int>::iterator it = regionByNote.begin(); it != regionByNote.end(); ++it) {
        //Serial.println((String) "regionU " + *it + " ... " + "h " + this->hue + " | s " + this->sat + " | b " + this->bri);

        if (this->hueIncrement > 0) hue = ledUtils.incrementHue(this->hue, this->hueIncrement);

        PixelUpdate onePixelUpdate;
        onePixelUpdate.ledNum = *it;
        onePixelUpdate.hue = hue;
        onePixelUpdate.sat = this->sat;
        onePixelUpdate.bri = this->bri;
        onePixelUpdate.fade = this->fade;
        matrixUpdate.push_back(onePixelUpdate);
    }
}
