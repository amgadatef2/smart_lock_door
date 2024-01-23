/*
 * PORT_LCFG.c
 *
 * Created: 9/16/2023 12:15:32 PM
 *  Author: amgad
 */ 

#include "PORT_LCFG.h"

PIN_PARAMETERS PORT_Initialization[DEFINED_PINS]=
{
	
    { PORTA_PIN1   ,  PIN_DIR_OUTPUT  }, //Rs
    { PORTA_PIN2   ,  PIN_DIR_OUTPUT  }, //E
    { PORTA_PIN3   ,  PIN_DIR_OUTPUT  }, //D4
    { PORTA_PIN4   ,  PIN_DIR_OUTPUT  }, //D5
    { PORTA_PIN5   ,  PIN_DIR_OUTPUT  }, //D6
    { PORTA_PIN6   ,  PIN_DIR_OUTPUT  }, //D7
	//{ PORTA_PIN7   ,  PIN_DIR_INPUT   },  //ADC
	//{ PORTC_PIN2   ,  PIN_DIR_OUTPUT  }  //ADC
		//Master
	{ PORTB_PIN5   ,  PIN_DIR_OUTPUT  },  //MOSI
	{ PORTB_PIN6   ,  PIN_DIR_INPUT  },	  //MISO
	{ PORTB_PIN4   ,  PIN_DIR_OUTPUT  }, //ss
	{ PORTB_PIN7   ,  PIN_DIR_OUTPUT  }, //clk
	{ PORTD_PIN0   ,  PIN_DIR_INPUT  } ,
	{ PORTD_PIN1   ,  PIN_DIR_OUTPUT  },
		{ PORTD_PIN5   ,  PIN_DIR_OUTPUT  },
		{ PORTC_PIN0   ,  PIN_DIR_OUTPUT  },//SCL
		{ PORTC_PIN1   ,  PIN_DIR_OUTPUT  },  //SDA
		{ PORTC_PIN5  ,  PIN_DIR_OUTPUT  }  //buzzer
		
						
};  //This is Array of Structs