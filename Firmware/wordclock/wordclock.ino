/*
Project:  Wordclock
Author:   Michael Mühlemann
Date:     Created 26.12.2024
Version:  V0.1 (Prototype)
IDE:      Arduino IDE 2.0.3
*/



#include <Adafruit_NeoPixel.h>
// #ifdef __AVR__
//  #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
// #endif
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include "RTClib.h"
#include <WiFiUdp.h>

#include "secrets.h"  // Comment out if you do not use WiFi
#include "words.h"

// NeoPixel
// Which pin on the Arduino is connected to the NeoPixels?
#define LED_PIN     D6

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT   110  // Max Value 255 (uint8_t)

// NeoPixel brightness, 0 (min) to 255 (max)
#define BRIGHTNESS 50 // Set BRIGHTNESS to about 1/5 (max = 255)

// Declare NeoPixel strip object
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

// Sleep mode
// Required for LIGHT_SLEEP_T delay mode
extern "C"
{
#include "user_interface.h"
}
#define FPM_SLEEP_MAX_TIME    0xFFFFFFF
#define LIGHT_WAKE_PIN        D7  // D3 & D4 produce problems while flashing (D4 = FLASHPIN)

// RTC
RTC_DS3231 rtc;

// WiFi
bool wifi_on = true;
// #ifdef SECRETS_H
  
// #else
//   bool wifi_on = false;
// #endif

// NTPClient
// You can specify the time server pool and the offset (GMT+1), (in seconds)
// additionally you can specify the update interval (in milliseconds).
// NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ch.pool.ntp.org", 3600, 60000);

bool wifi_sleeping = false;

/*
-----------------------------------------------------------------------------------------
----------------------- SETUP -----------------------------------------------------------
-----------------------------------------------------------------------------------------
*/

void setup() {
  // --- Setup LEDs ---
  Serial.begin(115200);
  Serial.println();
  if (! rtc.begin()) {
    Serial.println("Finde keine RTC");
    while (true);
  }
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(BRIGHTNESS);
  Serial.println("Setup Complete");

  // --- SETUP RTC ---
  rtc.disable32K(); // we don't need the 32K Pin, so disable it
  //Alarm register löschen und beide Alarme vorerst ausschalten  
  rtc.clearAlarm(1);
  rtc.clearAlarm(2);  
  rtc.disableAlarm(1);
  rtc.disableAlarm(2);
  rtc.writeSqwPinMode(DS3231_OFF);
  Serial.println("Cleared Alarms");

  // --- SETUP WiFi ---
  if (wifi_on) {
    
    Serial.println("WiFi Setup");
    // Connecting to WiFi...
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to ");
    Serial.print(WIFI_SSID);
    // Loop continuously while WiFi is not connected
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(100);
      Serial.print(".");
    }

    // Connected to WiFi
    Serial.println();
    Serial.print("Connected! IP address: ");
    Serial.println(WiFi.localIP());

    timeClient.begin();
    update_rtc_time();
  }

  // Light sleep mode
  pinMode(LIGHT_WAKE_PIN, INPUT_PULLUP);

  // Alarm 1 und 2 setzen
  // löst jede Minute einen Alarm aus (55 Sekunden)
  rtc.setAlarm1(DateTime(0, 0, 0, 0, 19, 30), DS3231_A1_Minute); 
  // löst jede Minute aus
  rtc.setAlarm2(DateTime(0, 0, 0, 0, 0, 0), DS3231_A2_PerMinute);  

  Serial.println("Setup complete");
}
/*
-----------------------------------------------------------------------------------------
----------------------- MAIN ------------------------------------------------------------
-----------------------------------------------------------------------------------------
*/

void loop() {
  // Initialize variables for time words
  const Word* timeWords[10]; // Platz für 10 Wörter
  size_t wordCount;

  bool running = true;

  while (running) {
    // Check if the alarm to update the rtc time
    if(rtc.alarmFired(1)) {
      rtc.clearAlarm(1);
      Serial.println("Alarm 1 ausgelöst über alarmFired Register");
      Serial.println();
      update_rtc_time();
    }

    // Check if the alarm for new Time has been triggered (Every Minute)
    if(rtc.alarmFired(2)) {
      rtc.clearAlarm(2);
      Serial.println("Alarm 2 ausgelöst über alarmFired Register");
      Serial.println();

      // Build the words for the current time
      DateTime now = rtc.now();
      build_time_words(now.hour(), now.minute(), timeWords, &wordCount);
      show_time(timeWords, wordCount);
    }


    
    light_sleep();

    // TODO: Add buttons to change time

  }
 
}

// Build the words for the current time
void build_time_words(int hour, int minute, const Word *result[], size_t *wordCount)
{
  *wordCount = 0; // Zähler zurücksetzen

  // Always displayed "Es isch"
  result[(*wordCount)++] = &ESISCH; // "Es isch"

  // TODO: Implement the minutes in corners (Modulo 5)

  // Add minutes to the result
  switch (minute / 5)
  {
  case 1:
    result[(*wordCount)++] = &FUEF; // "Füf"
    result[(*wordCount)++] = &AB;   // "ab"
    break;
  case 2:
    result[(*wordCount)++] = &ZAEAE; // "Zäae"
    result[(*wordCount)++] = &AB;    // "ab"
    break;
  case 3:
    result[(*wordCount)++] = &VIURTU; // "Viertu"
    result[(*wordCount)++] = &AB;     // "ab"
    break;
  case 4:
    result[(*wordCount)++] = &ZWAENZG; // "Zwänzg"
    result[(*wordCount)++] = &AB;      // "ab"
    break;
  case 5:
    result[(*wordCount)++] = &FUEF; // "Füf"
    result[(*wordCount)++] = &VOR;  // "vor"
    result[(*wordCount)++] = &HAUBI; // "halb"
    break;
  case 6:
    result[(*wordCount)++] = &HAUBI; // "halb"
    break;
  case 7:
    result[(*wordCount)++] = &FUEF; // "Füf"
    result[(*wordCount)++] = &AB;   // "ab"
    result[(*wordCount)++] = &HAUBI; // "halb"
    break;
  case 8:
    result[(*wordCount)++] = &ZWAENZG; // "Zwänzg"
    result[(*wordCount)++] = &VOR;     // "vor"
    break;
  case 9:
    result[(*wordCount)++] = &VIURTU; // "Viertu"
    result[(*wordCount)++] = &VOR;    // "vor"
    break;
  case 10:
    result[(*wordCount)++] = &ZAEAE; // "Zäae"
    result[(*wordCount)++] = &VOR;   // "vor"
    break;
  case 11:
    result[(*wordCount)++] = &FUEF; // "Füf"
    result[(*wordCount)++] = &VOR;  // "vor"
    break;
  default:
    break;
  }

  // Add hour to the result
  if (minute >= 25) // From 25 minutes on, the next hour will be displayed (e.g. füf vor haubi eis)
  {
    hour++;
  }

  switch (hour % 12)
  {
  case 0:
    result[(*wordCount)++] = &ZWOEUFI;
    break; // "Zwoeufi"  
  case 1:
    result[(*wordCount)++] = &EIS;
    break; // "Eis"
  case 2:
    result[(*wordCount)++] = &ZWOEI;
    break; // "Zwoei"
  case 3:
    result[(*wordCount)++] = &DRUE;
    break; // "Drü"
  case 4:
    result[(*wordCount)++] = &VIERI;
    break; // "Vieri"
  case 5:
    result[(*wordCount)++] = &FUEFI;
    break; // "Füfi"
  case 6:
    result[(*wordCount)++] = &SAECHSI;
    break; // "Sächsi"
  case 7:
    result[(*wordCount)++] = &SIEBNI;
    break; // "Siebni"
  case 8:
    result[(*wordCount)++] = &ACHTI;
    break; // "Achti"
  case 9:
    result[(*wordCount)++] = &NUENI;
    break; // "Nueni"
  case 10:
    result[(*wordCount)++] = &ZAENI;
    break; // "Zaeni"
  case 11:
    result[(*wordCount)++] = &EUFI;
    break; // "Eufi"
  }
}

// Display the time on the wordclock
void show_time(const Word *words[], size_t wordCount) {
  // Initialize all LEDs to off
  strip.clear();
  strip.show();

  // Set LEDs for each word
  for (size_t i = 0; i < wordCount; i++) {
      const Word* word = words[i];
      for (size_t j = 0; j < word->size; j++) {
          strip.setPixelColor(word->word[j], strip.Color(0, 0, 0, 255)); // True white (not RGB white)
      } 
  }
  strip.show();
}

// Set the RTC time to the NTP time
void update_rtc_time() {
  // Set the date and time
  timeClient.update();
  unsigned long nowNTP = timeClient.getEpochTime();
  unsigned long nowRTC = rtc.now().unixtime();

  if (rtc.now().unixtime() != nowNTP) {
    Serial.println("Set new RTC time");
    rtc.adjust(DateTime(nowNTP));
  }
}

// Enter light sleep mode
void light_sleep() {
  Serial.println("Enter light sleep mode");
  Serial.flush();
  gpio_pin_wakeup_enable(LIGHT_WAKE_PIN, GPIO_PIN_INTR_LOLEVEL);
  wifi_set_opmode(NULL_MODE);
  wifi_fpm_set_sleep_type(LIGHT_SLEEP_T);
  wifi_fpm_open();
  wifi_fpm_do_sleep(FPM_SLEEP_MAX_TIME);
  delay(1000);
  Serial.println("Exit light sleep mode");
}
