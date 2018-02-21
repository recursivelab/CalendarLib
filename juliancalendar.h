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

#ifndef JULIANCALENDAR_H
#define JULIANCALENDAR_H

#include "christiancalendar.h"

class JulianCalendar : public ChristianCalendar {
public:
  bool valid(Date date) const;
  int jdn(Date date) const;
  Date date(int jdn) const;
  bool leap(int year) const;
  int easter(int year) const;
  static JulianCalendar &instance();
};

#define JULIAN_CALENDAR (JulianCalendar::instance())

#endif // JULIANCALENDAR_H
