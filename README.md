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


## Features

TODO


## Links

TODO

- Project homepage: https://muehlima.github.com/wortuhr/
- Repository: https://github.com/muehlima/wortuhr/
- Issue tracker: https://github.com/muehlima/wortuhr/issues
  - In case of sensitive bugs like security vulnerabilities, please contact
    my@email.com directly instead of using issue tracker. We value your effort
    to improve the security and privacy of this project!

## Licensing

TODO



## Contributors

Michael Mühlemann

Bern, 21.12.2024