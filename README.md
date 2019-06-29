
# A R K A N O I D    O N    E S P 3 2

Play Arkanoid on a web page served by an ESP32.

The GUI is served to a browser on a desktop computer or a smartphone and you can move the cursor with two physical buttons attached to the ESP. A third button enters automatic mode, i.e. the cursor move automaticaly all the time.

It is also possible to play with a mouse or a touch screen, so if you only want to make a quick test, it is possible even without connecting buttons to the ESP.

The idea behind this project was to test the [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer/blob/master/README.md) library, especially the communication through websocket.

This program was tested with an *esp32doit-devkit-v1* and an *ESP32 M5Stack Core*.

It must be compiled with PlatformIO.

The game engine is written in JavaScript with the [threejs](https://threejs.org) library. I reused their example at <https://threejs.org/editor/> (click on `Examples/Arkanoid` in the top left menu and then on `Play`).

<p align="center">
<img height=400px alt="Arkanoid on ESP32" src="images/arkanoid.jpg" />
</p>


## Prerequisites

- Create the file `src/WifiSettings.h` manualy and fill it with the code below. Change the default values so that they make sense.

<pre><code>const char *ssid = "...";
const char *password = "...";
const char *hostName = "arkanoid";
const char *http_username = "admin";
const char *http_password = "admin";</code></pre>

- Change the board type (`env_default` flag) in `platformio.ini`. Currently there are two boards defined, but any ESP32 should work.

So if you have a regular ESP32 the `env_default` flag should be:

    env_default = esp32doit-devkit-v1

If you have a M5STACK, it should be

    env_default = m5stack-core-esp32

- The Arkanoid game will be served by the ESP32. So you need to upload the files by running the command below ina terminal so that the ESP32 can serve them to the browser:

<pre><code>platformio run --target uploadfs</code></pre>

- If you want to control the game from the ESP, you need to connect three buttons to it. Change `BUTTON_A_PIN`, `BUTTON_B_PIN` and `BUTTON_C_PIN` in `platformio.ini` according to the pins to which you have connected the buttons.

# Dependencies

Dependencies are defined under `lib_deps` in `platformio.ini` and are therefore automatically downloaded by PlatformIO when you open the project or when you build it.

I used the following example to make the [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer/blob/master/README.md) library work:
<https://gist.github.com/dsteinman/f792f0af25ce6d7d1db4b62d29dd4d9e>

2019, ouilogique.com
