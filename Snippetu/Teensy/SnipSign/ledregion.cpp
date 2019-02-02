#include "ledregion.h"

LedRegion::LedRegion(LedUtils ledUtils, int midiNote) : ledUtils(ledUtils), midiNote(midiNote)
{
    setColorProperties();
}

void LedRegion::setColorProperties(uint8_t hue, uint8_t sat, uint8_t bri, double hueIncrement)
{
    this->hue = hue;
    this->sat = sat;
    this->bri = bri;
    this->hueIncrement = hueIncrement;
}

void LedRegion::setAnimationProperties(int midiNote, int fade)
{
    this->midiNote = midiNote;
    this->fade = fade;
}

void LedRegion::nextFrame(vector<PixelUpdate> &matrixUpdate)
{
    int regionUCount = 59;
    int regionU[regionUCount] = {240, 241, 242, 239, 243, 204, 205, 206, 207, 238, 203, 208, 237, 244, 209, 236, 245, 247, 210, 235, 246, 211, 183, 196, 212, 234, 184, 195, 213, 233, 185, 194, 214, 232, 186, 193, 215, 231, 187, 192, 216, 230, 188, 189, 190, 191, 217, 229, 218, 228, 219, 227, 220, 226, 221, 225, 224, 223, 222};
    int regionP1Count = 40;
    int regionP1[regionP1Count] = {170, 364, 365, 366, 367, 368, 369, 370, 169, 371, 168, 372, 373, 167, 374, 143, 166, 144, 165, 145, 164, 149, 148, 147, 146, 163, 150, 162, 150, 161, 160, 151, 159, 152, 158, 157, 153, 156, 155, 154};
    int regionP2Count = 38;
    int regionP2[regionP2Count] = {380, 381, 382, 383, 384, 385, 386, 378, 379, 387, 377, 388, 376, 389, 375, 390, 141, 120, 140, 121, 122, 139, 126, 125, 124, 123, 127, 138, 128, 137, 129, 136, 130, 135, 131, 134, 133, 132};
    int regionECount = 54;
    int regionE[regionECount] = {396, 397, 398, 399, 400, 401, 402, 394, 395, 403, 392, 393, 391, 404, 405, 119, 406, 118, 407, 117, 408, 116, 409, 410, 411, 115, 412, 114, 113, 420, 419, 418, 417, 416, 415, 414, 413, 421, 422, 423, 424, 425, 426, 427, 428, 429, 112, 111, 110, 109, 108, 107, 106, 105};

    int thisCount = 0;
    int *thisRegion;
    switch (this->midiNote)
    {
    case 10:
        thisCount = regionUCount;
        thisRegion = regionU;
        break;
    case 11:
        thisCount = regionP1Count;
        thisRegion = regionP1;
        break;
    case 12:
        thisCount = regionP2Count;
        thisRegion = regionP2;
        break;
    case 13:
        thisCount = regionECount;
        thisRegion = regionE;
        break;
    }

    if (thisCount > 0)
    {

        for (int i = 0; i < thisCount; i++)
        {
            if (DEBUG) Serial.println((String) "region " + i + " ... " + thisRegion[i] + " ... h " + this->hue + " | s " + this->sat + " | b " + this->bri);

            if (this->hueIncrement > 0)
                hue = ledUtils.incrementHue(this->hue, this->hueIncrement);

            PixelUpdate onePixelUpdate;
            onePixelUpdate.ledNum = thisRegion[i];
            onePixelUpdate.hue = hue;
            onePixelUpdate.sat = this->sat;
            onePixelUpdate.bri = this->bri;
            onePixelUpdate.fade = this->fade;
            matrixUpdate.push_back(onePixelUpdate);
        }
    }
}
