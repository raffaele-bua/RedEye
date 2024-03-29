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
*			File........: USART.c														*
*																						*
*			Author(s)...: Balestri Diego, Bua Raffaele, Toni Michele					*
*																						*
*			Target(s)...: ATmega169														*
*																						*
*			Description.: Functions for to communicate with computer (RS232)		  	*
*																						*
*			Version.....: 0.1															*
*																						*
*			Date........: 15 June 2009													*		
*																						*		
*			_____________________________________________________________________		*
*																						*
*																						*
*****************************************************************************************/
#include"../h/CONSTANTS_VARIABLES.h"
#include<avr/io.h>
#include<avr/interrupt.h>
#include"../h/USART.h"








/****************************************************************************************
*			_____________________________________________________________________		*
*																						*
*																						*
*			Function name....: cout232										   			*
*																						*
*			Returns..........: void														*
*																						*
*			Parameters.......: char c 													*
*																						*
*			Purpose..........: send char via rs232										*
*																						*
*																						*		
*			_____________________________________________________________________		*
*																						*
*****************************************************************************************/
void cout232(char c)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE))) ;

	/* Put data into buffer, sends the data */
	UDR = c;
}

/****************************************************************************************
*			_____________________________________________________________________		*
*																						*
*																						*
*			Function name....: init_usart									   			*
*																						*
*			Returns..........: void														*
*																						*
*			Parameters.......: void 													*
*																						*
*			Purpose..........: Initialization of Uart to receive and transmit			*
*																						*
*																						*		
*			_____________________________________________________________________		*
*																						*
*****************************************************************************************/	
void usart_init(void)
{
    // Set baud rate to 19200 for a clock equal to 8 Mhz
    UBRRH = (unsigned char)(51>>8);
    UBRRL = (unsigned char) 51;

    // Enable 2x speed
    UCSRA = (1<<U2X);

    // Enable receiver-transmitter and enable interrupts of receiver
    UCSRB = (1<<RXEN)|(1<<TXEN)|(0<<UDRIE);

    // Async. mode, 8N1
    UCSRC = (0<<UMSEL)|(0<<UPM0)|(0<<USBS)|(3<<UCSZ0)|(0<<UCPOL);

	put_start();
	
}


/****************************************************************************************
*			_____________________________________________________________________		*
*																						*
*																						*
*			Function name....: transmit										   			*
*																						*
*			Returns..........: void														*
*																						*
*			Parameters.......: char * baud, char degree									*
*																						*
*			Purpose..........: put the distance and the degree							*
*																						*
*																						*		
*			_____________________________________________________________________		*
*																						*
*****************************************************************************************/
void transmit(short int distance, unsigned char degree)
{


char* baud= (char* )&distance;


	cout232(baud[0]);
	cout232(baud[1]);
	cout232(degree);


	
	return ;
}






/****************************************************************************************
*			_____________________________________________________________________		*
*																						*
*																						*
*			Function name....: put_start										   		*
*																						*
*			Returns..........: void														*
*																						*
*			Parameters.......: void														*
*																						*
*			Purpose..........: put the byte 0xFF										*
*																						*
*																						*		
*			_____________________________________________________________________		*
*																						*
*****************************************************************************************/

void put_start()
{
	short int i=0;
	for(;i<5;i++)

		cout232(0xFF);
	
}
