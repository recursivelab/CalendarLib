/***************************************************************************
*                                                                          *
*   Calendar - the calendar application.                                   *
*   Copyright (C) 2013 by Nedeljko Stefanovic.                             *
*                                                                          *
*   This program is free software: you can redistribute it and/or modify   *
*   it under the terms of the GNU General Public License as published by   *
*   the Free Software Foundation version 3.                                *
*                                                                          *
*   This program is distributed in the hope that it will be useful,        *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
*   GNU General Public License for more details.                           *
*                                                                          *
*   You should have received a copy of the GNU General Public License      *
*   along with this program. If not, see <http://www.gnu.org/licenses/>.   *
*                                                                          *
***************************************************************************/

#include "euclidean.h"
#include "gregoriancalendar.h"
#include "juliancalendar.h"
#include "revisedjuliancalendar.h"
#include <iostream>

int main() {
  int trumpInauguration = GREGORIAN_CALENDAR.jdn(Date(2017, 1, 20));
  int trump100 = trumpInauguration + 100;
  Date result = GREGORIAN_CALENDAR.date(trump100);
  std::cout << "Trump\'s 100 days is at " << result.month << "." << result.day
            << "." << result.year << "." << std::endl;
  std::cout << GREGORIAN_CALENDAR.jdn(Date(2017, 9, 1)) << std::endl;

  return 0;
}
