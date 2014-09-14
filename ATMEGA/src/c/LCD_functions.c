//*****************************************************************************
//
//  File........: LCD_functions.c
//
//  Author(s)...: ATMEL Norway
//
//  Target(s)...: ATmega169
//
//  Compiler....: AVR-GCC 4.1.1; avr-libc 1.4.5
//
//  Description.: Additional LCD functions, scrolling text and write data
//
//  Revisions...: 1.0
//
//  YYYYMMDD - VER. - COMMENT                                       - SIGN.
//
//  20021015 - 1.0  - Created                                       - LHM
//  20030116 - 2.0  - Code adapted to AVR Butterflyup               - KS
//  20031009          port to avr-gcc/avr-libc                      - M.Thomas
//  20070131          gLCD_Start_Scroll_Timer volatile              - mt
//  20070517          LCDClear, gTextBuffer[0] to 0-char            - mt
//*****************************************************************************

//  Include files
#include <stdint.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "../h/LCD_driver.h"
#include "../h/LCD_functions.h"


#define FALSE   0
#define TRUE    (!FALSE)

uint8_t CONTRAST = LCD_INITIAL_CONTRAST;

/****************************************************************************
*
*	Function name : LCD_puts
*
*	Returns :		None
*
*	Parameters :	pStr: Pointer to the string
*                   scrollmode: Not in use
*
*	Purpose :		Writes a string to the LCD
*
*****************************************************************************/
void LCD_puts(char *pStr)
{
    uint8_t i; // char i;

    while (gLCD_Update_Required);      // Wait for access to buffer

    for (i = 0; pStr[i] && i < TEXTBUFFER_SIZE; i++)
    {
		gTextBuffer[i] = pStr[i];
    }

    gTextBuffer[i] = '\0';

    gLCD_Update_Required = 1;
}


/****************************************************************************
*
*	Function name : LCD_UpdateRequired
*
*	Returns :		None
*
*	Parameters :	update: TRUE/FALSE
*                   scrollmode: not in use
*
*	Purpose :		Tells the LCD that there is new data to be presented
*
*****************************************************************************/
void LCD_UpdateRequired(char update)
{

    while (gLCD_Update_Required);

    gLCD_Update_Required = update;
}
