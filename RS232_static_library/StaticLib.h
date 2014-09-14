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
*			File........: stdafx.h													    *
*																						*
*			Author(s)...: Balestri Diego, Bua Raffaele, Toni Michele					*
*																						*
*			Target(s)...: Mingw 3.4.2               									*
*																						*
*			Description.: Static library for communication by RS232					  	*
*																						*
*			Version.....: 0.2															*
*																						*
*			Date........: 18 June 2009													*																
*																						*		
*			_____________________________________________________________________		*
*																						*
*																						*
*****************************************************************************************/	


//#pragma once


//#define WIN32_LEAN_AND_MEAN      

enum    ERROR_{     CREATION_HANDLER_FAIL, 
                        DCB_FAIL,
                        SET_TIMEOUT_FAIL,
                        SET_MASK_FAIL,
						INIT_OK,
						
                        CREATING_OVERLAPPED_FAIL,
                        RX_COMMUNICATION_FAIL,
                        WAIT_FOR_SINGLE_OBJECT_FAIL,
						READ_OK,
                     	NUMBER_BAUD_ERROR,
						RX_OK,
						CONFIGURATION_DCB_FAIL
							} error_code;   



extern "C"  struct polar_coordinate
{
	short int	distance;
	short int		angle;   
};

struct polar_coordinate coordinate;

DWORD bytesread;

OVERLAPPED o;

LPDWORD mask;

LPOVERLAPPED overlapped;

extern "C" HANDLE				rs232_init();

extern "C" char				rs232_read( HANDLE  port);

extern "C" void				rs232_close(HANDLE  port);

extern "C" polar_coordinate	rs232_receive(HANDLE  port);

extern "C"  char*           get_error();

extern "C"  BOOL                HandleASuccessfulRead(char* baud);   //finish the read

// TODO: reference additional headers your program requires here
