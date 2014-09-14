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
*			File........: MOTOR.c														*
*																						*
*			Author(s)...: Balestri Diego, Bua Raffaele, Toni Michele					*
*																						*
*			Target(s)...: ATmega169														*
*																						*
*			Description.: Control of step motor						  	*
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
#include"../h/MOTOR.h"
#include <avr/io.h>

//Waveform sequence
char STEP_V[4]= {0xC2,0xC4,0xC1,0xC8};

unsigned char where =0;
enum VERSE verse = COUNTERCLOCKWISE;


/****************************************************************************************
*			_____________________________________________________________________		*
*																						*
*																						*
*			Function name....: step											   			*
*																						*
*			Returns..........: void														*
*																						*
*			Parameters.......: char verse												*
*																						*
*			Purpose..........: move motor of one degree									*
*																						*
*																						*		
*			_____________________________________________________________________		*
*																						*
*****************************************************************************************/
void step ( enum VERSE verso) {

	where=(verso==COUNTERCLOCKWISE) ? where+1:where-1;
	

	where = where %4;

	PORTB = STEP_V[where];
	}