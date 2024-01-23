

/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  GPT_Core.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "GPT_Core.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
uint32 TIMER0Number_OVF_Flags_g;
uint32 TIMER0Init_Value_g;
uint32 TIMER0Number_CmprMatch_Flags_g;

uint32 TIMER1Number_OVF_Flags_g;
uint32 TIMER1Init_Value_g;
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
void GPT_Init(void)
{
	#if (TIMER0_STATE == TIMER_ENABLE)
	  #if (TIMER0_MODE == NORMAL_MODE)
	  CLR_BIT (TCCR0 , 3);
	  CLR_BIT (TCCR0 , 6);
	    #if (TIMER0_INTERRUPT_STATE == TIMER_INTERRUPT_ENABLE)
		SET_BIT (TIMSK , 0);
		#elif (TIMER0_INTERRUPT_STATE == TIMER_INTERRUPT_DISABLE)
		CLR_BIT (TIMSK , 0);
		#endif //#if (TIMER0_INTERRUPT_STATE == TIMER_INTERRUPT_ENABLE)
	  #elif (TIMER0_MODE == CTC_MODE)
	  SET_BIT (TCCR0 , 3);
	  CLR_BIT (TCCR0 , 6);
	     #if (TIMER0_INTERRUPT_STATE == TIMER_INTERRUPT_ENABLE)
	     SET_BIT (TIMSK , 1);
	     #elif (TIMER0_INTERRUPT_STATE == TIMER_INTERRUPT_DISABLE)
	     CLR_BIT (TIMSK , 1);
	     #endif //#if (TIMER0_INTERRUPT_STATE == TIMER_INTERRUPT_ENABLE)
	  #endif //#if (TIMER0_MODE == NORMAL_MODE)
	  #if (TIMER0_PRESCALE == TIMER_CLK_SRC_NO_PRESCALING)
	  TCCR0 |= 0X01;
	  #elif (TIMER0_PRESCALE == TIMER_CLK_SRC_PRESCALING_8)
	  TCCR0 |= 0X02;
	  #elif (TIMER0_PRESCALE == TIMER_CLK_SRC_PRESCALING_64)
	  TCCR0 |= 0X03;
	  #elif (TIMER0_PRESCALE == TIMER_CLK_SRC_PRESCALING_256)
	  TCCR0 |= 0X04;
	  #elif (TIMER0_PRESCALE == TIMER_CLK_SRC_PRESCALING_1024)
	  TCCR0 |= 0X05;
	  #endif // #if (TIMER0_PRESCALE == TIMER_CLK_SRC_NO_PRESCALING) 
	#endif //#if (TIMER0_STATE == TIMER_ENABLE)
	
	#if (TIMER1_STATE == TIMER_ENABLE)
	  #if (TIMER1_MODE == NORMAL_MODE)
	  CLR_BIT (TCCR1A , 0);
	  CLR_BIT (TCCR1A , 1);
	  CLR_BIT (TCCR1B , 3);
	  CLR_BIT (TCCR1B , 4);
	    #if (TIMER1_INTERRUPT_STATE == TIMER_INTERRUPT_ENABLE)
	    SET_BIT (TIMSK , 2);
	    #elif (TIMER1_INTERRUPT_STATE == TIMER_INTERRUPT_DISABLE)
	    CLR_BIT (TIMSK , 2);
	    #endif //#if (TIMER1_INTERRUPT_STATE == TIMER_INTERRUPT_ENABLE)
	  #elif (TIMER1_MODE == CTC_MODE)
	  CLR_BIT (TCCR1A , 0);
	  CLR_BIT (TCCR1A , 1);
	  SET_BIT (TCCR1B , 3);
	  CLR_BIT (TCCR1B , 4);
	     #if (TIMER1_INTERRUPT_STATE == TIMER_INTERRUPT_ENABLE)
	     SET_BIT (TIMSK , 4);
	     #elif (TIMER1_INTERRUPT_STATE == TIMER_INTERRUPT_DISABLE)
	     CLR_BIT (TIMSK , 4);
	     #endif //#if (TIMER1_INTERRUPT_STATE == TIMER_INTERRUPT_ENABLE)
	  #endif //#if (TIMER1_MODE == NORMAL_MODE)
	  
	#if (TIMER1_PRESCALE == TIMER_CLK_SRC_NO_PRESCALING)
	TCCR1B |= 0X01;
	#elif (TIMER1_PRESCALE == TIMER_CLK_SRC_PRESCALING_8)
	TCCR1B |= 0X02;
	#elif (TIMER1_PRESCALE == TIMER_CLK_SRC_PRESCALING_64)
	TCCR1B |= 0X03;
	#elif (TIMER1_PRESCALE == TIMER_CLK_SRC_PRESCALING_256)
	TCCR1B |= 0X04;
	#elif (TIMER1_PRESCALE == TIMER_CLK_SRC_PRESCALING_1024)
	TCCR1B |= 0X05;
	#endif //(TIMER1_PRESCALE == TIMER_CLK_SRC_NO_PRESCALING)
	
	#endif //#if (TIMER1_STATE == TIMER_ENABLE)
	
	#if (TIMER2_STATE == TIMER_ENABLE)
	  #if (TIMER2_MODE == NORMAL_MODE)
	  
	  #elif (TIMER2_MODE == CTC_MODE)
	  
	  #endif //#if (TIMER2_MODE == NORMAL_MODE)
	
	#endif //#if (TIMER2_STATE == TIMER_ENABLE)
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
void GPT_SetTime (void)
{
	uint8 MCU_CLK_Mhz = 16; //16MHz = 16,000,000
	#if (TIMER0_STATE == TIMER_ENABLE)
	  #if (TIMER0_MODE == NORMAL_MODE)
	  uint8 TIMER0Tick_Time_us = TIMER0_PRESCALE / MCU_CLK_Mhz;  //64us
	  uint32 Time_ms = TIMER0_COUNTING_MS;
	  uint32 TIMER0Total_Ticks = (Time_ms*1000)/ TIMER0Tick_Time_us; 	  
	  TIMER0Number_OVF_Flags_g = TIMER0Total_Ticks / TIMER0_REGISTER_CAPACITY;
	  TIMER0Init_Value_g = TIMER0_REGISTER_CAPACITY - (TIMER0Total_Ticks % TIMER0_REGISTER_CAPACITY);	  
	  TCNT0 = TIMER0Init_Value_g;
	  if((TIMER0Total_Ticks % TIMER0_REGISTER_CAPACITY) !=0 )
	  {
	  	TIMER0Number_OVF_Flags_g++;
	  }
	  
	  #elif (TIMER0_MODE == CTC_MODE)
	  uint8 TIMER0Tick_Time_us = TIMER0_PRESCALE / MCU_CLK_Mhz;
	  uint32 Time_ms = TIMER0_COUNTING_MS;
	  uint32 TIMER0Total_Ticks = (Time_ms*1000)/ TIMER0Tick_Time_us;
	  OCR0 = 156; //10ms
	  TIMER0Number_CmprMatch_Flags_g = TIMER0Total_Ticks / 156;
	  
	  #endif //#if (TIMER0_MODE == NORMAL_MODE)
	#endif //#if (TIMER0_STATE == TIMER_ENABLE)
	
	#if (TIMER1_STATE == TIMER_ENABLE)
	  #if (TIMER1_MODE == NORMAL_MODE)
	  uint8 TIMER1Tick_Time_us = TIMER1_PRESCALE / MCU_CLK_Mhz;
	  uint32 Time_ms = TIMER1_COUNTING_MS;
	  uint32 TIMER1Total_Ticks = (Time_ms*1000)/ TIMER1Tick_Time_us;
	  TIMER1Init_Value_g = (TIMER1_REGISTER_CAPACITY - TIMER1Total_Ticks);
	  TCNT1_16BIT_ACCESS = TIMER1Init_Value_g;
	  
	  #elif (TIMER1_MODE == CTC_MODE)
	  uint8 TIMER1Tick_Time_us = TIMER1_PRESCALE / MCU_CLK_Mhz;
	  uint32 Time_ms = TIMER1_COUNTING_MS;
	  uint32 TIMER1Total_Ticks = (Time_ms*1000)/ TIMER1Tick_Time_us;
	  OCR1A_16BIT_ACCESS = TIMER1Total_Ticks;
	  #endif //#if (TIMER1_MODE == NORMAL_MODE)
	#endif //#if (TIMER1_STATE == TIMER_ENABLE)
	
}
/**********************************************************************************************************************
 *  END OF FILE: GPT_Core.c
 *********************************************************************************************************************/
