#include <WiFi.h>     // For WiFi
#include "time.h"     // For time things
#include "RTClib.h"   // For DS3231 RTC Module, also DS1307, PCF8523, & PCF8563. https://github.com/adafruit/RTClib
#include <Wire.h>     // For I2C Communication (DS3231)

/****************************************************************************** 
 * Configure these variables
 * 
 * ssid
 *    Your WiFi SSID
 * 
 * password
 *    The password for your WiFi
 * 
 * UTCOffset
 *    The time zone you are in relative to UTC
 ******************************************************************************/
const char* ssid = "";
const char* password = "";
const int  UTCOffset = -4;


struct tm timeinfo;

RTC_DS3231 rtc;
//RTC_DS1307 rtc;
//RTC_PCF8523 rtc;
//RTC_PCF8563 rtc;

void setup()
{
  Serial.begin(115200);
  delay(1000);
  
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
  }
  
  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");
  
  configTime(0, 0, "pool.ntp.org");
  getLocalTime(&timeinfo);

  rtc.adjust(DateTime(mktime(&timeinfo)+UTCOffset*3600));
  
  printRTCTime();
}

void loop()
{
  printRTCTime();
  delay(10000);
}

void printRTCTime()
{
  DateTime now = rtc.now();
  
  Serial.print("RTC: ");
  Serial.printf("%02d/%02d/%04d (%02d:%02d:%02d)\n", now.month(), now.day(), now.year(), now.hour(), now.minute(), now.second());
}
