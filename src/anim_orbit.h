#ifndef ANIM_ORBIT_H
#define ANIM_ORBIT_H

#include <FastLED.h>
#include <Arduino.h>
#include "settings.h"
#include "data.h"
#include "animation.h"
#include "traveler.h"
#include "color_palette.h"

class AnimationOrbit : public Animation
{
private:
    ColorPalette *colorPalette;
    int numTravelers = 12;
    Traveler travelers[12] = {
        Traveler(0, 27, 270, DIR_E, STEERING_CW),
        Traveler(1, 4, 40, DIR_E, STEERING_CW),
        Traveler(2, 30, 309, DIR_E, STEERING_CW),
        Traveler(3, 29, 299, DIR_W, STEERING_CW),
        Traveler(4, 21, 210, DIR_W, STEERING_CW),
        Traveler(5, 28, 289, DIR_W, STEERING_CW),
        Traveler(6, 32, 329, DIR_W, STEERING_CCW),
        Traveler(7, 8, 89, DIR_W, STEERING_CCW),
        Traveler(8, 35, 350, DIR_W, STEERING_CCW),
        Traveler(9, 34, 340, DIR_E, STEERING_CCW),
        Traveler(10, 17, 179, DIR_E, STEERING_CCW),
        Traveler(11, 33, 330, DIR_E, STEERING_CCW)
    };

public:
    void setup(CRGB leds[], ColorPalette *colorPalette)
    {
        this->colorPalette = colorPalette;

        for (int i = 0; i < numTravelers; i++)
        {
            travelers[i].color = colorPalette->GetNextColor(numTravelers);
            leds[travelers[i].pos] = travelers[i].color;
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
