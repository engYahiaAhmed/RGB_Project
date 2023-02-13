/*
 * RGB_config.c
 *
 * Created: 2/11/2023 5:18:37 AM
 *  Author: Yahia Ahmed
 */ 
#include "RGB_interface.h"
/* insert your new color range then go to REG_interface file to insert its name in RGB_Color_type enum*/
	
const u8 RGB_ColorsArray[TOTAL_COLORS][3]={
	
	{255,255,0},       /*Yellow  */
	{0,0,255},		    /*Blue  */
	{0,255,0},          /*Green  */
	{255,0,0},          /*Red  */
	{255,165,0},        /*orange  */
	{0,0,0},            /*Black  */
	{255,255,255},      /*White */
	{128,0,128},		/*Purple */
	{128,128,128},      /* Gray */
	{192,192,192},      /*Silver  */
	{255,20,147},       /* deep pink */
	{128,128,0}			/*Olive*/
		//totalColors=12
	};	
