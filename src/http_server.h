#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "settings.h"

ESP8266WebServer server(80);

char message[100];

const char htmlTemplate[] PROGMEM = "\
           <html>\
  <head>\
    <title>Bestagons!</title>\
    <style>\
      html, body { background-color: #35393b; color: #7aabff; padding: 10px; margin: 0; }\
      input[type=\"submit\"] {width: 100px; padding: 10px; background-color: #181a1b; color: #e8e6e3; }\
      .section {background: #222; padding: 5px; margin-bottom:10px;}\
      .message {background: #404b5f; color: #e8e6e3; padding: 5px;}\
    </style>\
  </head>\
  <body>\
    <h1>Bestagons!</h1>\
    <p class=\"message\">%s</p>\
    <div class=\"section\">\
        <h2>Change Animation</h2>\
        <form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/anim\">\
        <input type=\"submit\" name=\"anim\" value=\"random\">\
        <input type=\"submit\" name=\"anim\" value=\"travelers\">\
        <input type=\"submit\" name=\"anim\" value=\"orbit\">\
        <input type=\"submit\" name=\"anim\" value=\"sparkles\">\
        <input type=\"submit\" name=\"anim\" value=\"explosion\">\
        </form>\
    </div>\
    <div class=\"section\">\
        <h2>Change Palette</h2>\
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
        <h2>Change Brightness</h2>\
        <form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/brightness\">\
        <input type=\"submit\" name=\"down\" value=\"-\">\
        <span>%i</span>\
        <input type=\"submit\" name=\"up\" value=\"+\">\
        </form>\
    </div>\
    <div class=\"section\">\
        <h2>Change FPS</h2>\
        <form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/fps\">\
        <input type=\"submit\" name=\"down\" value=\"-\">\
        <span>%i</span>\
        <input type=\"submit\" name=\"up\" value=\"+\">\
        </form>\
    </div>\
  </body>\
</html>";

void handleRoot() {
  char buffer[2300];
  sprintf_P(buffer, htmlTemplate, message, BRIGHTNESS, FRAMES_PER_SECOND);
  server.send(200, "text/html", buffer);
    message[0] = 0;
}

void handleNotFound() {
  String output = "File Not Found\n\n";
  output += "URI: ";
  output += server.uri();
  output += "\nMethod: ";
  output += (server.method() == HTTP_GET) ? "GET" : "POST";
  output += "\nArguments: ";
  output += server.args();
  output += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    output += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", output);
}

void changeAnim() {
  if (server.method() != HTTP_POST) {
    server.send(405, "text/plain", "Method Not Allowed");
  } else {
    changeAnimation = true;
    for (uint8_t i = 0; i < server.args(); i++) {
        if (server.argName(i) == "anim")
        {
            sprintf(changeAnimationValue, "%s", server.arg(i));
            sprintf(message, "Changed animation to %s", server.arg(i));
        }
    }
    server.sendHeader("Location", String("/"), true);
    server.send ( 302, "text/plain", "");
  }
}

void changePal() {
  if (server.method() != HTTP_POST) {
    server.send(405, "text/plain", "Method Not Allowed");
  } else {
    changePalette = true;
    for (uint8_t i = 0; i < server.args(); i++) {
        if (server.argName(i) == "palette")
        {
            sprintf(changePaletteValue, "%s", server.arg(i));
            sprintf(message, "Changed palette to %s", server.arg(i));
        }
    }
    server.sendHeader("Location", String("/"), true);
    server.send ( 302, "text/plain", "");
  }
}

void changeBrightness() {
  if (server.method() != HTTP_POST) {
    server.send(405, "text/plain", "Method Not Allowed");
  } else {
    for (uint8_t i = 0; i < server.args(); i++) {
        if (server.argName(i) == "up")
        {
            BRIGHTNESS += 10;
            if (BRIGHTNESS > 255) BRIGHTNESS = 255;
        }
        if (server.argName(i) == "down")
        {
            BRIGHTNESS -= 10;
            if (BRIGHTNESS < 0) BRIGHTNESS = 0;
        }
    }
    server.sendHeader("Location", String("/"), true);
    server.send ( 302, "text/plain", "");
  }
}

void changeFps() {
  if (server.method() != HTTP_POST) {
    server.send(405, "text/plain", "Method Not Allowed");
  } else {
    for (uint8_t i = 0; i < server.args(); i++) {
        if (server.argName(i) == "up")
        {
            FRAMES_PER_SECOND += 10;
            if (FRAMES_PER_SECOND > 255) FRAMES_PER_SECOND = 255;
        }
        if (server.argName(i) == "down")
        {
            FRAMES_PER_SECOND -= 10;
            if (FRAMES_PER_SECOND < 0) FRAMES_PER_SECOND = 0;
        }
    }
    server.sendHeader("Location", String("/"), true);
    server.send ( 302, "text/plain", "");
  }
}


void http_server_setup() {
  server.on("/", handleRoot);
  server.on("/anim", changeAnim);
  server.on("/palette", changePal);
  server.on("/brightness", changeBrightness);
  server.on("/fps", changeFps);
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  server.onNotFound(handleNotFound);
  server.begin();
  debug_println("HTTP server started");
}

void http_server_loop() {
  server.handleClient();
}
