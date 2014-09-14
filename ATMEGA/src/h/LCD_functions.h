//*****************************************************************************
//
//  File........: LCD_functions.h
//
//  Author(s)...: ATMEL Norway
//
//  Target(s)...: ATmega169
//
//  Description.: Functions for LCD_functions.c
//
//  Revisions...: 1.0
//
//  YYYYMMDD - VER. - COMMENT                                       - SIGN.
//
//  20021015 - 1.0  - File created                                  - LHM
//  20031009          port to avr-gcc/avr-libc                      - M.Thomas
//
//*****************************************************************************

#include <avr/pgmspace.h>
void LCD_puts(char *pStr);
void LCD_UpdateRequired(char update);
