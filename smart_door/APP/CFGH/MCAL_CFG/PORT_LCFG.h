/*
 * PORT_LCFG.h
 *
 * Created: 9/16/2023 12:14:51 PM
 *  Author: amgad
 */ 


#ifndef PORT_LCFG_H_
#define PORT_LCFG_H_

#include "STD.h"

#define  DEFINED_PINS          20 //DEFINED_PINS is the number of pins we need in our project
#define  NUMBER_OF_PORT_PINS   8

#define PORTA_PIN0  0
#define PORTA_PIN1  1
#define PORTA_PIN2  2
#define PORTA_PIN3  3
#define PORTA_PIN4  4
#define PORTA_PIN5  5
#define PORTA_PIN6  6
#define PORTA_PIN7  7


#define PORTB_PIN0  8
#define PORTB_PIN1  9
#define PORTB_PIN2  10
#define PORTB_PIN3  11
#define PORTB_PIN4  12
#define PORTB_PIN5  13
#define PORTB_PIN6  14
#define PORTB_PIN7  15

#define PORTC_PIN0  16
#define PORTC_PIN1  17
#define PORTC_PIN2  18
#define PORTC_PIN3  19
#define PORTC_PIN4  20
#define PORTC_PIN5  21
#define PORTC_PIN6  22
#define PORTC_PIN7  23

#define PORTD_PIN0  24
#define PORTD_PIN1  25
#define PORTD_PIN2  26
#define PORTD_PIN3  27
#define PORTD_PIN4  28
#define PORTD_PIN5  29
#define PORTD_PIN6  30
#define PORTD_PIN7  31

#define PIN_DIR_INPUT    0
#define PIN_DIR_OUTPUT   1

typedef struct 
{
	uint8 PIN_NUM;
	uint8 DIR;
}PIN_PARAMETERS;

extern PIN_PARAMETERS PORT_Initialization[DEFINED_PINS];



#endif /* PORT_LCFG_H_ */