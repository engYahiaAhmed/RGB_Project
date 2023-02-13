/*
 * RGB.c
 *
 * Created: 2/11/2023 5:14:38 AM
 *  Author: Yahia Ahmed
 */ 
#include "RGB_interface.h"
#include "RGB_private.h"
#include "DIO_Interface.h"
#include "Timers.h"
#include "LCD.h"
#include <util/delay.h>
volatile u8 ShowRoomColor=0,flagFree=1,flag=0,showRoomSwapFlag=0,showRoomSwapColor1=0,showRoomSwapColor2=0;
void RGB_Init()
{
	#if RGB_TYPE_MODE==COMMAN_ANODE
	TIMER0_Init(TIMER0_FASTPWM_MODE,TIMER0_SCALER_8);
	Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER1_SCALER_8);
	TIMER0_OC0Mode(OC0_NON_INVERTING);
	Timer1_OCRA1Mode(OCRA_NON_INVERTING);
	Timer1_OCRB1Mode(OCRB_NON_INVERTING);
	#elif RGB_TYPE_MODE==COMMAN_CATHODE
	TIMER0_Init(TIMER0_FASTPWM_MODE,TIMER0_SCALER_8);
	Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER1_SCALER_8);
	TIMER0_OC0Mode(OC0_NON_INVERTING);
	Timer1_OCRA1Mode(OCRA_NON_INVERTING);
	Timer1_OCRB1Mode(OCRB_NON_INVERTING);
	#endif
	TIMER2_Init(TIMER2_NORMAL_MODE,TIMER2_SCALER_8);
	GOLBLE_INT_ENABLE();
	ICR1=255;
}
void RGB_lightWithColor(RGB_Color_type color)
{
	#if RGB_TYPE_MODE == COMMAN_ANODE

	 RED_REG =255-RGB_ColorsArray[color][RED_INDEX];
	 GREEN_REG=255-RGB_ColorsArray[color][GREEN_INDEX];
	 BLUE_REG=255-RGB_ColorsArray[color][BLUE_INDEX];
	 
	 #elif RGB_TYPE_MODE == COMMAN_CATHODE

	 RED_REG =RGB_ColorsArray[color][RED_INDEX];
	 GREEN_REG =RGB_ColorsArray[color][GREEN_INDEX];
	 BLUE_REG =RGB_ColorsArray[color][BLUE_INDEX];
	 #endif
}
void RGB_setColorRange(u8 redValue,u8 greenValu,u8 blue_value)
{
	#if RGB_TYPE_MODE==COMMAN_ANODE
	RED_REG =255-redValue;
	GREEN_REG=255-greenValu;
	BLUE_REG=255-blue_value;
	#elif RGB_TYPE_MODE==COMMAN_CATHODE
	RED_REG = redValue;
	GREEN_REG=greenValu;
	BLUE_REG= blue_value;
	#endif
}
void RGB_showRoom(RGB_Color_type color)
{
	
	ShowRoomColor=color;
	flagFree=0;
	flag=1;
	TIMER2_OV_InterruptEnable();
	
}
bool_t RGB_showRoomIsRunning()
{
	
	return !flagFree;
}
void RGB_showRoomSwap(RGB_Color_type color1,RGB_Color_type color2)
{
	showRoomSwapFlag=1;
	showRoomSwapColor1=color1;
	showRoomSwapColor2=color2;
	ShowRoomColor=showRoomSwapColor1;
	TIMER2_OV_InterruptEnable();
	flagFree=0;
	flag=1;
}
void RGB_showRoomSwapDisaple()
{
	showRoomSwapFlag=0;
	flagFree=1;
	flag=0;
	TIMER2_OV_InterruptDisable();
}
void RGB_TravelAllColors()
{
	u8 i;
	for(i=0;i<TOTAL_COLORS;i++)
	{
		RGB_lightWithColor(i);
		_delay_ms(2000);
	}
}
u8 RGB_totalNumOfColors()
{
	return TOTAL_COLORS;
}
ISR(TIMER2_OVF_vect)
{
	static u8 c=0,c2=0;
	static REG,RedFlag=0,GreenFlag=0,BlueFlag=0;
	if(flag==1)
	{
		flag=0;
		c=0;
		c2=0;
		RedFlag=0;
		GreenFlag=0;
		BlueFlag=0;
	}
	TCNT2=6;
	c++;
 	if(c == 100 )
 	{
		c2++;
		c=0;
		#if RGB_TYPE_MODE == COMMAN_ANODE
		DIO_TogglePin(PINC0);
		if(RGB_ColorsArray[ShowRoomColor][RED_INDEX] > (255-RED_REG))
		{
			RED_REG=RED_REG-1;
			
		}else if (RGB_ColorsArray[ShowRoomColor][RED_INDEX]<(255-RED_REG))
		{
			RED_REG=RED_REG+1;
		}else
		{
			RedFlag=1;
		}
		if(RGB_ColorsArray[ShowRoomColor][GREEN_INDEX] > (255-GREEN_REG))
		{
			GREEN_REG=GREEN_REG-1;
			
		}else if (RGB_ColorsArray[ShowRoomColor][GREEN_INDEX]<(255-GREEN_REG))
		{
			GREEN_REG=GREEN_REG+1;
		}else
		{
			GreenFlag=1;
		}
		if(RGB_ColorsArray[ShowRoomColor][BLUE_INDEX] > (255-BLUE_REG))
		{
			BLUE_REG=BLUE_REG-1;
			
		}else if (RGB_ColorsArray[ShowRoomColor][BLUE_INDEX]<(255-BLUE_REG))
		{
			BLUE_REG=BLUE_REG+1;
		}else
		{
			BlueFlag=1;
		}
		#elif RGB_TYPE_MODE == COMMAN_CATHODE
		if(RGB_ColorsArray[ShowRoomColor][RED_INDEX] < RED_REG)
		{
			RED_REG=RED_REG-1;
			
		}else if (RGB_ColorsArray[ShowRoomColor][RED_INDEX]>RED_REG)
		{
			RED_REG=RED_REG+1;
		}else
		{
			RedFlag=1;
		}
		if(RGB_ColorsArray[ShowRoomColor][GREEN_INDEX] < GREEN_REG)
		{
			GREEN_REG=GREEN_REG-1;
			
		}else if (RGB_ColorsArray[ShowRoomColor][GREEN_INDEX]> GREEN_REG)
		{
			GREEN_REG=GREEN_REG+1;
		}else
		{
			GreenFlag=1;
		}
		if(RGB_ColorsArray[ShowRoomColor][BLUE_INDEX] < BLUE_REG)
		{
			BLUE_REG=BLUE_REG-1;
			
		}else if (RGB_ColorsArray[ShowRoomColor][BLUE_INDEX]>BLUE_REG)
		{
			BLUE_REG=BLUE_REG+1;
		}else
		{
			BlueFlag=1;
		}
		#endif
		
	}
	if((RedFlag == 1  && GreenFlag == 1  && BlueFlag == 1 )|| c2 == 255)
	{
		if(showRoomSwapFlag == 1)
		{
			ShowRoomColor = (ShowRoomColor==showRoomSwapColor1) ? showRoomSwapColor2:showRoomSwapColor1;
			flag=1;
		}else{
			flagFree=1;
			TIMER2_OV_InterruptDisable();
		}
		
	}
	
	
}
