#include "fragmentRowMovingUp.h"

RowMovingUp::RowMovingUp(LedUtils ledUtils, unsigned long time) : 
	ledUtils(ledUtils) {

    this->time = time;
    setColorProperties();
    setAnimationProperties();
}

void RowMovingUp::setColorProperties(uint8_t hue, uint8_t sat, uint8_t bri, double hueIncrement) {
    this->hue = hue;
    this->sat = sat;
    this->bri = bri;
    this->hueIncrement = hueIncrement;
}

void RowMovingUp::setAnimationProperties(int wait, int fade, bool reverse, int length, int start) {
    this->wait = wait;
    this->fade = fade;
    this->reverse = reverse;

    this->rowCountLocal = rowCount;
    if (length!=0) {
        this->rowCountLocal = length;
    }
    if (this->reverse) {
        this->currentRow = rowCount-1-start;
    }
    else {
        this->currentRow = start;
    }
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
        bool rowCondition = false;
        if (this->reverse) {
            if (this->currentRow>=0) {
                rowCondition = true;
            }
        }
        else {
            if (this->currentRow<this->rowCountLocal) {
                rowCondition = true;
            }
        }
        if (rowCondition) {
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
            if (this->reverse) {
                this->currentRow--;
            }
            else {
                this->currentRow++;
            }
        }
        else {
            animationFinished = true;
        }
    }
}
