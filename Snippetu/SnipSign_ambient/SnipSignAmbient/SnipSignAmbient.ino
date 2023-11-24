#include "FastLED.h"
#include "twinkleFox.h"
#include "constants.h"
#include "constMatrix.h"
#include "fragmentRowMovingDown.h"
#include "fragmentProperties.h"

// LedUtils ledUtils;
TwinkleFox twinkleFox;

#define NUM_LEDS 479
#define LED_TYPE WS2812
#define COLOR_ORDER GRB
#define DATA_PIN 12
// #define CLK_PIN       4
#define VOLTS 12
#define MAX_MA 4000

// System variables
LedUtils ledUtils;
CRGBArray<NUM_LEDS> leds;
RowMovingDown rmd1(ledUtils, millis());

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

// Input pins
#define SPEED_POTI_PIN 34
#define PRGCHG_BTN_PIN 32
#define DEBOUNCE_TIME 50 // the debounce time in millisecond, increase this time if it still chatters

// Variables will change:
int lastSteadyState = LOW;      // the previous steady state from the input pin
int lastFlickerableState = LOW; // the previous flickerable state from the input pin
int currentState;               // the current reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0; // the last time the output pin was toggled




void startRmd1(FragmentProperties fP)
{
  rmd1.setColorProperties(fP.hue, fP.sat, fP.bri, fP.hueIncrement);
  rmd1.setAnimationProperties(fP.wait, fP.fade, fP.reverse, fP.length, fP.start);
}



// read button
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
    // button state has changed
    if (lastSteadyState == LOW && currentState == HIGH) {
      // change to new target palette
      twinkleFox.chooseNextColorPalette(twinkleFox.gTargetPalette);
    }

    // save the the last steady state
    lastSteadyState = currentState;
  }
}

// normalize poti value
float floatMap(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}



// Cylon settings
bool forward = true;
int cylonLed = 0;


// Cylon code

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); } }

void cylonUpdateLedFrame() {
	static uint8_t hue = 0;
	// First slide the led in one direction
	if (cylonLed < NUM_LEDS) {
		// Set the cylonLed'th led to red 
		leds[cylonLed] = CHSV(hue++, 255, 255);
		FastLED.show(); 
		fadeall();
		cylonLed++;
	}
	if (cylonLed == NUM_LEDS) {
		cylonLed = 0;
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



// Main program
void setup()
{
  delay(3000); // safety startup delay
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_MA);
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS)
      .setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(255);

  Serial.begin(115200);
  Serial.println("Start");

  // configure btn pin
  pinMode(PRGCHG_BTN_PIN, INPUT_PULLUP);
  
  startRmd1(getFragmentProperties(1, 100));
}

void loop()
{
  vector<PixelUpdate> matrixUpdate; 

  // reading input: speed poti
  int spdPotiVal = analogRead(SPEED_POTI_PIN);
  twinkleFox.twinkleSpeed = round(floatMap(spdPotiVal, 0, 4095, 0, 8)); // Rescale to possible speed values (0-8)

  // reading input: program change btn
  readPrgChgBtn();

  // TODO: gTargetPalette needed in twinkleFox, but misused as general mode setting => fix this
  if (twinkleFox.gTargetPalette == Cylon) {
    cylonUpdateLedFrame();
  }
  else if (twinkleFox.gTargetPalette == RowsMovingDown) {
    Serial.print("r");
    rmd1.nextFrame(millis(), matrixUpdate);
  }
  else {
    nblendPaletteTowardPalette(twinkleFox.gCurrentPalette, twinkleFox.gTargetPalette, 60);
    twinkleFox.drawTwinkles(leds);
  }
  FastLED.show();
}
