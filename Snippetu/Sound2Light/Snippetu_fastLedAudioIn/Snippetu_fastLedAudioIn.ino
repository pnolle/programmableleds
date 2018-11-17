#include <FastLED.h>
#include <Adafruit_NeoPixel.h>


// #######
// AudioIn
// #######

//variable to store incoming audio sample
byte incomingAudio;

//clipping indicator variables
boolean clipping = 0;


// ####
// LEDs
// ####

// General
#define DATA_PIN 6
#define NUM_LEDS 150 // 5 meter reel @ 30 LEDs/m
#define DEBUG false
#define SOUND2LIGHT false

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
const int colCount = 37;
const int rowCount = 15;
uint32_t matrixColumnsLeftRight[colCount][rowCount] = {
  { -1, -1, -1,  -1 , -1 , -1 , -1 , -1, 55 , 56 , -1 , -1 , -1 , -1 , -1 },
  { -1, -1, -1,  -1 , -1 , -1 , -1 , -1, 54 , -1 , 57 , -1 , -1 , -1 , -1 },
  { -1, -1, -1,  -1 , -1 , -1 , -1 , -1, 53 , -1 , -1 , 58 , -1 , 59 , 60 },
  { -1, -1, -1,  -1 , -1 , -1 , -1 , -1, 52 , -1 , -1 , 61 , -1 , 45 , 46 },
  { -1, -1, -1,  -1 , -1 , -1 , -1 , -1, 51 , -1 , -1 , -1 , 62 , 44 , 47 },
  { -1, -1, -1,  -1 , -1 , -1 , -1 , -1, 50 , 63 , 48 , 49 , 43 , 42 , 41 },
  { -1, -1, -1, 40 , 39 , -1 , 138, 137, -1 , -1 , -1 , -1 , -1 , -1 , 64 },
  { -1, -1, -1, 38 , -1 , -1 , 139, 136, -1 , -1 , -1 , -1 , -1 , -1 , 65 },
  { -1, -1, -1, 37 , -1 , -1 , 140, 135, -1 , -1 , -1 , -1 , -1 , -1 , 66 },
  { -1, -1, -1, 36 , -1 , -1 , 141, 134, -1 , -1 , -1 , -1 , -1 , -1 , 67 },
  { -1, -1, -1, 35 , -1 , -1 , 142, 133, -1 , -1 , -1 , -1 , -1 , -1 , 68 },
  { -1, -1, -1, 34 , -1 , -1 , 143, 132, -1 , -1 , -1 , -1 , -1 , -1 , 69 },
  { -1, -1, -1, 33 , -1 , -1 , 144, 131, -1 , -1 , -1 , -1 , -1 , -1 , 70 },
  { -1, -1, -1, 32 , -1 , -1 , 145, 130, -1 , -1 , -1 , -1 , -1 , -1 , 71 },
  { -1, -1, -1, 31 , -1 , -1 , 146, 129, -1 , -1 , -1 , -1 , -1 , -1 , 72 },
  { -1, -1, -1, 30 , -1 , -1 , 147, 128, -1 , -1 , -1 , -1 , -1 , -1 , 73 },
  { -1, -1, -1, 29 , -1 , -1 , 148, 127, -1 , -1 , -1 , -1 , -1 , -1 , 74 },
  { 25, 27, 28 , -1, -1 , -1 , 149, 126, -1 , -1 , -1 , -1 , -1 , -1 , 75 },
  { 24, 26, -1 , -1, -1 , -1 , 150, 125, -1 , -1 , -1 , -1 , -1 , -1 , 76 },
  { 23, -1, -1 , -1, 122, 121, 123, 124, -1 , 77 , 78 , 79 , 80 , 81  , 82},
  { 22, -1, -1 , -1, 118, -1 , 120 , 119, 83, -1 , -1 , -1 , -1 , -1 , -1 },
  { 21, -1 , -1, -1 , 117, -1 , -1 , -1 , 84, -1 , -1 , -1 , -1 , -1 , -1 },
  { 20, -1 , -1, -1 , 116, -1 , -1 , -1 , 85, -1 , -1 , -1 , -1 , -1 , -1 },
  { 19, -1 , -1, -1 , 115, -1 , -1 , -1 , 86, -1 , -1 , -1 , -1 , -1 , -1 },
  { 18, -1 , -1, -1 , 114, -1 , -1 , -1 , 87, -1 , -1 , -1 , -1 , -1 , -1 },
  { 17, -1 , -1, -1 , 113, -1 , -1 , -1 , 88, -1 , -1 , -1 , -1 , -1 , -1 },
  { 16, -1 , -1, -1 , 112, -1 , -1 , -1 , 89, -1 , -1 , -1 , -1 , -1 , -1 },
  { 15, -1 , -1, -1 , 111, -1 , -1 , -1 , 90, -1 , -1 , -1 , -1 , -1 , -1 },
  { 14, -1 , -1, -1 , 110, -1 , -1 , -1 , 91, -1 , -1 , -1 , -1 , -1 , -1 },
  { 13, -1 , -1, -1 , 109, -1 , -1 , -1 , 92, -1 , -1 , -1 , -1 , -1 , -1 },
  { 12, -1 , -1, -1 , -1 , -1 , 108, 107, -1 , -1 , -1 , -1 , -1 , -1 , 93},
  { 11, -1 , -1, -1 , -1 , -1 , 100, 101, -1 , -1 , 94 , 95 , 99 , 106,102},
  { 10, -1 , -1, -1 ,  1 , 105, 104, 103,  0 , -1 , -1 , 96 , 97 , 98 , -1},
  { -1,  9 , -1, -1 ,  2 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1},
  { -1,  8 , -1, -1 ,  3 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1},
  { -1, -1 ,  7,  4 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1},
  { -1, -1 ,  6,  5 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1}
};
uint32_t matrixColumnsDownTop[colCount][rowCount] = {
  { -1, -1, -1,  -1 , -1 ,-1 , -1 , -1, -1 , -1, 55 , 56  , -1  , -1  , -1 },
  { -1, -1, -1,  -1 , -1 ,-1 , -1 , -1, 52 , -1, 54 , -1  , 58  , 60  , -1 },
  { -1, -1, -1,  -1 , -1 ,-1 , -1 , -1, 51 , 53, -1 , -1  , 57 , 59  , -1 },
  { -1, -1, -1,  -1 , -1 ,-1 , 43 , 50, 45 , 47, -1 , -1  , -1 , -1  , 61 },
  { -1, -1, -1,  -1 , -1 ,-1 , 42 , 44, -1 , 48, -1 , -1  , -1 , -1  , 62 },
  { -1, -1, -1,  -1 , 41 ,-1 , -1 , -1, 49 , 46, -1 , -1  , -1 , -1  , 63 },
  { -1, -1, -1, 40 ,  -1 ,39 , -1  , -1, -1 , -1 , 138, 137, -1 , -1  , 64 },
  { -1, -1, -1, 38 ,  -1 ,-1 , -1  , -1, -1 , -1 , 139, 136, -1 , -1  , 65 },
  { -1, -1, -1, 37 ,  -1 ,-1 , -1  , -1, -1 , -1 , 140, 135, -1 , -1  , 66 },
  { -1, -1, -1, 36 ,  -1 ,-1 , -1  , -1, -1 , -1 , 141, 134, -1 , -1  , 67 },
  { -1, -1, -1, 35 ,  -1 ,-1 , -1  , -1, -1 , -1 , 142, 133, -1 , -1  , 68 },
  { -1, -1, -1, 34 ,  -1 ,-1 , -1  , -1, -1 , -1 , 143, 132, -1 , -1  , 69 },
  { -1, -1, -1, 33 ,  -1 ,-1 , -1  , -1, -1 , -1 , 144, 131, -1 , -1  , 70 },
  { -1, -1, -1, 32 ,  -1 ,-1 , -1  , -1, -1 , -1 , 145, 130, -1 , -1  , 71 },
  { -1, -1, -1, 31 ,  -1 ,-1 , -1  , -1, -1 , -1 , 146, 129, -1 , -1  , 72 },
  { -1, -1, -1, 30 ,  -1 ,-1 , -1  , -1, -1 , -1 , 147, 128, -1 , -1  , 73 },
  { -1, -1, -1, 29 ,  -1 ,-1 , -1  , -1, -1 , -1 , 148, 127, -1 , -1  , 74 },
  { 25, 27, 28 , -1,  -1 ,-1 , -1  , -1, -1 , -1 , 149, 126, -1 , -1  , 75 },
  { 24, 26, -1 , -1,  -1 ,-1 , -1  , -1, -1 , -1 , 150, 125, -1 , -1  , 76 },
  { 23, -1, -1 , -1,  -1 ,-1 , -1  , -1, -1 , -1 , 123, 124, 81 , 80   , -1},
  { 22, -1, -1 , -1,  -1 ,118, 119 , 120, -1, -1 , -1 ,  83, 82 , 79  , 77 },
  { 21, -1 , -1, -1 , -1 ,117, -1 , -1, -1 , 122, -1 ,  84, -1 , -1  , 78 },
  { 20, -1 , -1, -1 , -1 ,116, -1 , -1, 121, -1, -1 ,  85, -1 , -1  , -1 },
  { 19, -1 , -1, -1 , -1 ,115, -1 , -1, -1 , -1 , -1 ,  86, -1 , -1  , -1 },
  { 18, -1 , -1, -1 , -1 ,114, -1 , -1, -1 , -1 , -1 ,  87, -1 , -1  , -1 },
  { 17, -1 , -1, -1 , -1 ,113, -1 , -1, -1 , -1 , -1 ,  88, -1 , -1  , -1 },
  { 16, -1 , -1, -1 , -1 ,112, -1 , -1, -1 , -1 , -1 ,  89, -1 , -1  , -1 },
  { 15, -1 , -1, -1 , -1 ,111, -1 , -1, -1 , 99 , -1 ,  90, -1 , -1  , -1 },
  { 14, -1 , -1, -1 , -1 ,110,  0 , -1, -1 , 98 , -1 ,  91, -1 , -1  , -1 },
  { 13, -1 , -1, -1 , -1 ,109, 107, -1, -1 , 97 , -1 ,  92, -1 , -1  , -1 },
  { 12, -1 , -1, -1 , -1 ,-1 , 108, -1, -1 , 96 , 95 ,  93, -1 , -1 , -1},
  { 11, -1 , -1, -1 , -1 ,-1 , -1 , -1, 100, 101, 102,  94, -1 ,106 , -1},
  { 10, -1 , -1, -1 , -1 ,-1 , 105, -1, 104, 103, -1 ,  -1,  -1,  -1, -1},
  { 9,  -1, -1, -1 ,  -1 ,-1 ,  1 , -1, -1 , -1 , -1 ,  -1, -1 , -1 , -1},
  { -1,  8 , -1, -1 , -1 , 3 ,  2 , -1, -1 , -1 , -1 ,  -1, -1 , -1 , -1},
  { -1,  7 , -1, -1 ,  4 ,-1 , -1 , -1, -1 , -1 , -1 ,  -1, -1 , -1 , -1},
  { -1, -1 ,  6,  5 , -1 ,-1 , -1 , -1, -1 , -1 , -1 ,  -1, -1 , -1 , -1}
};

// Mode Changer
#define NUMBEROFMODES 9
uint32_t mode = 0;

void setup() {
	Serial.begin(57600);
	Serial.println("### setup ###");


// ####
// LEDs
// ####
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
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
  
  ADCSRA |= (1 << ADPS2) | (1 << ADPS0); //set ADC clock with 32 prescaler- 16mHz/32=500kHz
  ADCSRA |= (1 << ADATE); //enabble auto trigger
  ADCSRA |= (1 << ADIE); //enable interrupts when measurement complete
  ADCSRA |= (1 << ADEN); //enable ADC
  ADCSRA |= (1 << ADSC); //start ADC measurements
  
  sei();//enable interrupts

}


// #######
// AudioIn
// #######

ISR(ADC_vect) {//when new ADC value ready
  incomingAudio = ADCH;//store 8 bit value from analog pin 0
  incomingAudio = incomingAudio*9;
  if (incomingAudio == 0 || incomingAudio == 255){//if clipping
    digitalWrite(13,HIGH);//set pin 13 high
    clipping = 1;//currently clipping
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
      Serial.println((String)"blinders regionColor: " + blinders[1][2] +' '+" ... red: " + redFromHexColor(blinders[1][2]) +' '+" ... green: " + greenFromHexColor(blinders[1][2])+' '+" ... blue: " + blueFromHexColor(blinders[1][2])+' '+" ...");
 */

if (SOUND2LIGHT) {
  lightHowManyRows(getNumLeds(incomingAudio, rowCount+3, -3), 220, 60, 0.2, 255, 255);
/* 
  lightHowMany(getNumLeds(incomingAudio, 150, -25), 240, 120, 0.1, 255, 255);
 */
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


static double getNumLeds(byte incomingAudio, int totalNumLeds, int offset) {
  if (clipping){//if currently clipping
    clipping = 0;//
    digitalWrite(13,LOW);//turn off clipping led indicator (pin 13)
  }

  double faktor = incomingAudio/255.0;
  int numLeds = (int)(totalNumLeds*faktor+offset)*1.2;
  if (DEBUG) Serial.println((String)"incoming: " + incomingAudio+' '+" ... faktor: " + faktor+' '+" ... numLeds: " + numLeds+' '+" ...");

  return numLeds;
}

static void lightEvery10() {
  eraseAll(); 
  for (int j=0; j<150; j++) {
    if (j%10==0) leds[j] = CHSV(20, 255, 255);
  }
  FastLED.show(); 
  delay(3000);
}

static void lightHowMany(int numLeds, int fade, double hue, double hueIncrement, int sat, int bri) {
    fadeAllDynamic(fade);
    for(int i=0; i<=numLeds; i++) {
      leds[i] = CHSV(hue+=hueIncrement, sat, bri);
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
      if (hueIncrement > 0) hue = incrementHue(hue, hueIncrement);
      leds[ledNum] = CHSV(hue, sat, bri);
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
        if (hueIncrement > 0) hue = incrementHue(hue, hueIncrement);
        leds[ledNum] = CHSV(hue, sat, bri);
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
        if (hueIncrement > 0) hue = incrementHue(hue, hueIncrement);
        leds[ledNum] = CHSV(hue, sat, bri);
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
        if (hueIncrement > 0) hue = incrementHue(hue, hueIncrement);
        leds[ledNum] = CHSV(hue, sat, bri);
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
        if (hueIncrement > 0) hue = incrementHue(hue, hueIncrement);
        leds[ledNum] = CHSV(hue, sat, bri);
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

static double incrementHue(double h, double hIncrementor) {
  h+=hIncrementor;
  if (h>=255) {
    h-=255;
  }
  return h;
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