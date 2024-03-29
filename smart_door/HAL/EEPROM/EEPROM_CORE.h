/*
 * EEPROM_CORE.h
 *
 * Created: 12/1/2023 11:36:18 AM
 *  Author: DELL
 */ 


#ifndef EEPROM_CORE_H_
#define EEPROM_CORE_H_

/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  <Write File Name>
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "MCU.h"
#include "STD.h"
#include "BIT_MATH.h"
#include "I2C_Core.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define   addres_EEPROM            0X50
#define   RX_BUFFER_SIZE           4U


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
void EEPROM_WRITE(uint8 DATA,uint8 addres,uint8 byte_loc);
void EEPROM_writemultiplebytes(uint8 *data,uint8 DATA_SIZE,uint8 addres,uint8 byte_loc);
uint8 EEPROM_READ(uint8 addres,uint8 BYTE_LOC);
uint8* EEPROM_ReadMultipleBytes (uint8 EEPROM_Address , uint8 Byte_Address);
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  END OF FILE: Std_Types.h
 *********************************************************************************************************************/




#endif /* EEPROM_CORE_H_ */