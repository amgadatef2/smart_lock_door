/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File: I2C_Core.h
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef I2C_CORE_H_
#define I2C_CORE_H_
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "MCU.h"
#include "BIT_MATH.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define START_COND                                   0X08 // start has been sent#define REP_START_COND                               0X10 // repeated start sent#define MR_SEND_SLAVE_ADD_AND_WR_OP_ACK_RECEIVED     0X18 // Master transmit ( slave address + Write request ) ACK received#define MR_SEND_SLAVE_ADD_AND_RD_OP_ACK_RECEIVED     0X40 // Master transmit ( slave address + Read request )  ACK received#define MR_WR_BYTE_ACK_RECEIVED                      0X28 // Master transmit data and ACK received#define MR_WR_BYTE_NACK_RECEIVED                     0X30 // Master transmit data NACK received#define MR_RD_BYTE_WITH_ACK_SENT                     0X50 // Master received data with ACK SENT#define MR_RD_BYTE_WITH_NACK_SENT                    0X58 // Master received data with not ACK SENT#define SLAVE_ADD_RCVD_RD_REQ_ACK_SENT               0XA8 // means that slave address is received with read req and ACK sent#define SLAVE_ADD_RCVD_WR_REQ_ACK_SENT               0X60 // means that slave address is received with write req and ACK sent#define SLAVE_DATA_RECEIVED_ACK_SENT                 0X80 // means that DATA has been received from the master and ACK is sent#define SLAVE_DATA_TRANSMITTED_ACK_RECEIVED          0XB8 // means that DATA has been SENT from the slave and ACK is received
/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void I2C_MasterInit(void);
void I2C_SlaveInit(void);
void I2C_StartCondition(void);
void I2C_RepeatedStart(void);
void I2C_SlaveAddress_WriteOperation(uint8 Address);
void I2C_SlaveAddress_ReadOperation(uint8 Address);
void I2C_WriteByte(uint8 Data);
uint8 I2C_ReadByte(void);
void I2C_StopCondition(void);
#endif /* I2C_CORE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: I2C_Core.h
 *********************************************************************************************************************/







