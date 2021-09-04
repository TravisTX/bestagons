#include <Arduino.h>
#include <FastLED.h>
#include "secrets.h"
#include "settings.h"

#if OTA
#include "OTA.h"
#endif

#include "anim_orbit.h"
#include "anim_travelers.h"
#include "data.h"

CRGB leds[NUM_LEDS];

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

Animation *animation;
unsigned long animationEnd;

//------------ forward declarations ----------//
Animation *getAnimation();

void setup()
{
  Serial.begin(74880);
  debug_println("hello world");

#if OTA
  setupOTA("Bestagons", WIFI_SSID, WIFI_PW);
#endif
  randomSeed(4); // chosen by fair dice roll, guaranteed to be random
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);

  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
  animation = getAnimation();
}

void loop()
{
#if OTA
  ArduinoOTA.handle();
#endif

  animation->loop(leds);

  if (ANIM_MIN_DURATION > -1 && millis() > animationEnd && animation->checkStoppingPoint())
  {
    animation = getAnimation();
    animation->loop(leds);
  }

  FastLED.delay(1000 / UPDATES_PER_SECOND);
}

Animation *getAnimation()
{
  debug_println("getting new animation");

  int animNum = random(1, 3);
  Animation *anim;

  switch (animNum)
  {
  case 1:
    anim = new AnimationTravelers();
    break;
  case 2:
    anim = new AnimationOrbit();
    break;
  default:
    debug_println("invalid animNum");
  }

  // debug
  anim = new AnimationTravelers();

  anim->setup(leds);
  animationEnd = millis() + ANIM_MIN_DURATION;
  return anim;
}