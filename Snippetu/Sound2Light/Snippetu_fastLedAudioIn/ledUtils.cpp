#include "ledUtils.h"

unsigned int LedUtils::blueFromHexColor(unsigned int hexColor) {
    unsigned int rgbBlue = hexColor & 0b11111111;
    return rgbBlue;
}
unsigned int LedUtils::greenFromHexColor(unsigned int hexColor) {
    unsigned int rgbGreen = (hexColor>>8) & 0b11111111;
    return rgbGreen;
}
unsigned int LedUtils::redFromHexColor(unsigned int hexColor) {
    unsigned int rgbRed = (hexColor>>16) & 0b11111111;
    return rgbRed;
}

int LedUtils::subColor(unsigned int c, int sub) {
  int result = c-sub;
  if (result>0x000000) {
    return result;
  }
  else if (result<=0x000000) {
    return 0xffffff;
  }
  else {
    return 0x000000;
  }
}

double LedUtils::incrementHue(double h, double hIncrementor) {
  h+=hIncrementor;
  if (h>=255) {
    h-=255;
  }
  return h;
}


double LedUtils::getNumLeds(byte incomingAudio, int totalNumLeds, int offset) {
  double faktor = incomingAudio/255.0;
  int numLeds = (int)(totalNumLeds*faktor+offset)*1.2;
  if (DEBUG) Serial.println((String)"incoming: " + incomingAudio+' '+" ... faktor: " + faktor+' '+" ... numLeds: " + numLeds+' '+" ...");
  return numLeds;
}


void LedUtils::checkInterrupts() {
/*   while (buttonState==HIGH) {
    digitalWrite(LEDPIN, buttonState);
    if (buttonState==LOW) {
      digitalWrite(LEDPIN, buttonState);
      break;
    }
  } */
} 