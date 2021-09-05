#ifndef ANIM_SPARKLES_H
#define ANIM_SPARKLES_H

#include <FastLED.h>
#include <Arduino.h>
#include "settings.h"
#include "traveler.h"
#include "animation.h"
#include "color_palette.h"

class AnimationSparkles : public Animation
{
private:
    ColorPalette *colorPalette;
    unsigned long nextSparkles;
    int sparkleChance = 200;

public:
    void setup(CRGB leds[], ColorPalette *colorPalette)
    {
        this->colorPalette = colorPalette;
    }

    void loop(CRGB leds[])
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            leds[i] = blend( leds[i], CRGB::Black, 40);

            if (random(1, sparkleChance) == 1)
            {
                leds[i] = colorPalette->GetNextColor(10);
            }
        }
    }

    bool checkStoppingPoint()
    {
        return true;
    }
};

#endif
