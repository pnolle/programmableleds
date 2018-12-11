#include "fragmentColumnMovingRight.h"

ColumnMovingRight::ColumnMovingRight(LedUtils ledUtils, unsigned long time) : 
	ledUtils(ledUtils) {

    this->time = time;
    setColorProperties();
    setAnimationProperties();
}

void ColumnMovingRight::setColorProperties(uint8_t hue=0, uint8_t sat=0, uint8_t bri=255, double hueIncrement=0) {
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

void ColumnMovingRight::nextFrame(unsigned long currentTime, std::vector<PixelUpdate> &matrixUpdate, bool &animationFinished) {
    
    // Serial.println((String) "nextFrame: currentTime " + currentTime + " > " + (this->time+this->wait) + " ... t/f " + (currentTime >= this->time+this->wait));
    if (DEBUG) Serial.println((String) "nextFrame: currentTime " + currentTime + " > time " + this->time + " + wait " + this->wait + " = " + (this->time+this->wait) + " ... t/f " + (currentTime >= this->time+this->wait));

    if (currentTime >= this->time+this->wait) {
        this->time = currentTime;
        if (this->currentCol<this->colCountLocal) {
            for (int currentRow=0; currentRow<rowCount; currentRow++) {
                // Todo hueIncrement not working??
                if (this->hueIncrement > 0) hue = ledUtils.incrementHue(this->hue, this->hueIncrement);

                PixelUpdate onePixelUpdate;
                onePixelUpdate.col = this->currentCol;
                onePixelUpdate.row = currentRow;
                onePixelUpdate.hue = hue;
                onePixelUpdate.sat = this->sat;
                onePixelUpdate.bri = this->bri;
                onePixelUpdate.fade = this->fade;
                onePixelUpdate.time = currentTime;
                matrixUpdate.push_back(onePixelUpdate);
            }
            currentCol++;
        }
        else {
            animationFinished = true;
        }
    }
}