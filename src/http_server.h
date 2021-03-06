#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <WiFiClient.h>
#include <ESPAsyncWebServer.h>

#include "settings.h"

//------------ forward declarations ----------//
String toHexString(CRGB color);

AsyncWebServer server(80);

char message[100];

const char htmlTemplate[] PROGMEM = "\
           <html>\
  <head>\
    <title>Bestagons!</title>\
    <style>\
      html, body { background-color: #35393b; color: #7aabff; padding: 10px; margin: 0; font-family: Sans-Serif; }\
      input[type=\"submit\"] {width: 100px; padding: 10px; background-color: #181a1b; color: #e8e6e3; }\
      .section {background: #222; padding: 5px; margin-bottom:10px;}\
      .message {background: #404b5f; color: #e8e6e3; padding: 5px;}\
    </style>\
  </head>\
  <body>\
    <h1>Bestagons!</h1>\
    <p class=\"message\">%MESSAGE%</p>\
    <div class=\"section\">\
        <h2>Animation</h2>\
        <form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/anim\">\
        <input type=\"submit\" name=\"anim\" value=\"random\">\
        <input type=\"submit\" name=\"anim\" value=\"travelers\">\
        <input type=\"submit\" name=\"anim\" value=\"orbit\">\
        <input type=\"submit\" name=\"anim\" value=\"sparkles\">\
        <input type=\"submit\" name=\"anim\" value=\"explosion\">\
        <input type=\"submit\" name=\"anim\" value=\"cylon\">\
        <input type=\"submit\" name=\"anim\" value=\"cylonVert\">\
        <input type=\"submit\" name=\"anim\" value=\"slowFade\">\
        <input type=\"submit\" name=\"anim\" value=\"weewoo\">\
        <input type=\"submit\" name=\"anim\" value=\"debug1\">\
        </form>\
    </div>\
    <div class=\"section\">\
        <h2>Palette</h2>\
        <form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/palette\">\
          <input type=\"submit\" name=\"palette\" value=\"random\">\
          <input type=\"submit\" name=\"palette\" value=\"blue\">\
          <input type=\"submit\" name=\"palette\" value=\"lava\">\
          <input type=\"submit\" name=\"palette\" value=\"forest\">\
          <input type=\"submit\" name=\"palette\" value=\"party\">\
          <input type=\"submit\" name=\"palette\" value=\"joker\">\
          <input type=\"submit\" name=\"palette\" value=\"bluePurp\">\
          <input type=\"submit\" name=\"palette\" value=\"royal\">\
          <input type=\"submit\" name=\"palette\" value=\"customF\">\
        </form>\
        <form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/updatePaletteCustomFixed\">\
          <input type=\"color\" name=\"color1\" value=\"%CUSTOM_FIXED_1%\">\
          <input type=\"color\" name=\"color2\" value=\"%CUSTOM_FIXED_2%\">\
          <input type=\"submit\" value=\"Update\">\
        </form>\
    </div>\
    <div class=\"section\">\
        <h2>Brightness</h2>\
        <form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/brightness\">\
        <input type=\"submit\" name=\"down\" value=\"-\">\
        <span>%BRIGHTNESS%</span>\
        <input type=\"submit\" name=\"up\" value=\"+\">\
        </form>\
    </div>\
    <div class=\"section\">\
        <h2>FPS</h2>\
        <form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/fps\">\
        <input type=\"submit\" name=\"down\" value=\"-\">\
        <span>%FPS%</span>\
        <input type=\"submit\" name=\"up\" value=\"+\">\
        </form>\
    </div>\
    <div class=\"section\">\
        <h2>System</h2>\
        <form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/system\">\
          <input type=\"submit\" name=\"off\" value=\"off\">\
          <span>%SYSTEM_ON%</span>\
          <input type=\"submit\" name=\"on\" value=\"on\">\
        </form>\
    </div>\
  </body>\
</html>";

String htmlProcessor(const String &var)
{
  if (var == "MESSAGE")
    return message;
  if (var == "BRIGHTNESS")
    return String(BRIGHTNESS);
  if (var == "FPS")
    return String(FRAMES_PER_SECOND);
  if (var == "SYSTEM_ON")
    return String(SYSTEM_ON ? "on" : "off");
  if (var == "CUSTOM_FIXED_1")
    return toHexString(customFixed1);
  if (var == "CUSTOM_FIXED_2")
    return toHexString(customFixed2);
  return String();
}

void handleRoot(AsyncWebServerRequest *request)
{
  request->send_P(200, "text/html", htmlTemplate, htmlProcessor);
  message[0] = 0;
}

void handleNotFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Not found");
}

void handleAnim(AsyncWebServerRequest *request)
{
  String value = request->getParam("anim", true)->value();
  sprintf(changeAnimationValue, "%s", value);
  sprintf(message, "Changed animation to %s", value);
  changeAnimation = true;

  request->redirect("/");
}

void handlePal(AsyncWebServerRequest *request)
{
  String value = request->getParam("palette", true)->value();
  sprintf(changePaletteValue, "%s", value);
  sprintf(message, "Changed palette to %s", value);
  changePalette = true;
  request->redirect("/");
}

void handleBrightness(AsyncWebServerRequest *request)
{
  if (request->hasParam("up", true))
  {
    BRIGHTNESS += 25;
    if (BRIGHTNESS > 255)
      BRIGHTNESS = 255;
  }
  if (request->hasParam("down", true))
  {
    BRIGHTNESS -= 25;
    if (BRIGHTNESS < 0)
      BRIGHTNESS = 0;
  }
  request->redirect("/");
}

void handleFps(AsyncWebServerRequest *request)
{
  if (request->hasParam("up", true))
  {
    FRAMES_PER_SECOND += 10;
    if (FRAMES_PER_SECOND > 255)
      FRAMES_PER_SECOND = 255;
  }
  if (request->hasParam("down", true))
  {
    FRAMES_PER_SECOND -= 10;
    if (FRAMES_PER_SECOND < 0)
      FRAMES_PER_SECOND = 0;
  }
  request->redirect("/");
}

String toHexString(CRGB color) {
    // r, g, b -> "#RRGGBB"
    char output[8];
    sprintf(output,"#%02X%02X%02X", color.r, color.g, color.b);
    return String(output);
}

void handleUpdatePalCustomFixed(AsyncWebServerRequest *request)
{
  String color1str = "0x" + request->getParam("color1", true)->value().substring(1);
  String color2str = "0x" + request->getParam("color2", true)->value().substring(1);

  customFixed1 = CRGB(strtol(color1str.c_str(), NULL, 16));
  customFixed2 = CRGB(strtol(color2str.c_str(), NULL, 16));
  changeCustomFixedColor = true;

  sprintf(message, "Changed custom palette to %s %s", color1str, color2str);
  request->redirect("/");
}

void handleSystem(AsyncWebServerRequest *request)
{
  if (request->hasParam("on", true))
  {
    SYSTEM_ON = true;
    sprintf(message, "System turned on");
  }
  if (request->hasParam("off", true))
  {
    SYSTEM_ON = false;
    sprintf(message, "System turned off");
  }
  request->redirect("/");
}

void http_server_setup()
{
  server.on("/", HTTP_GET, handleRoot);
  server.on("/anim", HTTP_POST, handleAnim);
  server.on("/palette", HTTP_POST, handlePal);
  server.on("/updatePaletteCustomFixed", HTTP_POST, handleUpdatePalCustomFixed);
  server.on("/brightness", HTTP_POST, handleBrightness);
  server.on("/fps", HTTP_POST, handleFps);
  server.on("/system", HTTP_POST, handleSystem);
  server.on("/system", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", String(SYSTEM_ON));
  });

  server.onNotFound(handleNotFound);
  server.begin();
  debug_println("HTTP server started");
}

void http_server_loop()
{
}
