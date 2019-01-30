#ifndef FRAGMENTPROPERTIES
#define FRAGMENTPROPERTIES

struct FragmentProperties {
    // Animation Properties
    int wait = 10;
    int fade = 250;
    bool reverse = false;
    int length = -1;
    int start = -1;
    bool strobe = false;
    int strobeIncDec = 0;   // <0: strobe speed decreases, >0: strobe speed increases

    // Color Properties
    uint8_t hue = 0;
    uint8_t sat = 0;
    uint8_t bri = 255;
    double hueIncrement = 0;

    // Shape Properties

    uint8_t thickness = 1;  // number of lines with maximum brightness
    uint8_t fadeIn = 0;     // number of lines before maximum brightness is reached
};

#endif 