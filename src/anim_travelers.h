#ifndef ANIM_TRAVELER_H
#define ANIM_TRAVELER_H

#include <FastLED.h>
#include <Arduino.h>
#include "settings.h"
#include "traveler.h"
#include "animation.h"

class AnimationTravelers : public Animation
{
private:
    int numTravelers = 6;
    Traveler travelers[6] = {
        Traveler(0),
        Traveler(1),
        Traveler(2),
        Traveler(3),
        Traveler(4),
        Traveler(5)};

public:
    void setup(CRGB leds[])
    {
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
