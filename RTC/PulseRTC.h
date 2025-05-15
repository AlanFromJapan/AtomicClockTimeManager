/*
 * pulse.h
 *
 *  Created on: May 13, 2025
 *      Author: alan
 */

#ifndef PULSE_PULSE_H_
#define PULSE_PULSE_H_

#include "../utils/date_type.h"

//The 600Hz from the Rubidium package is on PD3
#define PULSE600HZ_PIN	PD3

#define PULSE_PER_SEC	600

void initPulse(Date* pTimeDate);

void pulseReadTime(Date* pTimeDate);

#endif /* PULSE_PULSE_H_ */
