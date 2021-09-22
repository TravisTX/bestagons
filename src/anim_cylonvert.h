#ifndef ANIM_CYLONVERT_H
#define ANIM_CYLONVERT_H

#include <FastLED.h>
#include <Arduino.h>
#include "settings.h"
#include "data.h"
#include "animation.h"
#include "traveler.h"
#include "color_palette.h"

class AnimationCylonVert : public Animation
{
private:
    ColorPalette *colorPalette;

    int numTravelers = 6;
    Traveler travelers[6] = {
        Traveler(0, 1, 19, DIR_W, STEERING_PATH_REPEAT, {1, 0, 25, 24, 23, 22, 28, 27, 3, 2}, 10),
        Traveler(1, 3, 30, DIR_E, STEERING_PATH_REPEAT, {3, 27, 28, 22, 23, 24, 25, 0, 1, 2}, 10),
        Traveler(2, 5, 59, DIR_W, STEERING_PATH_REPEAT, {5, 30, 29, 20, 19, 18, 33, 32, 7, 6}, 10),
        Traveler(3, 7, 70, DIR_E, STEERING_PATH_REPEAT, {7, 32, 33, 18, 19, 20, 29, 30, 5, 6}, 10),
        Traveler(4, 9, 99, DIR_W, STEERING_PATH_REPEAT, {9, 35, 34, 16, 15, 14, 13, 12, 11, 10}, 10),
        Traveler(5, 11, 110, DIR_E, STEERING_PATH_REPEAT, {11, 12, 13, 14, 15, 16, 34, 35, 9, 10}, 10),
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
        fadeToBlackBy(leds, NUM_LEDS, 3);

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
