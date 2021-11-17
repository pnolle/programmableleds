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

#include "FastLED.h"

#define NUM_STRIPS 2

#define DATA_PIN 19
//#define CLK_PIN   4
#define LED_TYPE WS2813
#define COLOR_ORDER RGB
#define NUM_LEDS 149
#define NUM_PATTERNS 80
//CRGB leds[NUM_LEDS];

#define BRIGHTNESS 96
#define FRAMES_PER_SECOND 120

// Following lines from: Testing FastLED's CRGBSet array function and using it with the fill_solid and fill_rainbow functions. by Chemdoc77
CRGB rawleds[NUM_LEDS];
CRGBSet leds(rawleds, NUM_LEDS);
CRGBSet leds1(leds(0, 7));
CRGBSet leds2(leds(8, 15));
CRGBSet leds3(leds(126, 148));

struct CRGB *ledarray[] = {leds1, leds2, leds3};

// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = {sinelon, rainbowWithGlitter, confetti, juggle, bpm, rainbow};

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0;                  // rotating "base color" used by many of the patterns

void setup()
{
  delay(3000); // 3 second delay for recovery

  // tell FastLED about the LED strip configuration
  //FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<NUM_STRIPS, WS2813, 19, GRB>(leds, NUM_LEDS);
  FastLED.addLeds<NUM_STRIPS, WS2813, 17, GRB>(leds, NUM_LEDS);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 1500);
  set_max_power_indicator_LED(13);
}

// void loop()
// {

//   fill_solid(ledarray[0], 8, CHSV(213, 255, 255)); //8 is number of elements in the array
//   FastLED.show();
//   delay(700);
//   fill_solid(ledarray[0], 8, CRGB::Black);
//   FastLED.show();

//   fill_solid(ledarray[1], 8, CRGB::Green);
//   FastLED.show();
//   delay(700);
//   fill_solid(ledarray[1], 8, CRGB::Black);
//   FastLED.show();

// }

void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  uhrzeiger();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();
  // insert a delay to keep the framerate modest
  FastLED.delay(1000 / FRAMES_PER_SECOND);

  // do some periodic updates
  EVERY_N_MILLISECONDS(20) { gHue++; }   // slowly cycle the "base color" through the rainbow
  EVERY_N_SECONDS(10) { nextPattern(); } // change patterns periodically
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void uhrzeiger()
{
  fill_solid(ledarray[2], 22, CHSV(213, 255, 255));
  FastLED.show();
  // delay(700);
  // fill_solid(ledarray[2], 22, CRGB::Black);
  // FastLED.show();

  // for (int i = 0; i < arrZeigerCount; i++)
  // {
  //   leds[arrZeigerMatrix[i]] = CRGB::GreenYellow; //CRGB( 0, 255, 0);
  //   //CRGBPalette16 palette = HeatColors_p;
  //   //leds[ arrZeigerMatrix[i] ] = ColorFromPalette(palette, 5, 1);
  // }
  // //fill_solid();
}

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE(gPatterns);
}

void rainbow()
{
  // FastLED's built-in rainbow generator
  fill_rainbow(leds, NUM_PATTERNS, gHue, 7);
}

void rainbowWithGlitter()
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void addGlitter(fract8 chanceOfGlitter)
{
  if (random8() < chanceOfGlitter)
  {
    leds[random16(NUM_PATTERNS)] += CRGB::White;
  }
}

void confetti()
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy(leds, NUM_PATTERNS, 10);
  int pos = random16(NUM_PATTERNS);
  leds[pos] += CHSV(gHue + random8(64), 200, 255);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy(leds, NUM_PATTERNS, 20);
  int pos = beatsin16(13, 0, NUM_PATTERNS - 1);
  leds[pos] += CHSV(gHue, 255, 192);
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8(BeatsPerMinute, 64, 255);
  for (int i = 0; i < NUM_PATTERNS; i++)
  { //9948
    leds[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
  }
}

void juggle()
{
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy(leds, NUM_PATTERNS, 20);
  byte dothue = 0;
  for (int i = 0; i < 8; i++)
  {
    leds[beatsin16(i + 7, 0, NUM_PATTERNS - 1)] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}
