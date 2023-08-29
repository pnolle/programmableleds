#include <FastLED.h>

#define NUM_LEDS 479
#define CHIPSET WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
#define LED_PIN 12
// #define CLK_PIN       4
#define VOLTS 12
#define MAX_MA 4000

int BRIGHTNESS = 255;
int lastBrightness = 255;


// FastLED v2.1 provides two color-management controls:
//   (1) color correction settings for each LED strip, and
//   (2) master control of the overall output 'color temperature' 
//
// THIS EXAMPLE demonstrates the second, "color temperature" control.
// It shows a simple rainbow animation first with one temperature profile,
// and a few seconds later, with a different temperature profile.
//
// The first pixel of the strip will show the color temperature.
//
// HELPFUL HINTS for "seeing" the effect in this demo:
// * Don't look directly at the LED pixels.  Shine the LEDs aganst
//   a white wall, table, or piece of paper, and look at the reflected light.
//
// * If you watch it for a bit, and then walk away, and then come back 
//   to it, you'll probably be able to "see" whether it's currently using
//   the 'redder' or the 'bluer' temperature profile, even not counting
//   the lowest 'indicator' pixel.
//
//
// FastLED provides these pre-conigured incandescent color profiles:
//     "Candle", "Tungsten40W", "Tungsten100W", "Halogen", "CarbonArc", "HighNoonSun", "DirectSunlight", "OvercastSky", "ClearBlueSky",
// FastLED provides these pre-configured gaseous-light color profiles:
//     "WarmFluorescent", "StandardFluorescent", "CoolWhiteFluorescent", "FullSpectrumFluorescent", "GrowLightFluorescent", "BlackLightFluorescent", "MercuryVapor", "SodiumVapor", "MetalHalide", "HighPressureSodium",
// FastLED also provides an "Uncorrected temperature" profile
//    UncorrectedTemperature;

// const CRGB TEMPERATURES[19] = { Candle, Tungsten40W, Tungsten100W, Halogen, CarbonArc, HighNoonSun, DirectSunlight, OvercastSky, ClearBlueSky, WarmFluorescent, StandardFluorescent, CoolWhiteFluorescent, FullSpectrumFluorescent, GrowLightFluorescent, BlackLightFluorescent, MercuryVapor, SodiumVapor, MetalHalide, HighPressureSodium };

int tempInterator = 0;

void chooseNextColorTemp() {
  // draw a solid warm white
  fill_solid( leds + 5, NUM_LEDS - 5, CRGB(255,250,240));
  
  if (tempInterator > 1)  tempInterator = 0;
  switch (tempInterator) {
    case 0:
      FastLED.setTemperature( Candle );
    case 1:
      FastLED.setTemperature( DirectSunlight );
  }
  Serial.println(tempInterator);
  tempInterator++;
  FastLED.show();
}


// Input pins
#define BRIGHT_POTI_PIN 34
#define PRGCHG_BTN_PIN 32
#define DEBOUNCE_TIME 50 // the debounce time in millisecond, increase this time if it still chatters

// Variables will change:
int lastSteadyState = LOW;      // the previous steady state from the input pin
int lastFlickerableState = LOW; // the previous flickerable state from the input pin
int currentState;               // the current reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0; // the last time the output pin was toggled


void readPrgChgBtn()
{
  // read the state of the switch/button:
  currentState = digitalRead(PRGCHG_BTN_PIN);
  
  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch/button changed, due to noise or pressing:
  if (currentState != lastFlickerableState)
  {
    // reset the debouncing timer
    lastDebounceTime = millis();
    // save the the last flickerable state
    lastFlickerableState = currentState;
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_TIME)
  {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
     if (lastSteadyState == HIGH && currentState == LOW)
       Serial.println("The button is pressed");
    if (lastSteadyState == LOW && currentState == HIGH) {
      chooseNextColorTemp();
      Serial.println("The button is released");
    }

    // save the the last steady state
    lastSteadyState = currentState;
  }
}

float floatMap(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void loop()
{
  // reading input: brightness poti
  int brightPotiVal = analogRead(BRIGHT_POTI_PIN);
  BRIGHTNESS = round(floatMap(brightPotiVal, 0, 4095, 0, 255)); // Rescale to possible brightness values
  FastLED.setBrightness( BRIGHTNESS );
//  if ( BRIGHTNESS != lastBrightness) {
//    Serial.println(BRIGHTNESS);
//  }
  
  // reading input: program change btn
  readPrgChgBtn();
}

void setup() {
  delay( 3000 ); // power-up safety delay
  // It's important to set the color correction for your LED strip here,
  // so that colors can be more accurately rendered through the 'temperature' profiles
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalSMD5050 );
  FastLED.setBrightness( BRIGHTNESS );
  
  // configure btn pin
  pinMode(PRGCHG_BTN_PIN, INPUT_PULLUP);
  
  chooseNextColorTemp();
  
  Serial.begin(115200);
  Serial.println("Start");
}
