#include <StandardCplusplus.h>
#include <FastLED.h>
#include <Adafruit_NeoPixel.h>
#include <vector>
using namespace std;

// General
#define DATA_PIN 6
#define NUM_LEDS 150 // 5 meter reel @ 30 LEDs/m

// Blinder Button
#define BUTTONPIN 2
#define LEDPIN 13
int buttonState = 0;

// Define the array of leds
CRGB leds[NUM_LEDS];

// SnipSign
// Glossary:
// 0: [array length (n)]
// 1-n: [startPx][lengthPx][color]
uint32_t blinders[][3] = {
  {2},
  {44, 8, 0xffffff},
  {97, 8, 0xffffff}
};
uint32_t snippet[][3] = {
  {2},
  {53, 30, 0xe71709},
  {124, 15, 0xf6a46a}
};
uint32_t upper[][3] = {
  {4},
  {29, 15, 0xacdfe5},
  {138, 12, 0x171f8a},
  {83, 15, 0x171f8a},
  {104, 18, 0xacdfe5}
};
uint32_t laser[][3] = {
  {1},
  {1, 28, 0xe71709}
};

// assigns single LEDs by number to columns of an imaginary LED matrix
/* vector<int> col1 {37};
vector<int> col2 {55,56};
vector<int> col3 {54,57};
vector<int> col4 {53,58,59,60};
vector<int> col5 {52,61,45,46};
vector<int> col6 {51,62,44,47};
vector<int> col7 {50,63,48,49,43,42,41};
vector<int> col8 {40,39,64,138,137}; */

vector< vector<int> > cols {
    {55,56},
    {54,57},
    {53,58,59,60},
    {52,61,45,46},
    {51,62,44,47},
    {50,63,48,49,43,42,41},
    {40,39,64,138,137},
    {38,65,139,136},
    {37,66,140,135},
    {36,67,141,134},
    {35,68,142,133},
    {34,69,143,132},
    {33,70,144,131},
    {32,71,145,130},
    {31,72,146,129},
    {30,73,147,128},
    {29,74,148,127},
    {28,75,149,126},
    {27,26,25,24,76,150,125},
    {23,77,78,79,80,81,82,124,123,122,121,120,119},
    {22,83,118},
    {21,84,117},
    {20,85,116},
    {19,86,115},
    {18,87,114},
    {17,88,113},
    {16,89,112},
    {15,90,111},
    {14,91,110},
    {13,92,109},
    {12,93,100,108,107,101},
    {11,94,95,99,106,102},
    {10,96,97,98,105,104,103,1},
    {9,2,0},
    {8,3},
    {7,4},
    {6,5}
};

// Mode Changer
#define NUMBEROFMODES 9
uint32_t mode = 0;

void setup() {
	Serial.begin(57600);
	Serial.println("resetting");
  	FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
	LEDS.setBrightness(84);
/* 
  // initialize the LED pin as an output:
  pinMode(LEDPIN, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(BUTTONPIN, INPUT);

  attachInterrupt(digitalPinToInterrupt(BUTTONPIN), blinderButton, CHANGE); */
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
      Serial.println((String)"blinders regionColor: " + blinders[1][2] +' '+" ... red: " + redFromHexColor(blinders[1][2]) +' '+" ... green: " + greenFromHexColor(blinders[1][2])+' '+" ... blue: " + blueFromHexColor(blinders[1][2])+' '+" ...");
 */

colsLtr(0,0,50,235,0,1,255,255);  // slow color
colsLtr(0,0,20,240,0,0,0,0);  // slow black out

colsRtl(0,cols.size()/4,10,130,0,0,150,255);    // fast part
colsRtl(0,cols.size()/4*2,10,130,0,0,150,255);    // fast part
colsRtl(0,cols.size()/4*3,10,130,0,0,150,255);    // fast part
colsRtl(0,cols.size(),10,130,0,0,150,255);    // fast part

colsRtl(0,0,10,130,0,0,0,255);    // fast white
colsLtr(0,0,10,130,0,0,0,255);    // fast white
colsRtl(0,0,20,230,0,1,255,255);  // fast color
colsRtl(0,0,10,240,0,0,0,0);  // fast black out
colsLtr(0,0,10,130,125,0.2,150,255);    // fast turquoise
colsRtl(0,0,10,130,220,0.2,150,255);    // fast purple


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



// #############
// F/X Functions
// #############



static void colsLtr(int start, int length, int wait, int fade, int hue, int hueIterator, int sat, int bri) {
    int colCount = cols.size();
    if (length!=0) {
        colCount = length;
    }
    for (int i=start; i<=colCount; i++) {
        vector<int> col = cols[i];
        int ledCount = col.size();
        for (int j=0; j<ledCount; j++) {
            int ledNum = col[j];
            leds[ledNum] = CHSV(hue+=hueIterator, sat, bri);
        }
        FastLED.show(); 
        delay(wait);
        fadeAllDynamic(fade);
    }
}
static void colsRtl(int start, int length, int wait, int fade, int hue, int hueIterator, int sat, int bri) {
    int colCount = cols.size();
    if (length!=0) {
        colCount = length;
    }
    for (int i=colCount; i>=start; i--) {
/*         if (i<start) {
          break;
        } */
        vector<int> col = cols[i];
        int ledCount = col.size();
        for (int j=0; j<ledCount; j++) {
            int ledNum = col[j];
            leds[ledNum] = CHSV(hue+=hueIterator, sat, bri);
        }
        FastLED.show(); 
        delay(wait);
        fadeAllDynamic(fade);
    }
}


static void cylon() {
	static uint8_t hue = 0;
	Serial.print("x");
	// First slide the led in one direction
	for(int i = 0; i < NUM_LEDS; i++) {
		// Set the i'th led to red 
		leds[i] = CHSV(0, 255, 255);
		// Show the leds
		FastLED.show(); 
		// now that we've shown the leds, reset the i'th led to black
		// leds[i] = CRGB::Black;
		fadeAll();
		// Wait a little bit before we loop around and do it again
		delay(10);
	}

	Serial.print("y");
	// Now go in the other direction.  
	for(int i = (NUM_LEDS)-1; i >= 0; i--) {
		// Set the i'th led to red 
		leds[i] = CHSV(hue++, 255, 255);
		// Show the leds
		FastLED.show();
		// now that we've shown the leds, reset the i'th led to black
		// leds[i] = CRGB::Black;
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
      leds[p] = CRGB(redFromHexColor(regions[r][2]), greenFromHexColor(regions[r][2]), blueFromHexColor(regions[r][2]));
    }
  }
  FastLED.show();
}

static void unltdFlashRegions(uint32_t regions[][3], uint16_t flashDelay) {
  while (1==1) {
    for (uint16_t r=1; r<=regions[0][0]; r++) {
      for(uint16_t p=regions[r][0]; p<regions[r][0]+regions[r][1]; p++) {
        leds[p] = CRGB(redFromHexColor(regions[r][2]), greenFromHexColor(regions[r][2]), blueFromHexColor(regions[r][2]));
      }
    }
    FastLED.show();
    delay(flashDelay);
      
    eraseAll();
    delay(flashDelay);

    checkInterrupts();
  }
}

static void flashRegions(uint32_t regions[][3], uint16_t flashCount, uint16_t flashDelay) {
  for (uint16_t f=0; f<flashCount; f++) {
    checkInterrupts();
    for (uint16_t r=1; r<=regions[0][0]; r++) {
      for(uint16_t p=regions[r][0]; p<regions[r][0]+regions[r][1]; p++) {
        leds[p] = CRGB(redFromHexColor(regions[r][2]), greenFromHexColor(regions[r][2]), blueFromHexColor(regions[r][2]));
        //Serial.println((String)"regionColor: " + regions[r][2] +' '+" ... red: " + redFromHexColor(regions[r][2]) +' '+" ... green: " + greenFromHexColor(regions[r][2])+' '+" ... blue: " + blueFromHexColor(regions[r][2])+' '+" ...");
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
    checkInterrupts();
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
    checkInterrupts();
    leds[pixel] = CRGB(redFromHexColor(c), greenFromHexColor(c), blueFromHexColor(c));
    c = subColor(c, sub);
    pixel = incrementPixel(pixel, inc);
    FastLED.show();
    delay(10);
  }
  
  delay(100);
  eraseAll();
}



// ################
// Helper Functions
// ################


void fadeAll() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); } }
void fadeAllFast() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(200); } }
void fadeAllDynamic(int fade) { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(fade); } }

uint32_t blueFromHexColor(uint32_t hexColor) {
    uint32_t rgbBlue = hexColor & 0b11111111;
    return rgbBlue;
}
uint32_t greenFromHexColor(uint32_t hexColor) {
    uint32_t rgbGreen = (hexColor>>8) & 0b11111111;
    return rgbGreen;
}
uint32_t redFromHexColor(uint32_t hexColor) {
    uint32_t rgbRed = (hexColor>>16) & 0b11111111;
    return rgbRed;
}

static int32_t subColor(uint32_t c, int32_t sub) {
  int32_t result = c-sub;
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

static void setPixelColorWithinSnipleds(uint32_t p, uint32_t c) {
    // if outside bounds, don't try to set this pixel
    if (p>0 && p<=NUM_LEDS) {
        leds[p] = CRGB(redFromHexColor(c), greenFromHexColor(c), blueFromHexColor(c));
    }
}

static void switchMode() {
  if (mode<=NUMBEROFMODES) {
    mode++;
  }
  else {
    mode = 0;
  }
}

static void eraseAll() {
    for(uint16_t i=0; i<NUM_LEDS; i++) {
        leds[i] = CRGB(0,0,0);
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

static void checkInterrupts() {
/*   while (buttonState==HIGH) {
    digitalWrite(LEDPIN, buttonState);
    if (buttonState==LOW) {
      digitalWrite(LEDPIN, buttonState);
      break;
    }
  } */
} 