#pragma once
#include "RTClib.h"

extern SettingsMemory settingsMemory;

RTC_DS1307 rtc;

char global_dateChar[10];

class Datetime {
  uint8_t _day = 1;
  uint16_t _year = 2025;
  uint8_t _month = 5;
  uint8_t _hour = 1;
  uint8_t _minute = 0;
  uint8_t _second = 0;
public:
  void clockInit() {
    rtc.begin();
    refresh();
  }
  void refresh() {
    _day = rtc.now().day();
    _year = rtc.now().year();
    _month = rtc.now().month();
    _hour = rtc.now().hour();
    _minute = rtc.now().minute();
    _second = rtc.now().second();
  }
  void saveHour(const uint8_t hour) {
    rtc.adjust(DateTime(
      _year,
      _month,
      _day,
      hour,
      _minute,
      _second
    ));
    refresh();
  }
  void saveMinute(const uint8_t minute) {
    rtc.adjust(DateTime(
      _year,
      _month,
      _day,
      _hour,
      minute,
      0
    ));
    refresh();
  }

  void saveYear(const uint16_t year) {
    rtc.adjust(DateTime(
      year,
      _month,
      _day,
      _hour,
      _minute,
      _second
    ));
    refresh();
  }

  void saveMonth(const uint8_t month) {
    rtc.adjust(DateTime(
      _year,
      month,
      _day > getMaxDays(month) ? getMaxDays(month) : _day,
      _hour,
      _minute,
      _second
    ));
    refresh();
  }

  void saveDay(const uint8_t day) {
    rtc.adjust(DateTime(
      _year,
      _month,
      day,
      _hour,
      _minute,
      _second
    ));
    refresh();
  }

  static char* getHourChar(const uint8_t hour) {
    if(settingsMemory.getDateHourType() == 1) {
      sprintf(global_dateChar, "%02d", hour);
      return global_dateChar;
    }

    uint8_t hour12 = hour % 12;
    if (hour12 == 0) {
      hour12 = 12;
    }

    sprintf(global_dateChar, "%u", hour12);
    return global_dateChar;
  }

  static char* getMinuteChar(const uint8_t minute) {
    sprintf(global_dateChar, "%02d", minute);

    return global_dateChar;
  }

  uint8_t getHour() const {
    return _hour;
  }
  uint8_t getMinute() const {
    return _minute;
  }

  static bool isTwoLevel(const uint8_t hour) {
    if(settingsMemory.getDateHourType() == 1) {
      return true;
    }
    uint8_t hour12 = hour % 12;
    if (hour12 == 0) {
      hour12 = 12;
    }

    return hour12 > 9;
  }

  bool static isTypeAm(const uint8_t hour) {
    return hour < 12;
  }

  const static char* getTypeHour(const uint8_t hour) {
    return hour >= 12 ? "PM" : "AM";
  }
  
  uint8_t getDay() const {
    return _day;
  }

  uint16_t getYear() const {
    return _year;
  }

  uint8_t getMonth() const {
    return _month;
  }

  static char* getYearChar(const uint16_t year) {
    sprintf(global_dateChar, "%u", year);
    return global_dateChar;
  }

  static char* getDayChar(const uint8_t day) {
    sprintf(global_dateChar, "%02d", day);
    return global_dateChar;
  }

  static char* getMonthNumericChar(const uint8_t month) {
    sprintf(global_dateChar, "%02d", month);
    return global_dateChar;
  }

  static char* getMonthChar(uint8_t month) {
    if (month > 12) month = 0;
    strncpy(global_dateChar, _translateMonths[month], sizeof(global_dateChar) - 1);
    global_dateChar[sizeof(global_dateChar) - 1] = '\0';
    return global_dateChar;
  }

  int getMaxDays(const uint8_t month) const {
    uint8_t maxDays = 31;

    if (month == 4 || month == 6 || month == 9 || month == 11) {
      maxDays = 30;
    } else if (month == 2) {
      if ((getYear() % 4 == 0 && getYear() % 100 != 0) || (getYear() % 400 == 0)) {
        maxDays = 29;
      } else {
        maxDays = 28;
      }
    }
    return maxDays;
  }
};
