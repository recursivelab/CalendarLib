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

#include "gregoriancalendar.h"
#include "euclidean.h"
#include "juliancalendar.h"
#include "monthlengths.h"

bool GregorianCalendar::valid(Date date) const {
  if (date.year < 1582) {
    return JULIAN_CALENDAR.valid(date);
  }

  if (date.month < 1 || date.month > 12 || date.day < 1 ||
      date.day > monthLengths[date.month]) {
    return false;
  }

  if (date.month == 2 && date.day == 29) {
    return leap(date.year);
  }

  if (date.year < 1582) {
    return false;
  }

  if (date.year == 1582) {
    if (date.month == 10) {
      return date.day >= 15;
    }

    return date.month > 10;
  }

  return true;
}

int GregorianCalendar::jdn(Date date) const {
  bool julian;

  if (date.year != 1582) {
    julian = date.year < 1582;
  } else if (date.month != 10) {
    julian = date.month < 10;
  } else {
    julian = date.day <= 4;
  }

  if (julian) {
    return JULIAN_CALENDAR.jdn(date);
  }

  date.month -= 3;

  if (date.month < 0) {
    date.month += 12;
    --date.year;
  }

  int result = date.day + elapsedDays[date.month] + 1721119;

  result += quotientAndReminder(date.year, 400) * 146097;
  result += quotientAndReminder(date.year, 100) * 36524;
  result += quotientAndReminder(date.year, 4) * 1461;
  result += date.year * 365;

  return result;
}

Date GregorianCalendar::date(int jdn) const {
  if (jdn <= 2299160) {
    return JULIAN_CALENDAR.date(jdn);
  }

  Date result;

  jdn -= 1721119;
  result.year = quotientAndReminder(jdn, 146097) * 400;
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

bool GregorianCalendar::leap(int year) const {
  if ((year & 3) != 0) {
    return false;
  }

  return (year < 1582) || (year % 100 != 0) || (year % 400 == 0);
}

int GregorianCalendar::easter(int year) const {
  if (year <= 1582) {
    return JULIAN_CALENDAR.easter(year);
  }

  int a = remainder(year, 19);
  int b = quotient(year, 100);
  int c = year - b * 100;
  int d = quotient(b, 4);
  int e = b - d * 4;
  int f = quotient(b + 8, 25);
  int g = quotient(b - f + 1, 3);
  int h = remainder(19 * a + b - d - g + 15, 30);
  int i = c >> 2;
  int k = c & 0x3;
  int l = remainder(4 + ((e + i) << 1) - h - k, 7);
  int result = jdn(Date(year, 3, 22)) + h + l;

  if (a + 11 * h + 22 * l > 450) {
    result -= 7;
  }

  return result;
}

GregorianCalendar &GregorianCalendar::instance() {
  static GregorianCalendar object;

  return object;
}
