#ifndef ANIM_DEBUG1_H
#define ANIM_DEBUG1_H

#include <FastLED.h>
#include <Arduino.h>
#include "settings.h"
#include "traveler.h"
#include "animation.h"
#include "color_palette.h"

class AnimationDebug1 : public Animation
{
private:
    ColorPalette *colorPalette;

public:
    void setup(CRGB leds[], ColorPalette *colorPalette)
    {
        this->colorPalette = colorPalette;
    }

    void loop(CRGB leds[])
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            leds[i] = colorPalette->GetNextColor(NUM_LEDS);
        }
    }

    bool checkStoppingPoint()
    {
        return false;
    }
};

#endif
