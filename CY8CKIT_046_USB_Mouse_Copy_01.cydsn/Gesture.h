/*****************************************************************************
* File Name		: Gesture.h
* Version		: 1.0 
*
* Description:
*  This file contains the function prototypes and constants used in
*  Gesture.c
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

#ifndef GESTURE_H		/* Guard to prevent multiple inclusions */
	#define GESTURE_H 

	#include "cytypes.h"
	#include "CapSense.h"
	#include "stdbool.h"


	/*******************************************************************************
	* 	Macro Definitions
	*******************************************************************************/

	/* Defines the resolution of the radial slider */
	#define SLIDER_RESOLUTION				(180)
	
    /* Macro used to calculate xPos and yPos from radius and theta in the DetectGesture API - 
    if not defined then xPos and yPos will not be calculated by the DetectGesture() API */
	#define CALCULATE_X_Y_IN_GES	
    
    /* Defines the number of sticky gestures supported in the design - max 4 and minimum 0 
        The type of gesture which should be handled as sticky is defined by the STICKY_GESTURE_x macros 
        Note that number of STICKY_GESTURE_x macros used depend on the number of sticky macros supported */
    #define NO_OF_STICKY_GESTURES       2    
    #define STICKY_GESTURE_1            GESTURE_UP_SWIPE
    #define STICKY_GESTURE_2            GESTURE_DOWN_SWIPE
    #define STICKY_GESTURE_3            GESTURE_LEFT_SWIPE
    #define STICKY_GESTURE_4            GESTURE_RIGHT_SWIPE
    
    /* Defines the condition to check before storing the sticky gesture - the condition will vary depending 
        on number of sticky gestures supported */
    #if (NO_OF_STICKY_GESTURES == 0)
        #define STICKY_GESTURE_CONDITION                 (0)
    #elif (NO_OF_STICKY_GESTURES == 1)
        #define STICKY_GESTURE_CONDITION(gesture,g1)     ((gesture == g1))
    #elif (NO_OF_STICKY_GESTURES == 2)
        #define STICKY_GESTURE_CONDITION(gesture,g1,g2)     ((gesture == g1) || (gesture == g2))
    #elif (NO_OF_STICKY_GESTURES == 3)
        #define STICKY_GESTURE_CONDITION(gesture,g1,g2,g3)     ((gesture == g1) || (gesture == g2) || (gesture == g3))
    #else        
        #define STICKY_GESTURE_CONDITION(gesture,g1,g2,g3,g4)     ((gesture == g1) || (gesture == g2) || (gesture == g3) || (gesture == g4))
    #endif
		
	/* These macros indicate the sensor number or index to be used with CapSense
	 * APIs.
	 */
	#define LEFT_BTN_ID					CapSense_LEFT_WDGT_ID
	#define RIGHT_BTN_ID				CapSense_RIGHT_WDGT_ID
	#define UP_BTN_ID					CapSense_UP_WDGT_ID
	#define DOWN_BTN_ID					CapSense_DOWN_WDGT_ID
	#define CENTRE_BTN_ID				CapSense_CENTRE_WDGT_ID	
	#define SLIDER_ID					CapSense_RADIALSLIDER0_WDGT_ID

	/* These macros defines the mask for each sensor to be used with CapSense APIs
	 * or global variables. 
	 */
	#define LEFT_BTN_MASK				(1 << LEFT_BTN_ID)
	#define RIGHT_BTN_MASK				(1 << RIGHT_BTN_ID)
	#define UP_BTN_MASK					(1 << UP_BTN_ID)
	#define DOWN_BTN_MASK				(1 << DOWN_BTN_ID)
	#define CENTRE_BTN_MASK				(1 << CENTRE_BTN_ID)
	#define SLIDER_ACT_MASK				(1 << SLIDER_ID)
		
	#define SLIDER_4_SECTOR_MASK		0x06
	#define SECTOR_LEFT					0x04
	#define SECTOR_UP					0x06
	#define SECTOR_RIGHT				0x00
	#define SECTOR_DOWN					0x02
		
//	#define GetSignal(x)				CapSense_GetDiffCountData(x)
		
	#define SLIDER_MID_POS				SLIDER_RESOLUTION/2

	#define ANGLE_0						0
	#define ANGLE_45					(SLIDER_RESOLUTION/8)
	#define ANGLE_90					(SLIDER_RESOLUTION/4)
	#define ANGLE_135					(ANGLE_45 + ANGLE_90)
	#define ANGLE_180					(SLIDER_RESOLUTION/2)
	#define INVALID_ANGLE				250
		
	#define INVALID_SECTOR				255
	#define INVALID_SINE				1000
	#define INVALID_RADIUS				0xFF
		
	#define MAX_X_Y						4
	#define MAX_R						4
	#define MAX_SINE					256
		
	#define GESTURE_STATE_IDLE				1
	#define GESTURE_STATE_1ST_SECTOR		2
	#define GESTURE_STATE_1ST_SECTOR_MOVED	3
	#define GESTURE_STATE_2ND_SECTOR		4
	#define GESTURE_STATE_3RD_SECTOR		5
	#define GESTURE_STATE_OUTWARD_SWIPE		6
	#define GESTURE_STATE_SECTOR_RELEASE	7
	#define GESTURE_STATE_ERROR				8

	#define SECTOR_0						0
	#define SECTOR_1						1
	#define SECTOR_2						2
	#define SECTOR_3						3
	#define SECTOR_4						4

	#define SECTOR_0_WEIGHT						2
	#define SECTOR_1_WEIGHT						3
	#define SECTOR_2_WEIGHT						5
	#define SECTOR_3_WEIGHT						7
	#define SECTOR_4_WEIGHT						11

	#define FIRST_SECTOR_WEIGHT				13
	#define SECOND_SECTOR_WEIGHT			17
	#define THIRD_SECTOR_WEIGHT				19

	#define SECTOR_1_0_3					(SECTOR_1_WEIGHT*FIRST_SECTOR_WEIGHT + SECTOR_0_WEIGHT*SECOND_SECTOR_WEIGHT + SECTOR_3_WEIGHT*THIRD_SECTOR_WEIGHT)
	#define SECTOR_3_0_1					(SECTOR_3_WEIGHT*FIRST_SECTOR_WEIGHT + SECTOR_0_WEIGHT*SECOND_SECTOR_WEIGHT + SECTOR_1_WEIGHT*THIRD_SECTOR_WEIGHT)
	#define SECTOR_2_0_4					(SECTOR_2_WEIGHT*FIRST_SECTOR_WEIGHT + SECTOR_0_WEIGHT*SECOND_SECTOR_WEIGHT + SECTOR_4_WEIGHT*THIRD_SECTOR_WEIGHT)
	#define SECTOR_4_0_2					(SECTOR_4_WEIGHT*FIRST_SECTOR_WEIGHT + SECTOR_0_WEIGHT*SECOND_SECTOR_WEIGHT + SECTOR_2_WEIGHT*THIRD_SECTOR_WEIGHT)
	#define SECTOR_1_2_3					(SECTOR_1_WEIGHT*FIRST_SECTOR_WEIGHT + SECTOR_2_WEIGHT*SECOND_SECTOR_WEIGHT + SECTOR_3_WEIGHT*THIRD_SECTOR_WEIGHT)
	#define SECTOR_2_3_4					(SECTOR_2_WEIGHT*FIRST_SECTOR_WEIGHT + SECTOR_3_WEIGHT*SECOND_SECTOR_WEIGHT + SECTOR_4_WEIGHT*THIRD_SECTOR_WEIGHT)
	#define SECTOR_3_4_1					(SECTOR_3_WEIGHT*FIRST_SECTOR_WEIGHT + SECTOR_4_WEIGHT*SECOND_SECTOR_WEIGHT + SECTOR_1_WEIGHT*THIRD_SECTOR_WEIGHT)
	#define SECTOR_4_1_2					(SECTOR_4_WEIGHT*FIRST_SECTOR_WEIGHT + SECTOR_1_WEIGHT*SECOND_SECTOR_WEIGHT + SECTOR_2_WEIGHT*THIRD_SECTOR_WEIGHT)
	#define SECTOR_1_4_3					(SECTOR_1_WEIGHT*FIRST_SECTOR_WEIGHT + SECTOR_4_WEIGHT*SECOND_SECTOR_WEIGHT + SECTOR_3_WEIGHT*THIRD_SECTOR_WEIGHT)
	#define SECTOR_4_3_2					(SECTOR_4_WEIGHT*FIRST_SECTOR_WEIGHT + SECTOR_3_WEIGHT*SECOND_SECTOR_WEIGHT + SECTOR_2_WEIGHT*THIRD_SECTOR_WEIGHT)
	#define SECTOR_3_2_1					(SECTOR_3_WEIGHT*FIRST_SECTOR_WEIGHT + SECTOR_2_WEIGHT*SECOND_SECTOR_WEIGHT + SECTOR_1_WEIGHT*THIRD_SECTOR_WEIGHT)
	#define SECTOR_2_1_4					(SECTOR_2_WEIGHT*FIRST_SECTOR_WEIGHT + SECTOR_1_WEIGHT*SECOND_SECTOR_WEIGHT + SECTOR_4_WEIGHT*THIRD_SECTOR_WEIGHT)

	#define FIRST_SECTOR_INDEX				0
	#define SECOND_SECTOR_INDEX				1
	#define THIRD_SECTOR_INDEX				2

	#define TOTAL_SECTORS					5

	#define TAP_TIME_1_SEC					100

	#define THETA_CHANGE_THRESHOLD			ANGLE_45
	#define RADIUS_CHANGE_THRESHOLD			2

	#define SECTOR_DEBOUNCE					3

	/*******************************************************************************
	* 	Data Type Definitions
	*******************************************************************************/

	/* Defines the various gesture Ids */
	typedef enum
	{
		GESTURE_NONE,
		GESTURE_RELEASE,
		GESTURE_LEFT_CLICK,
		GESTURE_RIGHT_CLICK,
		GESTURE_MIDDLE_CLICK,
		GESTURE_LEFT_SWIPE, 
		GESTURE_RIGHT_SWIPE,
		GESTURE_UP_SWIPE,
		GESTURE_DOWN_SWIPE,
		GESTURE_OUTWARD_SWIPE,
		GESTURE_INNER_CLKWISE,
		GESTURE_INNER_COUNTER_CLKWISE, 
		GESTURE_OUTER_CLKWISE,
		GESTURE_OUTER_COUNTER_CLKWISE,
		GESTURE_UP_CLICK,
		GESTURE_DOWN_CLICK,
		GESTURE_INVALID
	}tGestureId;

	/*****************************************************************************
	* 	Function Prototypes
	*****************************************************************************/

	tGestureId DetectGesture(uint8 isAnySensorActive);

	extern uint32 capsenseButtonStatus;
	extern int32 xPos, yPos;
	/* Accumulated theta and radius during CapSense activity on the Gesture Pad*/
	extern int32 accRadius, accTheta;

	extern uint32 radius;
	extern int32 theta;
		
#endif /* #ifndef GESTURES_H */

/* [] END OF FILE */
