#ifndef ANIM_H
#define ANIM_H
#include <FastLED.h>
#include <Arduino.h>

class Animation
{
private:
public:
  virtual void setup(CRGB leds[]);
  virtual void loop(CRGB leds[]);
  virtual bool checkStoppingPoint();
};

#endif
