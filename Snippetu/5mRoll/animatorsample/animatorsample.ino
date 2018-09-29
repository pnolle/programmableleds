#include <Adafruit_NeoPixel.h>
#include <NeoPixelStripAnimator.h>

#define PIN 6

// Declare and configure the NeoPixel strand
Adafruit_NeoPixel strip = Adafruit_NeoPixel(20, PIN, NEO_GRB + NEO_KHZ800);
// Declare and configure the animator
NeoPixelStripAnimator neoPixelStripAnimator(&strip);

int state = 0;
void setup() {
    strip.begin();
    //Serial.begin(9600);
    neoPixelStripAnimator.setup();
}

void loop() {
    neoPixelStripAnimator.loop();
    // if (Serial.available() > 0) {
    //     Serial.read();
        state = (state + 1) % 2;
        if(state){
            neoPixelStripAnimator.startAnimation(new NightRiderAnimation(Adafruit_NeoPixel::Color(255,0,0), 70));
        }else{
            neoPixelStripAnimator.clear();
        }
    // }
}