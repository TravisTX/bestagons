#include <Arduino.h>
#include <FastLED.h>
#include "secrets.h"
#include "settings.h"

#if OTA
#include "OTA.h"
#include "http_server.h"
#endif

#include "anim_cylon.h"
#include "anim_cylonvert.h"
#include "anim_explosion.h"
#include "anim_orbit.h"
#include "anim_sparkles.h"
#include "anim_travelers.h"
#include "anim_debug1.h"
#include "data.h"
#include "color_palette.h"

CRGB leds[NUM_LEDS];

ColorPalette *colorPalette = new ColorPalette();
Animation *animation;
unsigned long animationEnd;
bool prevSystemOn = SYSTEM_ON;

//------------ forward declarations ----------//
Animation *getAnimation(String newAnimation = "");

void setup()
{
  Serial.begin(74880);
  debug_println("hello world");

#if OTA
  setupOTA("Bestagons", WIFI_SSID, WIFI_PW);
  http_server_setup();
#endif
  randomSeed(analogRead(0));
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
  animation = getAnimation("travelers");
}

void loop()
{
#if OTA
  ArduinoOTA.handle();
  http_server_loop();
#endif

  if (SYSTEM_ON != prevSystemOn)
  {
    if (SYSTEM_ON)
    {
      for (int i = 0; i < 100; i++)
      {
        animation->loop(leds);
      }
    }
    else
    {
      for (int i = 0; i < NUM_LEDS; i++)
      {
        leds[i] = CRGB::Black;
      }
    }
    prevSystemOn = SYSTEM_ON;
  }

  if (!SYSTEM_ON)
  {
    FastLED.delay(1000 / FRAMES_PER_SECOND);
    return;
  }

  animation->loop(leds);

  if (ANIM_MIN_DURATION > -1 && millis() > animationEnd && animation->checkStoppingPoint())
  {
    changeAnimation = true;
    changePalette = true;
    // random
    changeAnimationValue[0] = 0;
  }

  if (changeAnimation)
  {
    animation = getAnimation(changeAnimationValue);
    animation->loop(leds);

    // reset
    changeAnimation = false;
    changeAnimationValue[0] = 0;
  }

  if (changePalette)
  {
    colorPalette->SetPalette(changePaletteValue);
    animation->setup(leds, colorPalette);

    // reset
    changePalette = false;
    changePaletteValue[0] = 0;
  }

  FastLED.setBrightness(BRIGHTNESS);
  FastLED.delay(1000 / FRAMES_PER_SECOND);
}

Animation *getRandomAnimation()
{
  int animNum = random(1, 6);
  switch (animNum)
  {
  case 1:
    return new AnimationTravelers();
  case 2:
    return new AnimationOrbit();
  case 3:
    return new AnimationSparkles();
  case 4:
    return new AnimationCylon();
  case 5:
    return new AnimationCylonVert();
  default:
    debug_println("invalid animNum");
    return new AnimationTravelers();
  }
}

Animation *getAnimation(String newAnimation)
{
  debug_println("getting new animation");

  Animation *anim;

  if (newAnimation == "travelers")
    anim = new AnimationTravelers();
  else if (newAnimation == "orbit")
    anim = new AnimationOrbit();
  else if (newAnimation == "sparkles")
    anim = new AnimationSparkles();
  else if (newAnimation == "explosion")
    anim = new AnimationExplosion();
  else if (newAnimation == "cylon")
    anim = new AnimationCylon();
  else if (newAnimation == "cylonVert")
    anim = new AnimationCylonVert();
  else if (newAnimation == "debug1")
    anim = new AnimationDebug1();
  else
    anim = getRandomAnimation();

  anim->setup(leds, colorPalette);
  animationEnd = millis() + ANIM_MIN_DURATION;
  return anim;
}