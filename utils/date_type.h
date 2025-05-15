/*
 * date_type.h
 *
 *  Created on: May 15, 2025
 *      Author: alan
 */

#ifndef UTILS_DATE_TYPE_H_
#define UTILS_DATE_TYPE_H_


typedef struct {
  unsigned char second;
  unsigned char minute;
  unsigned char hour;
  unsigned char dayOfWeek;
  unsigned char dayOfMonth;
  unsigned char month;
  unsigned char year;
}
Date;


#endif /* UTILS_DATE_TYPE_H_ */
