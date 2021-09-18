#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <WiFiClient.h>
#include <ESPAsyncWebServer.h>

#include "settings.h"

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
  changeAnimation = true;

  String value = request->getParam("anim", true)->value();
  sprintf(changeAnimationValue, "%s", value);
  sprintf(message, "Changed animation to %s", value);

  request->redirect("/");
}

void handlePal(AsyncWebServerRequest *request)
{
  changePalette = true;
  String value = request->getParam("palette", true)->value();
  sprintf(changePaletteValue, "%s", value);
  sprintf(message, "Changed palette to %s", value);
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



void http_server_setup()
{
  server.on("/", HTTP_GET, handleRoot);
  server.on("/anim", HTTP_POST, handleAnim);
  server.on("/palette", HTTP_POST, handlePal);
  server.on("/brightness", handleBrightness);
  server.on("/fps", handleFps);
  server.onNotFound(handleNotFound);
  server.begin();
  debug_println("HTTP server started");
}

void http_server_loop()
{
}
