#pragma once
#include "EEPROM.h"
#include "stdint.h"
#include "Clock.h"

const int EST_OFFSET = -(5*3600); // note, this offset is in seconds
const int EDT_OFFSET = -4;
const int EEPROMSize = 18; //18 bits required to display the maximum time, will be changed to include date later
unsigned long epochTime;

Clock::Clock(): timeClient(ntpUDP, EST_OFFSET) {
    timeClient.begin();
    // EEPROM.begin(EEPROMSize);
    
    // daylightSavings = EEPROM.read(daylightSavingsMemoryAdress);
    
    // char* arrWeekDays[] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    // weekday = arrWeekDays[EEPROM.read(EEPROMHoursAddress)];
    
    // day = EEPROM.read(EEPROMDayAddress);
    // month = EEPROM.read(EEPROMMonthAddress);
    // year = EEPROM.read(EEPROMYearAddress);
    // hours = EEPROM.read(EEPROMHoursAddress);
    // minutes = EEPROM.read(EEPROMMinutesAddress);
    // seconds = EEPROM.read(EEPROMSecondsAddress);
    // EEPROM.end();
}

bool Clock::isLeapYear(int year) { 
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
char* Clock::getMonthName(int intMonth) {
    char* monthNames[] = {
        "January", "February", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December"
    };
    return monthNames[intMonth -1];
}

bool Clock::update() {
    if (timeClient.update()) {
        unsigned long epochTime = timeClient.getEpochTime();
        this->epochTimeMillis = epochTime * 1000ULL;
        calculateTimeAndDate(this->epochTimeMillis);
        
        Serial.print("Updated time: ");
        Serial.print(this->hours);
        Serial.print(":");
        Serial.print(this->minutes);
        Serial.print(":");
        Serial.println(this->seconds);

        Serial.print("Updated date: ");
        Serial.print(this->day);
        Serial.print("/");
        Serial.print(this->month);
        Serial.print("/");
        Serial.println(this->year);
        char suffix[3];
        
        if (this->day % 10 == 1) { // Check to see what the last digit of the int is
            strcpy(suffix, "st");
        }
        else if (this->day % 10 == 2) {
            strcpy(suffix, "nd");
        }
        else if (this->day % 10 == 3) {
            strcpy(suffix, "rd");
        }
        else {
            strcpy(suffix, "th");
        }

        char sentence[20];
        sprintf(sentence, "%s, %s %d%s, %d", this->weekday, getMonthName(this->month), this->day, suffix, this->year);
        Serial.println(sentence);
        return true;

    }
    else {
        Serial.println("Did not receive packet from NTP client.");
        return false;
    }
}

void Clock::calculateTimeAndDate(unsigned long long epochTimeMillis) {
    unsigned long epochTime = epochTimeMillis/1000ULL; // converts from milliseconds to seconds to do

    int year, month, day, hours, minutes, seconds;
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // Time stuff
    int totalSeconds = epochTime % (60 * 60 * 24);
    
    this->seconds = totalSeconds % 60;
    totalSeconds /= 60;

    this->minutes = totalSeconds % 60;
    totalSeconds /= 60;

    this->hours = totalSeconds;

    // Date stuff
    int days = epochTime / (60 * 60 * 24); // floors, which is what we want
    

    for (year = 1970; days >= 365; year++) {
        days -= (isLeapYear(year) ? 366 : 365);
    }
    int totalDays = days;
    this->year = year;

    for (month = 1; month <= 12; month++) {
        int daysInThisMonth = (month == 2 && isLeapYear(year)) ? 29 : daysInMonth[month]; 
        if (days <= daysInThisMonth) {
            this->day = days + 1;
            break;
        }
        days -= daysInThisMonth;
    }
    this->month = month;

    // check for daylight savings
    int extraDay = isLeapYear(year) ? 1 : 0;
    if ((totalDays >= 69 + extraDay) && (totalDays <= 307 + extraDay))  {
      this->hours++;
    }

    // weekday stuff
    if (month < 3) {
        month += 12;
        day -= 1;
    }
        
    int k = year % 100;
    int j = year / 100;
    
    this->intWeekday = (day + 13 * (month + 1) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;
    char* arrWeekDays[] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    
    this->weekday = arrWeekDays[intWeekday];
}


void Clock::addTime(unsigned long long deltaMillis) {
    this->epochTimeMillis += deltaMillis;
    calculateTimeAndDate(this->epochTimeMillis);
}


char* Clock::getFormattedTime() {
    char formattedTime[9];
    sprintf(formattedTime, "%02d:%02d:%02d", hours, minutes, seconds); // 02 meaning that it should be 2 chars long (5 -> 05)
    char* formattedTimeCHAR = new char[strlen(formattedTime) + 1];
    strcpy(formattedTimeCHAR, formattedTime);
    return formattedTimeCHAR;
}

char* Clock::getFormattedDate() {
    char formattedDate[20]; // Enough space for "Month Day, Year" + null terminator
    sprintf(formattedDate, "%02d/%02d/%04d", month, day, year);
    char* formattedDateCHAR = new char[strlen(formattedDate) + 1]; // will i need to free memory for this? to ensure no memory leaks
    strcpy(formattedDateCHAR, formattedDate);
    return formattedDateCHAR;
}