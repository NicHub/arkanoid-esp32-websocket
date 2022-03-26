/**
 * ARKANOID ON ESP32
 *
 * Copyright (C) 2019, GPL-3.0-or-later, Nicolas Jeanmonod, ouilogique.com
 */

#include <Arduino.h>
#include <WebServerApp.h>
#include <Arkanoid.h>

AsyncWebSocket ws("/ws");
AsyncWebServer server(80);
AsyncEventSource events("/events");

/**
 *
 */
void setup()
{
    setupSerial();
    printCompilationDateAndTime();
    setupButtons();
    scanNetwork();
    setupWebServer();
}

/**
 *
 */
void loop()
{
    ArduinoOTA.handle();
    play();
}
