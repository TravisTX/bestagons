#ifndef ANIM_H
#define ANIM_H
#include <FastLED.h>
#include <Arduino.h>
#include "color_palette.h"

class Animation
{
private:
public:
  virtual void setup(CRGB leds[], ColorPalette *colorPalette);
  virtual void loop(CRGB leds[]);
  virtual bool checkStoppingPoint();
};

#endif
