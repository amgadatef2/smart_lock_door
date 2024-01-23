/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  DIO_Core.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "DIO_Core.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
	
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void DIO_WriteChannel (uint8 Pin_Order, PIN_VAL_e Pin_Val)
{
	uint8 PORT =0, PIN=0 ;
	PORT= Pin_Order / NUMBER_OF_PORT_PINS;
	PIN=  Pin_Order  % NUMBER_OF_PORT_PINS;
	
	switch (Pin_Val)
	{
		case PIN_HIGH :
		switch(PORT)
		{
			case 0:
			SET_BIT (PORTA , PIN);
			break;
			case 1:
			SET_BIT (PORTB , PIN);
			break;
			case 2:
			SET_BIT (PORTC , PIN);
			break;
			case 3:
			SET_BIT (PORTD , PIN);
			break;
			default:
			break;
		}
		break;
		
		case PIN_LOW :
		switch(PORT)
		{
			case 0:
			CLR_BIT (PORTA , PIN);
			break;
			case 1:
			CLR_BIT (PORTB , PIN);
			break;
			case 2:
			CLR_BIT (PORTC , PIN);
			break;
			case 3:
			CLR_BIT (PORTD , PIN);
			break;
			default:
			break;
		}
		break;
		
		default:
		break;
	}
}

/******************************************************************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/

PIN_VAL_e DIO_ReadChannel (uint8 Pin_Order)
{
		uint8 PORT =0, PIN=0, OUTPUT_Val=0 ;
		PORT= Pin_Order / NUMBER_OF_PORT_PINS;
		PIN=  Pin_Order  % NUMBER_OF_PORT_PINS;
		
		switch (PORT)
		{
			case 0:
			OUTPUT_Val= GET_BIT (PINA , PIN);
			break;
			case 1:
			OUTPUT_Val= GET_BIT (PINB , PIN);
			break;
			case 2:
			OUTPUT_Val= GET_BIT (PINC , PIN);
			break;
			case 3:
			OUTPUT_Val= GET_BIT (PIND , PIN);
			break;
			default:
			break;
		}
		return OUTPUT_Val;
}

/******************************************************************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/

void DIO_FlipChannel (uint8 Pin_Order)
{
	uint8 PORT =0, PIN=0 ;
	PORT= Pin_Order / NUMBER_OF_PORT_PINS;
	PIN=  Pin_Order  % NUMBER_OF_PORT_PINS;
	
	switch(PORT)
	{
		case 0:
		TGL_BIT(PORTA,PIN); 
		break;
		case 1:
		TGL_BIT(PORTB,PIN);
		break;
		case 2:
		TGL_BIT(PORTC,PIN);
		break;
		case 3:
		TGL_BIT(PORTD,PIN);
		break;
		default:
		break;
	}
}

/******************************************************************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/

void DIO_WritePort (uint8 Pin_Order, uint8 Port_Val)
{
	uint8 PORT =0;
	PORT= Pin_Order / NUMBER_OF_PORT_PINS;
	
	switch(PORT)
	{
		case 0:
		PORTA = Port_Val;
		break;
		case 1:
		PORTB = Port_Val;
		break;
		case 2:
		PORTC = Port_Val;
		break;
		case 3:
		PORTD = Port_Val;
		break;
		default:
		break;
	}
}

/******************************************************************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/

uint8 DIO_ReadPort (uint8 Pin_Order)
{
	uint8 PORT =0 , Output_Val=0;
	PORT= Pin_Order / NUMBER_OF_PORT_PINS;
	
	switch(PORT)
	{
		case 0:
		Output_Val = PINA;
		break;
		case 1:
		Output_Val = PINB;
		break;
		case 2:
		Output_Val = PINC;
		break;
		case 3:
		Output_Val = PIND;
		break;
		default:
		break;
	}
	return Output_Val;
}



/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
