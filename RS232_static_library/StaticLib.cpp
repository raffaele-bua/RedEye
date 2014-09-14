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
*			File........: stdafx.cpp												    *
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

// stdafx.cpp : source file that includes just the standard includes
// RS232RedEye_LIB.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include <tchar.h>
#include <assert.h>
#include <stdio.h>
#include <cstdlib>
#include <windows.h>
#include "StaticLib.h"



// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

using namespace std;



/****************************************************************************************
*			_____________________________________________________________________		*
*																						*
*																						*
*			Function name....: rs232_init									   			*
*																						*
*			Returns..........: HANDLE													*
*																						*
*			Parameters.......: 															*
*																						*
*			Purpose..........: Initialize the port for communication		  			*
*																						*
*																						*		
*			_____________________________________________________________________		*
*																						*
*****************************************************************************************/	
extern "C" HANDLE rs232_init()
{
    BOOL open;
    HANDLE port;

    
    
    port = CreateFile("COM1",
                   GENERIC_READ ,
                   0,
                   0,
                   OPEN_EXISTING,
                   FILE_ATTRIBUTE_NORMAL,
                   0);

    if (port == INVALID_HANDLE_VALUE)
    {
        error_code  =   CREATION_HANDLER_FAIL;
        return INVALID_HANDLE_VALUE;
    }


    DCB dcb;
    dcb.DCBlength = sizeof(dcb);

    GetCommState(port,&dcb);

    dcb.BaudRate          =   19200;           
    dcb.ByteSize          =   8;              
    dcb.Parity            =   NOPARITY;         
    dcb.StopBits          =   ONESTOPBIT;     
    dcb.fBinary           =   TRUE;           
    //dcb.fParity           =   
    //dcb.fTXContinueOnXoff =   
    //dcb.fOutX             =   
   // dcb.fInX              =   
    //dcb.XonChar           =   
    //dcb.XoffChar          =   
    //dcb.XonLim            =   
    //dcb.XoffLim           =  
    open = SetCommState(port,&dcb);
    if(!open)
    {
		error_code = CONFIGURATION_DCB_FAIL;
		return 		INVALID_HANDLE_VALUE;


	}
    
    return port;
}

/****************************************************************************************
*			_____________________________________________________________________		*
*																						*
*																						*
*			Function name....: rs232_read									   			*
*																						*
*			Returns..........: char														*
*																						*
*			Parameters.......: 	HANDLE PORT												*
*																						*
*			Purpose..........: Pop a char by port							  			*
*																						*
*																						*		
*			_____________________________________________________________________		*
*																						*
*****************************************************************************************/	

extern "C" char  rs232_read( HANDLE  port)
{
   

    char lpBuf;    

    if(!ReadFile(port,  &lpBuf, 1, &bytesread, NULL))
              
    {
        error_code = RX_COMMUNICATION_FAIL;
        
    }
    
  

    return  lpBuf;

}




/****************************************************************************************
*			_____________________________________________________________________		*
*																						*
*																						*
*			Function name....: rs232_close									   			*
*																						*
*			Returns..........: void														*
*																						*
*			Parameters.......: HANDLE port												*
*																						*
*			Purpose..........: Close the port								  			*
*																						*
*																						*		
*			_____________________________________________________________________		*
*																						*
*****************************************************************************************/	
extern "C" void rs232_close(HANDLE  port)
{
      CloseHandle(port);

}

/****************************************************************************************
*			_____________________________________________________________________		*
*																						*
*																						*
*			Function name....: rs232_receive								   			*
*																						*
*			Returns..........: polar_coordinate											*
*																						*
*			Parameters.......: HANDLE port												*
*																						*
*			Purpose..........: Receive the distance and the position of red eye			*
*																						*
*																						*		
*			_____________________________________________________________________		*
*																						*
*****************************************************************************************/	
extern "C" polar_coordinate  rs232_receive(HANDLE  port)
{
        static short int counter=0;
        static short int old_read= 0;
        BYTE buffer[3];
        for(int i=0;i<3;i++)
        {
            buffer[i]=   rs232_read( port);
            
            if((buffer[i]==0xFF)&&(old_read==0xFF))
                   counter++;
            else
                    counter=0;
                           
                
            old_read=buffer[i];
            
            if(counter==4)
                return coordinate;
       }
       
        coordinate.angle    =    buffer[2];
      
        coordinate.distance=*(short int *)buffer;


       return coordinate;
}





/****************************************************************************************
*			_____________________________________________________________________		*
*																						*
*																						*
*			Function name....: get_error									   			*
*																						*
*			Returns..........: void														*
*																						*
*			Parameters.......: void 													*
*																						*
*			Purpose..........:                         									*
*																						*
*																						*
*			_____________________________________________________________________		*
*																						*
*****************************************************************************************/


extern "C"  char * get_error()
{
    switch(error_code)
    {
        case DCB_FAIL:
            return " fallimento nell'impostazione del DCB \n";
        break;
        
        case SET_TIMEOUT_FAIL:
            return " fallimento nell'impostazione Timeout \n";
        break;
        
        case SET_MASK_FAIL:
            return " Fallimento impostazione Maschera Eventi \n";
        break;
        
		
        case CREATING_OVERLAPPED_FAIL:
            return " Fallimento creazione struttura Overlapped \n";
        break;
        
        case RX_COMMUNICATION_FAIL:
            return " Fallimento nella comunicazione \n";
        break;
        
        case WAIT_FOR_SINGLE_OBJECT_FAIL:
            return " Fallimento Wait for single object \n";
        break;
        
		
        
        case NUMBER_BAUD_ERROR:
            return "  Il numero dei caratteri ricevuti non combacia \n";
        break;
        
		case RX_OK :
            return "  errore in ricezione\n";
        break;
        
        case CONFIGURATION_DCB_FAIL :
            return "  Errore nella configurazione del DCB\n";
        break;
        
        default:
            return "Nessun errore!\n";
        
        
        
        
    }
}
