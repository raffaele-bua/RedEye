/****************************************************************************************
*									__													*
*				  	               /\ \           										*                   
*					  _ __    __   \_\ \         __   __  __     __   					*
*					 /\`'__\/'__`\ /'_` \      /'__`\/\ \/\ \  /'__`\ 					*
*					 \ \ \//\  __//\ \_\ \    /\  __/\ \ \_\ \/\  __/ 					*
*					  \ \_\\ \____\ \___,_\   \ \____\\/`____ \ \____\					*
*					   \/_/ \/____/\/__,_ /    \/____/ `/___/> \/____/					*
*					                                      /\___/      					*
*					                                      \/__/   						*
*																						*		
*			_____________________________________________________________________		*
*																						*
*																						*
*			File........: DEMIURGO.c													*
*																						*
*			Author(s)...: Balestri Diego, Bua Raffaele, Toni Michele					*
*																						*
*			Target(s)...: ATmega169														*
*																						*
*			Description.: Working cycle												  	*
*																						*
*			Version.....: 0.1															*
*																						*
*			Date........: 15 June 2009													*		
*																						*		
*			_____________________________________________________________________		*
*																						*
*																						*
*****************************************************************************************/

#include <avr/interrupt.h>
#include <stdlib.h>

#include"../h/CONSTANTS_VARIABLES.h"
#include "../h/ADC.h"
#include "../h/RULER.h"
#include "../h/USART.h"
#include "../h/MOTOR.h"
#include "../h/LCD_driver.h"
#include "../h/LCD_functions.h"

short int notch=0;
short int distance[MAX_NOTCH];
char num[6];

/****************************************************************************************
*			_____________________________________________________________________		*
*																						*
*																						*
*			Function name....: ISR (TIMER0_COMP_vect) 										   			*
*																						*
*			Returns..........: void														*
*																						*
*			Parameters.......: void 													*
*																						*
*			Purpose..........: cycle of device, interrupt called every ms											*
*																						*
*																						*		
*			_____________________________________________________________________		*
*																						*
*****************************************************************************************/

ISR (TIMER0_COMP_vect) {
	cli();
	static short int i=0;
	i=(i+1)%DELAY;

	if (i==0) {

		distance[notch]=measure();
		
		//show distance
		itoa(distance[notch],num,10);
		LCD_puts(num);
		
		transmit(distance[notch],notch);
				
		verse = (notch==MAX_NOTCH-1)?CLOCKWISE:(notch==0)?COUNTERCLOCKWISE:verse;
		notch=(verse==COUNTERCLOCKWISE)?notch+1:notch-1;
		
		step(verse);

		}

	sei();
		
	}
