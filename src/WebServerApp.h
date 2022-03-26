/**
 * ARKANOID ON ESP32
 *
 * Copyright (C) 2019, GPL-3.0-or-later, Nicolas Jeanmonod, ouilogique.com
 */

#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <ArduinoOTA.h>
#include <FS.h>
#include <AsyncTCP.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>

extern AsyncWebServer server;
extern AsyncWebSocket ws;
extern AsyncEventSource events;

void onWsEvent(AsyncWebSocket *server,
               AsyncWebSocketClient *client,
               AwsEventType type,
               void *arg,
               uint8_t *data,
               size_t len);
void writeServerInfoToFile();
void setupWebServer();
void inverseBubbleSortIndexes(int inputArray[], int indexes[], int arraySize);
void scanNetwork();
