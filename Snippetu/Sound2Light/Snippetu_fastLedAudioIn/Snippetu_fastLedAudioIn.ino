#include "const.h"
#include <FastLED.h>
//#include <Adafruit_NeoPixel.h>
#include "fragmentColumnMovingRight.h"
#include <StandardCplusplus.h>
#include "vector"

using namespace std;

LedUtils ledUtils;
ColumnMovingRight turquoiseCMR(ledUtils, millis());
ColumnMovingRight orangeCMR(ledUtils, millis());

// ####
// LEDs
// ####

// General
#define DATA_PIN 6
#define NUM_LEDS 150 // 5 meter reel @ 30 LEDs/m
#define DEBUG false
#define SOUND2LIGHT false
#define FRAGMENTS true

// Blinder Button
#define BUTTONPIN 2
#define LEDPIN 13

// Mode Changer
#define NUMBEROFMODES 9

//variable to store incoming audio sample
byte incomingAudio;

//clipping indicator variables
boolean clipping = 0;

// Blinder Button
int buttonState = 0;

// Mode
uint32_t mode = 0;

// Define the array of crgbledstrip
CRGB crgbledstrip[NUM_LEDS];
vector<int> fadestrip;


void setup() {
	Serial.begin(57600);
	Serial.println("### setup ###");


// ####
// LEDs
// ####
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(crgbledstrip, NUM_LEDS);
	LEDS.setBrightness(84);
/* 
  // initialize the LED pin as an output:
  pinMode(LEDPIN, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(BUTTONPIN, INPUT);

  attachInterrupt(digitalPinToInterrupt(BUTTONPIN), blinderButton, CHANGE); */


// #######
// AudioIn
// #######
  
  pinMode(13,OUTPUT);//led indicator pin
  
  cli();//disable interrupts
  
  //set up continuous sampling of analog pin 0
  
  //clear ADCSRA and ADCSRB registers
  ADCSRA = 0;
  ADCSRB = 0;
  
  ADMUX |= (1 << REFS0); //set reference voltage
  ADMUX |= (1 << ADLAR); //left align the ADC value- so we can read highest 8 bits from ADCH register only
  
  ADCSRA |= (1 << ADPS2) | (1 << ADPS0); //set ADC clock with 32 prescaler- 1mHz/32=500kHz
  ADCSRA |= (1 << ADATE); //enabble auto trigger
  ADCSRA |= (1 << ADIE); //enable interrupts when measurement complete
  ADCSRA |= (1 << ADEN); //enable ADC
  ADCSRA |= (1 << ADSC); //start ADC measurements
  
  sei();//enable interrupts


  turquoiseCMR.setColorProperties(39, 1.0, 150, 10.0);
  turquoiseCMR.setAnimationProperties(0, 0, 50, 240);

  orangeCMR.setColorProperties(30, 200, 250, 0.0);
  orangeCMR.setAnimationProperties(0, 0, 20, 250);

  eraseAll();
}


// #######
// AudioIn
// #######

ISR(ADC_vect) { //when new ADC value ready
  incomingAudio = ADCH; //store 8 bit value from analog pin 0
  incomingAudio = incomingAudio*9;
  if (incomingAudio == 0 || incomingAudio == 255){
    digitalWrite(13,HIGH);
    clipping = 1;
  }
  else {
    if (clipping){
      clipping = 0;
      digitalWrite(13,LOW);
    }
  }
}


/* void blinderButton() {
  buttonState = digitalRead(BUTTONPIN);
  digitalWrite(LEDPIN, buttonState);
  if (buttonState!=HIGH) {
    eraseAll();
  }
  else {
    unltdLightRegions(blinders);
  }
} */




void loop() {
/* 
      Serial.println((String)"blinders regionColor: " + blinders[1][2] +' '+" ... red: " + ledUtils.redFromHexColor(blinders[1][2]) +' '+" ... green: " + ledUtils.greenFromHexColor(blinders[1][2])+' '+" ... blue: " + ledUtils.blueFromHexColor(blinders[1][2])+' '+" ...");
 */

if (SOUND2LIGHT) {
  lightHowManyRows(ledUtils.getNumLeds(incomingAudio, rowCount+3, -3), 220, 60, 0.2, 255, 255);
/* 
  lightHowMany(getNumLeds(incomingAudio, 150, -25), 240, 120, 0.1, 255, 255);
 */
}
else if (FRAGMENTS) {

// ToDo: Refactor this into a generic function. Goal is that animations can be started like "impulses" and the rest will run automatically.
// ToDo: active animation objects should sit in a vector and remove themselves when they're finished.
  bool turquoiseAnimationFinished = false;
  bool orangeAnimationFinished = false;

  vector<PixelUpdate> matrixUpdate;
  orangeCMR.nextFrame(millis(), matrixUpdate, fadestrip, orangeAnimationFinished);
  if (orangeAnimationFinished == true) {
    orangeCMR.setAnimationProperties(0, 0, 20, 250);
    if (DEBUG) Serial.println((String) "orangeAnimationFinished");
    orangeAnimationFinished = false;
  }

  turquoiseCMR.nextFrame(millis(), matrixUpdate, fadestrip, turquoiseAnimationFinished);
  if (turquoiseAnimationFinished == true) {
    turquoiseCMR.setAnimationProperties(0, 0, 50, 240);
    if (DEBUG) Serial.println((String) "turquoiseAnimationFinished");
    turquoiseAnimationFinished = false;
  }

  if (matrixUpdate.size() > 0) {
    for (vector<PixelUpdate>::iterator it = matrixUpdate.begin(); it != matrixUpdate.end(); ++it) {
      int ledNum = matrixColumnsLeftRight[it->col][it->row];
      if (DEBUG) Serial.println((String) "matrixUpdate at time " + millis() + ": col" + it->col + " / row" + it->row + " ... hue" + it->hue + " ... sat" + it->sat + " ... bri" + it->bri + " ... time" + it->time + " ... ledNum" + ledNum);
      crgbledstrip[ledNum] = CHSV(it->hue, it->sat, it->bri);
    }
    FastLED.show();
    // ToDo: store fade values in fadelist
    //fadeIndividual();
    fadeAllDynamic(230);
  }
}
else {

  lightEvery10();

  matrixTtd(0,0,50,235,120,0.1,255,255);  // slow color
  matrixTtd(0,0,20,240,0,0,0,0);  // slow black out
  matrixLtr(0,0,50,235,0,0.3,255,255);  // slow color
  matrixLtr(0,0,20,240,0,0,0,0);  // slow black out

  matrixDtt(0,0,20,130,125,0.2,150,255);    // fast turquoise
  matrixTtd(0,0,20,130,220,0.2,150,255);    // fast purple

  matrixRtl(0,0,10,130,0,0,0,255);    // fast white
  matrixLtr(0,0,10,130,0,0,0,255);    // fast white
  matrixRtl(0,0,20,230,0,1,255,255);  // fast color
  matrixRtl(0,0,10,240,0,0,0,0);  // fast black out
  matrixLtr(0,0,10,130,125,0.2,150,255);    // fast turquoise
  matrixRtl(0,0,10,130,220,0.2,150,255);    // fast purple


/* 
  switch(mode) {
    case 0: 
      sparkle(0xff0000, 50, 20, 10);
      switchMode();
      break;
    case 1:
      flashRegions(blinders, 20, 30);
      switchMode();
      break;
     case 2:
      chase(0x00dddd, true, 0x000000);
      switchMode();
      break;
    case 3:
      flashRegions(blinders, 20, 30);
      switchMode();
      break;
    case 4:
      //sparkle(0x00ff00, 100, 10, 30);
      switchMode();
      break;
    case 5:
      flashRegions(blinders, 20, 30);
      switchMode();
      break;
    case 6:
      flashRegions(snippet, 20, 20);
      switchMode();
      break;
    case 7:
      flashRegions(upper, 20, 20);
      switchMode();
      break;
    case 8:
      flashRegions(laser, 20, 20);
      switchMode();
      break;
    case 9:
      flashRegions(blinders, 20, 30);
      switchMode();
      break; 
    case 10:
      cylon();
      switchMode();
      break;
    default:
      chase(0x0000ff, false, 0x000000);
      switchMode();
      break;
  }
 */

    //bothdir(0x0000FF); // Blue
    //chase(0x00FF00, false); // Green
}
}



// #############
// F/X Functions
// #############



static void lightEvery10() {
  eraseAll(); 
  for (int j=0; j<150; j++) {
    if (j%10==0) crgbledstrip[j] = CHSV(20, 255, 255);
  }
  FastLED.show(); 
  delay(3000);
}

static void lightHowMany(int numLeds, int fade, double hue, double hueIncrement, int sat, int bri) {
    fadeAllDynamic(fade);
    for(int i=0; i<=numLeds; i++) {
      crgbledstrip[i] = CHSV(hue+=hueIncrement, sat, bri);
    }
    FastLED.show(); 
}

static void lightHowManyRows(int numRows, int fade, double hue, double hueIncrement, int sat, int bri) {
  fadeAllDynamic(fade);
  int colCountLocal = colCount;
/*   if (length!=0) {
      colCountLocal = length;
  } */
  int ledCount = numRows;
  for (int i=0; i<ledCount; i++) {
      if (DEBUG) Serial.print("row ");
      if (DEBUG) Serial.print(i);
    for (int j=0; j<colCountLocal; j++) {
      if (DEBUG) Serial.print(" | col");
      if (DEBUG) Serial.print(j);
      int ledNum = matrixColumnsDownTop[j][i];
      if (hueIncrement > 0) hue = ledUtils.incrementHue(hue, hueIncrement);
      crgbledstrip[ledNum] = CHSV(hue, sat, bri);
      if (DEBUG) Serial.print(" #");
      if (DEBUG) Serial.print(ledNum);
    }
    if (DEBUG) Serial.println(" | EOR");
    FastLED.show(); 
  }
  if (DEBUG) Serial.println(" | EOM");
  FastLED.show(); 
}


static void matrixLtr(int start, int length, int wait, int fade, double hue, double hueIncrement, int sat, int bri) {
    int colCountLocal = colCount;
    if (length!=0) {
        colCountLocal = length;
    }
    int ledCount = rowCount;
    for (int i=start; i<colCountLocal; i++) {
      for (int j=0; j<ledCount; j++) {
        int ledNum = matrixColumnsLeftRight[i][j];
        if (hueIncrement > 0) hue = ledUtils.incrementHue(hue, hueIncrement);
        crgbledstrip[ledNum] = CHSV(hue, sat, bri);
      }
      FastLED.show(); 
      delay(wait);
      fadeAllDynamic(fade);
    }
}
static void matrixRtl(int start, int length, int wait, int fade, double hue, double hueIncrement, int sat, int bri) {
    int colCountLocal = colCount;
    if (length!=0) {
        colCountLocal = length;
    }
    int ledCount = rowCount;
    for (int i=colCountLocal-1; i>=start; i--) {
      for (int j=0; j<ledCount; j++) {
        int ledNum = matrixColumnsLeftRight[i][j];
        if (hueIncrement > 0) hue = ledUtils.incrementHue(hue, hueIncrement);
        crgbledstrip[ledNum] = CHSV(hue, sat, bri);
      }
      FastLED.show(); 
      delay(wait);
      fadeAllDynamic(fade);
    }
}

static void matrixTtd(int start, int length, int wait, int fade, double hue, double hueIncrement, int sat, int bri) {
    int colCountLocal = colCount;
    if (length!=0) {
        colCountLocal = length;
    }
    if (DEBUG) Serial.print("matrixTtd | colCount");
    if (DEBUG) Serial.print(colCountLocal);
    int ledCount = rowCount;
    if (DEBUG) Serial.print(" | rowCount");
    if (DEBUG) Serial.println(ledCount);
    for (int i=start; i<ledCount; i++) {
        if (DEBUG) Serial.print("row ");
        if (DEBUG) Serial.print(i);
      for (int j=0; j<colCountLocal; j++) {
        if (DEBUG) Serial.print(" | col");
        if (DEBUG) Serial.print(j);
        int ledNum = matrixColumnsDownTop[j][i];
        if (hueIncrement > 0) hue = ledUtils.incrementHue(hue, hueIncrement);
        crgbledstrip[ledNum] = CHSV(hue, sat, bri);
        if (DEBUG) Serial.print(" #");
        if (DEBUG) Serial.print(ledNum);
      }
      if (DEBUG) Serial.println(" | EOR");
      FastLED.show(); 
      delay(wait);
      fadeAllDynamic(fade);
    }
    if (DEBUG) Serial.println(" | EOM");
}

static void matrixDtt(int start, int length, int wait, int fade, double hue, double hueIncrement, int sat, int bri) {
    int colCountLocal = colCount;
    if (length!=0) {
        colCountLocal = length;
    }
    if (DEBUG) Serial.print("matrixDtt | colCount");
    if (DEBUG) Serial.print(colCountLocal);
    int ledCount = rowCount;
    if (DEBUG) Serial.print(" | rowCount");
    if (DEBUG) Serial.println(ledCount);
    for (int i=ledCount-1; i>=start; i--) {
        if (DEBUG) Serial.print("row ");
        if (DEBUG) Serial.print(i);
      for (int j=colCountLocal-1; j>=0; j--) {
        if (DEBUG) Serial.print(" | col");
        if (DEBUG) Serial.print(j);
        int ledNum = matrixColumnsDownTop[j][i];
        if (hueIncrement > 0) hue = ledUtils.incrementHue(hue, hueIncrement);
        crgbledstrip[ledNum] = CHSV(hue, sat, bri);
        if (DEBUG) Serial.print(" #");
        if (DEBUG) Serial.print(ledNum);
      }
      if (DEBUG) Serial.println(" | EOR");
      FastLED.show(); 
      delay(wait);
      fadeAllDynamic(fade);
    }
    if (DEBUG) Serial.println(" | EOM");
}


static void cylon() {
	static uint8_t hue = 0;
	Serial.print("x");
	// First slide the led in one direction
	for(int i = 0; i < NUM_LEDS; i++) {
		// Set the i'th led to red 
		crgbledstrip[i] = CHSV(0, 255, 255);
		// Show the crgbledstrip
		FastLED.show(); 
		// now that we've shown the crgbledstrip, reset the i'th led to black
		// crgbledstrip[i] = CRGB::Black;
		fadeAll();
		// Wait a little bit before we loop around and do it again
		delay(10);
	}

	Serial.print("y");
	// Now go in the other direction.  
	for(int i = (NUM_LEDS)-1; i >= 0; i--) {
		// Set the i'th led to red 
		crgbledstrip[i] = CHSV(hue++, 255, 255);
		// Show the crgbledstrip
		FastLED.show();
		// now that we've shown the crgbledstrip, reset the i'th led to black
		// crgbledstrip[i] = CRGB::Black;
		fadeAll();
		// Wait a little bit before we loop around and do it again
		delay(10);
	}

}



static void unltdLightRegions(uint32_t regions[][3]) {
  eraseAll();
  delay(100);
  for (uint16_t r=1; r<=regions[0][0]; r++) {
    for(uint16_t p=regions[r][0]; p<regions[r][0]+regions[r][1]; p++) {
      crgbledstrip[p] = CRGB(ledUtils.redFromHexColor(regions[r][2]), ledUtils.greenFromHexColor(regions[r][2]), ledUtils.blueFromHexColor(regions[r][2]));
    }
  }
  FastLED.show();
}

static void unltdFlashRegions(uint32_t regions[][3], uint16_t flashDelay) {
  while (1==1) {
    for (uint16_t r=1; r<=regions[0][0]; r++) {
      for(uint16_t p=regions[r][0]; p<regions[r][0]+regions[r][1]; p++) {
        crgbledstrip[p] = CRGB(ledUtils.redFromHexColor(regions[r][2]), ledUtils.greenFromHexColor(regions[r][2]), ledUtils.blueFromHexColor(regions[r][2]));
      }
    }
    FastLED.show();
    delay(flashDelay);
      
    eraseAll();
    delay(flashDelay);

    ledUtils.checkInterrupts();
  }
}

static void flashRegions(uint32_t regions[][3], uint16_t flashCount, uint16_t flashDelay) {
  for (uint16_t f=0; f<flashCount; f++) {
    ledUtils.checkInterrupts();
    for (uint16_t r=1; r<=regions[0][0]; r++) {
      for(uint16_t p=regions[r][0]; p<regions[r][0]+regions[r][1]; p++) {
        crgbledstrip[p] = CRGB(ledUtils.redFromHexColor(regions[r][2]), ledUtils.greenFromHexColor(regions[r][2]), ledUtils.blueFromHexColor(regions[r][2]));
        //Serial.println((String)"regionColor: " + regions[r][2] +' '+" ... red: " + ledUtils.redFromHexColor(regions[r][2]) +' '+" ... green: " + ledUtils.greenFromHexColor(regions[r][2])+' '+" ... blue: " + ledUtils.blueFromHexColor(regions[r][2])+' '+" ...");
      }
    }
    FastLED.show();
    delay(flashDelay);
      
    eraseAll();
    delay(flashDelay);
  }

}

static void sparkle(uint32_t c, uint16_t sparklength, uint16_t delaydraw, uint16_t delaydel) {
  uint32_t sub = 0x000000;

  // draw
  int startpixel = -1 * sparklength; // start at pixel number with negative sparklength so that sparke "enters" the strip
  int p = startpixel;
  for(uint16_t j=0; j<NUM_LEDS+sparklength; j++) {
     Serial.println(startpixel);
    ledUtils.checkInterrupts();
    // draw "frames" from front
    for (uint16_t d=0; d<=sparklength/2; d++) {
        setPixelColorWithinSnipleds(p, c);
        c-=sub;
        p=incrementPixel(p,2);
    }
    startpixel++;
    p = startpixel;
    
    FastLED.show();
    delay(delaydraw);
  
    eraseAll();
    delay(delaydel);
  }

}

static void chase(uint32_t c, bool forward, int32_t sub) {
  int8_t inc = 1;
  uint16_t pixel = 0;
  if (!forward) {
    inc = -1;
    pixel = NUM_LEDS;
  }
  for(uint16_t i=0; i<getAmountOfSnipPixels(); i++) {
    ledUtils.checkInterrupts();
    crgbledstrip[pixel] = CRGB(ledUtils.redFromHexColor(c), ledUtils.greenFromHexColor(c), ledUtils.blueFromHexColor(c));
    c = ledUtils.subColor(c, sub);
    pixel = incrementPixel(pixel, inc);
    FastLED.show();
    delay(10);
  }
  
  delay(100);
  eraseAll();
}




// ################
// General F/X
// ################


void fadeAll() { for(int i = 0; i < NUM_LEDS; i++) { crgbledstrip[i].nscale8(250); } }
void fadeAllFast() { for(int i = 0; i < NUM_LEDS; i++) { crgbledstrip[i].nscale8(200); } }
void fadeAllDynamic(int fade) { for(int i = 0; i < NUM_LEDS; i++) { crgbledstrip[i].nscale8(fade); } }
void fadeIndividual() { 
  for(int i = 0; i < NUM_LEDS; i++) {
    crgbledstrip[i].nscale8(fadestrip[i]);
  }
}


void setPixelColorWithinSnipleds(uint32_t p, uint32_t c) {
    // if outside bounds, don't try to set this pixel
    if (p>0 && p<=NUM_LEDS) {
        crgbledstrip[p] = CRGB(ledUtils.redFromHexColor(c), ledUtils.greenFromHexColor(c), ledUtils.blueFromHexColor(c));
    }
}

void switchMode() {
  if (mode<=NUMBEROFMODES) {
    mode++;
  }
  else {
    mode = 0;
  }
}

void eraseAll() {
    for(uint16_t i=0; i<NUM_LEDS; i++) {
        crgbledstrip[i] = CRGB(0,0,0);
    }
    FastLED.show(); 
}

static uint16_t incrementPixel(uint16_t p, uint16_t inc) {
  uint16_t result = p+inc;
  while ((result>=blinders[1][0] && result<blinders[1][0]+blinders[1][1]) ||
         (result>=blinders[2][0] && result<blinders[2][0]+blinders[2][1])
  ) {
    result+=inc;
  }
  return result;
}

static uint16_t getAmountOfSnipPixels() {
  return NUM_LEDS - 2*blinders[1][1];
}