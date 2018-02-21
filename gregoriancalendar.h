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

#ifndef GREGORIANCALENDAR_H
#define GREGORIANCALENDAR_H

#include "christiancalendar.h"

class GregorianCalendar : public ChristianCalendar {
public:
  bool valid(Date date) const;
  int jdn(Date date) const;
  Date date(int jdn) const;
  bool leap(int year) const;
  int easter(int year) const;
  static GregorianCalendar &instance();
};

#define GREGORIAN_CALENDAR (GregorianCalendar::instance())

#endif // GREGORIANCALENDAR_H
