#ifndef ANIM_EXPLOSION_H
#define ANIM_EXPLOSION_H

#include <FastLED.h>
#include <Arduino.h>
#include "settings.h"
#include "data.h"
#include "animation.h"
#include "traveler.h"
#include "color_palette.h"

class AnimationExplosion : public Animation
{
private:
    ColorPalette *colorPalette;

    int numTravelers = 12;
    Traveler travelers[12] = {
        Traveler(0, 30, 300, DIR_W, STEERING_PATH, {30, 4, 3, 2, 1}, 5 ),
        Traveler(1, 30, 300, DIR_W, STEERING_PATH, {30, 4, 27, 26, 0}, 5 ),
        Traveler(2, 30, 300, DIR_W, STEERING_PATH, {30, 4, 27, 26, 25}, 5 ),
        Traveler(3, 29, 299, DIR_W, STEERING_PATH, {29, 21, 28, 26, 0}, 5 ),
        Traveler(4, 29, 299, DIR_W, STEERING_PATH, {29, 21, 28, 26, 25}, 5 ),
        Traveler(5, 29, 299, DIR_W, STEERING_PATH, {29, 21, 22, 23, 24}, 5 ),

        Traveler(6, 31, 310, DIR_E, STEERING_PATH, {31, 32, 8, 9, 10, 11}, 6),
        Traveler(7, 31, 310, DIR_E, STEERING_PATH, {31, 32, 8, 35, 36, 12}, 6),
        Traveler(8, 31, 310, DIR_E, STEERING_PATH, {31, 32, 8, 35, 36, 13}, 6),
        Traveler(9, 31, 310, DIR_E, STEERING_PATH, {31, 33, 17, 34, 36, 12}, 6),
        Traveler(10, 31, 310, DIR_E, STEERING_PATH, {31, 33, 17, 34, 36, 13}, 6),
        Traveler(11, 31, 310, DIR_E, STEERING_PATH, {31, 33, 17, 16, 15, 14}, 6),
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
