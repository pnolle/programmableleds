#include "fragmentRowMovingDown.h"

RowMovingDown::RowMovingDown(LedUtils ledUtils, unsigned long time) : 
	ledUtils(ledUtils) {

    this->time = time;
    setColorProperties();
    setAnimationProperties();
}

void RowMovingDown::setColorProperties(uint8_t hue, uint8_t sat, uint8_t bri, double hueIncrement) {
    this->hue = hue;
    this->sat = sat;
    this->bri = bri;
    this->hueIncrement = hueIncrement;
}

void RowMovingDown::setAnimationProperties(int wait, int fade, bool reverse, int length, int start) {
    this->wait = wait;
    this->fade = fade;
    this->reverse = reverse;
    this->lengthLocal = length;
    this->lengthCounter = 0;
    this->rowCountLocal = rowCount;
    this->currentRow = 0;
    if (start>0) {
        if (this->reverse) {
            this->currentRow = rowCount-1-start;
        }
        else {
            this->currentRow = start;
        }
    }
    else if (this->reverse) {
        this->currentRow = rowCount-1;
    }
}

void RowMovingDown::resetTimer(unsigned long time) {
    this->time = time;
}

void RowMovingDown::nextFrame(unsigned long currentTime, vector<PixelUpdate> &matrixUpdate, int &animationRunning) {
    if (DEBUG) Serial.println((String) "nextFrame: currentTime " + currentTime + " > time " + this->time + " + wait " + this->wait + " = " + (this->time+this->wait) + " ... t/f " + (currentTime >= this->time+this->wait));

    // check if defined wait is over
    if (currentTime >= this->time+this->wait) {
        this->time = currentTime;
        // paint next frame 
        if  (
            ((this->reverse && this->currentRow>=0) ||
             (!this->reverse && this->currentRow<this->rowCountLocal)) &&
            (this->lengthLocal == 0 ||
             (this->lengthLocal>0 && this->lengthCounter<this->lengthLocal))
             ) {
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
            this->lengthCounter++;
        }
        else {
            animationRunning = 0;
        }
    }
}
