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

#include "calendar.h"
#include "euclidean.h"

Date::Date() {}

Date::Date(int year, int month, int day) : year(year), month(month), day(day) {}

Calendar::~Calendar() {}

Calendar::DayOfWeek Calendar::dayOfWeek(int jdn) {
  return (DayOfWeek)remainder(--jdn, 7);
}

Calendar::DayOfWeek Calendar::dayOfWeek(Date date) const {
  return dayOfWeek(jdn(date));
}

int Calendar::firstFrom(int jdn, Calendar::DayOfWeek dayOfWeek) {
  int difference = dayOfWeek - Calendar::dayOfWeek(jdn);

  if (difference < 0) {
    difference += 7;
  }

  return jdn + difference;
}

int Calendar::firstAfter(int jdn, Calendar::DayOfWeek dayOfWeek) {
  int difference = dayOfWeek - Calendar::dayOfWeek(jdn);

  if (difference <= 0) {
    difference += 7;
  }

  return jdn + difference;
}

int Calendar::lastTo(int jdn, Calendar::DayOfWeek dayOfWeek) {
  int difference = dayOfWeek - Calendar::dayOfWeek(jdn);

  if (difference > 0) {
    difference -= 7;
  }

  return jdn + difference;
}

int Calendar::lastBefore(int jdn, Calendar::DayOfWeek dayOfWeek) {
  int difference = dayOfWeek - Calendar::dayOfWeek(jdn);

  if (difference >= 0) {
    difference -= 7;
  }

  return jdn + difference;
}
