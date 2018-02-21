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

#ifndef CHRISTIANCALENDAR_H
#define CHRISTIANCALENDAR_H

#include "calendar.h"

class ChristianCalendar : public Calendar {
public:
  virtual int easter(int year) const = 0;
  int months(int year) const override;
  int daysInMonth(int month, int year) const override;
  int daysInYear(int year) const override;
};

#endif // CHRISTIANCALENDAR_H
