#include "fragmentColumnMovingRight.h"

ColumnMovingRight::ColumnMovingRight(int length, int start, LedUtils ledUtils) : 
	length(length), start(start), ledUtils(ledUtils) {

    colCountLocal = colCount;
    if (length!=0) {
        colCountLocal = length;
    }
    currentCol = start;
}

void ColumnMovingRight::setColorProperties(double hue=0, int sat=0, int bri=255, double hueIncrement=0) {
    hue = hue;
    sat = sat;
    bri = bri;
    hueIncrement = hueIncrement;
}

void ColumnMovingRight::setAnimationProperties(int wait=10, int fade=240) {
    wait = wait;
    fade = fade;
}


String ColumnMovingRight::getValues() {
    return (String)"currentCol " + currentCol
     + " ... colCountLocal" + colCountLocal
     + " ... hue" + hue
     + " ... sat" + sat
     + " ... bri" + bri
     + " ... hueIncrement" + hueIncrement
     + " ... wait" + wait
     + " ... fade" + fade
     ;
}


std::vector<PixelUpdate> ColumnMovingRight::nextFrame() {
    
    bri=255; // TODO: TEMPORARY. something's not right with bri

    std::vector<PixelUpdate> matrixUpdate;

    if (currentCol<colCountLocal) {
        for (int currentRow=0; currentRow<rowCount; currentRow++) {
            if (hueIncrement > 0) hue = ledUtils.incrementHue(hue, hueIncrement);

            PixelUpdate onePixelUpdate;
            onePixelUpdate.col = currentCol;
            onePixelUpdate.row = currentRow;
            onePixelUpdate.hue = hue;
            onePixelUpdate.sat = sat;
            onePixelUpdate.bri = bri;
            matrixUpdate.push_back(onePixelUpdate);
        }
    //     Serial.println((String)"nextFrame: currentCol" + currentCol);
    //     delay(wait);    // ToDo calculate time since last time
        currentCol++;
    }
    else { // ToDo: remove. this should end the animation
        currentCol = 0;
    }


    /*
Calling nexFrame of turquoiseCMR 
currentCol 0 ... 
colCountLocal37 ... 
hue0.00 ... 
sat0 ... 
bri37 ... 
hueIncrement0.00 ... 
wait0 ... 
fade0
matrixUpdate col-1 / row-1 ... hue NAN ... sat-1 ... bri-1 ... ledNum0
matrixUpdate col-1 / row-1 ... hue NAN ... sat-1 ... bri-1 ... ledNum0
matrixUpdate col-1 / row-1 ... hue NAN ... sat-1 ... bri-1 ... ledNum0
matrixUpdate col-1 / row-1 ... hue NAN ... sat-1 ... bri-1 ... ledNum0
matrixUpdate col-1 / row-1 ... hue NAN ... sat-1 ... bri-1 ... ledNum0
matrixUpdate col-1 / row-1 ... hue NAN ... sat-1 ... bri-1 ... ledNum0
matrixUpdate col-1 / row-1 ... hue NAN ... sat-1 ... bri-1 ... ledNum0
matrixUpdate col-1 / row-1 ... hue NAN ... sat-1 ... bri-1 ... ledNum0
matrixUpdate col-1 / row-1 ... hue NAN ... sat1024 ... bri342 ... ledNum0
matrixUpdate col8510 / row170 ... hue0.00 ... sat3967 ... bri1 ... ledNum0
matrixUpdate col-208 / row1024 ... hue0.00 ... sat2560 ... bri27402 ... ledNum3084
matrixUpdate col42 / row2560 ... hue0.00 ... sat2688 ... bri42 ... ledNum-2566
matrixUpdate col0 / row5120 ... hue0.00 ... sat1024 ... bri598 ... ledNum5140
matrixUpdate col2330 / row8525 ... hue0.00 ... sat2562 ... bri44 ... ledNum33
matrixUpdate col-23773 / row0 ... hue0.00 ... sat-20986 ... bri512 ... ledNum-5761

Calling nexFrame of turquoiseCMR currentCol 7 ... colCountLocal37 ... hue0.00 ... sat0 ... bri37 ... hueIncrement0.00 ... wait0 ... fade0
matrixUpdate col-1 / row-1 ... hue NAN ... sat-1 ... bri-1 ... ledNum0
matrixUpdate col-1 / row-1 ... hue NAN ... sat-1 ... bri-1 ... ledNum0
matrixUpdate col-1 / row-1 ... hue NAN ... sat-1 ... bri-1 ... ledNum0
matrixUpdate col-1 / row-1 ... hue NAN ... sat-1 ... bri-1 ... ledNum0
matrixUpdate col-1 / row-1 ... hue NAN ... sat-1 ... bri-1 ... ledNum0
matrixUpdate col-1 / row-1 ... hue NAN ... sat-1 ... bri-1 ... ledNum0
matrixUpdate col-1 / row-1 ... hue NAN ... sat-1 ... bri-1 ... ledNum0
matrixUpdate col-1 / row-1 ... hue NAN ... sat-1 ... bri-1 ... ledNum0
matrixUpdate col-1 / row-1 ... hue NAN ... sat1024 ... bri342 ... ledNum0
matrixUpdate col8498 / row168 ... hue0.00 ... sat-14815 ... bri-21727 ... ledNum0
matrixUpdate col8960 / row0 ... hue0.00 ... sat1027 ... bri8609 ... ledNum-1058
matrixUpdate col0 / row5120 ... hue-743087390000000000000.00 ... sat-11487 ... bri11274 ... ledNum12288


*/
    
    return matrixUpdate;
}