/*****************************************************************************
* File Name		: LedControl.h
* Version		: 1.0 
*
* Description:
*  This file contains the function prototypes and constants used in
*  LedControl.c
*
*******************************************************************************
* Copyright (2018), Cypress Semiconductor Corporation. All rights reserved.
*******************************************************************************
* This software, including source code, documentation and related materials
* (“Software”), is owned by Cypress Semiconductor Corporation or one of its
* subsidiaries (“Cypress”) and is protected by and subject to worldwide patent
* protection (United States and foreign), United States copyright laws and
* international treaty provisions. Therefore, you may use this Software only
* as provided in the license agreement accompanying the software package from
* which you obtained this Software (“EULA”).
*
* If no EULA applies, Cypress hereby grants you a personal, nonexclusive,
* non-transferable license to copy, modify, and compile the Software source
* code solely for use in connection with Cypress’s integrated circuit products.
* Any reproduction, modification, translation, compilation, or representation
* of this Software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, 
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED 
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress 
* reserves the right to make changes to the Software without notice. Cypress 
* does not assume any liability arising out of the application or use of the 
* Software or any product or circuit described in the Software. Cypress does 
* not authorize its products for use in any products where a malfunction or 
* failure of the Cypress product may reasonably be expected to result in 
* significant property damage, injury or death (“High Risk Product”). By 
* including Cypress’s product in a High Risk Product, the manufacturer of such 
* system or application assumes all risk of such use and in doing so agrees to 
* indemnify Cypress against all liability.
*******************************************************************************/

#ifndef LED_CONTROL_H		/* Guard to prevent multiple inclusions */
#define LED_CONTROL_H 

#include "cytypes.h"
#include "Gesture.h"


/*******************************************************************************
* 	Data Type Definitions
********************************************************************************/
	
typedef enum
{
	COLOR_OFF, 
	COLOR_VIOLET, 
	COLOR_INDIGO,
	COLOR_BLUE,
	COLOR_GREEN,
	COLOR_YELLOW,
	COLOR_ORANGE,
	COLOR_RED,
	COLOR_WHITE
}tLedColor;

/* Exponential values for brightness level control. */
typedef enum
{
	BRIGHT_LEVEL_0 = 500, 
	BRIGHT_LEVEL_1 = 1000,
	BRIGHT_LEVEL_2 = 2000,
	BRIGHT_LEVEL_3 = 4000,
	BRIGHT_LEVEL_4 = 8000,
	BRIGHT_LEVEL_5 = 12000,
	BRIGHT_LEVEL_6 = 16000,
	BRIGHT_LEVEL_7 = 20000,
	BRIGHT_LEVEL_8 = 24000,
	BRIGHT_LEVEL_9 = 28000
}tBrightLevel;


/*******************************************************************************
* 	Macro Definitions
********************************************************************************/

/* Defines the initial color of the RGB LED at power-up. */
#define INIT_LED_COLOR					COLOR_OFF

/* Defines the initial brightness level of the RGB LED at power-up. */
#define INIT_BRIGHT_LEVEL				BRIGHT_LEVEL_0

/* Defines the minimum delta or shift in the slider centroid (accumulated over
 * multiple scans) required to change the brightness level. 
 */
#define BRIGHT_CHANGE_ACCU_SLIDER_DELTA		(20)

/* Defines the PWM period value that turns off the LED */
#define LED_OFF_PWM_PERIOD				(0)


/*******************************************************************************
* 	Function Prototypes
*******************************************************************************/

void UpdateLedColor(tGestureId gestureId);
void SetLedColor(tLedColor ledColor, tBrightLevel brightness);

	
#endif /* #ifndef LED_CONTROL_H */


/* [] END OF FILE */
