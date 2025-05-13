/*
 * pulse.c
 *
 *  Created on: May 13, 2025
 *      Author: alan
 */


#include "pulse.h"

#include <avr/io.h>
#include <avr/interrupt.h>

#include "../serial/serialComm.h"

/**
 * Sets the interupt on the proper pin to receive the 600Hz signal
 */
void initPulse(){
	//interrupt on RISING EDGE of the signal on INT1 (physical pin D3)
	EICRA |= (1<< ISC11) | (1 << ISC10);

	//only INT1
	EIMSK |= (1 << INT1);

	//go interrupts
	sei();
}

/**
 * On INT1 interrupt (pulse received)
 */
SIGNAL (INT1_vect)
{
	//USART_SendString("|_");
	;

}
