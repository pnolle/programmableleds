/* New Product Test Sketch by Chemdoc77
   used to test new RGB LED strips and Matrix that I purchase.

   Note:  Uses FastLED's Parallel Output procedure to work with a Teensy 4.0

*/

#include <FastLED.h>

#define DATA_PIN  7 // it is critical that you use this pin number or other pin numbers using FastLED's Parallel Output procedure
int brightness = 70;

// Teensy 4.0 Stuff ================
#define NUM_LEDS_PER_STRIP 30
#define NUM_STRIPS 1
#define NUM_LEDS   NUM_LEDS_PER_STRIP  
CRGB leds[NUM_LEDS_PER_STRIP * NUM_STRIPS];

void setup() { 
  delay(1000);
  // Teensy 4.0 Stuff ==============
    FastLED.addLeds<NUM_STRIPS, WS2812B,DATA_PIN,GRB>(leds, NUM_LEDS_PER_STRIP);
  //USE for WS2811:      
 // FastLED.addLeds<NUM_STRIPS, WS2811, DATA_PIN >(leds, NUM_LEDS_PER_STRIP);

 Serial.begin(57600);
  Serial.println("resetting");
  Serial.println(NUM_LEDS);
 
  FastLED.setBrightness(brightness);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 1500);
   set_max_power_indicator_LED(13);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
 
}
void loop() {  

//  Serial.println("start red");
//     fill_solid( leds, NUM_LEDS, CRGB::Red);
//     FastLED.delay(500);
//      
//  Serial.println("start black");
//     fill_solid( leds, NUM_LEDS, CRGB::Black);
//     FastLED.delay(500);
//    
//  Serial.println("start blue");
//     fill_solid( leds, NUM_LEDS, CRGB::Blue);
//     FastLED.delay(500);
//      
//     fill_solid( leds, NUM_LEDS, CRGB::Black);
//     FastLED.delay(500);
//     
//     fill_solid( leds, NUM_LEDS, CRGB::Green);
//     FastLED.delay(500);
//      
//     fill_solid( leds, NUM_LEDS, CRGB::Black);
//     FastLED.delay(500);
       
     Serial.println("start YYY");
     fill_solid( leds, NUM_LEDS, CRGB::Yellow);
     FastLED.delay(500);
      
     Serial.println("start black");
     fill_solid( leds, NUM_LEDS, CRGB::Black);
     FastLED.delay(500);

     Serial.println("start WIPE");
     cd77_colorwipe_dot(CRGB::Red, 0, NUM_LEDS, 40);
     cd77_colorwipe_dot(CRGB::Blue, 0, NUM_LEDS, 40);
     cd77_colorwipe_dot(CRGB::Green, 0, NUM_LEDS, 40);
   
}

//==================== Functions ===============================


void cd77_colorwipe(CRGB color,  uint16_t to, uint16_t wait) {
  for (uint16_t i = 0; i <to; i++) {
    leds[i] = color;
    FastLED.delay(500);
  }
}


void cd77_colorwipe_line2(CRGB color, uint16_t wait) {
  for (uint16_t i = 0; i <NUM_LEDS; i++) {
    leds[i] = color;
    FastLED.show();
   }
}

void cd77_colorwipe_line(CRGB color, uint16_t wait) {
  for (uint16_t i = 0; i <NUM_LEDS; i++) {
    leds[i] = color;
    FastLED.delay(wait);
   }
}


void cd77_colorwipe_dot(CRGB color,uint16_t from,  uint16_t to,  uint16_t wait) {
  for (uint16_t i = from; i <to; i++) {
    leds[i] = color;
    FastLED.delay(wait);
    leds[i] = CRGB::Black;
    FastLED.show();
    
    
  }
}

void cd77_colorwipe_dot_fast(CRGB color) {
  for (uint16_t i = 0; i <NUM_LEDS; i++) {
    leds[i] = color;
     FastLED.show();
    leds[i] = CRGB::Black;
    FastLED.show();
    
    
  }
}  
