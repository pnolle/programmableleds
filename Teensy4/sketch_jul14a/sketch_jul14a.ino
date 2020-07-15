#include <FastLED.h>

/*
 * Source: https://pastebin.com/YkjpDs7S
 * 
    First: 1,0,24,25,19,18,14,15,17,16,22,23,20,21,26,27
    Second: 10,12,11,13,6,9,32,8,7
    Third: 37, 36, 35, 34, 39, 38, 28, 31, 30

 */

#define NUM_LEDS_PER_STRIP 150
#define NUM_STRIPS 1
#define NUM_RUNS 1
#define LEDtotal (NUM_LEDS_PER_STRIP * NUM_STRIPS * NUM_RUNS)

CRGB leds[LEDtotal];

void setup() {
  FastLED.addLeds<NUM_STRIPS, WS2813, 19, GRB>(leds, NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NUM_STRIPS, WS2813, 17, GRB>(leds, NUM_LEDS_PER_STRIP);
  Serial.begin(9600);
  delay(500);
  Serial.print("Lights ");
  Serial.println(sizeof(leds));
}

void loop() {
  // put your main code here, to run repeatedly:
  FastLED.clear();
  for(int i = 0; i < LEDtotal; i++){
    leds[i] = CHSV(i*5, 255, 255);
    FastLED.show();
  }
  EVERY_N_MILLIS(500){
    Serial.println(LEDS.getFPS());
  }
}
