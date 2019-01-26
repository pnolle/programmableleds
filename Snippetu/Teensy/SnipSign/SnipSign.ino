/* 
##############################
SnipSign programmable LED sign
by Niklas Köhn
##############################

Uses FastLED to animate Neopixels. Receives MIDI.

Contains parts from Marc Merlin's work Neopixel-IR.
MIDI part adapted from Teensy MIDI demo.
*/


#include "const.h"
#include <FastLED.h>
#include "fragmentColumnMovingRight.h"
#include "fragmentRowMovingUp.h"
#include "vector"

using namespace std;

LedUtils ledUtils;
ColumnMovingRight turquoiseCMR(ledUtils, millis());
ColumnMovingRight orangeCMR(ledUtils, millis());
RowMovingUp greenRMU(ledUtils, millis());
RowMovingUp redRMU(ledUtils, millis());

#define DATA_PIN 6
#define NUM_LEDS 479
#define DEBUG true
#define SOUND2LIGHT false
#define FRAGMENTS true

// Define the array of leds
CRGB crgbledstrip[NUM_LEDS];
// The fade values of the last 2 LEDs were always messed up. By increasing the array size by 2 the problem disappears... don't know why.
int fadestrip[NUM_LEDS+2];

// AudioIn
byte incomingAudio;
boolean clipping = 0;




void setup() {
  Serial.begin(115200);

  // init fadestrip: set all values to 0
  for(int i = 0; i < NUM_LEDS; i++) {
    fadestrip[i] = 0;
  }

	Serial.println("LED Setup");
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(crgbledstrip, NUM_LEDS);
	LEDS.setBrightness(84); //84);
  FastLED.show(); // Initialize all pixels to 'off'

  // setupAudioIn();

  turquoiseCMR.setColorProperties(39, 1.0, 150, 0.0);
  resetTurquoiseCMRAnimation();

  orangeCMR.setColorProperties(30, 200, 250, 0.0);
  resetOrangeCMRAnimation();

  greenRMU.setColorProperties(116, 78, 100, 0.0);
  resetGreenRMUAnimation();

  redRMU.setColorProperties(0, 93, 94, 0.5);
  resetRedRMUAnimation();

  eraseAll();

  Serial.println("Setup done");
}



void resetTurquoiseCMRAnimation() {
  turquoiseCMR.setAnimationProperties(100, 230, true, 20, 30);
}
void resetOrangeCMRAnimation() {
  orangeCMR.setAnimationProperties(30, 180, false);
}
void resetGreenRMUAnimation() {
  greenRMU.setAnimationProperties(40, 230, false, 10, 20);
}
void resetRedRMUAnimation() {
  redRMU.setAnimationProperties(40, 230, false);
}




void loop() {
// ToDo: Refactor this into a generic function. Goal is that animations can be started like "impulses" and the rest will run automatically.
// ToDo: active animation objects should sit in a vector and remove themselves when they're finished.
  bool turquoiseAnimationFinished = false;
  bool orangeAnimationFinished = false;
  bool greenAnimationFinished = false;
  bool redAnimationFinished = false;

  vector<PixelUpdate> matrixUpdate;

  orangeCMR.nextFrame(millis(), matrixUpdate, orangeAnimationFinished);
  if (orangeAnimationFinished == true) {
    resetOrangeCMRAnimation();
    if (DEBUG) Serial.println((String) "orangeAnimationFinished");
    orangeAnimationFinished = false;
  }

  turquoiseCMR.nextFrame(millis(), matrixUpdate, turquoiseAnimationFinished);
  if (turquoiseAnimationFinished == true) {
    resetTurquoiseCMRAnimation();
    if (DEBUG) Serial.println((String) "turquoiseAnimationFinished");
    turquoiseAnimationFinished = false;
  }

   greenRMU.nextFrame(millis(), matrixUpdate, greenAnimationFinished);
   if (greenAnimationFinished == true) {
     resetGreenRMUAnimation();
     if (DEBUG) Serial.println((String) "greenAnimationFinished");
     greenAnimationFinished = false;
   }

   redRMU.nextFrame(millis(), matrixUpdate, redAnimationFinished);
   if (redAnimationFinished == true) {
     resetRedRMUAnimation();
     if (DEBUG) Serial.println((String) "redAnimationFinished");
     redAnimationFinished = false;
   }

  if (matrixUpdate.size() > 0) {
    for (vector<PixelUpdate>::iterator it = matrixUpdate.begin(); it != matrixUpdate.end(); ++it) {
      int ledNum = matrixColumnsDownTop[it->row][it->col];
      if (ledNum > -1) {
        crgbledstrip[ledNum] = CHSV(it->hue, it->sat, it->bri);
        if (DEBUG) Serial.println((String) "matrixUpdate at time " + millis() + ": col" + it->col + " / row" + it->row + " ... hue" + it->hue + " ... sat" + it->sat + " ... bri" + it->bri + ": fade" + it->fade + " ... time" + it->time + " ... ledNum" + ledNum + " ... fadestrip[ledNum]" + fadestrip[ledNum]); 
      }
      fadestrip[ledNum] = it->fade;
    }
    FastLED.show();
    fadeIndividual();
  }


	// static uint8_t hue = 0;
	// // First slide the led in one direction
	// for(int i = 0; i < NUM_LEDS; i++) {
	// 	// Set the i'th led to red 
	// 	crgbledstrip[i] = CHSV(0, 255, 255);
	// 	// Show the leds
	// 	FastLED.show(); 
	// 	// now that we've shown the 193, reset the i'th led to black
	// 	// crgbledstrip[i] = CRGB::Black;
	// 	fadeall();
	// 	// Wait a little bit before we loop around and do it again
	// 	delay(5);
	// }

	// // Now go in the other direction.  
	// for(int i = (NUM_LEDS)-1; i >= 0; i--) {
	// 	// Set the i'th led to red 
	// 	crgbledstrip[i] = CHSV(hue++, 255, 255);
	// 	// Show the leds
	// 	FastLED.show();
	// 	// now that we've shown the leds, reset the i'th led to black
	// 	// crgbledstrip[i] = CRGB::Black;
	// 	fadeall();
	// 	// Wait a little bit before we loop around and do it again
	// 	delay(5);
	// }
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





void processMIDI(void) {
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
  switch (type) {
    case usbMIDI.NoteOff: // 0x80
      Serial.print("Note Off, ch=");
      Serial.print(channel, DEC);
      Serial.print(", note=");
      Serial.print(data1, DEC);
      Serial.print(", velocity=");
      Serial.println(data2, DEC);
      break;

    case usbMIDI.NoteOn: // 0x90
      Serial.print("Note On, ch=");
      Serial.print(channel, DEC);
      Serial.print(", note=");
      Serial.print(data1, DEC);
      Serial.print(", velocity=");
      Serial.println(data2, DEC);
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



void eraseAll() {
  for(uint16_t i=0; i<NUM_LEDS; i++) {
      crgbledstrip[i] = CRGB(0,0,0);
  }
  FastLED.show(); 
}

void fadeall() { 
  for(int i = 0; i < NUM_LEDS; i++) { 
    crgbledstrip[i].nscale8(250); 
  } 
}

void fadeIndividual() {
  for(int i = 0; i < NUM_LEDS; i++) {
    crgbledstrip[i].nscale8(fadestrip[i]);
  }
}


void printBytes(const byte *data, unsigned int size) {
  while (size > 0) {
    byte b = *data++;
    if (b < 16) Serial.print('0');
    Serial.print(b, HEX);
    if (size > 1) Serial.print(' ');
    size = size - 1;
  }
}

