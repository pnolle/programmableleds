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
#define N_LEDS 60 // 5 meter reel @ 30 LEDs/m

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
}

void loop() {
  chase(0xFF0000); // Red
  chase(0x00FF00); // Green
  chase(0x0000FF); // Blue
}

static void chase(uint32_t c) {
  uint8_t n = 30;
  for(uint16_t i=0; i<strip.numPixels()+n; i++) {
      uint16_t p = i;
      uint32_t sub = 0x001000;
      for (uint8_t l=0; l<n/2; l++) {
        strip.setPixelColor(p  , c); // Draw new pixel
        c-=sub;
        p--;
        strip.setPixelColor(p, 0); // Erase pixel
        p--;
      }
      strip.show();
      delay(30);
  }
}
