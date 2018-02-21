#include "christiancalendar.h"

int ChristianCalendar::months(int) const { return 12; }

int ChristianCalendar::daysInMonth(int month, int year) const {
  static const int monthLengths[13] = {0,  31, 29, 31, 30, 31, 30,
                                       31, 31, 30, 31, 30, 31};

  if (month < 1 || month > 12) {
    return 0;
  }

  if (month != 2) {
    return monthLengths[month];
  }

  if (leap(year)) {
    return 29;
  }

  return 28;
}

int ChristianCalendar::daysInYear(int year) const {
  if (leap(year)) {
    return 366;
  }

  return 365;
}
