/*
Project:  DS3231 RTC - Alarm
Author:   Thomas Edlinger for www.edistechlab.com
Date:     Created 08.02.2023
Version:  V1.0
IDE:      Arduino IDE 2.0.3
 
Required Board (Tools -> Board -> Boards Manager...)
 - Board: esp8266 by ESP8266 Community   V3.1.1 

Required libraries (sketch -> include library -> manage libraries)
 - Adafruit RTClib library V2.1.1 / https://github.com/adafruit/RTClib
 - Adafruit BusIO library V1.13.2 / https://github.com/adafruit/Adafruit_BusIO

Wirering for the DS3231 RTC Modul:
DS3231      Wemos d1 mini    
VCC         3.3V          
GND         GND       
SCL         D1/5    
SDA         D2/4     
SQW         D4/2
*/

#include <NTPClient.h>
#include "RTClib.h"
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include "secrets.h"

// Required for LIGHT_SLEEP_T delay mode
extern "C"
{
#include "user_interface.h"
}

#define FPM_SLEEP_MAX_TIME           0xFFFFFFF
#define LIGHT_WAKE_PIN D7

WiFiUDP ntpUDP;

// You can specify the time server pool and the offset (GMT+1), (in seconds)
// additionally you can specify the update interval (in milliseconds).
// NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);
NTPClient timeClient(ntpUDP, "ch.pool.ntp.org", 3600, 60000);

RTC_DS3231 rtc;
const uint8_t alarmPin = D4;




void callback() {
  Serial.println("Callback");
  Serial.flush();
}

void setup () {
  Serial.begin(115200);
  if (! rtc.begin()) {
    Serial.println("Finde keine RTC");
    while (true);
  }
  
  //we don't need the 32K Pin, so disable it
  rtc.disable32K();

  //Alarm register löschen und beide Alarme vorerst ausschalten  
  rtc.disableAlarm(1);
  rtc.disableAlarm(2);
  rtc.clearAlarm(1);
  rtc.clearAlarm(2);  
  rtc.writeSqwPinMode(DS3231_OFF);
  Serial.println("Cleared Alarms");


   // Begin WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  // Connecting to WiFi...
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

  // pinMode(alarmPin, INPUT_PULLUP);
  // attachInterrupt(digitalPinToInterrupt(alarmPin), onAlarmIntPin, FALLING);
  pinMode(LIGHT_WAKE_PIN, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  gpio_init(); // Initilise GPIO pins

  // Alarm 1 und 2 setzen
  // rtc.setAlarm1(rtc.now() + TimeSpan(0, 0, 0, 10), DS3231_A1_PerSecond); // löst jede Sekunde von jetzt plus 10 Sek. aus.
  //rtc.setAlarm2(DateTime(0, 0, 0, 21, 41, 0), DS3231_A2_Hour);  // löst um 21:41:00 aus
  rtc.setAlarm2(rtc.now() , DS3231_A2_PerMinute);  // löst jede Minute aus

  Serial.println("Setup complete");
}

void loop () {
  //if(rtc.alarmFired(1)) {
     //rtc.clearAlarm(1);
     //Serial.println("Alarm 1 ausgelöst über alarmFired Register");
   //  Serial.println();
   //}

  Serial.println("Start loop");
  Serial.print("Current time: ");
  char buf1[] = "DD.MMM.YYYY-hh:mm:ss";
  Serial.println(rtc.now().toString(buf1));
  Serial.println();

  
  Serial.print("NTP time: ");
  Serial.println(timeClient.getFormattedTime());

  if(rtc.alarmFired(2)) {
    rtc.clearAlarm(2);
    Serial.println("Alarm 2 ausgelöst über alarmFired Register");
    //Formatierung vom Datum und der Zeit
    char buf1[] = "DD.MMM.YYYY-hh:mm:ss";
    Serial.println(rtc.now().toString(buf1));
    Serial.println();
  }


   // Light sleep mode 
  Serial.println("Enter light sleep mode");
  Serial.flush();
  gpio_pin_wakeup_enable(GPIO_ID_PIN(LIGHT_WAKE_PIN), GPIO_PIN_INTR_LOLEVEL);
  wifi_set_opmode(NULL_MODE);
  wifi_fpm_set_sleep_type(LIGHT_SLEEP_T);
  wifi_fpm_open();
  //wifi_fpm_set_wakeup_cb(callback);
  wifi_fpm_do_sleep(FPM_SLEEP_MAX_TIME);
  delay(1000);

  Serial.println("Exit light sleep mode");



}

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
