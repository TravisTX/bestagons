#ifndef ANIM_CYLON_H
#define ANIM_CYLON_H

#include <FastLED.h>
#include <Arduino.h>
#include "settings.h"
#include "data.h"
#include "animation.h"
#include "traveler.h"
#include "color_palette.h"

class AnimationCylon : public Animation
{
private:
    ColorPalette *colorPalette;

    int numTravelers = 4;
    Traveler travelers[4] = {
        Traveler(0, 1, 10, DIR_E, STEERING_PATH_PINGPONG, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, 11),
        Traveler(1, 0, 9, DIR_E, STEERING_PATH_PINGPONG, {0, 26, 27, 4, 30, 31, 32, 8, 35, 36, 12}, 11),
        Traveler(2, 25, 250, DIR_E, STEERING_PATH_PINGPONG, {25, 26, 28, 21, 29, 31, 33, 17, 34, 36, 13}, 11),
        Traveler(3, 24, 249, DIR_E, STEERING_PATH_PINGPONG, {24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14}, 11),
    };

public:
    void setup(CRGB leds[], ColorPalette *colorPalette)
    {
        this->colorPalette = colorPalette;

        for (int i = 0; i < numTravelers; i++)
        {
            travelers[i].color = colorPalette->GetNextColor(numTravelers);
        }
    }

    void loop(CRGB leds[])
    {
        fadeToBlackBy(leds, NUM_LEDS, 40);

        for (int i = 0; i < numTravelers; i++)
        {
            travelers[i].move();
            leds[travelers[i].pos] = travelers[i].color;
        }
    }

    bool checkStoppingPoint()
    {
        return true;
    }
};

#endif
