#include <Adafruit_NeoPixel.h>
#include <stdio.h>

// #######
// AudioIn
// #######

//variable to store incoming audio sample
byte incomingAudio;

//clipping indicator variables
boolean clipping = 0;

// ####
// LEDs
// ####

// General
#define PIN 6
#define N_LEDS 150 // 5 meter reel @ 30 LEDs/m

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);


void setup(){
    Serial.begin(9600);

// #######
// AudioIn
// #######
  
  pinMode(13,OUTPUT);//led indicator pin
  
  cli();//disable interrupts
  
  //set up continuous sampling of analog pin 0
  
  //clear ADCSRA and ADCSRB registers
  ADCSRA = 0;
  ADCSRB = 0;
  
  ADMUX |= (1 << REFS0); //set reference voltage
  ADMUX |= (1 << ADLAR); //left align the ADC value- so we can read highest 8 bits from ADCH register only
  
  ADCSRA |= (1 << ADPS2) | (1 << ADPS0); //set ADC clock with 32 prescaler- 16mHz/32=500kHz
  ADCSRA |= (1 << ADATE); //enabble auto trigger
  ADCSRA |= (1 << ADIE); //enable interrupts when measurement complete
  ADCSRA |= (1 << ADEN); //enable ADC
  ADCSRA |= (1 << ADSC); //start ADC measurements
  
  sei();//enable interrupts



// ####
// LEDs
// ####

  strip.begin();
}

ISR(ADC_vect) {//when new ADC value ready
  incomingAudio = ADCH;//store 8 bit value from analog pin 0
  incomingAudio = incomingAudio*9;
  if (incomingAudio == 0 || incomingAudio == 255){//if clipping
    digitalWrite(13,HIGH);//set pin 13 high
    clipping = 1;//currently clipping
  }
}

void loop(){
  if (clipping){//if currently clipping
    clipping = 0;//
    digitalWrite(13,LOW);//turn off clipping led indicator (pin 13)
  }

  double faktor = incomingAudio/255.0;
  int numLeds = (int)(150*faktor-25)*1.2;
  Serial.println((String)"incoming: " + incomingAudio+' '+" ... faktor: " + faktor+' '+" ... numLeds: " + numLeds+' '+" ...");
  lightHowMany(numLeds, randomColor(numLeds));
}

static uint32_t randomColor(int measurement) {
/*    int r = (int)measurement/16;
    int g = 16-(int)measurement/16;
    int b = (int)measurement/16;
    color << r;
     color << g;
    color << b; */
    uint32_t color = 0x0000FF;
    if (measurement <70) {
        color = 0x0000FF;
    }
    else if (measurement <100) {
        color = 0x00FF00;
    }
    else if (measurement <=150) {
        color = 0xFF0000;
    }

    return color;
}

static void lightHowMany(int numLeds, uint32_t color) {
    eraseAll();
    for(int i=0; i<=numLeds; i++) {
        strip.setPixelColor(i, color); 
    }
    strip.show();
}

static void eraseAll() {
    for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, 0);
    }
    strip.show(); 
}