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

#include <WebServerApp.h>
#include <Arkanoid.h>

/**
 *
 */
void setup()
{
    setupM5STACKStart();
    setupSerial();
    setupButtons();
    scanNetwork();
    setupWebServer();
    printCompilationDateAndTime();
    setupM5STACKEnd();
}

/**
 *
 */
void loop()
{
    ArduinoOTA.handle();
    play();
}
