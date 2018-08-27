// Simple NeoPixel test.  Lights just a few pixels at a time so a
// long strip can safely be powered from Arduino 5V pin.  Arduino
// may nonetheless hiccup when LEDs are first connected and not
// accept code.  So upload code first, unplug USB, connect pixels
// to GND FIRST, then +5V and digital pin 6, then re-plug USB.
// A working strip will show a few pixels moving down the line,
// cycling between red, green and blue.  If you get no response,
// might be connected to wrong end of strip -- look for the data
// direction arrows printed on the strip.

#include <Adafruit_NeoPixel.h>

#define PIN    6
#define N_LEDS 150 // 5 meter reel @ 30 LEDs/m

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
}

void loop() {
  sparkle(0xff0000); // Red
  //chase(0x00FF00, true); // Green
  //bothdir(0x0000FF); // Blue
  //chase(0x00FF00, false); // Green
}

static void sparkle(uint32_t c) {
  uint8_t n = 30;
  uint32_t sub = 0x000000;

  // draw
  uint16_t iopp = strip.numPixels()+16;
  uint16_t p = -18;
  uint16_t popp = iopp;
  for(uint16_t i=0; i<strip.numPixels()+18; i++) {

      //from front
      strip.setPixelColor(p  , c); // Draw new pixel
      c-=sub;
      p+=2;
      strip.setPixelColor(p  , c); // Draw new pixel
      c-=sub;
      p+=2;
      strip.setPixelColor(p  , c); // Draw new pixel
      c-=sub;
      p+=2;
      strip.setPixelColor(p  , c); // Draw new pixel
      c-=sub;
      p+=2;
      strip.setPixelColor(p  , c); // Draw new pixel
      c-=sub;
      p+=2;
      strip.setPixelColor(p  , c); // Draw new pixel
      c-=sub;
      p+=2;
      strip.setPixelColor(p  , c); // Draw new pixel
      c-=sub;
      p+=2;
      strip.setPixelColor(p  , c); // Draw new pixel
      c-=sub;
      p+=2;
      strip.setPixelColor(p  , c); // Draw new pixel
      c-=sub;
      p+=2;
      strip.setPixelColor(p  , c); // Draw new pixel
      c-=sub;
      p-=17;
      
      strip.show();
      delay(10);
    
      // erase all
      for(uint16_t i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i  , 0);
      }
      strip.show();
      delay(30);
  }
}

static void chase(uint32_t c, bool forward) {
  uint8_t n = 30;
  uint32_t sub = 0x001000;
  int8_t increment = 1;
  uint16_t p = 0;
  if (!forward) {
    increment = -1;
    p = strip.numPixels();
  }
  for(uint16_t i=0; i<strip.numPixels()+n; i++) {
      strip.setPixelColor(p  , c); // Draw new pixel
      c-=sub;
      p+=increment;
      strip.show();
      delay(10);
  }
  
  // erase all
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i  , 0);
    strip.show();
  }
}
