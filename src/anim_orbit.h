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
    std::initializer_list<int> path = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
    int numTravelers = 26;
    Traveler travelers[26] = {
        Traveler(0, 0, 0, DIR_W, STEERING_PATH_REPEAT, path, 26),
        Traveler(0, 1, 0, DIR_E, STEERING_PATH_REPEAT, path, 26),
        Traveler(0, 2, 0, DIR_E, STEERING_PATH_REPEAT, path, 26),
        Traveler(0, 3, 0, DIR_E, STEERING_PATH_REPEAT, path, 26),
        Traveler(0, 4, 0, DIR_E, STEERING_PATH_REPEAT, path, 26),
        Traveler(0, 5, 0, DIR_E, STEERING_PATH_REPEAT, path, 26),
        Traveler(0, 6, 0, DIR_E, STEERING_PATH_REPEAT, path, 26),
        Traveler(0, 7, 0, DIR_E, STEERING_PATH_REPEAT, path, 26),
        Traveler(0, 8, 0, DIR_E, STEERING_PATH_REPEAT, path, 26),
        Traveler(0, 9, 0, DIR_E, STEERING_PATH_REPEAT, path, 26),
        Traveler(0, 10, 0, DIR_E, STEERING_PATH_REPEAT, path, 26),
        Traveler(0, 11, 0, DIR_E, STEERING_PATH_REPEAT, path, 26),
        Traveler(0, 12, 0, DIR_W, STEERING_PATH_REPEAT, path, 26),
        Traveler(0, 13, 0, DIR_E, STEERING_PATH_REPEAT, path, 26),
        Traveler(0, 14, 0, DIR_W, STEERING_PATH_REPEAT, path, 26),
        Traveler(0, 15, 0, DIR_W, STEERING_PATH_REPEAT, path, 26),
        Traveler(0, 16, 0, DIR_W, STEERING_PATH_REPEAT, path, 26),
        Traveler(0, 17, 0, DIR_W, STEERING_PATH_REPEAT, path, 26),
        Traveler(0, 18, 0, DIR_W, STEERING_PATH_REPEAT, path, 26),
        Traveler(0, 19, 0, DIR_W, STEERING_PATH_REPEAT, path, 26),
        Traveler(0, 20, 0, DIR_W, STEERING_PATH_REPEAT, path, 26),
        Traveler(0, 21, 0, DIR_W, STEERING_PATH_REPEAT, path, 26),
        Traveler(0, 22, 0, DIR_W, STEERING_PATH_REPEAT, path, 26),
        Traveler(0, 23, 0, DIR_W, STEERING_PATH_REPEAT, path, 26),
        Traveler(0, 24, 0, DIR_W, STEERING_PATH_REPEAT, path, 26),
        Traveler(0, 25, 0, DIR_E, STEERING_PATH_REPEAT, path, 26),
    };

public:
    void setup(CRGB leds[], ColorPalette *colorPalette)
    {
        this->colorPalette = colorPalette;

        for (int i = 0; i < numTravelers; i++)
        {
            travelers[i].pos = random(travelers[i].segment.LowLed, travelers[i].segment.HighLed);
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
