/*
 * RGB_interface.h
 *
 * Created: 2/11/2023 5:15:36 AM
 *  Author: Yahia Ahmed
 */ 


#ifndef RGB_INTERFACE_H_
#define RGB_INTERFACE_H_
#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
/*
	Only the order can be changed like 
	RED_REG take replace by only one from 
	OCR0 OCR1B OCR1A and the same for 
	GREEN_REG and BLUE_REG 
	*/

#define  RED_REG      OCR0
#define  GREEN_REG    OCR1B
#define  BLUE_REG     OCR1A
/*Range
#define RGB_TYPE_MODE  COMMAN_ANODE
#define RGB_TYPE_MODE  COMMAN_CATHODE
*/
#define RGB_TYPE_MODE COMMAN_ANODE	
/* If you want to add a new color, you have to add it in a location equivalent to its index in the array*/
typedef enum{
	  RGB_Yellow=0,
	  RGB_Blue  ,
	  RGB_Green ,
	   RGB_Red,  
	  RGB_Orange,
	  RGB_Black ,
	  RGB_White ,
	  RGB_Purple,
	  RGB_Gray ,
	  RGB_Silver ,
	  RGB_Deep_pink, 
	  RGB_Olive,
	TOTAL_COLORS
}RGB_Color_type;

typedef enum{
	RED_INDEX=0,
	GREEN_INDEX,
	BLUE_INDEX
}RGB_INDEX;
typedef struct {
	u8 currRed;
	u8 currGreen;
	u8 currBlue;
	}currColor;
#define  COMMAN_CATHODE  1
#define  COMMAN_ANODE    2
void RGB_Init();
void RGB_lightWithColor(RGB_Color_type color);
void RGB_setColorRange(u8 redValue,u8 greenValu,u8 blue_value);
void RGB_showRoom(RGB_Color_type color);
void RGB_showRoomSwap(RGB_Color_type color1,RGB_Color_type color2);
bool_t RGB_showRoomIsRunning();
void RGB_TravelAllColors();
u8 RGB_totalNumOfColors();
void RGB_showRoomSwapDisaple();

#endif /* RGB_INTERFACE_H_ */