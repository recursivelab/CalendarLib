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

#ifndef EUCLIDEAN_H
#define EUCLIDEAN_H

inline int remainder(int a, int b) {
  if (a >= 0) {
    return a % b;
  }

  return b - 1 - (-++a) % b;
}

inline int quotient(int a, int b) {
  if (a >= 0) {
    return a / b;
  }

  return -1 - (-++a) / b;
}

inline int quotientAndReminder(int &a, int b) {
  if (a >= 0) {
    int q = a / b;

    a -= q * b;

    return q;
  }

  int q = -1 - (-a - 1) / b;

  a -= q * b;

  return q;
}

#endif // EUCLIDEAN_H
