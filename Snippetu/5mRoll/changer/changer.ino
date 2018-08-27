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

// General
#define PIN    6
#define N_LEDS 150 // 5 meter reel @ 30 LEDs/m

// SnipSign
#define SNIPLEDS 108
#define BLINDERONESTART 40
#define BLINDERTWOSTART 91
#define BLINDERLENGTH 8

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

// Mode Changer
#define MODEMAX 10
#define NUMBEROFMODES 5
uint32_t mode = 1;

void setup() {
  strip.begin();
}

void loop() {
  switch(mode) { 
    case 0: 
      sparkle(0xff0000, 50, 20, 10);
    case 1:
      flashBlinders(0xff0000, 20, 30);
    case 2:
      chase(0x00FF00, true, 0x00000D);
    case 3:
      flashBlinders(0xffffff, 20, 30);
    case 4:
      sparkle(0x00ff00, 100, 10, 30);
    case 5:
      flashBlinders(0xffffff, 20, 30);
    default:
      chase(0x0000ff, false, 0x000000);
    //bothdir(0x0000FF); // Blue
    //chase(0x00FF00, false); // Green
  }
}

static void increaseMode() {
  if (mode<=NUMBEROFMODES) {
    mode++;
  }
  else {
    mode = 0;
  }
}

static void eraseAll() {
    for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, 0);
    }
    strip.show(); 
}

static uint16_t incrementPixel(uint16_t p, uint16_t inc) {
  return p+inc;
}

static void flashBlinders(uint32_t c, uint16_t flashCount, uint16_t flashDelay) {
  for (uint16_t f=0; f<flashCount; f++) {
    // Blinder 1
    for(uint16_t p=BLINDERONESTART; p<BLINDERONESTART+BLINDERLENGTH; p++) {
      strip.setPixelColor(p, c);
    }
    // Blinder 2
    for(uint16_t p=BLINDERTWOSTART; p<BLINDERTWOSTART+BLINDERLENGTH; p++) {
      strip.setPixelColor(p, c);
    }
    strip.show();
    delay(flashDelay);
      
    eraseAll();
    delay(flashDelay);
  }

  increaseMode();  
}

static void sparkle(uint32_t c, uint16_t sparklength, uint16_t delaydraw, uint16_t delaydel) {
  uint32_t sub = 0x000000;

  // draw
  uint16_t p = -1 * sparklength; // start at pixel number with negative sparklength so that sparke "enters" the strip
  uint16_t startpixel = 0;
  for(uint16_t j=0; j<SNIPLEDS+sparklength; j++) {
      // draw "frames" from front
      for (uint16_t d=0; d<=sparklength/2; d++) {
        if (p>=SNIPLEDS) {
          strip.setPixelColor(p, 0);
        }
        else {
          strip.setPixelColor(p, c);
        }
        c-=sub;
        p=incrementPixel(p,2);
      }
      p = incrementPixel(p, -1*sparklength+1);
      startpixel++;
      
      strip.show();
      delay(delaydraw);
    
      eraseAll();
      delay(delaydel);
  }

  increaseMode();
}

static void chase(uint32_t c, bool forward, int32_t sub) {
  uint8_t n = 0;
  int8_t inc = 1;
  uint16_t p = 0;
  if (!forward) {
    inc = -1;
    p = SNIPLEDS+n;
  }
  for(uint16_t i=0; i<SNIPLEDS+n; i++) {
      strip.setPixelColor(p, c); // Draw new pixel
      c = subColor(c, sub);
      p = incrementPixel(p, inc);
      strip.show();
      delay(10);
  }
  
  eraseAll();
  increaseMode();
}

static int32_t subColor(uint32_t c, int32_t sub) {
  int32_t result = c-sub;
  if (result>0x000000) {
    return result;
  }
  else if (result<=0x000000) {
    return 0xffffff;
  }
  else {
    return 0x000000;
  }
}

