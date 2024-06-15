#pragma once
#include "stdint.h"
#include <NTPClient.h> 
#include <WiFiUdp.h>

class Clock {
  private:
      WiFiUDP ntpUDP;
      NTPClient timeClient;
      
  public:
      unsigned long long epochTimeMillis;
    
      int hours;
      int minutes;
      int seconds;
      int year;
      int month;
      int day;
      int intWeekday;
      char* weekday;

      Clock();
      bool isLeapYear(int year);
      void calculateTimeAndDate(unsigned long long epochTimeMillis);
      bool update();
  
      void addTime(unsigned long long deltaMillis);

      char* getMonthName(int intMonth);
      char* getFormattedTime();
      char* getFormattedDate();
};
