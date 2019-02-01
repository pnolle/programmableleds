#ifndef PIXELUPDATE
#define PIXELUPDATE

struct PixelUpdate {
    int ledNum = -1;
    int col;
    int row;  
    double hue;
    int sat;
    int bri;
    int fade;
    long time;
};

#endif 