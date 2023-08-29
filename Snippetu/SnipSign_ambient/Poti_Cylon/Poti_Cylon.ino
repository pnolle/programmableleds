#include <FastLED.h>

// How many leds in your strip?
//#define NUM_LEDS 452  // 452 LEDs in Arrow
//#define NUM_LEDS 515  // 515 LEDs in Laser v2 + Scissors
//#define NUM_LEDS 507  // 507 LEDs in Circle
#define NUM_LEDS 479    // 479 in good ole SnipSign

#define LED_TYPE WS2812
#define DATA_PIN 12
#define COLOR_ORDER GRB

// Define the array of leds
CRGB leds[NUM_LEDS];

float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup() { 
	Serial.begin(115200);
	Serial.println("resetting");
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
	FastLED.setBrightness(255);
}

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); } }

bool forward = true;
int iLed = 0;

void updateLedFrame() {
	static uint8_t hue = 0;
	// First slide the led in one direction
	if (iLed < NUM_LEDS) {
		// Set the iLed'th led to red 
		leds[iLed] = CHSV(hue++, 255, 255);
		// Show the leds
		FastLED.show(); 
		// now that we've shown the leds, reset the i'th led to black
		// leds[iLed] = CRGB::Black;
		fadeall();
		// Wait a little bit before we loop around and do it again
		// delay(10);
		iLed++;
	}
	if (iLed == NUM_LEDS) {
		iLed = 0;
	}
}

void loop() { 
  // read the input on analog pin GPIO36:
  int analogValue = analogRead(34);
  // Rescale to potentiometer's voltage (from 0V to 3.3V):
  float voltage = floatMap(analogValue, 0, 4095, 0, 3.3);

  // print out the value you read:
  Serial.print("Analog: ");
  Serial.print(analogValue);
  Serial.print(", Voltage: ");
  Serial.println(voltage);
  Serial.print(", Delay: ");
  Serial.println(round(voltage) * (100/3.3));
  delay(round(voltage) * (100/3.3));

  updateLedFrame();
}
