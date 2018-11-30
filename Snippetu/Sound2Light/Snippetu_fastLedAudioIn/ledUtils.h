#ifndef LEDUTILS
#define LEDUTILS

#include "Arduino.h"

#define DEBUG false

class LedUtils
{
    public:
        static unsigned int blueFromHexColor(unsigned int hexColor);
        static unsigned int greenFromHexColor(unsigned int hexColor);
        static unsigned int redFromHexColor(unsigned int hexColor);
        static int subColor(unsigned int c, int sub);
        static double incrementHue(double h, double hIncrementor);
        static double getNumLeds(byte incomingAudio, int totalNumLeds, int offset);
        static void checkInterrupts();
};

#endif 