/*
 * MCU.h
 *
 * Created: 9/15/2023 10:06:24 AM
 *  Author:amgad
 */ 


#ifndef MCU_H_
#define MCU_H_

#include "STD.h"


/****************** GPIO Registers **************/
#define PINA   *(volatile uint8*)(0x39)
#define DDRA   *(volatile uint8*)(0x3A)
#define PORTA  *(volatile uint8*)(0x3B)

#define PINB   *(volatile uint8*)(0x36)
#define DDRB   *(volatile uint8*)(0x37)
#define PORTB  *(volatile uint8*)(0x38)

#define PINC   *(volatile uint8*)(0x33)
#define DDRC   *(volatile uint8*)(0x34)
#define PORTC  *(volatile uint8*)(0x35)

#define PIND   *(volatile uint8*)(0x30)
#define DDRD   *(volatile uint8*)(0x31)
#define PORTD  *(volatile uint8*)(0x32)
/************************************************/

/************************************** EXTERNAL INT Registers ******************************/
#define SREG   (*(volatile uint8*)(0X5F))
#define GICR   (*(volatile uint8*)(0X5B))
#define MCUCR  (*(volatile uint8*)(0X55))
#define MCUCSR (*(volatile uint8*)(0X54))


/*************************************** ADC Registers ************************************************/#define ADMUX                      (*(volatile uint8 *)(0x27))#define ADCSRA                     (*(volatile uint8 *)(0x26))#define ADCH                       (*(volatile uint8 *)(0x25))#define ADCL                       (*(volatile uint8 *)(0x24))#define ADC_INPUT_16BIT_ACCESS     (*(volatile uint16*)(0x24))#define SFIOR                      (*(volatile uint8 *)(0x50))/*******************************************************************************************************/

/*************************************** Timer0 ************************************************/#define TCNT0     (*(volatile uint8 *)(0x52))#define TCCR0     (*(volatile uint8 *)(0x53))#define OCR0      (*(volatile uint8 *)(0x5C))#define TIMSK     (*(volatile uint8 *)(0x59))/*******************************************************************************************************/

/**************************************Timer1***********************************************************/
#define TCCR1A              (*(volatile uint8* )(0x4F))#define TCCR1B              (*(volatile uint8* )(0x4E))#define TCNT1H              (*(volatile uint8* )(0x4D))#define TCNT1L              (*(volatile uint8* )(0x4C))#define TCNT1_16BIT_ACCESS  (*(volatile uint16*)(0x4C))#define OCR1AH              (*(volatile uint8* )(0x4B))#define OCR1AL              (*(volatile uint8* )(0x4A))#define OCR1A_16BIT_ACCESS  (*(volatile uint16*)(0x4A))#define OCR1BH              (*(volatile uint8* )(0x49))#define OCR1BL              (*(volatile uint8* )(0x48))#define OCR1B_16BIT_ACCESS  (*(volatile uint16*)(0x48))#define ICR1H               (*(volatile uint8* )(0x47))#define ICR1L               (*(volatile uint8* )(0x46))#define ICR1_16BIT_ACCESS   (*(volatile uint16*)(0x46))
/*****************************************************************************************************/

/**************************************WDT***********************************************************/

#define WDTCR    (*(volatile uint8*)(0X41))

/**************************************UART***********************************************************/
#define UBRRH   (*((volatile uint8*)0x40))#define UBRRL   (*((volatile uint8*)0x29))#define UCSRA   (*((volatile uint8*)0x2B))#define UCSRB   (*((volatile uint8*)0x2A))#define UCSRC   (*((volatile uint8*)0x40))#define UDR     (*((volatile uint8*)0x2C))

/**************************************SPI***********************************************************/

typedef struct
{
	uint8 SPR : 2;
	uint8 CPHA: 1;
	uint8 CPOL: 1;
	uint8 MSTR: 1;
	uint8 DORD: 1;
	uint8 SPE : 1;
	uint8 SPIE: 1;
}SPCR_BITS;

typedef struct  
{
	SPCR_BITS SPCR;
	uint8     SPSR;
	uint8     SPDR;
}SPI_Type;


#define SPI_REGS ((volatile SPI_Type*)(0X2D))
/****************************************************************************************************/

/**************************************I2C***********************************************************/
#define TWCR    (*((volatile uint8*)0x56))#define TWDR    (*((volatile uint8*)0x23))#define TWAR    (*((volatile uint8*)0x22))#define TWBR    (*((volatile uint8*)0x20))#define TWSR    (*((volatile uint8*)0x21))
/****************************************************************************************************/

#endif /* MCU_H_ */