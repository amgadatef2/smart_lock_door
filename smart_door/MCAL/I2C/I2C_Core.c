/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  I2C_Core.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "I2C_Core.h"
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
void I2C_MasterInit(void)
{
	// 400KHz   
	TWBR = 0X0C;
	//TWPS =0
	CLR_BIT (TWSR , 0);
	CLR_BIT (TWSR , 1);
	//ENABLE ACK FOR MASTER
	SET_BIT (TWCR,6);
	//ENABLE I2C
	SET_BIT (TWCR,2);
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
void I2C_SlaveInit(void)
{
	// Set Address for the Slave
	TWAR = 0X02 << 1;
	//ENABLE ACK FOR Slave
	SET_BIT (TWCR,6);
	//ENABLE I2C
	SET_BIT (TWCR,2);
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
void I2C_StartCondition(void)
{
	// GENERATE Start condition 
	SET_BIT(TWCR ,5);
	//TRIGGER THE FLAG we also enabled I2C one more time which is not necessary (4) 
	TWCR = 0X84; //                             <----
	// POLLING ON THE FLAG 
	while (GET_BIT(TWCR , 7)==0);
	//CHECK ON THE STATUS
	while ((TWSR & 0XF8) != START_COND);
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
void I2C_RepeatedStart(void)
{
	// GENERATE Start condition
	SET_BIT(TWCR ,5);
	//TRIGGER THE FLAG we also enabled I2C one more time which is not necessary (4) 
	TWCR |= 0X84;   // ask why here there's | in here , and in start there's no |   <-----
	// POLLING ON THE FLAG
	while (GET_BIT(TWCR , 7)==0);
	//CHECK ON THE STATUS
	while ((TWSR & 0XF8) != REP_START_COND);
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
void I2C_SlaveAddress_WriteOperation(uint8 Address)
{
	//Send Slave Address with Write Operation
	TWDR = (Address << 1);
	//TRIGGER THE FLAG we also enabled I2C one more time which is not necessary (4) 
	TWCR = 0X84;
	// POLLING ON THE FLAG
	while (GET_BIT(TWCR , 7)==0);
	//CHECK ON THE STATUS
	while ((TWSR & 0XF8) != MR_SEND_SLAVE_ADD_AND_WR_OP_ACK_RECEIVED);
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
void I2C_SlaveAddress_ReadOperation(uint8 Address)
{
	//Send Slave Address with READ Operation
	TWDR = (Address << 1) | (0X01);
	//TRIGGER THE FLAG we also enabled I2C one more time which is not necessary (4) 
	TWCR = 0X84;
	// POLLING ON THE FLAG
	while (GET_BIT(TWCR , 7)==0);
	//CHECK ON THE STATUS
	while ((TWSR & 0XF8) != MR_SEND_SLAVE_ADD_AND_RD_OP_ACK_RECEIVED);
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
void I2C_WriteByte(uint8 Data)
{
	// Send Byte of Data
	TWDR = Data;
	//TRIGGER THE FLAG we also enabled I2C one more time which is not necessary (4) 
	TWCR = 0X84;
	// POLLING ON THE FLAG
	while (GET_BIT(TWCR , 7)==0);
	//CHECK ON THE STATUS
	while ((TWSR & 0XF8) != MR_WR_BYTE_ACK_RECEIVED);
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
uint8 I2C_ReadByte(void)
{
	uint8 Data=0;
	
	//TRIGGER THE FLAG we also enabled I2C one more time which is not necessary (4) 
	TWCR = 0X84;
	SET_BIT(TWCR,6);
	// POLLING ON THE FLAG
	while (GET_BIT(TWCR , 7)==0);
	//CHECK ON THE STATUS
	while ((TWSR & 0XF8) != MR_RD_BYTE_WITH_ACK_SENT);
	
	//Load the Data on the Register
	Data = TWDR;
	return Data;
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
void I2C_StopCondition(void)
{
	//Stop Condition
	//TRIGGER THE FLAG
	TWCR = 0X94;
}



/**********************************************************************************************************************
 *  END OF FILE: I2C_Core.c
 *********************************************************************************************************************/

