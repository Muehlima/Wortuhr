# Wortuhr

This project is a "word clock" which shows the time in words by using a microcontroller adressing LED's.


## Used Hardware
- WeMos D1 mini ESP8266 Board
- RTC Module
- RGBW LED 30 LEDS/m (SK6812)

## Installing / Getting started

1. **Clone the Repository**
    ```sh
    git clone https://github.com/muehlima/wortuhr.git
    cd wortuhr
    ```

2. **Install Dependencies**
    - Install the CH340 Driver (https://www.wemos.cc/en/latest/ch340_driver.html)
    
    Make sure you have the required libraries installed in your Arduino IDE:
    - Adafruit NeoPixel (https://github.com/adafruit/Adafruit_NeoPixel)
    - Adafruit RTClib (https://github.com/adafruit/RTClib)
    - Adafruit BusIO (https://github.com/adafruit/Adafruit_BusIO)

3. **Add Microcontroller to Arduino IDE**
    - Add additional Boards under `File=>Preferences=>Additional Boards Manager` and add the following URL:
        ```
        http://arduino.esp8266.com/stable/package_esp8266com_index.json
        ```
    - Next you can go to `Tools=>Boards=>Boards Manager` and under `ESP8266` you can chose `WeMos D1 R2 & mini` or what microcontroller you may have

4. **WiFi Credentials**
    - Change file name from `secrets_example.h`to `secrets.h`
    - Add WiFi credentials to `secrets.h`

## Features

- Connects to WiFi and gets current time from ntp server

### Planned features:

The following features are planned ideas but may change or be canceled without any fixed timeline.
- Add Buttons 
    - for local configuration of time (lose WiFi dependency)
    - change settings, like brightness and color
- Support for light sensor and dynamic brightness
- Support for DCF77 time signal reception
- Add Server functionality and use WiFi as AP
    - Add Desktop client for configuration
    - Add Mobile client for configuration
- ...

## Links

- Repository: https://github.com/muehlima/wortuhr/
- Issue tracker: https://github.com/muehlima/wortuhr/issues

## Licensing

This project is licensed under the GNU General Public License v3.0 or later.

See [COPYING](./COPYING) to see the full text.

## Contributors

Michael Mühlemann

Bern, 27.12.2024