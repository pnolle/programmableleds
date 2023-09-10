#ifndef TWINKLEFOX
#define TWINKLEFOX

#include "FastLED.h"


// TwinkleFOX Settings: Twinkling 'holiday' lights that fade in and out.

// Overall twinkle density.
// 0 (NONE lit) to 8 (ALL lit at once).
// Default is 5.
#define TWINKLE_DENSITY 5

// How often to change color palettes.
#define SECONDS_PER_PALETTE 30
// Also: toward the bottom of the file is an array
// called "ActivePaletteList" which controls which color
// palettes are used; you can add or remove color palettes
// from there freely.

// Background color for 'unlit' pixels
// Can be set to CRGB::Black if desired.
static CRGB gBackgroundColor = CRGB::Black;
// Example of dim incandescent fairy light background color
// CRGB gBackgroundColor = CRGB(CRGB::FairyLight).nscale8_video(16);

// If AUTO_SELECT_BACKGROUND_COLOR is set to 1,
// then for any palette where the first two entries
// are the same, a dimmed version of that color will
// automatically be used as the background color.
#define AUTO_SELECT_BACKGROUND_COLOR 0

// If COOL_LIKE_INCANDESCENT is set to 1, colors will
// fade out slighted 'reddened', similar to how
// incandescent bulbs change color as they get dim down.
#define COOL_LIKE_INCANDESCENT 1


class TwinkleFox
{
    public:
    // Overall twinkle speed.
    // 0 (VERY slow) to 8 (VERY fast).
    // 4, 5, and 6 are recommended, default is 4.
    int twinkleSpeed = 4;
    CRGBPalette16 gCurrentPalette;
    CRGBPalette16 gTargetPalette;

    void drawTwinkles(CRGBSet &L);
    CRGB computeOneTwinkle(uint32_t ms, uint8_t salt);
    uint8_t attackDecayWave8(uint8_t i);
    void coolLikeIncandescent(CRGB &c, uint8_t phase);
    void chooseNextColorPalette(CRGBPalette16 &pal);
};


#endif
