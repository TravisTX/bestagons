#ifndef COLOR_PALETTE_H
#define COLOR_PALETTE_H

#include <FastLED.h>
#include <Arduino.h>
#include "settings.h"

DEFINE_GRADIENT_PALETTE(blueGp){
    0, 0, 0, 139,      // CRGB::DarkBlue
    255, 135, 206, 235 // CRGB::LightSkyBlue
};

DEFINE_GRADIENT_PALETTE(lavaGp){
    0, 128, 0, 0,     // CRGB::Maroon
    85, 139, 0, 0,    // CRGB::DarkRed
    170, 255, 0, 0,   // CRGB::Red
    255, 255, 165, 0, // CRGB::Orange
};

DEFINE_GRADIENT_PALETTE(forestGp){
    0, 0, 128, 0,      // CRGB::Green
    255, 144, 238, 144 // CRGB::LightGreen
};

DEFINE_GRADIENT_PALETTE(jokerFixedGp){
    0, 0, 128, 0,     // CRGB::Green
    128, 128, 0, 128, // CRGB::Purple
    255, 0, 128, 0    // CRGB::Green
};

DEFINE_GRADIENT_PALETTE(bluePurpFixedGp){
    0, 0, 0, 255,     // CRGB::Blue
    128, 128, 0, 128, // CRGB::Purple
    255, 0, 0, 255    // CRGB::Blue
};

DEFINE_GRADIENT_PALETTE(royalFixedGp){
    0, 255, 165, 0,   // CRGB::Orange
    128, 128, 0, 128, // CRGB::Purple
    255, 255, 165, 0  // CRGB::Orange
};

class ColorPalette
{
private:
  int colorIndex = 0;
  int stepOverride = -1;

public:
  CRGBPalette16 currentPalette;

  CRGBPalette16 bluePal = blueGp;
  CRGBPalette16 lavaPal = lavaGp;
  CRGBPalette16 forestPal = forestGp;
  CRGBPalette16 partyPal = PartyColors_p;
  CRGBPalette16 jokerFixedPal = jokerFixedGp;
  CRGBPalette16 bluePurpFixedPal = bluePurpFixedGp;
  CRGBPalette16 royalFixedPal = royalFixedGp;

  const int numPalettes = 7;
  CRGBPalette16 allPalettes[7] = {
      bluePal,
      lavaPal,
      forestPal,
      partyPal,
      jokerFixedPal,
      bluePurpFixedPal,
      royalFixedPal};

  // for most palettes, we're fine with the default behavior of
  // arbitrarily picking colors out of the gradient.
  // however, for these ones, we have a fixed number of steps
  // (currently always 2 steps)
  const int numFixedPalettes = 3;
  CRGBPalette16 allFixedPalettes[3] = {
      jokerFixedPal,
      bluePurpFixedPal,
      royalFixedPal};

  ColorPalette()
  {
    SetPalette("");
  }

  void SetPalette(String paletteName)
  {
    if (paletteName == "blue")
      currentPalette = bluePal;
    else if (paletteName == "lava")
      currentPalette = lavaPal;
    else if (paletteName == "forest")
      currentPalette = forestPal;
    else if (paletteName == "party")
      currentPalette = partyPal;
    else if (paletteName == "joker")
      currentPalette = jokerFixedPal;
    else if (paletteName == "bluePurp")
      currentPalette = bluePurpFixedPal;
    else if (paletteName == "royal")
      currentPalette = royalFixedPal;
    else
      currentPalette = allPalettes[random(0, numPalettes)];

    stepOverride = -1;
    for (int i = 0; i < numFixedPalettes; i++)
    {
      if (currentPalette == allFixedPalettes[i])
      {
        stepOverride = 2;
      }
    }
  }

  CRGB GetNextColor(int steps)
  {
    if (stepOverride > -1)
      steps = stepOverride;
    debug_println(colorIndex += 255 / steps);
    return ColorFromPalette(currentPalette, colorIndex, 255, NOBLEND);
  }
};

#endif
