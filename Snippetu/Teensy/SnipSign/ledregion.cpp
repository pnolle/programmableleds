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
    int regionSCount = 46;
    int regionS[regionSCount] = {254, 292, 293, 290, 291, 294, 289, 295, 288, 296, 286, 287, 297, 285, 298, 284, 283, 282, 281, 280, 299, 279, 278, 276, 277, 267, 275, 266, 268, 274, 273, 265, 269, 272, 270, 271, 255, 264, 257, 256, 263, 258, 259, 262, 260, 261};
    int regionNCount = 7;
    int regionN[regionNCount] = {301, 302, 300, 253, 252, 251, 250};

    int regionSICount = 6;
    int regionSI[regionSICount] = {303, 306, 307, 305, 304, 249};

    int regionSP1Count = 12;
    int regionSP1[regionSP1Count] = {308, 309, 310, 248, 177, 176, 247, 178, 246, 179, 180, 181};
    int regionSP2Count = 13;
    int regionSP2[regionSP2Count] = {311, 313, 312, 175, 174, 173, 205, 201, 200, 197, 199, 198, 202};
    int regionSECount = 6;
    int regionSE[regionSECount] = {315, 314, 316, 171, 363, 172};
    int regionSTCount = 21;
    int regionST[regionSTCount] = {326, 325, 327, 324, 328, 323, 322, 321, 363, 362, 318, 353, 317, 354, 355, 356, 357, 358, 359, 360, 361};
    int regionSC1Count = 3;
    int regionSC1[regionSC1Count] = {329, 330, 352};
    int regionSC2Count = 3;
    int regionSC2[regionSC2Count] = {331, 351, 350};
    int regionSCISSORSCount = 18;
    int regionSCISSORS[regionSCISSORSCount] = {332, 337, 338, 335, 336, 339, 333, 334, 340, 341, 342, 348, 347, 346, 343, 349, 345, 344};
    int regionUCount = 59;
    int regionU[regionUCount] = {240, 241, 242, 239, 243, 204, 205, 206, 207, 238, 203, 208, 237, 244, 209, 236, 245, 247, 210, 235, 246, 211, 183, 196, 212, 234, 184, 195, 213, 233, 185, 194, 214, 232, 186, 193, 215, 231, 187, 192, 216, 230, 188, 189, 190, 191, 217, 229, 218, 228, 219, 227, 220, 226, 221, 225, 224, 223, 222};
    int regionP1Count = 40;
    int regionP1[regionP1Count] = {170, 364, 365, 366, 367, 368, 369, 370, 169, 371, 168, 372, 373, 167, 374, 143, 166, 144, 165, 145, 164, 149, 148, 147, 146, 163, 150, 162, 150, 161, 160, 151, 159, 152, 158, 157, 153, 156, 155, 154};
    int regionP2Count = 38;
    int regionP2[regionP2Count] = {380, 381, 382, 383, 384, 385, 386, 378, 379, 387, 377, 388, 376, 389, 375, 390, 141, 120, 140, 121, 122, 139, 126, 125, 124, 123, 127, 138, 128, 137, 129, 136, 130, 135, 131, 134, 133, 132};
    int regionECount = 54;
    int regionE[regionECount] = {396, 397, 398, 399, 400, 401, 402, 394, 395, 403, 392, 393, 391, 404, 405, 119, 406, 118, 407, 117, 408, 116, 409, 410, 411, 115, 412, 114, 113, 420, 419, 418, 417, 416, 415, 414, 413, 421, 422, 423, 424, 425, 426, 427, 428, 429, 112, 111, 110, 109, 108, 107, 106, 105};
    int regionRCount = 54;
    int regionR[regionRCount] = {442, 443, 444, 445, 446, 440, 441, 447, 448, 438, 439, 449, 450, 451, 437, 436, 452, 435, 453, 434, 454, 456, 455, 433, 458, 457, 432, 459, 460, 431, 467, 466, 465, 464, 463, 462, 461, 468, 469, 470, 471, 472, 473, 474, 475, 103, 102, 101, 100, 99, 98, 97, 96, 95};
    int regionLaser1Count = 11;
    int regionLaser1[regionLaser1Count] = {66, 67, 68, 69, 65, 64, 63, 62, 61, 60, 70};
    int regionLLCount = 17;
    int regionLL[regionLLCount] = {421, 422, 423, 424, 112, 74, 75, 73, 76, 72, 77, 71, 59, 58, 57, 56, 55};
    int regionLACount = 16;
    int regionLA[regionLACount] = {425, 426, 427, 111, 110, 109, 108, 78, 79, 80, 81, 54, 53, 52, 51, 50};
    int regionLSCount = 21;
    int regionLS[regionLSCount] = {428, 429, 430, 467, 468, 107, 106, 105, 104, 103, 107, 106, 82, 83, 84, 85, 86, 48, 47, 46, 45};
    int regionLECount = 14;
    int regionLE[regionLECount] = {469, 470, 471, 102, 101, 100, 99, 87, 88, 89, 44, 43, 42, 41};
    int regionLRCount = 25;
    int regionLR[regionLRCount] = {472, 473, 474, 475, 476, 477, 478, 98, 97, 96, 95, 90, 91, 92, 93, 94, 34, 479, 35, 33, 36, 40, 39, 38, 37};
    int regionLaser2Count = 33;
    int regionLaser2[regionLaser2Count] = {8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15, 0, 16, 17, 32, 18, 31, 19, 30, 20, 29, 21, 28, 22, 27, 23, 26, 24, 25};

    int thisCount = 0;
    int *thisRegion;
    Serial.print(this->midiNote);
    switch (this->midiNote)
    {
    case 0:
        thisCount = regionSCount;
        thisRegion = regionS;
        break;
    case 1:
        thisCount = regionNCount;
        thisRegion = regionN;
        break;
    case 2:
        thisCount = regionSICount;
        thisRegion = regionSI;
        break;
    case 3:
        thisCount = regionSP1Count;
        thisRegion = regionSP1;
        break;
    case 4:
        thisCount = regionSP2Count;
        thisRegion = regionSP2;
        break;
    case 5:
        thisCount = regionSECount;
        thisRegion = regionSE;
        break;
    case 6:
        thisCount = regionSTCount;
        thisRegion = regionST;
        break;
    case 7:
        thisCount = regionSC1Count;
        thisRegion = regionSC1;
        break;
    case 8:
        thisCount = regionSC2Count;
        thisRegion = regionSC2;
        break;
    case 9:
        thisCount = regionSCISSORSCount;
        thisRegion = regionSCISSORS;
        break;
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
    case 14:
        thisCount = regionRCount;
        thisRegion = regionR;
        break;
    case 15:
        thisCount = regionLaser1Count;
        thisRegion = regionLaser1;
        break;
    case 16:
        thisCount = regionLLCount;
        thisRegion = regionLL;
        break;
    case 17:
        thisCount = regionLACount;
        thisRegion = regionLA;
        break;
    case 18:
        thisCount = regionLSCount;
        thisRegion = regionLS;
        break;
    case 19:
        thisCount = regionLECount;
        thisRegion = regionLE;
        break;
    case 20:
        thisCount = regionLRCount;
        thisRegion = regionLR;
        break;
    case 21:
        thisCount = regionLaser2Count;
        thisRegion = regionLaser2;
        break;
    }

    if (thisCount > 0)
    {
        Serial.println((String)"thisCount " + thisCount);
        for (int i = 0; i < thisCount; i++)
        {
            Serial.println((String) "region " + i + " ... " + thisRegion[i] + " ... h " + this->hue + " | s " + this->sat + " | b " + this->bri);

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
