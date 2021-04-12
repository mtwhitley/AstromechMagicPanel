#include "FastLED.h"

// =======================================================================================
//  Astromech Magic Panel (AMP)
// =======================================================================================
//                                 
// This code animates the Magic Panel for Astromech droids. When combined with a semi-
// transparent panel and LEDs it produces a striking effect. This code is based on 
// FastLED's TwinkleFox example http://fastled.io
//
// Homepage: https://github.com/mtwhitley/AstromechMagicPanel
// 
// Authors: Michael Whitley (astromech.net - umlungu), Mark Kriegsman (FastLED)
//
// Required Library: 
//   FastLED
//
// Setup: Use with 2 x APA102 20/20 8x8 matrix panels from Adafruit or Sparkfun. 
// I recommend using an Adafruit QT Py to drive the LEDs, but any 
// microcontroller 16MHz or faster will likely work. If using a different board
// be sure to adjust the Data and Clock pins accordingly.
//
// This program is free software: made available under the MIT license.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY.
// =======================================================================================

#define DATA_PIN 1          // Adafruit QT Py
#define CLK_PIN  0          // Adafruit QT Py
#define LED_TYPE    APA102  // APA102 20/20 8x8 matrix panels 
#define COLOR_ORDER BGR     // APA102 20/20 8x8 matrix panels 
#define NUM_LEDS    128     // 2 x APA102 20/20 8x8 matrix panels 
#define BRIGHTNESS  25      // The LED panels can get HOT so don't go above 25-30 max

// Overall twinkle speed.
// 0 (VERY slow) to 8 (VERY fast).  
// Default is 4.
int twinkle_speed=4;

// Overall twinkle density.
// 0 (NONE lit) to 8 (ALL lit at once).  
// Default is 2.
int twinkle_density=2;

// How often to change color palettes.
#define SECONDS_PER_PALETTE  30

// =======================================================================================
//  Color Pallete Definitions - Use "CRGB::Gray" for white to keep the brightness uniform
// =======================================================================================

const TProgmemRGBPalette16 White_p FL_PROGMEM =
{  CRGB::Gray,  CRGB::Gray,  CRGB::Gray,  CRGB::Gray,
   CRGB::Gray,  CRGB::Gray,  CRGB::Gray,  CRGB::Gray,
   CRGB::Gray,  CRGB::Gray,  CRGB::Gray,  CRGB::Gray,
   CRGB::Gray,  CRGB::Gray,  CRGB::Gray,  CRGB::Gray};

const TProgmemRGBPalette16 Red_p FL_PROGMEM =
{  CRGB::Red,  CRGB::Red,  CRGB::Red,  CRGB::Red,
   CRGB::Red,  CRGB::Red,  CRGB::Red,  CRGB::Red,
   CRGB::Red,  CRGB::Red,  CRGB::Red,  CRGB::Red,
   CRGB::Red,  CRGB::Red,  CRGB::Red,  CRGB::Red};

const TProgmemRGBPalette16 Blue_p FL_PROGMEM =
{  CRGB::Blue,  CRGB::Blue,  CRGB::Blue,  CRGB::Blue,
   CRGB::Blue,  CRGB::Blue,  CRGB::Blue,  CRGB::Blue,
   CRGB::Blue,  CRGB::Blue,  CRGB::Blue,  CRGB::Blue,
   CRGB::Blue,  CRGB::Blue,  CRGB::Blue,  CRGB::Blue};

const TProgmemRGBPalette16 Black_p FL_PROGMEM =
{  CRGB::Black,  CRGB::Black,  CRGB::Black,  CRGB::Black,
   CRGB::Black,  CRGB::Black,  CRGB::Black,  CRGB::Black,
   CRGB::Black,  CRGB::Black,  CRGB::Black,  CRGB::Black,
   CRGB::Black,  CRGB::Black,  CRGB::Black,  CRGB::Black};

const TProgmemRGBPalette16 RedWhite_p FL_PROGMEM =
{  CRGB::Red,  CRGB::Red,  CRGB::Red,  CRGB::Red, 
   CRGB::Red, CRGB::Gray, CRGB::Red, CRGB::Gray,
   CRGB::Red,  CRGB::Red,  CRGB::Red,  CRGB::Red, 
   CRGB::Gray, CRGB::Red, CRGB::Gray, CRGB::Red };

const TProgmemRGBPalette16 RedBlue_p FL_PROGMEM =
{  CRGB::Red,  CRGB::Red,  CRGB::Red,  CRGB::Red, 
   CRGB::Blue, CRGB::Blue, CRGB::Blue, CRGB::Blue,
   CRGB::Red,  CRGB::Red,  CRGB::Red,  CRGB::Red, 
   CRGB::Red, CRGB::Red, CRGB::Blue, CRGB::Blue };

const TProgmemRGBPalette16 BlueWhite_p FL_PROGMEM =
{  CRGB::Blue, CRGB::Blue, CRGB::Blue, CRGB::Blue, 
   CRGB::Blue, CRGB::Blue, CRGB::Blue, CRGB::Blue, 
   CRGB::Blue, CRGB::Blue, CRGB::Blue, CRGB::Blue, 
   CRGB::Blue, CRGB::Blue, CRGB::Blue, CRGB::Gray };

// =======================================================================================
//  Color Pallete Order - Use "&Black_p" for OFF
// =======================================================================================

const TProgmemRGBPalette16* ActivePaletteList[] = {
   &Red_p,
   &Red_p,
   &Black_p,
   &RedBlue_p,
   &Blue_p,
   &Black_p,
   &RedWhite_p,
   &White_p,
   &White_p,
   &Black_p,
   &BlueWhite_p,
   &Blue_p,
   &Blue_p,
   &Black_p,
   &RainbowColors_p,
   &RainbowColors_p,
   &Black_p,
};

// =======================================================================================
//  Main Program - Shouldn't need to edit below
// =======================================================================================

#define AUTO_SELECT_BACKGROUND_COLOR 0
#define COOL_LIKE_INCANDESCENT 0
CRGB gBackgroundColor = CRGB::Black;
CRGBArray<NUM_LEDS> leds;
CRGBPalette16 gCurrentPalette;
CRGBPalette16 gTargetPalette;

void setup() {
  delay( 3000 );
  FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS)
    .setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);

  chooseNextColorPalette(gTargetPalette);
}

void loop() {
  EVERY_N_SECONDS( SECONDS_PER_PALETTE ) { 
    chooseNextColorPalette( gTargetPalette ); 
  }
  
  EVERY_N_MILLISECONDS( 10 ) {
    nblendPaletteTowardPalette( gCurrentPalette, gTargetPalette, 12);
  }

  drawTwinkles( leds);
  
  FastLED.show();
}

void drawTwinkles( CRGBSet& L) {
  uint16_t PRNG16 = 11337;
  
  uint32_t clock32 = millis();

  CRGB bg;
  if( (AUTO_SELECT_BACKGROUND_COLOR == 1) &&
      (gCurrentPalette[0] == gCurrentPalette[1] )) {
    bg = gCurrentPalette[0];
    uint8_t bglight = bg.getAverageLight();
    if( bglight > 64) {
      bg.nscale8_video( 16);
    } else if( bglight > 16) {
      bg.nscale8_video( 64);
    } else {
      bg.nscale8_video( 86);
    }
  } else {
    bg = gBackgroundColor;
  }

  uint8_t backgroundBrightness = bg.getAverageLight();
  
  for( CRGB& pixel: L) {
    PRNG16 = (uint16_t)(PRNG16 * 2053) + 1384;
    uint16_t myclockoffset16= PRNG16;
    PRNG16 = (uint16_t)(PRNG16 * 2053) + 1384;
    uint8_t myspeedmultiplierQ5_3 =  ((((PRNG16 & 0xFF)>>4) + (PRNG16 & 0x0F)) & 0x0F) + 0x08;
    uint32_t myclock30 = (uint32_t)((clock32 * myspeedmultiplierQ5_3) >> 3) + myclockoffset16;
    uint8_t  myunique8 = PRNG16 >> 8;

    CRGB c = computeOneTwinkle( myclock30, myunique8);

    uint8_t cbright = c.getAverageLight();
    int16_t deltabright = cbright - backgroundBrightness;
    if( deltabright >= 32 || (!bg)) {
      pixel = c;
    } else if( deltabright > 0 ) {
      pixel = blend( bg, c, deltabright * 8);
    } else { 
      pixel = bg;
    }
  }
}

CRGB computeOneTwinkle( uint32_t ms, uint8_t salt) {
  uint16_t ticks = ms >> (8-twinkle_speed);
  uint8_t fastcycle8 = ticks;
  uint16_t slowcycle16 = (ticks >> 8) + salt;
  slowcycle16 += sin8( slowcycle16);
  slowcycle16 =  (slowcycle16 * 2053) + 1384;
  uint8_t slowcycle8 = (slowcycle16 & 0xFF) + (slowcycle16 >> 8);
  
  uint8_t bright = 0;
  if( ((slowcycle8 & 0x0E)/2) < twinkle_density) {
    bright = attackDecayWave8( fastcycle8);
  }

  uint8_t hue = slowcycle8 - salt;
  CRGB c;
  if( bright > 0) {
    c = ColorFromPalette( gCurrentPalette, hue, bright, NOBLEND);
    if( COOL_LIKE_INCANDESCENT == 1 ) {
      coolLikeIncandescent( c, fastcycle8);
    }
  } else {
    c = CRGB::Black;
  }
  return c;
}

uint8_t attackDecayWave8( uint8_t i) {
  if( i < 86) {
    return i * 3;
  } else {
    i -= 86;
    return 255 - (i + (i/2));
  }
}

void coolLikeIncandescent( CRGB& c, uint8_t phase) {
  if( phase < 128) return;

  uint8_t cooling = (phase - 128) >> 4;
  c.g = qsub8( c.g, cooling);
  c.b = qsub8( c.b, cooling * 2);
}

void chooseNextColorPalette( CRGBPalette16& pal) {
  const uint8_t numberOfPalettes = sizeof(ActivePaletteList) / sizeof(ActivePaletteList[0]);
  static uint8_t whichPalette = -1; 
  whichPalette = addmod8( whichPalette, 1, numberOfPalettes);

  pal = *(ActivePaletteList[whichPalette]);
}
