/**
 * https://www.oryx-embedded.com/doc/date__time_8h_source.html
 * @file date_time.h
 * @brief Date and time management
 *
 * @section License
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Copyright (C) 2010-2022 Oryx Embedded SARL. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * @author Oryx Embedded SARL (www.oryx-embedded.com)
 * @version 2.1.6
 **/

#ifndef _DATE_TIME_H
#define _DATE_TIME_H
#ifndef LSB
#define LSB(x) ((x)&0xFF)
#endif

#ifndef MSB
#define MSB(x) (((x) >> 8) & 0xFF)
#endif

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifndef arraysize
#define arraysize(a) (sizeof(a) / sizeof(a[0]))
#endif

// Dependencies
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// C++ guard
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Date and time representation
 **/

typedef struct {
  uint16_t year;
  uint8_t month;
  uint8_t day;
  uint8_t dayOfWeek;
  uint8_t hours;
  uint8_t minutes;
  uint8_t seconds;
  uint16_t milliseconds;
} DateTime;

typedef uint32_t systime_t;
typedef char char_t;
typedef signed int int_t;
typedef unsigned int uint_t;

// Date and time management
const char *formatSystemTime(systime_t time, char_t *str);
const char *formatDate(const DateTime *date, char_t *str);

void getCurrentDate(DateTime *date);
time_t getCurrentUnixTime(void);

void convertUnixTimeToDate(time_t t, DateTime *date);
time_t convertDateToUnixTime(const DateTime *date);

int_t compareDateTime(const DateTime *date1, const DateTime *date2);

uint8_t computeDayOfWeek(uint16_t y, uint8_t m, uint8_t d);

// C++ guard
#ifdef __cplusplus
}
#endif

#endif
