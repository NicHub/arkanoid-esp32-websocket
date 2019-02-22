/**
 * A R K A N O I D    O N    E S P 3 2
 *
 * This program was tested with an ESP32 M5Stack Core
 * compiled with PlatformIO.
 *
 *
 * The web server files must be uploaded with the command:
 * platformio run --target uploadfs
 *
 *
 * You have to create `WifiSettings.h` manualy with the
 * following code:
 * const char *ssid = "...";
 * const char *password = "...";
 * const char *hostName = "...";
 * const char *http_username = "admin";
 * const char *http_password = "admin";
 *
 *
 * If needed, you’ll have to install "ESP Async WebServer"
 * pio lib install "ESP Async WebServer"
 *
 *
 * ESPAsyncWebServer
 * https://github.com/me-no-dev/ESPAsyncWebServer/blob/master/README.md
 *
 * ESPAsyncWebServer example
 * https://gist.github.com/dsteinman/f792f0af25ce6d7d1db4b62d29dd4d9e
 *
 *
 * February 2019, ouilogique.com
 *
 */

#include <WebServerApp.h>
#define LCD // Comment this line if you don’t have a M5Stack.
#ifdef LCD
#include <M5Stack.h>
#endif // LCD

void setup()
{
#ifdef LCD
  M5.begin();

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
#endif // LCD

  setupSerial();
  setupButtons();
  scanNetwork();
  setupWebServer();
  printCompilationDateAndTime();

#ifdef LCD
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
#endif // LCD
}

void loop()
{
  // Handle web server.
  ArduinoOTA.handle();

  // Change game mode when button B is pressed.
  static uint8_t gameMode = 0;
  if (!digitalRead(BUTTON_B_PIN))
  {
    gameMode = ++gameMode % 2;
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
