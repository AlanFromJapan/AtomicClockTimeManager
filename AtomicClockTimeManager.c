/*
 * AtomicClockTimeManager.c
 *
 * "Branched" from my messy original repo https://github.com/AlanFromJapan/alanarduinotools/tree/master/Atmegaxx8/MultiClockManager
 * This is meant to serve the AtomicClock Revisited, so it has a special repo. I removed some unnecessary headers, will add what needed.
 * Clock page : http://electrogeek.tokyo/atomic%20clock%20revisited.html
 *
 */ 

//for delay.h >> defined in the compilation symbols
//#define F_CPU 16000000L

#include <stdlib.h>

//System includes
#include <avr/io.h>
#include <util/delay.h>

//Program includes
#include "utils/date_type.h"

//Choose what RTC to use
#include "RTC/DS3234.h"
//#include "RTCFake.h"
//Include pulse AFTER DS3234 (order matters)
#include "RTC/PulseRTC.h"


//Choose the display to use (put the define BEFORE the includes!)
#define USE_DISPLAY_NUMITRON
#include "displays/TinyNumitron.h"


//Serial communication, mostly for debugging
#include "serial/serialComm.h"



/************************************************************************/
/* Setup                                                                */
/************************************************************************/
void mainSetup() {

	//Start Serial
	serialHardwareInit();
	USART_SendString("\n------------------------");
	USART_SendString("\nHello!");

	//macro to be redefined by each RTC
	RTC_INIT();
	
	//Set time! (don't do it every time ;) Remove me later)
	//SetTimeDate3231(NULL);
	//SetTimeDate3234(7,6,2024,21,57,00);

	//macro to be redefined by each display
	SETUP_DISPLAY();
	
	//Start listening for 600Hz pulses
	Date d;
	RTC_READ_TIME(&d);
	initPulse(&d);
	// redefine the macro to get the time to be the PULSE time one
#undef RTC_READ_TIME
#define RTC_READ_TIME(d) pulseReadTime(d)
}



/************************************************************************/
/* Main                                                                 */
/************************************************************************/
int main(void) {
	mainSetup();

	
	Date vLastDate;

	
    while(1) {

	    //macro to be redefined by each RTC
    	RTC_READ_TIME(&vLastDate);
		
		//macro to be redefined by each display
		MAP_DATE_TO_DISPLAY(&vLastDate);
		
		//macro to be redefined by each display
		DRAW_DISPLAY();



//    	USART_SendString("h=");
//		char vBuff[15];
//		itoa(vLastDate.second, vBuff, 10);
//		USART_SendString(vBuff);
//
//		USART_SendString(". ");


		//Save the time to RTC: in case power is lost, save the time now to the RTC
		//Keep the delay below small to ensure not too much drift incurs
		//Save daily, most likely no benefit to save more frequently because of imprecision
		if (vLastDate.hour == 11 && vLastDate.minute == 11 && vLastDate.second == 11){
			RTC_SET_TIME(&vLastDate);

			//wait a sec (tubes don't need refresh, and not showing seconds anyway)
			_delay_ms(1100);
		}


	    //small delay
		_delay_ms(50);

		
    }
}
