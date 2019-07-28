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

#ifdef BOARD_M5STACK_CORE_ESP32
#include <M5Stack.h>
#endif

/**
 *
 */
void setupM5STACKStart()
{
#ifdef BOARD_M5STACK_CORE_ESP32
    M5.begin(true, false, false, false);

    // Display IP adresses on M5STACK.
    M5.Lcd.setTextSize(3);
    M5.Lcd.fillScreen(BLACK);

    M5.Lcd.setTextColor(BLUE, BLACK);
    M5.Lcd.setCursor(20, 10);
    M5.Lcd.print("COMPILATION");

    M5.Lcd.setCursor(20, 40);
    M5.Lcd.print("DATE AND TIME");

    M5.Lcd.setTextColor(WHITE, BLACK);
    M5.Lcd.setCursor(20, 100);
    M5.Lcd.print(__DATE__);

    M5.Lcd.setCursor(20, 130);
    M5.Lcd.print(__TIME__);
#endif
}

/**
 *
 */
void setupM5STACKEnd()
{
#ifdef BOARD_M5STACK_CORE_ESP32
    M5.Lcd.fillScreen(BLACK);

    M5.Lcd.setTextColor(RED, BLACK);
    M5.Lcd.setCursor(20, 10);
    M5.Lcd.print("A R K A N O I D");

    M5.Lcd.setTextColor(WHITE, BLACK);
    M5.Lcd.setCursor(20, 60);
    M5.Lcd.print("STATION IP");

    M5.Lcd.setCursor(20, 100);
    M5.Lcd.print(WiFi.localIP());

    M5.Lcd.setCursor(20, 150);
    M5.Lcd.print("SOFT-AP IP");

    M5.Lcd.setCursor(20, 190);
    M5.Lcd.print(WiFi.softAPIP());
#endif
}

/**
 *
 */
void setupSerial()
{
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    delay(10);
    Serial.printf("START\n");
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
    Serial.print("###\ncompilation date and time:\n");
    Serial.print(__DATE__);
    Serial.print("\n");
    Serial.print(__TIME__);
    Serial.print("\n###\n\n");
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
