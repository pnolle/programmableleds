#include "fragmentRowMovingUp.h"

RowMovingUp::RowMovingUp(LedUtils ledUtils, unsigned long time) : 
	ledUtils(ledUtils) {

    this->time = time;
    setColorProperties();
    setAnimationProperties();
}

void RowMovingUp::setColorProperties(uint8_t hue=0, uint8_t sat=0, uint8_t bri=255, double hueIncrement=0) {
    this->hue = hue;
    this->sat = sat;
    this->bri = bri;
    this->hueIncrement = hueIncrement;
}

void RowMovingUp::setAnimationProperties(int length=0, int start=0, int wait=10, int fade=250) {
    this->wait = wait;
    this->fade = fade;

    this->rowCountLocal = rowCount;
    if (length!=0) {
        this->rowCountLocal = length;
    }
    this->currentRow = start;
}

void RowMovingUp::resetTimer(unsigned long time) {
    this->time = time;
}

void RowMovingUp::nextFrame(unsigned long currentTime, vector<PixelUpdate> &matrixUpdate, bool &animationFinished) {
    if (DEBUG) Serial.println((String) "nextFrame: currentTime " + currentTime + " > time " + this->time + " + wait " + this->wait + " = " + (this->time+this->wait) + " ... t/f " + (currentTime >= this->time+this->wait));

    // check if defined wait is over
    if (currentTime >= this->time+this->wait) {
        this->time = currentTime;
        // paint next frame
        if (this->currentRow<this->rowCountLocal) {
            for (int currentCol=0; currentCol<colCount; currentCol++) {
                if (this->hueIncrement > 0) hue = ledUtils.incrementHue(this->hue, this->hueIncrement);

                PixelUpdate onePixelUpdate;
                onePixelUpdate.col = currentCol;
                onePixelUpdate.row = this->currentRow;
                onePixelUpdate.hue = hue;
                onePixelUpdate.sat = this->sat;
                onePixelUpdate.bri = this->bri;
                onePixelUpdate.fade = this->fade;
                onePixelUpdate.time = currentTime;
                matrixUpdate.push_back(onePixelUpdate);
            }
            this->currentRow++;
        }
        else {
            animationFinished = true;
        }
    }
}