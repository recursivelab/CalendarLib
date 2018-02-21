/***************************************************************************
*                                                                          *
*   CalendarLib - the calendar application.                                *
*   Copyright (C) 2015 by Nedeljko Stefanovic.                             *
*                                                                          *
*   GNU All-Permissive License                                             *
*                                                                          *
*   Copying and distribution of this file, with or without modification,   *
*   are permitted in any medium without royalty provided the copyright     *
*   notice and this notice are preserved.  This file is offered as-is,     *
*   without any warranty.                                                  *
*                                                                          *
***************************************************************************/

#include "revisedjuliancalendar.h"
#include "euclidean.h"
#include "juliancalendar.h"
#include "monthlengths.h"

bool RevisedJulianCalendar::valid(Date date) const {
  if (date.year < 1582) {
    return false;
  }

  if (date.year == 1582) {
    if (date.month == 10) {
      return date.day >= 15;
    }

    return date.month > 10;
  }

  if (date.month < 1 || date.month > 12 || date.day < 1 ||
      date.day > monthLengths[date.month]) {
    return false;
  }

  if (date.month == 2 && date.day == 29) {
    return leap(date.year);
  }

  return true;
}

int RevisedJulianCalendar::jdn(Date date) const {
  date.month -= 3;

  if (date.month < 0) {
    date.month += 12;
    --date.year;
  }

  date.year += 200;

  int result = quotientAndReminder(date.year, 900) * 328718;

  result += quotientAndReminder(date.year, 400) * 146097;
  result += quotientAndReminder(date.year, 100) * 36524;
  result += quotientAndReminder(date.year, 4) * 1461;
  result += date.year * 365;

  return result + date.day + elapsedDays[date.month] + 1648346;
}

Date RevisedJulianCalendar::date(int jdn) const {
  Date result;

  jdn -= 1648346;
  result.year = -200;
  result.year += quotientAndReminder(jdn, 328718) * 900;
  result.year += quotientAndReminder(jdn, 146097) * 400;
  result.year += quotientAndReminder(jdn, 36524) * 100;
  result.year += quotientAndReminder(jdn, 1461) * 4;
  result.year += quotientAndReminder(jdn, 365);
  result.month = (5 * jdn - 3) / 153;
  result.day = jdn - elapsedDays[result.month];
  result.month += 3;

  if (result.month > 12) {
    result.month -= 12;
    ++result.year;
  }

  return result;
}

bool RevisedJulianCalendar::leap(int year) const {
  if ((year & 3) != 0) {
    return false;
  }

  if (year % 100 != 0) {
    return true;
  }

  year = remainder(year, 900);

  return year == 200 || year == 600;
}

int RevisedJulianCalendar::months(int) const { return 12; }

int RevisedJulianCalendar::daysInMonth(int month, int year) const {
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

int RevisedJulianCalendar::daysInYear(int year) const {
  if (leap(year)) {
    return 366;
  }

  return 365;
}

int RevisedJulianCalendar::easter(int year) const {
  return JULIAN_CALENDAR.easter(year);
}

RevisedJulianCalendar &RevisedJulianCalendar::instance() {
  static RevisedJulianCalendar object;

  return object;
}
