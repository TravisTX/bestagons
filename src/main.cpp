#include <Arduino.h>
#include <FastLED.h>
#include "secrets.h"
#include "settings.h"

#if OTA
#include "OTA.h"
#include "http_server.h"
#endif

#include "anim_explosion.h"
#include "anim_orbit.h"
#include "anim_sparkles.h"
#include "anim_travelers.h"
#include "anim_debug1.h"
#include "data.h"
#include "color_palette.h"

CRGB leds[NUM_LEDS];

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

ColorPalette *colorPalette = new ColorPalette();
Animation *animation;
unsigned long animationEnd;

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
  animation = getAnimation();
}

void loop()
{
#if OTA
  ArduinoOTA.handle();
  http_server_loop();
#endif
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

Animation *getAnimation(String newAnimation)
{
  debug_println("getting new animation");

  int animNum;
  Animation *anim;

  if (newAnimation == "travelers")
    animNum = 1;
  else if (newAnimation == "orbit")
    animNum = 2;
  else if (newAnimation == "sparkles")
    animNum = 3;
  else if (newAnimation == "explosion")
    animNum = 4;
  else
    animNum = random(1, 5);

  switch (animNum)
  {
  case 1:
    anim = new AnimationTravelers();
    break;
  case 2:
    anim = new AnimationOrbit();
    break;
  case 3:
    anim = new AnimationSparkles();
    break;
  case 4:
    anim = new AnimationExplosion();
    break;
  default:
    debug_println("invalid animNum");
    anim = new AnimationTravelers();
  }

  anim->setup(leds, colorPalette);
  animationEnd = millis() + ANIM_MIN_DURATION;
  return anim;
}