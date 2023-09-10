#ifndef CONSTANTS
#define CONSTANTS

// Cylon mode
static const TProgmemRGBPalette16 Cylon FL_PROGMEM = {};

// Warm White
static const TProgmemRGBPalette16 WarmWhite_p FL_PROGMEM =
    {CRGB::Snow, CRGB::Snow, CRGB::Snow, CRGB::Snow,
    CRGB::White, CRGB::White, CRGB::White, CRGB::White,
    CRGB::White, CRGB::White, CRGB::White, CRGB::White,
    CRGB::Gray, CRGB::Gray, CRGB::Gray, CRGB::Gray};
    
// A mostly blue palette with white accents.
// "CRGB::Gray" is used as white to keep the brightness more uniform.
static const TProgmemRGBPalette16 BlueWhite_p FL_PROGMEM =
    {CRGB::Blue, CRGB::Blue, CRGB::Blue, CRGB::Blue,
    CRGB::Blue, CRGB::Blue, CRGB::Blue, CRGB::Blue,
    CRGB::Blue, CRGB::Blue, CRGB::Blue, CRGB::Blue,
    CRGB::Blue, CRGB::Gray, CRGB::Gray, CRGB::Gray};

// A palette of soft snowflakes with the occasional bright one
static const TProgmemRGBPalette16 Snow_p FL_PROGMEM =
    {0x304048, 0x304048, 0x304048, 0x304048,
    0x304048, 0x304048, 0x304048, 0x304048,
    0x304048, 0x304048, 0x304048, 0x304048,
    0x304048, 0x304048, 0x304048, 0xE0F0FF};

// A cold, icy pale blue palette
#define Ice_Blue1 0x0C1040
#define Ice_Blue2 0x182080
#define Ice_Blue3 0x5080C0
static const TProgmemRGBPalette16 Ice_p FL_PROGMEM =
    {
        Ice_Blue1, Ice_Blue1, Ice_Blue1, Ice_Blue1,
        Ice_Blue1, Ice_Blue1, Ice_Blue1, Ice_Blue1,
        Ice_Blue1, Ice_Blue1, Ice_Blue1, Ice_Blue1,
        Ice_Blue2, Ice_Blue2, Ice_Blue2, Ice_Blue3};

// Add or remove palette names from this list to control which color
// palettes are used, and in what order.
static const TProgmemRGBPalette16 *ActivePaletteList[] = {
    &Cylon,
    &BlueWhite_p,
    &WarmWhite_p,
    &Snow_p,
    &Ice_p};

#endif
