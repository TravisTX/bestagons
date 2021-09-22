#ifndef ANIM_WEEWOO_H
#define ANIM_WEEWOO_H

#include <FastLED.h>
#include <Arduino.h>
#include "settings.h"
#include "data.h"
#include "animation.h"
#include "traveler.h"
#include "color_palette.h"

class AnimationWeewoo : public Animation
{
private:
    ColorPalette *colorPalette;
    bool state = false;
    int segmentsPerColor = 17;
    int ledsPerColor = 15;
    int leftSegments[17] = {1,2,3,4,5,0,26,27,30,25,28,21,29,24,23,22,20};
    int rightSegments[17] = {7,8,9,10,11,32,35,36,12,33,17,34,13,18,16,15,14};
    int leftLeds[15] =  {60,61,62,63,64,310,311,312,313,314,195,196,197,198,199};
    int rightLeds[15] = {65,66,67,68,69,315,316,317,318,319,190,191,192,193,194};
    int delay = 500;
    unsigned long nextColorChange = millis() + delay;

public:
    void setup(CRGB leds[], ColorPalette *colorPalette)
    {
        this->colorPalette = colorPalette;

        for (int i = 0; i < NUM_LEDS; i++)
        {
            leds[i] = CRGB::Black;
        }
    }

    void loop(CRGB leds[])
    {
        CRGB leftColor = state ? CRGB::Blue : CRGB::Red;
        CRGB rightColor = state ? CRGB::Red : CRGB::Blue;

        for(int i = 0; i < segmentsPerColor; i++)
        {
            Segment leftSegment = segments[leftSegments[i]];
            for(int j = leftSegment.LowLed; j < leftSegment.HighLed; j++)
            {
                leds[j] = leftColor;
            }

            Segment rightSegment = segments[rightSegments[i]];
            for(int j = rightSegment.LowLed; j < rightSegment.HighLed; j++)
            {
                leds[j] = rightColor;
            }
        }

        if (millis() > nextColorChange)
        {
            nextColorChange = millis() + delay;
            state = !state;
        }
    }

    bool checkStoppingPoint()
    {
        return true;
    }
};

#endif
