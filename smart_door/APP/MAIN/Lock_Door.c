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
#include "Lock_Door.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

uint8 Password[Size_Pass]={'1','1','1','1'};
uint8 Attempts=0;
uint8 Arr_Pass_Full=0;
uint8 Pass_Full=0;
uint8 Arr[Size_Pass]={};
uint8 Cnt2=0;
uint8 VALUE =0;
uint8 Change_Pass[]="1.Change_Pass:";
uint8 Enter_Pass[]="2.Enter_Pass:";
uint8*pointer=NULL;
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
void Lock_Door_Inti(void){
	
	PORT_Init();
	LED_Init();
	LCD_Init();
	IRQH_SetGlobalInterrupts(INTERRUPT_ENABLE);
	UART_Init();
	ServoMotor_Init();
	I2C_MasterInit();
	IRQH_SetCallBack(Rechived_Char);
	Welcome_Message();
	ServoMotor_Home();
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
void Welcome_Message(void){
	
uint8 Welcome[]="Hallo User";
uint8 Lock_door_message[]="Lock door By";
uint8 My_Name[]="Amgad_Atef";
uint8 attemps_Number[]="3 Attempts";
LCD_WriteCustomCharacter();
LCD_GoTo(0,3);
LCD_WriteString(Welcome);
	
	
	_delay_ms(2000);
	LCD_Clear();
	LCD_GoTo(0,2);
	LCD_WriteString(Lock_door_message);
	LCD_GoTo(1,3);
	LCD_WriteString(My_Name);
	_delay_ms(2000);
	LCD_Clear();
	LCD_GoTo(0,3);
	LCD_WriteString(attemps_Number);
	
	LCD_GoTo(1,5);
	
	LCD_WriteChar(0);
	LCD_GoTo(1,7);
	LCD_WriteChar(1);
	_delay_ms(2000);
	
	LCD_Clear();

	LCD_GoTo(0,0);
	LCD_WriteString(Change_Pass);
	LCD_GoTo(1,0);
	LCD_WriteString(Enter_Pass);
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
void Option_1(void){
	VALUE= UART_RX_Char_Status();
	if(VALUE==1){
if(RechivedChar=='1'){
	LCD_Clear();
	LCD_WriteString(Change_Pass);
	LCD_GoTo(1,0);
	VALUE=0;
	Cnt2=0;
	while(Cnt2<Size_Pass){
		VALUE=UART_RX_Char_Status();
		if (VALUE==1)
		{
			RX_RecivedMultiBytes[Cnt2]=RechivedChar;
			LCD_WriteChar('*');
			Cnt2++;
			VALUE=0;
		}
		if(Cnt2==Size_Pass){
			Pass_Full=1;
		}
		
		
	}
	Cnt2=0;

	if(Pass_Full==1){
		EEPROM_writemultiplebytes(RX_RecivedMultiBytes,Size_Pass,addres_EEPROM,0x00);
		_delay_ms(5);
		LCD_Clear();
		LCD_WriteString(Change_Pass);
		LCD_GoTo(1,0);
		LCD_WriteString(Enter_Pass);
		Pass_Full=0;
	}
				
				
			}
			else if (RechivedChar=='2'){
					
				Option_2();
				if (Arr_Pass_Full==1){
					
					check_pass();
				}
				
				
			}
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
void Option_2(void){
pointer=EEPROM_ReadMultipleBytes(addres_EEPROM,0x00);
_delay_ms(5);
	LCD_Clear();
	LCD_WriteString(Enter_Pass);
	
	VALUE=0;
	LCD_GoTo(1,0);
	while(Cnt2<Size_Pass)
	{
		VALUE= UART_RX_Char_Status();
		if (VALUE==1)
		{
			Arr[Cnt2]=RechivedChar;
			LCD_WriteChar('*');
			Cnt2++;
			VALUE=0;
		}
		if (Cnt2==Size_Pass)
		{
			Arr_Pass_Full=1;
			
		}
	}
	Cnt2=0;

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
void check_pass(void){
		if ((Arr[0]==pointer[0])&&(Arr[1]==pointer[1])&&(Arr[2]==pointer[2])&&(Arr[3]==pointer[3]))
		{
			uint8 Hallo_Owner[]="Hallo_Owner";
			ServoMotor_SetAngle18(90);
			LCD_Clear();
			LCD_GoTo(0,3);
			LCD_WriteString(Hallo_Owner);
			LCD_GoTo(1,8);
			LCD_WriteChar(2);
			LCD_GoTo(1,9);
			LCD_WriteChar(3);
			_delay_ms(2000);
			ServoMotor_Home();
			Arr_Pass_Full=0;
			LCD_Clear();
			LCD_WriteString(Change_Pass);
			LCD_GoTo(1,0);
			LCD_WriteString(Enter_Pass);
			Attempts=0;
			
		}
		
		else{
			Wrong_pass();
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
void Wrong_pass(void){
	uint8 wrong[]="Wrong Passward";
	uint8 Get_out[]="Calling Police";
	Attempts++;
	if (Attempts < 3){
		LCD_Clear();
		LCD_GoTo(0,1);
		LCD_WriteString(wrong);
		_delay_ms(2000);
	}
	else
	{
		uint8 i=0;
		LCD_Clear();
		LCD_GoTo(0,3);
		LCD_WriteString(Get_out);
	start_buzzer();
	
		for (i=0;i<5;i++)
		{
			_delay_ms(1000);
			LED_TGL();
			LCD_Clear();
			LCD_GoTo(0,3);
			LCD_WriteString(Get_out);
			
		}
		
	stop_buzzer();
 LED_OFF();
		Attempts =0;
	}
	LCD_Clear();
	LCD_GoTo(0,0);
	LCD_WriteString(Change_Pass);
	LCD_GoTo(1,0);
	LCD_WriteString(Enter_Pass);
}
/******************************************************************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName  void
* \Parameters (out): void
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void Start_application(void){
	Option_1();
	
}
/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
