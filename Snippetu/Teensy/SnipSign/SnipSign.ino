/* 
##############################
SnipSign programmable LED sign
by Niklas Köhn
##############################

Uses FastLED to animate Neopixels. Receives MIDI.

Contains parts from Marc Merlin's work Neopixel-IR.
MIDI part adapted from Teensy MIDI demo.
*/

#include "constMatrix.h"
#include <FastLED.h>
#include "fragmentColumnMovingRight.h"
#include "fragmentRowMovingDown.h"
#include "fragmentGoRound.h"
#include "fragmentProperties.h"
#include "ledregion.h"
#include "vector"

using namespace std;

LedUtils ledUtils;
ColumnMovingRight cmr1(ledUtils, millis());
ColumnMovingRight cmr2(ledUtils, millis());
ColumnMovingRight cmr3(ledUtils, millis());
RowMovingDown rmd1(ledUtils, millis());
RowMovingDown rmd2(ledUtils, millis());
RowMovingDown rmd3(ledUtils, millis());
GoRound gr1(ledUtils, millis());
GoRound gr2(ledUtils, millis());
GoRound gr3(ledUtils, millis());
GoRound gr4(ledUtils, millis());
GoRound gr5(ledUtils, millis());
LedRegion reg00(ledUtils, 0);
LedRegion reg01(ledUtils, 1);
LedRegion reg02(ledUtils, 2);
LedRegion reg03(ledUtils, 3);
LedRegion reg04(ledUtils, 4);
LedRegion reg05(ledUtils, 5);
LedRegion reg06(ledUtils, 6);
LedRegion reg07(ledUtils, 7);
LedRegion reg08(ledUtils, 8);
LedRegion reg09(ledUtils, 9);
LedRegion reg10(ledUtils, 10);
LedRegion reg11(ledUtils, 11);
LedRegion reg12(ledUtils, 12);
LedRegion reg13(ledUtils, 13);
LedRegion reg14(ledUtils, 14);
LedRegion reg15(ledUtils, 15);
LedRegion reg16(ledUtils, 16);
LedRegion reg17(ledUtils, 17);
LedRegion reg18(ledUtils, 18);
LedRegion reg19(ledUtils, 19);
LedRegion reg20(ledUtils, 20);
LedRegion reg21(ledUtils, 21);
LedRegion reg22(ledUtils, 22);
LedRegion reg23(ledUtils, 23);
LedRegion reg24(ledUtils, 24);
LedRegion reg25(ledUtils, 25);
LedRegion reg26(ledUtils, 26);
LedRegion reg27(ledUtils, 27);

// The following flags are ints, because bools couldn't be overwritten from functions. Strange! 0=false, 1=true.
int cmr1Running = 0;
int cmr2Running = 0;
int cmr3Running = 0;
int rmd1Running = 0;
int rmd2Running = 0;
int rmd3Running = 0;
int gr1Running = 0;
int gr2Running = 0;
int gr3Running = 0;
int gr4Running = 0;
int gr5Running = 0;

uint32_t regionsRunning = 0;

int reg00Running = 0;
int reg01Running = 0;
int reg02Running = 0;
int reg03Running = 0;
int reg04Running = 0;
int reg05Running = 0;
int reg06Running = 0;
int reg07Running = 0;
int reg08Running = 0;
int reg09Running = 0;
int reg10Running = 0;
int reg11Running = 0;
int reg12Running = 0;
int reg13Running = 0;
int reg14Running = 0;
int reg15Running = 0;
int reg16Running = 0;
int reg17Running = 0;
int reg18Running = 0;
int reg19Running = 0;
int reg20Running = 0;
int reg21Running = 0;
int reg22Running = 0;

#define DATA_PIN 6
#define NUM_LEDS 479
#define DEBUG false
#define SOUND2LIGHT false
#define FRAGMENTS true

// Define the array of leds
CRGB crgbledstrip[NUM_LEDS];
// The fade values of the last 2 LEDs were always messed up. By increasing the array size by 2 the problem disappears... don't know why.
int fadestrip[NUM_LEDS + 2];

uint8_t fragmentsSaturation = 127;
uint8_t fragmentsBrightness = 127;
uint8_t regionsSaturation = 127;
uint8_t regionsBrightness = 127;
uint8_t fragmentsFade = 120;
uint8_t fragmentsWait = 30;
uint8_t regionsFade = 120;
uint8_t regionsHueInc = 0;
uint8_t fragmentsStart = 0;
uint8_t fragmentsLength = 0;


// AudioIn
byte incomingAudio;
boolean clipping = 0;

void setup()
{
  Serial.begin(115200);

  // init fadestrip: set all values to 0
  for (int i = 0; i < NUM_LEDS; i++)
  {
    fadestrip[i] = 0;
  }

  Serial.println("LED Setup");
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(crgbledstrip, NUM_LEDS);
  LEDS.setBrightness(84);
  eraseAll();

  // setupAudioIn();
  Serial.println("Setup done");
}

void loop()
{
  vector<PixelUpdate> matrixUpdate; 
  // dummy data
  PixelUpdate onePixelUpdate;
  for (uint16_t i = 0; i < NUM_LEDS; i+=25) {
    onePixelUpdate.ledNum = i;
    onePixelUpdate.hue = 1;
    onePixelUpdate.sat = 1;
    onePixelUpdate.bri = 1;
    onePixelUpdate.fade = 1;
    matrixUpdate.push_back(onePixelUpdate);
  }

  // usbMIDI.read() needs to be called rapidly from loop().  When
  // each MIDI messages arrives, it return true.  The message must
  // be fully processed before usbMIDI.read() is called again.
  if (usbMIDI.read())
  {
    processMIDI();
  }
  if (cmr1Running > 0)
  {
    cmr1.nextFrame(millis(), matrixUpdate, cmr1Running);
  }
  if (cmr2Running > 0)
  {
    cmr2.nextFrame(millis(), matrixUpdate, cmr2Running);
  }
  if (cmr3Running > 0)
  {
    cmr3.nextFrame(millis(), matrixUpdate, cmr3Running);
  }
  if (rmd1Running > 0)
  {
    rmd1.nextFrame(millis(), matrixUpdate, rmd1Running);
  }
  if (rmd2Running > 0)
  {
    rmd2.nextFrame(millis(), matrixUpdate, rmd2Running);
  }
  if (rmd3Running > 0)
  {
    rmd3.nextFrame(millis(), matrixUpdate, rmd3Running);
  }
  if (gr1Running > 0)
  {
    gr1.nextFrame(millis(), matrixUpdate, gr1Running);
  }
  if (gr2Running > 0)
  {
    gr2.nextFrame(millis(), matrixUpdate, gr2Running);
  }
  if (gr3Running > 0)
  {
    gr3.nextFrame(millis(), matrixUpdate, gr3Running);
  }
  if (gr4Running > 0)
  {
    gr4.nextFrame(millis(), matrixUpdate, gr4Running);
  }
  if (gr5Running > 0)
  {
    gr5.nextFrame(millis(), matrixUpdate, gr5Running);
  }

  // Check for enabled regions
  if (regionsRunning & (1 << 0))
  {
    reg00.nextFrame(matrixUpdate);
  }
  if (regionsRunning & (1 << 1))
  {
    reg01.nextFrame(matrixUpdate);
  }
  if (regionsRunning & (1 << 2))
  {
    reg02.nextFrame(matrixUpdate);
  }
  if (regionsRunning & (1 << 3))
  {
    reg03.nextFrame(matrixUpdate);
  }
  if (regionsRunning & (1 << 4))
  {
    reg04.nextFrame(matrixUpdate);
  }
  if (regionsRunning & (1 << 5))
  {
    reg05.nextFrame(matrixUpdate);
  }
  if (regionsRunning & (1 << 6))
  {
    reg06.nextFrame(matrixUpdate);
  }
  if (regionsRunning & (1 << 7))
  {
    reg07.nextFrame(matrixUpdate);
  }
  if (regionsRunning & (1 << 8))
  {
    reg08.nextFrame(matrixUpdate);
  }
  if (regionsRunning & (1 << 9))
  {
    reg09.nextFrame(matrixUpdate);
  }
  if (regionsRunning & (1 << 10))
  {
    reg10.nextFrame(matrixUpdate);
  }
  if (regionsRunning & (1 << 11))
  {
    reg11.nextFrame(matrixUpdate);
  }
  if (regionsRunning & (1 << 12))
  {
    reg12.nextFrame(matrixUpdate);
  }
  if (regionsRunning & (1 << 13))
  {
    reg13.nextFrame(matrixUpdate);
  }
  if (regionsRunning & (1 << 14))
  {
    reg14.nextFrame(matrixUpdate);
  }
  if (regionsRunning & (1 << 15))
  {
    reg15.nextFrame(matrixUpdate);
  }
  if (regionsRunning & (1 << 16))
  {
    reg16.nextFrame(matrixUpdate);
  }
  if (regionsRunning & (1 << 17))
  {
    reg17.nextFrame(matrixUpdate);
  }
  if (regionsRunning & (1 << 18))
  {
    reg18.nextFrame(matrixUpdate);
  }
  if (regionsRunning & (1 << 19))
  {
    reg19.nextFrame(matrixUpdate);
  }
  if (regionsRunning & (1 << 20))
  {
    reg20.nextFrame(matrixUpdate);
  }
  if (regionsRunning & (1 << 21))
  {
    reg21.nextFrame(matrixUpdate);
  }
  if (regionsRunning & (1 << 22))
  {
    reg22.nextFrame(matrixUpdate);
  }
  if (regionsRunning & (1 << 23))
  {
    reg23.nextFrame(matrixUpdate);
  }
  if (regionsRunning & (1 << 24))
  {
    reg24.nextFrame(matrixUpdate);
  }
  if (regionsRunning & (1 << 25))
  {
    reg25.nextFrame(matrixUpdate);
  }
  if (regionsRunning & (1 << 26))
  {
    reg26.nextFrame(matrixUpdate);
  }
  if (regionsRunning & (1 << 27))
  {
    reg27.nextFrame(matrixUpdate);
  }

Serial.println((String)"marix size" + matrixUpdate.size());
  if (matrixUpdate.size() > 0)
  {
    for (vector<PixelUpdate>::iterator it = matrixUpdate.begin(); it != matrixUpdate.end(); ++it)
    {
      int ledNum = -1;
      if (it->ledNum > -1)
      {
        ledNum = it->ledNum;
      }
      else
      {
        ledNum = snipSignMatrix[it->row][it->col];
      }
      if (ledNum > -1)
      {
        crgbledstrip[ledNum] = CHSV(it->hue, it->sat, it->bri);
        if (DEBUG)
          Serial.println((String) "matrixUpdate at time " + millis() + ": col" + it->col + " / row" + it->row + " ... hue" + it->hue + " ... sat" + it->sat + " ... bri" + it->bri + ": fade" + it->fade + " ... time" + it->time + " ... ledNum" + ledNum + " ... fadestrip[ledNum]" + fadestrip[ledNum]);
      }
      fadestrip[ledNum] = it->fade;
    }
  }
  else {
      crgbledstrip[0] = CHSV(0, 0, 0);
  }
  FastLED.show();
  fadeIndividual();
}

void startCmr1(FragmentProperties fP)
{
  cmr1.setColorProperties(fP.hue, fP.sat, fP.bri, fP.hueIncrement);
  cmr1.setAnimationProperties(fP.wait, fP.fade, fP.reverse, fP.length, fP.start);
}
void startCmr2(FragmentProperties fP)
{
  cmr2.setColorProperties(fP.hue, fP.sat, fP.bri, fP.hueIncrement);
  cmr2.setAnimationProperties(fP.wait, fP.fade, fP.reverse, fP.length, fP.start);
}
void startCmr3(FragmentProperties fP)
{
  cmr3.setColorProperties(fP.hue, fP.sat, fP.bri, fP.hueIncrement);
  cmr3.setAnimationProperties(fP.wait, fP.fade, fP.reverse, fP.length, fP.start);
}
void startRmd1(FragmentProperties fP)
{
  rmd1.setColorProperties(fP.hue, fP.sat, fP.bri, fP.hueIncrement);
  rmd1.setAnimationProperties(fP.wait, fP.fade, fP.reverse, fP.length, fP.start);
}
void startRmd2(FragmentProperties fP)
{
  rmd2.setColorProperties(fP.hue, fP.sat, fP.bri, fP.hueIncrement);
  rmd2.setAnimationProperties(fP.wait, fP.fade, fP.reverse, fP.length, fP.start);
}
void startRmd3(FragmentProperties fP)
{
  rmd3.setColorProperties(fP.hue, fP.sat, fP.bri, fP.hueIncrement);
  rmd3.setAnimationProperties(fP.wait, fP.fade, fP.reverse, fP.length, fP.start);
}
void startGr1(FragmentProperties fP)
{
  gr1.setColorProperties(fP.hue, fP.sat, fP.bri, fP.hueIncrement);
  gr1.setAnimationProperties(fP.wait, fP.fade, fP.reverse, fP.length, fP.start);
}
void startGr2(FragmentProperties fP)
{
  gr2.setColorProperties(fP.hue, fP.sat, fP.bri, fP.hueIncrement);
  gr2.setAnimationProperties(fP.wait, fP.fade, fP.reverse, fP.length, fP.start);
}
void startGr3(FragmentProperties fP)
{
  gr3.setColorProperties(fP.hue, fP.sat, fP.bri, fP.hueIncrement);
  gr3.setAnimationProperties(fP.wait, fP.fade, fP.reverse, fP.length, fP.start);
}
void startGr4(FragmentProperties fP)
{
  gr4.setColorProperties(fP.hue, fP.sat, fP.bri, fP.hueIncrement);
  gr4.setAnimationProperties(fP.wait, fP.fade, fP.reverse, fP.length, fP.start);
}
void startGr5(FragmentProperties fP)
{
  gr5.setColorProperties(fP.hue, fP.sat, fP.bri, fP.hueIncrement);
  gr5.setAnimationProperties(fP.wait, fP.fade, fP.reverse, fP.length, fP.start);
}

void processMIDI(void)
{
  byte type, channel, data1, data2, cable;

  // fetch the MIDI message, defined by these 5 numbers (except SysEX)
  //
  type = usbMIDI.getType();       // which MIDI message, 128-255
  channel = usbMIDI.getChannel(); // which MIDI channel, 1-16
  data1 = usbMIDI.getData1();     // first data byte of message, 0-127
  data2 = usbMIDI.getData2();     // second data byte of message, 0-127
  cable = usbMIDI.getCable();     // which virtual cable with MIDIx8, 0-7

  // uncomment if using multiple virtual cables
  //Serial.print("cable ");
  //Serial.print(cable, DEC);
  //Serial.print(": ");

  // print info about the message
  //
  switch (type)
  {
  case usbMIDI.NoteOff: // 0x80
    Serial.print("Note Off, ch=");
    Serial.print(channel, DEC);
    Serial.print(", note=");
    Serial.print(data1, DEC);
    Serial.print(", velocity=");
    Serial.println(data2, DEC);

    if (data1 == 0)
    {
      regionsRunning &= (0 << 0);
    }
    else if (data1 == 1)
    {
      regionsRunning &= (0 << 1);
    }
    else if (data1 == 2)
    {
      regionsRunning &= (0 << 2);
    }
    else if (data1 == 3)
    {
      regionsRunning &= (0 << 3);
    }
    else if (data1 == 4)
    {
      regionsRunning &= (0 << 4);
    }
    else if (data1 == 5)
    {
      regionsRunning &= (0 << 5);
    }
    else if (data1 == 6)
    {
      regionsRunning &= (0 << 6);
    }
    else if (data1 == 7)
    {
      regionsRunning &= (0 << 7);
    }
    else if (data1 == 8)
    {
      regionsRunning &= (0 << 8);
    }
    else if (data1 == 9)
    {
      regionsRunning &= (0 << 9);
    }
    else if (data1 == 10)
    {
      regionsRunning &= (0 << 10);
    }
    else if (data1 == 11)
    {
      regionsRunning &= (0 << 11);
    }
    else if (data1 == 12)
    {
      regionsRunning &= (0 << 12);
    }
    else if (data1 == 13)
    {
      regionsRunning &= (0 << 13);
    }
    else if (data1 == 14)
    {
      regionsRunning &= (0 << 14);
    }
    else if (data1 == 15)
    {
      regionsRunning &= (0 << 15);
    }
    else if (data1 == 16)
    {
      regionsRunning &= (0 << 16);
    }
    else if (data1 == 17)
    {
      regionsRunning &= (0 << 17);
    }
    else if (data1 == 18)
    {
      regionsRunning &= (0 << 18);
    }
    else if (data1 == 19)
    {
      regionsRunning &= (0 << 19);
    }
    else if (data1 == 20)
    {
      regionsRunning &= (0 << 20);
    }
    else if (data1 == 21)
    {
      regionsRunning &= (0 << 21);
    }
    else if (data1 == 22)
    {
      regionsRunning &= (0 << 22);
    }
    else if (data1 == 23)
    {
      regionsRunning &= (0 << 23);
    }
    else if (data1 == 24)
    {
      regionsRunning &= (0 << 24);
    }
    else if (data1 == 25)
    {
      regionsRunning &= (0 << 25);
    }
    else if (data1 == 26)
    {
      regionsRunning &= (0 << 26);
    }
    else if (data1 == 27)
    {
      regionsRunning &= (0 << 27);
    }
    break;

  case usbMIDI.NoteOn: // 0x90
    Serial.print("Note On, ch=");
    Serial.print(channel, DEC);
    Serial.print(", note=");
    Serial.print(data1, DEC);
    Serial.print(", velocity=");
    Serial.println(data2, DEC);

    // data1 = note
    // data2 = velocity
    if (data1 == 0) // S
    {
      regionsRunning |= (1 << 0);
      reg00.setAnimationProperties(data1, regionsFade*2);
      reg00.setColorProperties(data2*2, regionsSaturation*2+1, regionsBrightness*2+1); //, regionsHueInc/100);
    }
    else if (data1 == 1)  // n
    {
      regionsRunning |= (1 << 1);
      reg01.setAnimationProperties(data1, regionsFade*2);
      reg01.setColorProperties(data2*2, regionsSaturation*2+1, regionsBrightness*2+1); //, regionsHueInc/100);
    }
    else if (data1 == 2)  // i
    {
      regionsRunning |= (1 << 2);
      reg02.setAnimationProperties(data1, regionsFade*2);
      reg02.setColorProperties(data2*2, regionsSaturation*2+1, regionsBrightness*2+1); //, regionsHueInc/100);
    }
     else if (data1 == 3)  // Sp1
     {
      regionsRunning |= (1 << 3);
      reg03.setAnimationProperties(data1, regionsFade*2);
      reg03.setColorProperties(data2*2, regionsSaturation*2+1, regionsBrightness*2+1); //, regionsHueInc/100);
     }
    else if (data1 == 4)  // Sp2
    {
      regionsRunning |= (1 << 4);
      reg04.setAnimationProperties(data1, regionsFade*2);
      reg04.setColorProperties(data2*2, regionsSaturation*2+1, regionsBrightness*2+1); //, regionsHueInc/100);
    }
    else if (data1 == 5)  // Se
    {
      regionsRunning |= (1 << 5);
      reg05.setAnimationProperties(data1, regionsFade*2);
      reg05.setColorProperties(data2*2, regionsSaturation*2+1, regionsBrightness*2+1); //, regionsHueInc/100);
    }
    else if (data1 == 6)  // t
    {
      regionsRunning |= (1 << 6);
      reg06.setAnimationProperties(data1, regionsFade*2);
      reg06.setColorProperties(data2*2, regionsSaturation*2+1, regionsBrightness*2+1); //, regionsHueInc/100);
    }
    else if (data1 == 7)
    {
      regionsRunning |= (1 << 7);
      reg07.setAnimationProperties(data1, regionsFade*2);
      reg07.setColorProperties(data2*2, regionsSaturation*2+1, regionsBrightness*2+1); //, regionsHueInc/100);
    }
    else if (data1 == 8)
    {
      regionsRunning |= (1 << 8);
      reg08.setAnimationProperties(data1, regionsFade*2);
      reg08.setColorProperties(data2*2, regionsSaturation*2+1, regionsBrightness*2+1); //, regionsHueInc/100);
    }
    else if (data1 == 9)
    {
      regionsRunning |= (1 << 9);
      reg09.setAnimationProperties(data1, regionsFade*2);
      reg09.setColorProperties(data2*2, regionsSaturation*2+1, regionsBrightness*2+1); //, regionsHueInc/100);
    }
    else if (data1 == 10)
    {
      regionsRunning |= (1 << 10);
      reg10.setAnimationProperties(data1, regionsFade*2);
      reg10.setColorProperties(data2*2, regionsSaturation*2+1, regionsBrightness*2+1); //, regionsHueInc/100);
    }
    else if (data1 == 11)
    {
      regionsRunning |= (1 << 11);
      reg11.setAnimationProperties(data1, regionsFade*2);
      reg11.setColorProperties(data2*2, regionsSaturation*2+1, regionsBrightness*2+1); //, regionsHueInc/100);
    }
    else if (data1 == 12)
    {
      regionsRunning |= (1 << 12);
      reg12.setAnimationProperties(data1, regionsFade*2);
      reg12.setColorProperties(data2*2, regionsSaturation*2+1, regionsBrightness*2+1); //, regionsHueInc/100);
    }
    else if (data1 == 13)
    {
      regionsRunning |= (1 << 13);
      reg13.setAnimationProperties(data1, regionsFade*2);
      reg13.setColorProperties(data2*2, regionsSaturation*2+1, regionsBrightness*2+1); //, regionsHueInc/100);
    }
    else if (data1 == 14)
    {
      regionsRunning |= (1 << 14);
      reg14.setAnimationProperties(data1, regionsFade*2);
      reg14.setColorProperties(data2*2, regionsSaturation*2+1, regionsBrightness*2+1); //, regionsHueInc/100);
    }
    else if (data1 == 15)
    {
      regionsRunning |= (1 << 15);
      reg15.setAnimationProperties(data1, regionsFade*2);
      reg15.setColorProperties(data2*2, regionsSaturation*2+1, regionsBrightness*2+1); //, regionsHueInc/100);
    }
    else if (data1 == 16)
    {
      regionsRunning |= (1 << 16);
      reg16.setAnimationProperties(data1, regionsFade*2);
      reg16.setColorProperties(data2*2, regionsSaturation*2+1, regionsBrightness*2+1); //, regionsHueInc/100);
    }
    else if (data1 == 17)
    {
      regionsRunning |= (1 << 17);
      reg17.setAnimationProperties(data1, regionsFade*2);
      reg17.setColorProperties(data2*2, regionsSaturation*2+1, regionsBrightness*2+1); //, regionsHueInc/100);
    }
    else if (data1 == 18)
    {
      regionsRunning |= (1 << 18);
      reg18.setAnimationProperties(data1, regionsFade*2);
      reg18.setColorProperties(data2*2, regionsSaturation*2+1, regionsBrightness*2+1); //, regionsHueInc/100);
    }
    else if (data1 == 19)
    {
      regionsRunning |= (1 << 19);
      reg19.setAnimationProperties(data1, regionsFade*2);
      reg19.setColorProperties(data2*2, regionsSaturation*2+1, regionsBrightness*2+1); //, regionsHueInc/100);
    }
    else if (data1 == 20)
    {
      regionsRunning |= (1 << 20);
      reg20.setAnimationProperties(data1, regionsFade*2);
      reg20.setColorProperties(data2*2, regionsSaturation*2+1, regionsBrightness*2+1); //, regionsHueInc/100);
    }
    else if (data1 == 21)
    {
      regionsRunning |= (1 << 21);
      reg21.setAnimationProperties(data1, regionsFade*2);
      reg21.setColorProperties(data2*2, regionsSaturation*2+1, regionsBrightness*2+1); //, regionsHueInc/100);
    }
    else if (data1 == 22)
    {
      regionsRunning |= (1 << 22);
      reg22.setAnimationProperties(data1, regionsFade*2);
      reg22.setColorProperties(data2*2, regionsSaturation*2+1, regionsBrightness*2+1); //, regionsHueInc/100);
    }
    else if (data1 == 23)
    {
      regionsRunning |= (1 << 23);
      reg23.setAnimationProperties(data1, regionsFade*2);
      reg23.setColorProperties(data2*2, regionsSaturation*2+1, regionsBrightness*2+1); //, regionsHueInc/100);
    }
    else if (data1 == 24)
    {
      regionsRunning |= (1 << 24);
      reg24.setAnimationProperties(data1, regionsFade*2);
      reg24.setColorProperties(data2*2, regionsSaturation*2+1, regionsBrightness*2+1); //, regionsHueInc/100);
    }
    else if (data1 == 25)
    {
      regionsRunning |= (1 << 25);
      reg25.setAnimationProperties(data1, regionsFade*2);
      reg25.setColorProperties(data2*2, regionsSaturation*2+1, regionsBrightness*2+1); //, regionsHueInc/100);
    }
    else if (data1 == 26)
    {
      regionsRunning |= (1 << 26);
      reg26.setAnimationProperties(data1, regionsFade*2);
      reg26.setColorProperties(data2*2, regionsSaturation*2+1, regionsBrightness*2+1); //, regionsHueInc/100);
    }
    else if (data1 == 27)
    {
      regionsRunning |= (1 << 27);
      reg27.setAnimationProperties(data1, regionsFade*2);
      reg27.setColorProperties(data2*2, regionsSaturation*2+1, regionsBrightness*2+1); //, regionsHueInc/100);
    }
    else if (data1 == 30)
    {
      rmd1Running = 1;
      startRmd1(getFragmentProperties(channel, data2));
    }
    else if (data1 == 31)
    {
      rmd2Running = 1;
      startRmd2(getFragmentProperties(channel, data2));
    }
    else if (data1 == 32)
    {
      rmd3Running = 1;
      startRmd3(getFragmentProperties(channel, data2));
    }
    else if (data1 == 40)
    {
      cmr1Running = 1;
      startCmr1(getFragmentProperties(channel, data2));
    }
    else if (data1 == 41)
    {
      cmr2Running = 1;
      startCmr2(getFragmentProperties(channel, data2));
    }
    else if (data1 == 42)
    {
      cmr3Running = 1;
      startCmr3(getFragmentProperties(channel, data2));
    }
    else if (data1 == 41)
    {
      cmr2Running = 1;
      startCmr2(getFragmentProperties(channel, data2));
    }
    else if (data1 == 70)
    {
      gr1Running = 1;
      startGr1(getFragmentProperties(channel, data2));
    }
    else if (data1 == 71)
    {
      gr2Running = 1;
      startGr2(getFragmentProperties(channel, data2));
    }
    else if (data1 == 72)
    {
      gr3Running = 1;
      startGr3(getFragmentProperties(channel, data2));
    }
    else if (data1 == 73)
    {
      gr4Running = 1;
      startGr4(getFragmentProperties(channel, data2));
    }
    else if (data1 == 74)
    {
      gr5Running = 1;
      startGr5(getFragmentProperties(channel, data2));
    }
    break;

  case usbMIDI.AfterTouchPoly: // 0xA0
    Serial.print("AfterTouch Change, ch=");
    Serial.print(channel, DEC);
    Serial.print(", note=");
    Serial.print(data1, DEC);
    Serial.print(", velocity=");
    Serial.println(data2, DEC);
    break;

  case usbMIDI.ControlChange: // 0xB0
    Serial.print("Control Change, ch=");
    Serial.print(channel, DEC);
    Serial.print(", control=");
    Serial.print(data1, DEC);
    Serial.print(", value=");
    Serial.println(data2, DEC);

    // These can be 0
    if (channel == 5) {  // length and start for fragments
      fragmentsLength = data1;
      fragmentsStart = data2;
    }

    // Sometimes messages with 0 values come in, that have not been defined in the DAW.
    if (data1 > 0  && data2 > 0) {
      if (channel == 1) { // saturation and brightness for fragments
        fragmentsSaturation = data1;
        fragmentsBrightness = data2;
      }
      else if (channel == 2) {  // saturation and brightness for regions
        regionsSaturation = data1;
        regionsBrightness = data2;
      }
      else if (channel == 3) {  // fade and wait for fragments
        fragmentsFade = data1;
        fragmentsWait = data2;
      }
      else if (channel == 4) {  // fade for regions
        regionsFade = data1;
        // ToDo: HueInc commented out because sometimes it changes without the right message
        //regionsHueInc = data2;
      }
      Serial.println((String)"fSat " + fragmentsSaturation + " .. fBri " + fragmentsBrightness + " .. fFad " + fragmentsFade + " .. fWai " + fragmentsWait + " .. fLen " + fragmentsLength + " .. fSta " + fragmentsStart);
      Serial.println((String)"rSat " + regionsSaturation + " .. rBri " + regionsBrightness + " .. rFad " + regionsFade);
    };

    break;

  case usbMIDI.ProgramChange: // 0xC0
    Serial.print("Program Change, ch=");
    Serial.print(channel, DEC);
    Serial.print(", program=");
    Serial.println(data1, DEC);
    break;

  case usbMIDI.AfterTouchChannel: // 0xD0
    Serial.print("After Touch, ch=");
    Serial.print(channel, DEC);
    Serial.print(", pressure=");
    Serial.println(data1, DEC);
    break;

  case usbMIDI.PitchBend: // 0xE0
    Serial.print("Pitch Change, ch=");
    Serial.print(channel, DEC);
    Serial.print(", pitch=");
    Serial.println(data1 + data2 * 128, DEC);
    break;

  case usbMIDI.SystemExclusive: // 0xF0
    // Messages larger than usbMIDI's internal buffer are truncated.
    // To receive large messages, you *must* use the 3-input function
    // handler.  See InputFunctionsComplete for details.
    Serial.print("SysEx Message: ");
    printBytes(usbMIDI.getSysExArray(), data1 + data2 * 256);
    Serial.println();
    break;

  case usbMIDI.TimeCodeQuarterFrame: // 0xF1
    Serial.print("TimeCode, index=");
    Serial.print(data1 >> 4, DEC);
    Serial.print(", digit=");
    Serial.println(data1 & 15, DEC);
    break;

  case usbMIDI.SongPosition: // 0xF2
    Serial.print("Song Position, beat=");
    Serial.println(data1 + data2 * 128);
    break;

  case usbMIDI.SongSelect: // 0xF3
    Serial.print("Sond Select, song=");
    Serial.println(data1, DEC);
    break;

  case usbMIDI.TuneRequest: // 0xF6
    Serial.println("Tune Request");
    break;

  case usbMIDI.Clock: // 0xF8
    Serial.println("Clock");
    break;

  case usbMIDI.Start: // 0xFA
    Serial.println("Start");
    break;

  case usbMIDI.Continue: // 0xFB
    Serial.println("Continue");
    break;

  case usbMIDI.Stop: // 0xFC
    Serial.println("Stop");
    break;

  case usbMIDI.ActiveSensing: // 0xFE
    Serial.println("Actvice Sensing");
    break;

  case usbMIDI.SystemReset: // 0xFF
    Serial.println("System Reset");
    break;

  default:
    Serial.println("Opps, an unknown MIDI message type!");
  }
}

FragmentProperties getFragmentProperties(byte channel, byte data2) {
      FragmentProperties fP;
      fP.hue = data2*2;
      fP.sat = fragmentsSaturation*2;
      fP.bri = fragmentsBrightness*2;
      fP.hueIncrement = 0.0;
      fP.wait = fragmentsWait;
      fP.fade = fragmentsFade*2;
      if (channel == 1) {
        fP.reverse = false;
      }
      else {
        fP.reverse = true;
      }
      fP.length = fragmentsLength;
      fP.start = fragmentsStart;

      return fP;
}

void eraseAll()
{
  for (uint16_t i = 0; i < NUM_LEDS; i++)
  {
    crgbledstrip[i] = CRGB(0, 0, 0);
  }
  FastLED.show();
}

void fadeall()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    crgbledstrip[i].nscale8(250);
  }
}

void fadeIndividual()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    crgbledstrip[i].nscale8(fadestrip[i]);
  }
}

void printBytes(const byte *data, unsigned int size)
{
  while (size > 0)
  {
    byte b = *data++;
    if (b < 16)
      Serial.print('0');
    Serial.print(b, HEX);
    if (size > 1)
      Serial.print(' ');
    size = size - 1;
  }
}

// void setupAudioIn() {
//   pinMode(13,OUTPUT);//led indicator pin

//   cli();//disable interrupts

//   //set up continuous sampling of analog pin 0

//   //clear ADCSRA and ADCSRB registers
//   ADCSRA = 0;
//   ADCSRB = 0;

//   ADMUX |= (1 << REFS0); //set reference voltage
//   ADMUX |= (1 << ADLAR); //left align the ADC value- so we can read highest 8 bits from ADCH register only

//   ADCSRA |= (1 << ADPS2) | (1 << ADPS0); //set ADC clock with 32 prescaler- 1mHz/32=500kHz
//   ADCSRA |= (1 << ADATE); //enable auto trigger
//   ADCSRA |= (1 << ADIE); //enable interrupts when measurement complete
//   ADCSRA |= (1 << ADEN); //enable ADC
//   ADCSRA |= (1 << ADSC); //start ADC measurements

//   sei();//enable interrupts
// }

// ISR(ADC_vect) { //when new ADC value ready
//   incomingAudio = ADCH; //store 8 bit value from analog pin 0
//   incomingAudio = incomingAudio*9;
//   if (incomingAudio == 0 || incomingAudio == 255){
//     digitalWrite(13,HIGH);
//     clipping = 1;
//   }
//   else {
//     if (clipping){
//       clipping = 0;
//       digitalWrite(13,LOW);
//     }
//   }
// }
