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
#include <NeoPixelStripAnimator.h>

// General
#define PIN    6
#define N_LEDS 150 // 5 meter reel @ 30 LEDs/m

// SnipSign
#define SNIPLEDS 150

// Glossary:
// 0: [array length (n)]
// 1-n: [startPx][lengthPx][color]
uint32_t blinders[][3] = {
  {2},
  {44, 8, 0xffffff},
  {96, 8, 0xffffff}
};
uint32_t snippet[][3] = {
  {2},
  {53, 30, 0xe71709},
  {124, 15, 0xf6a46a}
};
uint32_t upper[][3] = {
  {4},
  {29, 15, 0xacdfe5},
  {138, 12, 0x171f8a},
  {83, 15, 0x171f8a},
  {104, 18, 0xacdfe5}
};
uint32_t laser[][3] = {
  {1},
  {1, 28, 0xe71709}
};

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

// Mode Changer
#define MODEMAX 10
#define NUMBEROFMODES 9
uint32_t mode = 6;

void setup() {
  strip.begin();
}

void loop() {
  switch(mode) {
    case 0: 
      sparkle(0xff0000, 50, 20, 10);
      break;
    case 1:
      flashRegions(blinders, 20, 30);
      break;
    case 2:
      chase(0x00dddd, true, 0x000000);
      break;
    case 3:
      flashRegions(blinders, 20, 30);
      break;
    case 4:
      sparkle(0x00ff00, 100, 10, 30);
      break;
    case 5:
      flashRegions(blinders, 20, 30);
      break;
    case 6:
      flashRegions(snippet, 20, 80);
      break;
    case 7:
      flashRegions(upper, 20, 80);
      break;
    case 8:
      flashRegions(laser, 20, 80);
      break;
    default:
      chase(0x0000ff, false, 0x000000);
      break;


    //bothdir(0x0000FF); // Blue
    //chase(0x00FF00, false); // Green
  }
}



// #############
// F/X Functions
// #############

static void flashRegions(uint32_t regions[][3], uint16_t flashCount, uint16_t flashDelay) {
  for (uint16_t f=0; f<flashCount; f++) {
    for (uint16_t r=1; r<=regions[0][0]; r++) {
      for(uint16_t p=regions[r][0]; p<regions[r][0]+regions[r][1]; p++) {
        strip.setPixelColor(p, regions[r][2]);
      }
    }
    strip.show();
    delay(flashDelay);
      
    eraseAll();
    delay(flashDelay);
  }

  switchMode();  
}

static void sparkle(uint32_t c, uint16_t sparklength, uint16_t delaydraw, uint16_t delaydel) {
  uint32_t sub = 0x000000;

  // draw
  uint16_t startpixel = -1 * sparklength; // start at pixel number with negative sparklength so that sparke "enters" the strip
  uint16_t p = startpixel;
  for(uint16_t j=0; j<getAmountOfSnipPixels()+sparklength; j++) {
      // draw "frames" from front
      for (uint16_t d=0; d<=sparklength/2; d++) {
        setPixelColorWithinSnipleds(p, c);
        c-=sub;
        p=incrementPixel(p,2);
      }
      startpixel++;
      p = startpixel;
      
      strip.show();
      delay(delaydraw);
    
      eraseAll();
      delay(delaydel);
  }

  switchMode();
}

static void chase(uint32_t c, bool forward, int32_t sub) {
  int8_t inc = 1;
  uint16_t pixel = 0;
  if (!forward) {
    inc = -1;
    pixel = SNIPLEDS;
  }
  for(uint16_t i=0; i<getAmountOfSnipPixels(); i++) {
      strip.setPixelColor(pixel, c); // Draw new pixel
      c = subColor(c, sub);
      pixel = incrementPixel(pixel, inc);
      strip.show();
      delay(10);
  }
  
  delay(100);
  eraseAll();
  switchMode();
}



// ################
// Helper Functions
// ################

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

static void setPixelColorWithinSnipleds(uint32_t p, uint32_t c) {
  // blackout everything beyond SNIPLEDS
  if (p>=SNIPLEDS) {
    strip.setPixelColor(p, 0);
  }
  else {
    strip.setPixelColor(p, c);
  }
}


static void switchMode() {
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
  uint16_t result = p+inc;
  while ((result>=blinders[1][0] && result<blinders[1][0]+blinders[1][1]) ||
         (result>=blinders[2][0] && result<blinders[2][0]+blinders[2][1])
  ) {
    result+=inc;
  }
  return result;
}

static uint16_t getAmountOfSnipPixels() {
  return SNIPLEDS - 2*blinders[1][1];
}
