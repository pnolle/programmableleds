#include "ledregion.h"

LedRegion::LedRegion(LedUtils ledUtils, uint8_t midiNote, uint8_t channel) : ledUtils(ledUtils), midiNote(midiNote), channel(channel)
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

void LedRegion::setAnimationProperties(uint8_t midiNote, uint8_t channel, int fade)
{
    this->midiNote = midiNote;
    this->channel = channel;
    this->fade = fade;
}

void LedRegion::nextFrame(vector<PixelUpdate> &matrixUpdate)
{
    const int16_t regionSCount = 46;
    const int16_t regionS[regionSCount] = {254, 292, 293, 290, 291, 294, 289, 295, 288, 296, 286, 287, 297, 285, 298, 284, 283, 282, 281, 280, 299, 279, 278, 276, 277, 267, 275, 266, 268, 274, 273, 265, 269, 272, 270, 271, 255, 264, 257, 256, 263, 258, 259, 262, 260, 261};
    const int16_t regionNCount = 7;
    const int16_t regionN[regionNCount] = {301, 302, 300, 253, 252, 251, 250};
    const int16_t regionSICount = 6;
    const int16_t regionSI[regionSICount] = {303, 306, 307, 305, 304, 249};
    const int16_t regionSPCount = 12;
    const int16_t regionSP[regionSPCount] = {308, 309, 310, 248, 177, 176, 247, 178, 246, 179, 180, 181};
    const int16_t regionSP2Count = 13;
    const int16_t regionSP2[regionSP2Count] = {311, 313, 312, 175, 174, 173, 205, 201, 200, 197, 199, 198, 202};
    const int16_t regionSECount = 6;
    const int16_t regionSE[regionSECount] = {315, 314, 316, 171, 363, 172};
    const int16_t regionSTCount = 21;
    const int16_t regionST[regionSTCount] = {326, 325, 327, 324, 328, 323, 322, 321, 363, 362, 318, 353, 317, 354, 355, 356, 357, 358, 359, 360, 361};
    const int16_t regionSC1Count = 3;
    const int16_t regionSC1[regionSC1Count] = {329, 330, 352};
    const int16_t regionSC2Count = 3;
    const int16_t regionSC2[regionSC2Count] = {331, 351, 350};
    const int16_t regionSCISSORSCount = 18;
    const int16_t regionSCISSORS[regionSCISSORSCount] = {332, 337, 338, 335, 336, 339, 333, 334, 340, 341, 342, 348, 347, 346, 343, 349, 345, 344};
    const int16_t regionUCount = 59;
    const int16_t regionU[regionUCount] = {240, 241, 242, 239, 243, 204, 205, 206, 207, 238, 203, 208, 237, 244, 209, 236, 245, 247, 210, 235, 246, 211, 183, 196, 212, 234, 184, 195, 213, 233, 185, 194, 214, 232, 186, 193, 215, 231, 187, 192, 216, 230, 188, 189, 190, 191, 217, 229, 218, 228, 219, 227, 220, 226, 221, 225, 224, 223, 222};
    const int16_t regionP1Count = 40;
    const int16_t regionP1[regionP1Count] = {170, 364, 365, 366, 367, 368, 369, 370, 169, 371, 168, 372, 373, 167, 374, 143, 166, 144, 165, 145, 164, 149, 148, 147, 146, 163, 150, 162, 150, 161, 160, 151, 159, 152, 158, 157, 153, 156, 155, 154};
    const int16_t regionPARRCount = 9;
    const int16_t regionPARR[regionPARRCount] = {138, 137, 136, 130, 135, 131, 134, 133, 132};
    const int16_t regionP2Count = 29;
    const int16_t regionP2[regionP2Count] = {380, 381, 382, 383, 384, 385, 386, 378, 379, 387, 377, 388, 376, 389, 375, 390, 141, 120, 140, 121, 122, 139, 126, 125, 124, 123, 127, 129, 128};
    const int16_t regionECount = 54;
    const int16_t regionE[regionECount] = {396, 397, 398, 399, 400, 401, 402, 394, 395, 403, 392, 393, 391, 404, 405, 119, 406, 118, 407, 117, 408, 116, 409, 410, 411, 115, 412, 114, 113, 420, 419, 418, 417, 416, 415, 414, 413, 421, 422, 423, 424, 425, 426, 427, 428, 429, 112, 111, 110, 109, 108, 107, 106, 105};
    const int16_t regionRCount = 54;
    const int16_t regionR[regionRCount] = {442, 443, 444, 445, 446, 440, 441, 447, 448, 438, 439, 449, 450, 451, 437, 436, 452, 435, 453, 434, 454, 456, 455, 433, 458, 457, 432, 459, 460, 431, 467, 466, 465, 464, 463, 462, 461, 468, 469, 470, 471, 472, 473, 474, 475, 103, 102, 101, 100, 99, 98, 97, 96, 95};
    const int16_t regionLaser1Count = 11;
    const int16_t regionLaser1[regionLaser1Count] = {66, 67, 68, 69, 65, 64, 63, 62, 61, 60, 70};
    const int16_t regionLLCount = 16;
    const int16_t regionLL[regionLLCount] = {422, 423, 424, 112, 74, 75, 73, 76, 72, 77, 71, 59, 58, 57, 56, 55};
    const int16_t regionLACount = 16;
    const int16_t regionLA[regionLACount] = {425, 426, 427, 111, 110, 109, 108, 78, 79, 80, 81, 54, 53, 52, 51, 50};
    const int16_t regionLSCount = 21;
    const int16_t regionLS[regionLSCount] = {428, 429, 430, 467, 468, 107, 106, 105, 104, 103, 107, 106, 82, 83, 84, 85, 86, 48, 47, 46, 45};
    const int16_t regionLECount = 14;
    const int16_t regionLE[regionLECount] = {469, 470, 471, 102, 101, 100, 99, 87, 88, 89, 44, 43, 42, 41};
    const int16_t regionLRCount = 25;
    const int16_t regionLR[regionLRCount] = {472, 473, 474, 475, 476, 477, 478, 98, 97, 96, 95, 90, 91, 92, 93, 94, 34, 479, 35, 33, 36, 40, 39, 38, 37};
    const int16_t regionLaser2Count = 33;
    const int16_t regionLaser2[regionLaser2Count] = {8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15, 0, 16, 17, 32, 18, 31, 19, 30, 20, 29, 21, 28, 22, 27, 23, 26, 24, 25};
    const int16_t regionSnippetCount = 135;
    const int16_t regionSnippet[regionSnippetCount] = {254, 292, 293, 290, 291, 294, 289, 295, 288, 296, 286, 287, 297, 285, 298, 284, 283, 282, 281, 280, 299, 279, 278, 276, 277, 267, 275, 266, 268, 274, 273, 265, 269, 272, 270, 271, 255, 264, 257, 256, 263, 258, 259, 262, 260, 261, 301, 302, 300, 253, 252, 251, 250, 303, 306, 307, 305, 304, 249, 308, 309, 310, 248, 177, 176, 247, 178, 246, 179, 180, 181, 311, 313, 312, 175, 174, 173, 205, 201, 200, 197, 199, 198, 202, 315, 314, 316, 171, 363, 172, 326, 325, 327, 324, 328, 323, 322, 321, 363, 362, 318, 353, 317, 354, 355, 356, 357, 358, 359, 360, 361, 329, 330, 352, 331, 351, 350, 332, 337, 338, 335, 336, 339, 333, 334, 340, 341, 342, 348, 347, 346, 343, 349, 345, 344};
    const int16_t regionUpperCount = 123;
    const int16_t regionUpper[regionUpperCount] = {240, 242, 243, 205, 207, 203, 237, 209, 245, 210, 246, 183, 212, 184, 213, 185, 214, 186, 215, 187, 216, 188, 190, 217, 218, 219, 220, 221, 224, 222, 364, 366, 368, 370, 371, 372, 167, 143, 144, 145, 149, 147, 163, 162, 161, 151, 152, 157, 156, 154, 137, 130, 131, 133, 380, 382, 384, 386, 379, 377, 376, 375, 141, 140, 122, 126, 124, 127, 128, 397, 399, 401, 394, 403, 393, 404, 119, 118, 117, 116, 410, 115, 114, 420, 418, 416, 414, 421, 423, 425, 427, 429, 111, 109, 107, 105, 443, 445, 440, 447, 438, 449, 451, 436, 435, 434, 456, 433, 457, 459, 431, 466, 464, 462, 468, 470, 472, 474, 103, 101, 99, 97, 95};
    const int16_t regionLaserCount = 68;
    const int16_t regionLaser[regionLaserCount] = {66, 68, 65, 63, 61, 70, 423, 112, 75, 76, 77, 59, 57, 55, 426, 111, 109, 78, 80, 54, 52, 50, 429, 467, 107, 105, 103, 106, 83, 85, 48, 46, 469, 471, 101, 99, 88, 44, 42, 472, 474, 476, 478, 97, 95, 91, 93, 34, 35, 36, 39, 37, 7, 6, 5, 4, 3, 2, 1, 0, 17, 18, 19, 20, 21, 22, 23, 24};
    const int16_t regionAllCount = 240;
    const int16_t regionAll[regionAllCount] = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 66, 68, 70, 72, 74, 76, 78, 80, 82, 84, 86, 88, 90, 92, 94, 96, 98, 100, 102, 104, 106, 108, 110, 112, 114, 116, 118, 120, 122, 124, 126, 128, 130, 132, 134, 136, 138, 140, 142, 144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 166, 168, 170, 172, 174, 176, 178, 180, 182, 184, 186, 188, 190, 192, 194, 196, 198, 200, 202, 204, 206, 208, 210, 212, 214, 216, 218, 220, 222, 224, 226, 228, 230, 232, 234, 236, 238, 240, 242, 244, 246, 248, 250, 252, 254, 256, 258, 260, 262, 264, 266, 268, 270, 272, 274, 276, 278, 280, 282, 284, 286, 288, 290, 292, 294, 296, 298, 300, 302, 304, 306, 308, 310, 312, 314, 316, 318, 320, 322, 324, 326, 328, 330, 332, 334, 336, 338, 340, 342, 344, 346, 348, 350, 352, 354, 356, 358, 360, 362, 364, 366, 368, 370, 372, 374, 376, 378, 380, 382, 384, 386, 388, 390, 392, 394, 396, 398, 400, 402, 404, 406, 408, 410, 412, 414, 416, 418, 420, 422, 424, 426, 428, 430, 432, 434, 436, 438, 440, 442, 444, 446, 448, 450, 452, 454, 456, 458, 460, 462, 464, 466, 468, 470, 472, 474, 476, 478};

    int16_t thisCount = 0;
    const int16_t *thisRegion;

    if (this->channel == 1) {
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
            thisCount = regionSPCount;
            thisRegion = regionSP;
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
            thisCount = regionPARRCount;
            thisRegion = regionPARR;
            break;
        case 13:
            thisCount = regionP2Count;
            thisRegion = regionP2;
            break;
        case 14:
            thisCount = regionECount;
            thisRegion = regionE;
            break;
        case 15:
            thisCount = regionRCount;
            thisRegion = regionR;
            break;
        case 16:
            thisCount = regionLaser1Count;
            thisRegion = regionLaser1;
            break;
        case 17:
            thisCount = regionLLCount;
            thisRegion = regionLL;
            break;
        case 18:
            thisCount = regionLACount;
            thisRegion = regionLA;
            break;
        case 19:
            thisCount = regionLSCount;
            thisRegion = regionLS;
            break;
        case 20:
            thisCount = regionLECount;
            thisRegion = regionLE;
            break;
        case 21:
            thisCount = regionLRCount;
            thisRegion = regionLR;
            break;
        case 22:
            thisCount = regionLaser2Count;
            thisRegion = regionLaser2;
            break;
        case 23:
            thisCount = regionSnippetCount;
            thisRegion = regionSnippet;
            break;
        case 24:
            thisCount = regionUpperCount;
            thisRegion = regionUpper;
            break;
        case 25:
            thisCount = regionLaserCount;
            thisRegion = regionLaser;
            break;
        case 26:
            thisCount = regionAllCount;
            thisRegion = regionAll;
            break;
        case 27:
            thisCount = goRoundCount;
            thisRegion = goRoundMatrix;
            break;
        }
    }
    else if (this->channel == 3) {  // row regions
        if (this->midiNote < rowCount) {
            thisCount = colCount;
            thisRegion = snipSignMatrix[this->midiNote];
        }
    }
    else if (this->channel == 4) {  // col regions
      Serial.println((String)"col region " + this->midiNote + " .. assembling ");
        if (this->midiNote < colCount) {
            thisCount = rowCount;
            int16_t colRegion[rowCount];
            for (int i=0; i<rowCount; i++) {
                colRegion[i] = snipSignMatrix[i][this->midiNote];
      Serial.print((String) + colRegion[i] + ", ");
            }
            thisRegion = colRegion;
        }
    }

    if (thisCount > 0)
    {
        for (int i = 0; i < thisCount; i++)
        {
              // Do not uncomment. Teensy seems to require this waste of time to correctly render the small regions.
              Serial.println((String) "region " + i + " ... " + thisRegion[i] + " ... h " + this->hue + " | s " + this->sat + " | b " + this->bri + " | hueInc " + this->hueIncrement);
  
            if (thisRegion[i] > -1) {
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
}

