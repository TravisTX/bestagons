#ifndef SETTINGS_H
#define SETTINGS_H

#define DEBUG true
#define OTA true

#define LED_PIN 5
#define SEGMENT_COUNT 37
#define LEDS_PER_SEGMENT 10
#define NUM_LEDS 370 // SEGMENT_COUNT * LEDS_PER_SEGMENT
int BRIGHTNESS = 25;
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
int FRAMES_PER_SECOND = 20;
#define ANIM_MIN_DURATION -1
bool SYSTEM_ON = true;

// commands coming from http
bool changeAnimation = false;
char changeAnimationValue[15] = "";
bool changePalette = false;
char changePaletteValue[10] = "";
bool changeCustomFixedColor = false;
CRGB customFixed1;
CRGB customFixed2;

#define debug_begin(...) do { if (DEBUG) { Serial.begin(__VA_ARGS__); while(!Serial); }} while (0)
#define debug_print(...) do { if (DEBUG) Serial.print(__VA_ARGS__); } while (0)
#define debug_println(...) do { if (DEBUG) Serial.println(__VA_ARGS__); } while (0)
#define debug_printf(...) do { if (DEBUG) Serial.printf(__VA_ARGS__); } while (0)

// add these settings to secrets.h
// #define WIFI_SSID "my_ssid"
// #define WIFI_PW "my_password"

#endif
