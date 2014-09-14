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
*			File........: INIT.c														*
*																						*
*			Author(s)...: Balestri Diego, Bua Raffaele, Toni Michele					*
*																						*
*			Target(s)...: ATmega169														*
*																						*
*			Description.: Initialization of varibles								  	*
*																						*
*			Version.....: 0.1															*
*																						*
*			Date........: 15 June 2009													*		
*																						*		
*			_____________________________________________________________________		*
*																						*
*																						*
*****************************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include"../h/ADC.h"
#include"../h/INIT.h"
#include"../h/USART.h"
#include"../h/LCD_driver.h"





/****************************************************************************************
*			_____________________________________________________________________		*
*																						*
*																						*
*			Function name....: init											   			*
*																						*
*			Returns..........: void														*
*																						*
*			Parameters.......: void 													*
*																						*
*			Purpose..........: Initialization of uController and Peripherals			*
*																						*
*																						*		
*			_____________________________________________________________________		*
*																						*
*****************************************************************************************/

void init()
{
	
	// set Clock Prescaler Change Enable        
	CLKPR = (1<<CLKPCE);

    
	// set prescaler = 1, Inter RC 8Mhz / 1 = 8Mhz
    CLKPR = (0<<CLKPS1) | (0<<CLKPS0);	

	// DISABLE JTAG

	unsigned char sreg;
	sreg=SREG;
	cli();
	MCUCR |= ( 1 <<JTD );
	MCUCR |= ( 1 <<JTD );
	SREG = sreg;
	
	//SET TIMER - 8 ms

	OCR0A = 249;
	TCCR0A=0x0C;
	TIMSK0=2;

	//SET PORTS

	DDRB = 0xCF;
	PORTB = 0xC0;
	
	sei();			//Interrupts enabled


	ADC_init();
	
	LCD_Init();

	usart_init();

	return;

}


