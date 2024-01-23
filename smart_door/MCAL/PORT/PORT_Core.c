/*
 * PORT_Core.c
 *
 * Created: 9/16/2023 12:05:33 PM
 *  Author: amgad
 */ 

#include "PORT_Core.h"

void PORT_Init(void)
{
	uint8 cntr=0 , PORT=0 , PIN =0 , DIR= 0;
	for(cntr = 0 ; cntr < DEFINED_PINS ; cntr++ )
	{
		PORT = PORT_Initialization[cntr].PIN_NUM/NUMBER_OF_PORT_PINS;
		PIN =  PORT_Initialization[cntr].PIN_NUM%NUMBER_OF_PORT_PINS;
		DIR =  PORT_Initialization[cntr].DIR;
		
		switch (DIR)
		{
			case PIN_DIR_INPUT :
			    switch (PORT)
				{
					case PORT_A:
					     CLR_BIT(DDRA , PIN);
					break;
					
					case PORT_B:
					     CLR_BIT(DDRB , PIN);
					break;
					
					case PORT_C:
					     CLR_BIT(DDRC , PIN);
					break;
					
					case PORT_D:
					     CLR_BIT(DDRD , PIN);
					break;
					
					default:
					break;
				}
			break;
			
			case PIN_DIR_OUTPUT :
			    switch (PORT)
			    {
				    case PORT_A:
				    SET_BIT(DDRA , PIN);
				    break;
				    
				    case PORT_B:
				    SET_BIT(DDRB , PIN);
				    break;
				    
				    case PORT_C:
				    SET_BIT(DDRC , PIN);
				    break;
				    
				    case PORT_D:
				    SET_BIT(DDRD , PIN);
				    break;
				    
				    default:
				    break;
			    }
			
			break;
			
			default:
			break;
		}
	}
}