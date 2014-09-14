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
*			File........: CONSTANTS_VARIABLES.h											*
*																						*
*			Author(s)...: Balestri Diego, Bua Raffaele, Toni Michele					*
*																						*
*			Target(s)...: ATmega169														*
*																						*
*			Description.: All constants of system									  	*
*																						*
*			Version.....: 0.1															*
*																						*
*			Date........: 15 June 2009													*																
*																						*		
*			_____________________________________________________________________		*
*																						*
*																						*
*****************************************************************************************/	

#ifndef __CONSTANTS
#define __CONSTANTS

#define		MAX_NOTCH	11		// steps/2 +1

#define 	DELAY 100			// motor pulse lenght / 8 (ms)

#define FALSE   0
#define TRUE    (!FALSE)

extern enum VERSE {COUNTERCLOCKWISE,CLOCKWISE}verse;

extern char STEP_V[4];

extern short int 		distance[MAX_NOTCH];

extern unsigned char where;

extern short int notch;

#endif
