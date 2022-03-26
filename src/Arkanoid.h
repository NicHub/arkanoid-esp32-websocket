/**
 * ARKANOID ON ESP32
 *
 * Copyright (C) 2019, GPL-3.0-or-later, Nicolas Jeanmonod, ouilogique.com
 */

#pragma once

#include <WebServerApp.h>

#if BOARD_TYPE==ESP32DOIT_DEVKIT_V1
#define BUTTON_A_PIN 0
#define BUTTON_B_PIN 2
#define BUTTON_C_PIN 15
#endif

/**
 *
 */
void setupSerial()
{
    Serial.begin(BAUD_RATE);
}

/**
 *
 */
void setupButtons()
{
    pinMode(BUTTON_A_PIN, INPUT_PULLUP);
    pinMode(BUTTON_B_PIN, INPUT_PULLUP);
    pinMode(BUTTON_C_PIN, INPUT_PULLUP);
}

/**
 *
 */
void printCompilationDateAndTime()
{
    Serial.println(F("\n\n\n# ARKANOID\n"));
    Serial.print(F("FILE NAME:        "));
    Serial.println(__FILE__);
    Serial.print(F("PIO PROJECT PATH: "));
    Serial.println(PIO_PROJECT_PATH);
    Serial.print(F("COMPILATION DATE: "));
    Serial.println(COMPILATION_DATE);
    Serial.print(F("COMPILATION TIME: "));
    Serial.println(COMPILATION_TIME);
    Serial.print(F("PYTHON VERSION:   "));
    Serial.println(PYTHON_VERSION);
    Serial.print(F("PYTHON PATH:      "));
    Serial.println(PYTHON_PATH);
    Serial.println("");
}

/**
 *
 */
void sendJSONcursorPos(int8_t cursorPos)
{
    static char jsonMsg[100];
    sprintf(jsonMsg, "{\"cpt\":{\"cpt1\":\"%d\",\"cpt2\":\"%d\"}}", cursorPos, 0);
    ws.textAll(jsonMsg);
}

/**
 *
 */
void autoPlay()
{
    if (!ws.enabled())
        return;

    const int8_t maxCursorPos = 7;
    static int8_t cursorPos = 0;
    const uint8_t wait = 30;
    static bool goLeft = true;

    if (goLeft)
    {
        Serial.print("<");
        cursorPos--;
        if (cursorPos < -maxCursorPos)
            goLeft = false;
        sendJSONcursorPos(cursorPos);
        delay(wait);
    }
    else
    {
        Serial.print(">");
        cursorPos++;
        if (cursorPos > maxCursorPos)
            goLeft = true;
        sendJSONcursorPos(cursorPos);
        delay(wait);
    }
}

/**
 *
 */
void manualPlay()
{
    if (!ws.enabled())
        return;

    const int8_t maxCursorPos = 7;
    static int8_t cursorPos = 0;
    const uint8_t wait = 60;

    if (!digitalRead(BUTTON_A_PIN))
    {
        Serial.println("Button A");
        cursorPos--;
        if (cursorPos < -maxCursorPos)
            cursorPos = -maxCursorPos;
        sendJSONcursorPos(cursorPos);
        delay(wait);
    }

    if (!digitalRead(BUTTON_C_PIN))
    {
        Serial.println("Button C");
        cursorPos++;
        if (cursorPos > maxCursorPos)
            cursorPos = maxCursorPos;
        sendJSONcursorPos(cursorPos);
        delay(wait);
    }
}

/**
 *
 */
void play()
{
    if (!ws.enabled())
        return;

    static uint8_t gameMode = 0;

    // Change game mode when button B is pressed.
    if (!digitalRead(BUTTON_B_PIN))
    {
        if (++gameMode > 1)
            gameMode = 0;
        Serial.print("game mode = ");
        Serial.println(gameMode);
        while (!digitalRead(BUTTON_B_PIN))
            yield();
    }

    // Play.
    if (gameMode == 0)
        manualPlay();
    else if (gameMode == 1)
        autoPlay();
}
