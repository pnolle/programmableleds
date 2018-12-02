#include "fragmentColumnMovingRight.h"

ColumnMovingRight::ColumnMovingRight(LedUtils ledUtils, unsigned long time) : 
	ledUtils(ledUtils) {

    this->time = time;
    setColorProperties();
    setAnimationProperties();
}

void ColumnMovingRight::setColorProperties(double hue=0, int sat=0, int bri=255, double hueIncrement=0) {
    this->hue = hue;
    this->sat = sat;
    this->bri = bri;
    this->hueIncrement = hueIncrement;
}

void ColumnMovingRight::setAnimationProperties(int length=0, int start=0, int wait=10, int fade=250) {
    this->wait = wait;
    this->fade = fade;

    this->colCountLocal = colCount;
    if (length!=0) {
        this->colCountLocal = length;
    }
    this->currentCol = start;
}

void ColumnMovingRight::resetTimer(unsigned long time) {
    this->time = time;
}

std::vector<PixelUpdate> ColumnMovingRight::nextFrame(unsigned long currentTime) {
    
    std::vector<PixelUpdate> matrixUpdate;

    if (currentTime >= time+wait) {
        if (currentCol<colCountLocal) {
            for (int currentRow=0; currentRow<rowCount; currentRow++) {
                // Todo hueIncrement not working??
                if (hueIncrement > 0) hue = ledUtils.incrementHue(hue, hueIncrement);

                PixelUpdate onePixelUpdate;
                onePixelUpdate.col = currentCol;
                onePixelUpdate.row = currentRow;
                onePixelUpdate.hue = hue;
                onePixelUpdate.sat = sat;
                onePixelUpdate.bri = bri;
                onePixelUpdate.fade = fade;
                onePixelUpdate.time = currentTime;
                matrixUpdate.push_back(onePixelUpdate);

                this->time = currentTime;
            }
            currentCol++;
        }
    }

    return matrixUpdate;
}