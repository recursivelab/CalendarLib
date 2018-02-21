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

#include "juliancalendar.h"
#include "euclidean.h"
#include "monthlengths.h"

bool JulianCalendar::valid(Date date) const {
  if (date.month < 1 || date.month > 12 || date.day < 1 ||
      date.day > monthLengths[date.month]) {
    return false;
  }

  if (date.month == 2 && date.day == 29) {
    return leap(date.year);
  }

  return true;
}

int JulianCalendar::jdn(Date date) const {
  date.month -= 3;

  if (date.month < 0) {
    date.month += 12;
    --date.year;
  }

  int result = quotientAndReminder(date.year, 4) * 1461;

  result += date.year * 365;

  return result + date.day + elapsedDays[date.month] + 1721117;
}

Date JulianCalendar::date(int jdn) const {
  Date result;

  jdn -= 1721117;
  result.year = quotientAndReminder(jdn, 1461) * 4;
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

bool JulianCalendar::leap(int year) const { return (year & 3) == 0; }

int JulianCalendar::easter(int year) const {
  return firstFrom(jdn(Date(year, 3, 22)) + (15 + year % 19 * 19) % 30, SUNDAY);
}

JulianCalendar &JulianCalendar::instance() {
  static JulianCalendar object;

  return object;
}
