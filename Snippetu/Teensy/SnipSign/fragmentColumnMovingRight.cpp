#include "fragmentColumnMovingRight.h"
ColumnMovingRight::ColumnMovingRight(LedUtils ledUtils, unsigned long time) : 
	ledUtils(ledUtils) {

    this->time = time;
    setColorProperties();
    setAnimationProperties();
}

void ColumnMovingRight::setColorProperties(uint8_t hue, uint8_t sat, uint8_t bri, double hueIncrement) {
    this->hue = hue;
    this->sat = sat;
    this->bri = bri;
    this->hueIncrement = hueIncrement;
}

void ColumnMovingRight::setAnimationProperties(int wait, int fade, bool reverse, int length, int start) {
    this->wait = wait;
    this->fade = fade;
    this->reverse = reverse;
    this->lengthLocal = length;
    this->lengthCounter = 0;
    this->colCountLocal = colCount;
    this->currentCol = 0;
    if (start>0) {
      if (this->reverse) {
        this->currentCol = colCount-1-start;
      }
      else {
        this->currentCol = start;
      }
    }
    else if (this->reverse) {
        this->currentCol = colCount-1;
    }
}

void ColumnMovingRight::resetTimer(unsigned long time) {
    this->time = time;
}

void ColumnMovingRight::nextFrame(unsigned long currentTime, vector<PixelUpdate> &matrixUpdate, int &animationRunning) {
    if (DEBUG) Serial.println((String) "nextFrame: currentTime " + currentTime + " > time " + this->time + " + wait " + this->wait + " = " + (this->time+this->wait) + " ... t/f " + (currentTime >= this->time+this->wait));

    // check if defined wait is over
    if (currentTime >= this->time+this->wait) {
        this->time = currentTime;
        // paint next frame
        if  (
            ((this->reverse && this->currentCol>=0) ||
             (!this->reverse && this->currentCol<this->colCountLocal)) &&
            (this->lengthLocal == 0 ||
             (this->lengthLocal>0 && this->lengthCounter<this->lengthLocal))
             ) {
            for (int currentRow=0; currentRow<rowCount; currentRow++) {
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
            if (this->reverse) {
              currentCol--;
            }
            else {
              currentCol++;
            }
            this->lengthCounter++;
        }
        else {
            animationRunning = 0;
        }
    }
}
