/*
 * pulse.c
 *
 *  Created on: May 13, 2025
 *      Author: alan
 */


#include "PulseRTC.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

#include "../serial/serialComm.h"


//THE in memory time variable
volatile Date _latest_time;

//number of pulse since last second
volatile uint16_t _pulse_cnt = 0;


/**
 * Sets the interupt on the proper pin to receive the 600Hz signal
 */
void initPulse(Date* pTimeDate){
	memcpy(&_latest_time, pTimeDate, sizeof(Date));

	//interrupt on RISING EDGE of the signal on INT1 (physical pin D3)
	EICRA |= (1<< ISC11) | (1 << ISC10);

	//only INT1
	EIMSK |= (1 << INT1);

	//go interrupts
	sei();
}


/**
 * Increase the date in-memory by one second
 */
void dateIncreaseSeconds (){
	if (++_latest_time.second >= 60){
		_latest_time.second = 0;
		if (++_latest_time.minute >= 60){
			_latest_time.minute = 0;
			if (++_latest_time.hour >= 24){
				_latest_time.hour = 0;

				_latest_time.dayOfWeek = (_latest_time.dayOfWeek + 1) % 7;

				//stop here: no day of month, month, year calculation
			}
		}
	}
}


/**
 * On INT1 interrupt (pulse received): happens 600 times a sec
 */
SIGNAL (INT1_vect)
{
	//USART_SendString("|_");

	//increase the in-memory time by a 600th of a sec
	_pulse_cnt++;
	if (_pulse_cnt >= PULSE_PER_SEC){
		_pulse_cnt = 0;

		//USART_SendString("+1");

		//one more second has passed
		dateIncreaseSeconds();
	}
}


/**
 * Reads the time not from the chip but from a calculated value based on original read + pulses
 */
void pulseReadTime(Date* pTimeDate){
	//just copy from stored variable. Maybe a memcpy would be faster?
	pTimeDate->dayOfMonth = _latest_time.dayOfMonth;
	pTimeDate->dayOfWeek = _latest_time.dayOfWeek;
	pTimeDate->hour = _latest_time.hour;
	pTimeDate->minute = _latest_time.minute;
	pTimeDate->month = _latest_time.month;
	pTimeDate->second = _latest_time.second;
	pTimeDate->year = _latest_time.year;

}

