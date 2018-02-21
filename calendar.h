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

#ifndef CALENDAR_H
#define CALENDAR_H

struct Date {
  int year;
  int month;
  int day;

  Date();
  Date(int year, int month, int day);

  bool operator==(const Date &other) const {
    return other.year == year && other.month == month && other.day == day;
  }

  bool operator!=(const Date &other) const {
    return operator==(other) == false;
  }

  int cmp(const Date &other) const {
    if (year != other.year) {
      return year < other.year ? -1 : 1;
    }

    if (month != other.month) {
      return month < other.month ? -1 : 1;
    }

    if (day != other.day) {
      return day < other.day ? -1 : 1;
    }

    return 0;
  }

  bool operator<(const Date &other) const { return cmp(other) < 0; }
};

class Calendar {
public:
  enum DayOfWeek {
    SUNDAY,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY
  };

  virtual ~Calendar();
  virtual bool valid(Date date) const = 0;
  virtual int jdn(Date date) const = 0;
  virtual Date date(int jdn) const = 0;
  virtual bool leap(int year) const = 0;
  virtual int months(int year) const = 0;
  virtual int daysInMonth(int month, int year) const = 0;
  virtual int daysInYear(int year) const = 0;
  static DayOfWeek dayOfWeek(int jdn);
  DayOfWeek dayOfWeek(Date date) const;
  static int firstFrom(int jdn, DayOfWeek dayOfWeek);
  static int firstAfter(int jdn, DayOfWeek dayOfWeek);
  static int lastTo(int jdn, DayOfWeek dayOfWeek);
  static int lastBefore(int jdn, DayOfWeek dayOfWeek);
};

#endif // CALENDAR_H
