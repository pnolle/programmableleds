#include "fragmentGoRound.h"
GoRound::GoRound(LedUtils ledUtils, unsigned long time) : 
	ledUtils(ledUtils) {

    this->time = time;
    setColorProperties();
    setAnimationProperties();
}

void GoRound::setColorProperties(uint8_t hue, uint8_t sat, uint8_t bri, double hueIncrement) {
    this->hue = hue;
    this->sat = sat;
    this->bri = bri;
    this->hueIncrement = hueIncrement;
}

void GoRound::setAnimationProperties(int wait, int fade, bool reverse, int length, int start) {
    this->wait = wait;
    this->fade = fade;
    this->reverse = reverse;
    this->lengthLocal = length;
    this->lengthCounter = 0;
    this->goRoundCountLocal = goRoundCount;
    this->currentGoRound = 0;
    if (start>-1) {
        if (this->reverse) {
        this->currentGoRound = goRoundCount-1-start;
        }
        else {
        this->currentGoRound = start;
        }
    }
    else if (this->reverse) {
        this->currentGoRound = colCount-1;
    }
}

void GoRound::resetTimer(unsigned long time) {
    this->time = time;
}

void GoRound::nextFrame(unsigned long currentTime, vector<PixelUpdate> &matrixUpdate, int &animationRunning) {
    // Do not uncomment. Teensy seems to require this waste of time to do anything at all here!
    Serial.println((String) "GoRound nextFrame: currentTime " + currentTime + " > time " + this->time + " + wait " + this->wait + " = " + (this->time+this->wait) + " ... t/f " + (currentTime >= this->time+this->wait));

    // check if defined wait is over
    if (currentTime >= this->time+this->wait) {
        this->time = currentTime;
        // paint next frame
        bool proceed = false;
        if  (
            ((this->reverse && this->currentGoRound>=0) ||
             (!this->reverse && this->currentGoRound<this->goRoundCountLocal)) &&
            (this->lengthLocal == -1 ||
             (this->lengthLocal>-1 && this->lengthCounter<this->lengthLocal))
             ) {
              Serial.println((String)"GoRound update " + goRoundMatrix[this->currentGoRound]);
            PixelUpdate onePixelUpdate;
            onePixelUpdate.ledNum = goRoundMatrix[this->currentGoRound];
            onePixelUpdate.hue = hue;
            onePixelUpdate.sat = this->sat;
            onePixelUpdate.bri = this->bri;
            onePixelUpdate.fade = this->fade;
            onePixelUpdate.time = currentTime;
            matrixUpdate.push_back(onePixelUpdate);
                
            if (this->reverse) {
              this->currentGoRound--;
            }
            else {
              this->currentGoRound++;
            }
            this->lengthCounter++;
        }
        else {
            animationRunning = 0;
        }
    }
}
