#include <FastLED.h>

#define NUM_LEDS 479
#define CHIPSET WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
#define LED_PIN 12

int BRIGHTNESS = 255;

// Input pins
#define BRIGHT_POTI_PIN 34


float floatMap(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void loop()
{
  // reading input: brightness poti
  int brightPotiVal = analogRead(BRIGHT_POTI_PIN);
  BRIGHTNESS = round(floatMap(brightPotiVal, 0, 4095, 0, 255)); // Rescale to possible brightness values
  Serial.println(BRIGHTNESS);
  FastLED.setBrightness( BRIGHTNESS );
  FastLED.show();
}

void setup() {
  delay( 3000 ); // power-up safety delay
  // It's important to set the color correction for your LED strip here,
  // so that colors can be more accurately rendered through the 'temperature' profiles
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalSMD5050 );
  FastLED.setBrightness( BRIGHTNESS );
  
  fill_solid( leds, NUM_LEDS, CRGB(100,200,250));
  FastLED.show();
  
  Serial.begin(115200);
  Serial.println("Start");
}
