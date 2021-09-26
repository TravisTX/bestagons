#ifndef ANIM_SLOWFADE_H
#define ANIM_SLOWFADE_H

#include <FastLED.h>
#include <Arduino.h>
#include "settings.h"
#include "traveler.h"
#include "animation.h"
#include "color_palette.h"

class AnimationSlowFade : public Animation
{
private:
    ColorPalette *colorPalette;
    CRGB currColor;
    CRGB targetColor;
    unsigned long frameNumber = 0;

public:
    void setup(CRGB leds[], ColorPalette *colorPalette)
    {
        this->colorPalette = colorPalette;
        targetColor = colorPalette->GetNextColor(255);
    }

    void loop(CRGB leds[])
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            leds[i] = blend(leds[i], targetColor, 1);
        }

        frameNumber++;
        if (frameNumber % 20 == 0)
        {
            targetColor = colorPalette->GetNextColor(255);
        }
    }

    bool checkStoppingPoint()
    {
        return true;
    }
};

#endif
