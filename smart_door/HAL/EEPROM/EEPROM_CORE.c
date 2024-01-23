/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  FileName.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "EEPROM_CORE.h"
#include "I2C_Core.h"
#include "LCD_Core.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
uint8 RX_RecivedMultiBytes[RX_BUFFER_SIZE];
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
void EEPROM_WRITE(uint8 DATA ,uint8 addres,uint8 byte_loc){
	I2C_StartCondition();
	
	I2C_SlaveAddress_WriteOperation(addres);
	
	I2C_WriteByte(byte_loc);
	
	I2C_WriteByte(DATA);
	
	I2C_StopCondition();
	
	
	
	
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
uint8 EEPROM_READ(uint8 addres,uint8 BYTE_LOC){
	uint8 DATA=0;
	I2C_StartCondition();
	
I2C_SlaveAddress_WriteOperation(addres);
I2C_WriteByte(BYTE_LOC);

I2C_RepeatedStart();
I2C_SlaveAddress_ReadOperation(addres);
DATA=I2C_ReadByte();
I2C_StopCondition();
return DATA;
	
	
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
void EEPROM_writemultiplebytes(uint8 *data,uint8 DATA_SIZE,uint8 addres,uint8 byte_loc){
	uint8 DATA_CNT=0;
	
	I2C_StartCondition();
	I2C_SlaveAddress_WriteOperation(addres);
	
	I2C_WriteByte(byte_loc);
	while(DATA_CNT<DATA_SIZE){
		
		I2C_WriteByte(data[DATA_CNT]);
		
		DATA_CNT++;
	}
	
	I2C_StopCondition();
	
	
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
uint8* EEPROM_ReadMultipleBytes (uint8 EEPROM_Address , uint8 Byte_Address)
{
	uint8 Data_Cntr=0;
	static uint8 Data[RX_BUFFER_SIZE]={0};
	I2C_StartCondition();
	I2C_SlaveAddress_WriteOperation(EEPROM_Address);
	I2C_WriteByte(Byte_Address);
	I2C_RepeatedStart();
	I2C_SlaveAddress_ReadOperation(EEPROM_Address);
	while (Data_Cntr < RX_BUFFER_SIZE)
	{
		Data[Data_Cntr]=I2C_ReadByte();
		Data_Cntr++;
	}
	I2C_StopCondition();
	return Data;
}


/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
