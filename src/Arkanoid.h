/**
 * A R K A N O I D    O N    E S P 3 2
 *
 * Copyright (C) 2019  Nicolas Jeanmonod, ouilogique.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include <WebServerApp.h>

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
