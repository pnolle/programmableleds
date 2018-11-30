#include "fragmentColumnMovingRight.h"

ColumnMovingRight::ColumnMovingRight(int length, int start, LedUtils ledUtils) : 
	length(length), start(start), ledUtils(ledUtils) {

    colCountLocal = colCount;
    if (length!=0) {
        colCountLocal = length;
    }

    ledCount = rowCount;
    currentCol = start;

// todo: should be set via setColorProperties()
    hueIncrement = 0.0;
}

bool ColumnMovingRight::nextFrame(CRGB crgbledstrip[]) {
    if (currentCol<colCountLocal) {
        for (int currentLed=0; currentLed<ledCount; currentLed++) {
            int ledNum = matrixColumnsLeftRight[currentCol][currentLed];
            if (hueIncrement > 0) hue = ledUtils.incrementHue(hue, hueIncrement);
            crgbledstrip[ledNum] = CHSV(hue, sat, bri);
        }
        delay(wait);
        currentCol++;
        return true;
    }
    // if max num of cols is exceeded, return false
    return false;
}