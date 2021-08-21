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
    int numTravelers = 12;
    Traveler travelers[12] = {
        Traveler(0),
        Traveler(1),
        Traveler(2),
        Traveler(3),
        Traveler(4),
        Traveler(5),
        Traveler(6),
        Traveler(7),
        Traveler(8),
        Traveler(9),
        Traveler(10),
        Traveler(11)};

    ColorPalette colorPalette = ColorPalette();

public:
    void setup(CRGB leds[])
    {
        // todo: constructor PLZ!
        travelers[0].segment = segments[27];
        travelers[0].pos = 270;
        travelers[0].animDir = DIR_E;
        travelers[0].steering = STEERING_CW;

        travelers[1].segment = segments[4];
        travelers[1].pos = 40;
        travelers[1].animDir = DIR_E;
        travelers[1].steering = STEERING_CW;

        travelers[2].segment = segments[30];
        travelers[2].pos = 309;
        travelers[2].animDir = DIR_E;
        travelers[2].steering = STEERING_CW;

        travelers[3].segment = segments[29];
        travelers[3].pos = 299;
        travelers[3].animDir = DIR_W;
        travelers[3].steering = STEERING_CW;

        travelers[4].segment = segments[21];
        travelers[4].pos = 210;
        travelers[4].animDir = DIR_W;
        travelers[4].steering = STEERING_CW;

        travelers[5].segment = segments[28];
        travelers[5].pos = 289;
        travelers[5].animDir = DIR_W;
        travelers[5].steering = STEERING_CW;

        travelers[6].segment = segments[32];
        travelers[6].pos = 329;
        travelers[6].animDir = DIR_W;
        travelers[6].steering = STEERING_CCW;

        travelers[7].segment = segments[8];
        travelers[7].pos = 89;
        travelers[7].animDir = DIR_W;
        travelers[7].steering = STEERING_CCW;

        travelers[8].segment = segments[35];
        travelers[8].pos = 350;
        travelers[8].animDir = DIR_W;
        travelers[8].steering = STEERING_CCW;

        travelers[9].segment = segments[34];
        travelers[9].pos = 340;
        travelers[9].animDir = DIR_E;
        travelers[9].steering = STEERING_CCW;

        travelers[10].segment = segments[17];
        travelers[10].pos = 179;
        travelers[10].animDir = DIR_E;
        travelers[10].steering = STEERING_CCW;

        travelers[11].segment = segments[33];
        travelers[11].pos = 330;
        travelers[11].animDir = DIR_E;
        travelers[11].steering = STEERING_CCW;

        for (int i = 0; i < numTravelers; i++)
        {
            travelers[i].color = colorPalette.GetNextColor(numTravelers);
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
