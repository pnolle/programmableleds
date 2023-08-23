#include <FastLED.h>

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few 
// of the kinds of animation patterns you can quickly and easily 
// compose using FastLED.  
//
// This example also shows one easy way to define multiple 
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define NUM_STRIPS 2

#define DATA_PIN    19
//#define CLK_PIN   4
#define LED_TYPE    WS2813
#define COLOR_ORDER RGB
#define NUM_LEDS    150
#define NUM_PATTERN 80
CRGB leds[NUM_LEDS];

#define BRIGHTNESS         128
#define FRAMES_PER_SECOND  120


const int16_t zeigerCount = 25;
const int16_t zeigerMatrix[zeigerCount] = {149,148,147,146,145,144,143,142,141,140,139,138,137,136,135,134,133,132,131,130,129,128,127,126,125};

void setup() {
  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  //FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  
  FastLED.addLeds<NUM_STRIPS, LED_TYPE, 19, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.addLeds<NUM_STRIPS, LED_TYPE, 17, COLOR_ORDER>(leds, NUM_LEDS);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { myColors, myColorsWithGlitter, confetti, juggle, bpm }; //  rainbow, rainbowWithGlitter
//sinelon, 
uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
  
void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  uhrzeiger(CRGB(1,100,50));

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 100 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void uhrzeiger(CRGB color) {
  for (int i=0; i<zeigerCount; i++) {
    leds[ zeigerMatrix[i] ] = color;
  }
}

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void myColors() 
{
  // FastLED's built-in rainbow generator
  //fill_rainbow( leds, NUM_LEDS, gHue, 7);
  //fill_gradient_RGB (CRGB *leds, uint16_t numLeds, const CRGB &c1, const CRGB &c2)
  CRGB c1 = CRGB(0, 100, 0);
  CRGB c2 = CRGB(100, 0, 0);
  fill_gradient_RGB (leds, NUM_PATTERN, c1, c2);
}

void myColorsWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  myColors();
  addGlitter(80);
}

void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_PATTERN, gHue, 7);
}

void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_PATTERN) ] += CRGB::White;
  }
}

void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_PATTERN, 10);
  int pos = random16(NUM_PATTERN);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_PATTERN, 20);
  int pos = beatsin16( 13, 0, NUM_PATTERN-1 );
  leds[pos] += CHSV( gHue, 255, 192);
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_PATTERN; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_PATTERN, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, NUM_PATTERN-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}
