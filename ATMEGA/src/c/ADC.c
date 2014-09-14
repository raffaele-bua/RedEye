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
*			File........: ADC.c															*
*																						*
*			Author(s)...: Balestri Diego, Bua Raffaele, Toni Michele					*
*																						*
*			Target(s)...: ATmega169														*
*																						*
*			Description.: Driver of ADC device of ATmega169							  	*
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
#include"../h/ADC.h"




/****************************************************************************************
*			_____________________________________________________________________		*
*																						*
*																						*
*			Function name....: init_adc										   			*
*																						*
*			Returns..........: void														*
*																						*
*			Parameters.......: void 													*
*																						*
*			Purpose..........: Initialization of ADC									*
*																						*
*																						*		
*			_____________________________________________________________________		*
*																						*
*****************************************************************************************/	
void ADC_init(void)
{
	
	ADMUX = (1<<MUX2) | (1<<REFS0); //AVCC reference, ADC4

	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (0<<ADPS0); // set ADC prescaler to 64, 8MHz / 64 = 125kHz

    ADC_read();        // dummy 
}



/****************************************************************************************
*			_____________________________________________________________________		*
*																						*
*																						*
*			Function name....: ADC_read										   			*
*																						*
*			Returns..........: short int												*
*																						*
*			Parameters.......: void 													*
*																						*
*			Purpose..........: Read a value by ADC										*
*																						*
*																						*		
*			_____________________________________________________________________		*
*																						*
*****************************************************************************************/




short int ADC_read(void)
{	
	char i;

    int ADC_temp;
    int ADCr = 0;     

    sbiBF(ADCSRA, ADEN);     // Enable the ADC

    //do a dummy readout first
    ADCSRA |= (1<<ADSC);        // do single conversion
    while(!(ADCSRA & 0x10));    // wait for conversion done, ADIF flag active
        
    for(i=0;i<8;i++)            // do the ADC conversion 8 times for better accuracy 
    {
        ADCSRA |= (1<<ADSC);        // do single conversion
        while(!(ADCSRA & 0x10));    // wait for conversion done, ADIF flag active
        
        ADC_temp = ADCL;            // read out ADCL register
        ADC_temp += (ADCH << 8);    // read out ADCH register        

        ADCr += ADC_temp;      // accumulate result (8 samples) for later averaging
    }

    ADCr = ADCr >> 3;     // average the 8 samples  
    
    cbiBF(ADCSRA, ADEN);      // disable the ADC

    return ADCr;



}


