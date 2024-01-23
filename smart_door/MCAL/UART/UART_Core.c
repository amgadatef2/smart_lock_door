/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  UART_Core.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "UART_Core.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
uint8 UART_TRANSMITTED_DATA[TX_BUFFER_SIZE];
uint8 UART_RECEIVED_DATA[RX_BUFFER_SIZE];
uint8 TX_STATUS_FLAG =0;
uint8 TX_CNTR =0;
uint8 RX_STATUS_FLAG =0;
uint8 RechivedChar =0;
uint8 Flag=0;
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
void UART_Init(void)
{
	uint8 BaudRate_Value_L =0;
	
	// SELECT UCSRC REGISTER
	SET_BIT (UCSRC , 7);
	//SELECT ASYNCHRONOUS MODE 
	CLR_BIT (UCSRC , 6);
	CLR_BIT (UCSRC , 0);
	 
	#if (UART_PARITY_STATE  == PARITY_ENABLED)
	  #if (UART_PARITY_TYPE == PARITY_ODD)
	  UCSRC |= 0XB0; // 0b10110000; 
	  #elif (UART_PARITY_TYPE == PARITY_EVEN)
	  UCSRC |= 0XA0; // 0b1010000;
	  #endif //(UART_PARITY_TYPE == PARITY_ODD)
	#elif (UART_PARITY_STATE  == PARITY_DISABLED)  
	CLR_BIT (UCSRC , 4);
	CLR_BIT (UCSRC , 5);
	#endif //#if (UART_PARITY_STATE  == PARITY_ENABLED)
	
	#if (UART_DATA_BITS == UART_DATA_BITS_5)
	UCSRC |= 0X80;
	CLR_BIT (UCSRB ,2);
	#elif (UART_DATA_BITS == UART_DATA_BITS_6)
	UCSRC |= 0X82;
	CLR_BIT (UCSRB ,2);
	#elif (UART_DATA_BITS == UART_DATA_BITS_7)
	UCSRC |= 0X84;
	CLR_BIT (UCSRB ,2);
	#elif (UART_DATA_BITS == UART_DATA_BITS_8)
	UCSRC |= 0X86;
	CLR_BIT (UCSRB ,2);
	#elif (UART_DATA_BITS == UART_DATA_BITS_9)
	UCSRC |= 0X86;
	SET_BIT (UCSRB ,2);
	#endif //#if (UART_DATA_BITS == UART_DATA_BITS_5)
	
	#if (UART_STOP_BITS == UART_STOP_BITS_1)
	CLR_BIT (UCSRC , 3);
	#elif (UART_STOP_BITS == UART_STOP_BITS_2)
	SET_BIT (UCSRC , 3);
	#endif //#if (UART_STOP_BITS == UART_STOP_BITS_1)
	
	#if (UART_INTERRUPT_STATE == UART_INTERRUPT_ENABLE)
	SET_BIT (UCSRB , 7); // ENABLE RX INTERRUPT
	SET_BIT (UCSRB , 6); // ENABLE TX INTERRUPT , I DIDN'T CHOOSE DATA REGISTER EMPTY INTERRUPT
	#elif (UART_INTERRUPT_STATE == UART_INTERRUPT_DISABLE)
	CLR_BIT (UCSRB , 7); // DISABLE RX INTERRUPT
	CLR_BIT (UCSRB , 6); // DISABLE TX INTERRUPT , I DIDN'T CHOOSE DATA REGISTER EMPTY INTERRUPT
	#endif //#if (UART_INTERRUPT_STATE == UART_INTERRUPT_ENABLE)
	
	//Enable TX
	SET_BIT (UCSRB , 3);
	//Enable RX
	SET_BIT (UCSRB , 4);
	
	//BaudRate equation
	BaudRate_Value_L = ((160000U) / (UART_BAUD_RATE * 16)) - 1;
	UBRRL = BaudRate_Value_L;
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
void UART_InitTx(void)
{
	//ENABLE TX INT
	SET_BIT(UCSRB ,6);
	TX_STATUS_FLAG =1;
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
void UART_SendData (void)
{
	if ( TX_CNTR == TX_BUFFER_SIZE)
	{
		TX_CNTR =0;
		TX_STATUS_FLAG =0;
		CLR_BIT (UCSRB ,6); // Disable Interrupt
	}
	if (TX_STATUS_FLAG ==1)
	{
		UDR = UART_TRANSMITTED_DATA[TX_CNTR];
		TX_STATUS_FLAG=0; 
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
void UART_ReceiveData (void)
{
	static uint8 REC_CNTR =0;
	UART_RECEIVED_DATA [REC_CNTR] = UDR;
	REC_CNTR++;
	
	if (UDR == '.')
	{
		REC_CNTR =0;
		RX_STATUS_FLAG =1;
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
uint8 UART_RX_Status (void)
{
	uint8 REC_Status =0;
	
	if (RX_STATUS_FLAG == 1)
	{
		REC_Status = 1;
		RX_STATUS_FLAG =0;
	}
	return REC_Status;
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
void Rechived_Char(void){
	RechivedChar=UDR;
	Flag=1;
	
	
	
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
uint8 UART_RX_Char_Status(void)
{
	uint8 REC_Status =0;
	
	if (Flag == 1)
	{
		REC_Status = 1;
		Flag =0;
	}
	return REC_Status;
}
/**********************************************************************************************************************
 *  END OF FILE: UART_Core.c
 *********************************************************************************************************************/