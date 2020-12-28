#include <FastLED.h>
#include "constMatrix.h"

FASTLED_USING_NAMESPACE

// Standard patterns taken from the FastLED "100-lines-of-code" demo reel

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    6
//#define CLK_PIN   4
#define LED_TYPE    NEOPIXEL
#define COLOR_ORDER GRB
#define NUM_LEDS    120
#define LEDS_IN_SIGN 93
CRGB leds[NUM_LEDS];

#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120
#define UPDATESEC           10
#define UPDATEBLINK        200
#define FADEBLINK           50

int arrowCount=0;

void setup() {
  Serial.begin(9600); // open the serial port at 9600 bps:
  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { buildup, snipColors1, snipColors1WithGlitter, blinkArrowsO2I, snipColors2, snipColors2WithGlitter, blinkLtR, confetti, sinelon, blinkArrowsLR, juggle, bpm };

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
  
void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();
  whiteout();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  EVERY_N_SECONDS( UPDATESEC ) { 
    nextPattern(); 
    Serial.print("Next pattern.\n");
  } // change patterns periodically
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}






// Sign regions

// white light > LEDS_IN_SIGN
void whiteout() {
  for (int i=LEDS_IN_SIGN; i<NUM_LEDS; i++) {
    leds[i] = CRGB::White;
  }
}

// blink arrows outer to inner
void blinkArrowsO2I() 
{
  EVERY_N_MILLISECONDS( UPDATEBLINK ) { 
    arrowCount++;
    if (arrowCount >= numArrows+1) {
      arrowCount = 0;
    }
  }
  switch (arrowCount) {
    case 0:
      arr1(CHSV( gHue, 255, 192));
      arr6(CHSV( gHue, 255, 192));
      break;
    case 1:
      arr2(CHSV( gHue, 255, 192));
      arr5(CHSV( gHue, 255, 192));
      break;
    case 2:
      arr3(CHSV( gHue, 255, 192));
      arr4(CHSV( gHue, 255, 192));
      break;
    case 3:
      store(CHSV( gHue, 255, 192));
      break;
  }
  fadeToBlackBy( leds, NUM_LEDS, FADEBLINK);
}

// blink arrows left right
void blinkArrowsLR() 
{
  EVERY_N_MILLISECONDS( UPDATEBLINK ) { 
    arrowCount++;
    if (arrowCount >= numArrows+1) {
      arrowCount = 0;
    }
  }
  switch (arrowCount) {
    case 0:
      arr1(CHSV( gHue, 255, 192));
      break;
    case 1:
      arr2(CHSV( gHue, 255, 192));
      break;
    case 2:
      arr3(CHSV( gHue, 255, 192));
      break;
    case 3:
      arr6(CHSV( gHue, 255, 192));
      break;
    case 4:
      arr5(CHSV( gHue, 255, 192));
      break;
    case 5:
      arr4(CHSV( gHue, 255, 192));
      break;
    case 6:
      store(CHSV( gHue, 255, 192));
      break;
  }
  fadeToBlackBy( leds, NUM_LEDS, FADEBLINK);
}

// blink LtR
void blinkLtR() 
{
  EVERY_N_MILLISECONDS( UPDATEBLINK ) { 
    arrowCount++;
    if (arrowCount > numArrows+6) {
      arrowCount = 0;
    }
  }
  switch (arrowCount) {
    case 0:
      arr1(CHSV( gHue, 255, 192));
      break;
    case 1:
      arr2(CHSV( gHue, 255, 192));
      break;
    case 2:
      arr3(CHSV( gHue, 255, 192));
      break;
    case 3:
      S(CHSV( gHue, 255, 192));
      break;
    case 4:
      T(CHSV( gHue, 255, 192));
      break;
    case 5:
      O(CHSV( gHue, 255, 192));
      break;
    case 6:
      R(CHSV( gHue, 255, 192));
      break;
    case 7:
      E(CHSV( gHue, 255, 192));
      break;
    case 9:
      arr4(CHSV( gHue, 255, 192));
      break;
    case 10:
      arr5(CHSV( gHue, 255, 192));
      break;
    case 11:
      arr6(CHSV( gHue, 255, 192));
      break;
    case 12:
      store(CHSV( gHue, 255, 192));
      break;
  }
  fadeToBlackBy( leds, NUM_LEDS, FADEBLINK);
}


// buildup
void buildup() 
{
  EVERY_N_MILLISECONDS( UPDATEBLINK ) { 
    arrowCount++;
    if (arrowCount > 23) {
      arrowCount = 0;
    }
  }
  switch (arrowCount) {
    case 0:
      arr1(CHSV( gHue, 255, 192));
      break;
    case 1:
      arr2(CHSV( gHue, 255, 192));
      break;
    case 2:
      arr3(CHSV( gHue, 255, 192));
      break;
    case 3:
      S(CHSV( gHue, 255, 192));
      break;

    case 4:
      arr6(CHSV( gHue, 255, 192));
      S(CHSV( gHue, 255, 192));
      break;
    case 5:
      arr5(CHSV( gHue, 255, 192));
      S(CHSV( gHue, 255, 192));
      break;
    case 6:
      arr4(CHSV( gHue, 255, 192));
      S(CHSV( gHue, 255, 192));
      break;
    case 7:
      S(CHSV( gHue, 255, 192));
      E(CHSV( gHue, 255, 192));
      break;

    case 8:
      arr1(CHSV( gHue, 255, 192));
      S(CHSV( gHue, 255, 192));
      E(CHSV( gHue, 255, 192));
      break;
    case 9:
      arr2(CHSV( gHue, 255, 192));
      S(CHSV( gHue, 255, 192));
      E(CHSV( gHue, 255, 192));
      break;
    case 10:
      arr3(CHSV( gHue, 255, 192));
      S(CHSV( gHue, 255, 192));
      E(CHSV( gHue, 255, 192));
      break;
    case 11:
      S(CHSV( gHue, 255, 192));
      T(CHSV( gHue, 255, 192));
      E(CHSV( gHue, 255, 192));
      break;

    case 12:
      arr6(CHSV( gHue, 255, 192));
      S(CHSV( gHue, 255, 192));
      T(CHSV( gHue, 255, 192));
      E(CHSV( gHue, 255, 192));
      break;
    case 13:
      arr5(CHSV( gHue, 255, 192));
      S(CHSV( gHue, 255, 192));
      T(CHSV( gHue, 255, 192));
      E(CHSV( gHue, 255, 192));
      break;
    case 14:
      arr4(CHSV( gHue, 255, 192));
      S(CHSV( gHue, 255, 192));
      T(CHSV( gHue, 255, 192));
      E(CHSV( gHue, 255, 192));
      break;
    case 15:
      S(CHSV( gHue, 255, 192));
      T(CHSV( gHue, 255, 192));
      R(CHSV( gHue, 255, 192));
      E(CHSV( gHue, 255, 192));
      break;

    case 16:
      O(CHSV( gHue, 255, 192));
      break;
    case 17:
      S(CHSV( gHue, 255, 192));
      T(CHSV( gHue, 255, 192));
      O(CHSV( gHue, 255, 192));
      R(CHSV( gHue, 255, 192));
      E(CHSV( gHue, 255, 192));

    case 18:
      O(CHSV( gHue, 255, 192));
      break;
    case 19:
      S(CHSV( gHue, 255, 192));
      T(CHSV( gHue, 255, 192));
      O(CHSV( gHue, 255, 192));
      R(CHSV( gHue, 255, 192));
      E(CHSV( gHue, 255, 192));

    case 20:
      O(CHSV( gHue, 255, 192));
      break;
    case 21:
      S(CHSV( gHue, 255, 192));
      T(CHSV( gHue, 255, 192));
      O(CHSV( gHue, 255, 192));
      R(CHSV( gHue, 255, 192));
      E(CHSV( gHue, 255, 192));

    case 22:
      O(CHSV( gHue, 255, 192));
      break;
    case 23:
      S(CHSV( gHue, 255, 192));
      T(CHSV( gHue, 255, 192));
      O(CHSV( gHue, 255, 192));
      R(CHSV( gHue, 255, 192));
      E(CHSV( gHue, 255, 192));
      break;
  }
  fadeToBlackBy( leds, NUM_LEDS, FADEBLINK);
}


void arr1(CHSV color) {
  for (int i=0; i<arr1Count; i++) {
    leds[ arr1Matrix[i] ] += color;
  }
}
void arr2(CHSV color) {
  for (int i=0; i<arr2Count; i++) {
    leds[ arr2Matrix[i] ] += color;
  }
}
void arr3(CHSV color) {
  for (int i=0; i<arr3Count; i++) {
    leds[ arr3Matrix[i] ] += color;
  }
}
void arr4(CHSV color) {
  for (int i=0; i<arr4Count; i++) {
    leds[ arr4Matrix[i] ] += color;
  }
}
void arr5(CHSV color) {
  for (int i=0; i<arr5Count; i++) {
    leds[ arr5Matrix[i] ] += color;
  }
}
void arr6(CRGB color) {
  for (int i=0; i<arr6Count; i++) {
    leds[ arr6Matrix[i] ] += color;
  }
}
void S(CRGB color) {
  for (int i=0; i<SCount; i++) {
    leds[ SMatrix[i] ] += color;
  }
}
void T(CRGB color) {
  for (int i=0; i<TCount; i++) {
    leds[ TMatrix[i] ] += color;
  }
}
void O(CRGB color) {
  for (int i=0; i<OCount; i++) {
    leds[ OMatrix[i] ] += color;
  }
}
void R(CRGB color) {
  for (int i=0; i<RCount; i++) {
    leds[ RMatrix[i] ] += color;
  }
}
void E(CRGB color) {
  for (int i=0; i<ECount; i++) {
    leds[ EMatrix[i] ] += color;
  }
}
void store(CRGB color) {
  for (int i=0; i<SCount; i++) {
    leds[ SMatrix[i] ] += color;
  }
  for (int i=0; i<TCount; i++) {
    leds[ TMatrix[i] ] += color;
  }
  for (int i=0; i<OCount; i++) {
    leds[ OMatrix[i] ] += color;
  }
  for (int i=0; i<RCount; i++) {
    leds[ RMatrix[i] ] += color;
  }
  for (int i=0; i<ECount; i++) {
    leds[ EMatrix[i] ] += color;
  }
}





// Fill colors

void snipColors1() 
{
  // FastLED's built-in rainbow generator
  //fill_rainbow( leds, NUM_LEDS, gHue, 7);
  //fill_gradient_RGB (CRGB *leds, uint16_t numLeds, const CRGB &c1, const CRGB &c2)

  CRGB c1 = CRGB::DarkRed;
  CRGB c2 = CRGB::Yellow;
  fill_gradient_RGB (leds, NUM_LEDS, c1, c2);
}

void snipColors1WithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  snipColors1();
  addGlitter(80);
}


void snipColors2() 
{
  // FastLED's built-in rainbow generator
  //fill_rainbow( leds, NUM_LEDS, gHue, 7);
  //fill_gradient_RGB (CRGB *leds, uint16_t numLeds, const CRGB &c1, const CRGB &c2)

  CRGB c1 = CRGB::DarkBlue;
  CRGB c2 = CRGB::Cyan;
  fill_gradient_RGB (leds, NUM_LEDS, c1, c2);
}

void snipColors2WithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  snipColors2();
  addGlitter(80);
}





// F/X

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  Serial.println(random16(NUM_LEDS)); 
  }
}

void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( gHue, 255, 192);
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}
