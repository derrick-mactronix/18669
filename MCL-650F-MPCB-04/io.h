/*******************************************************************************
 *               Copyright(c) 2022, Mactronix. All rights reserved
 *
 *               File:         io.h
 *               Description:  IO ports assignments
 *               Author:       Jered Yang
 *               Date:         2022-07-06
 ******************************************************************************/

/** Inputs */
#define  PB_PRESENT_SEN                 53
#define  PUSHER_HOME_SEN                52
#define  INDEX_FRONT_SEN                51
#define  INDEX_BACK_SEN                 50
#define  TOP_RT_CLOSE_SEN               49
#define  TOP_RT_OPEN_SEN                48
#define  LOW_RT_CLOSE_SEN               47
#define  LOW_RT_OPEN_SEN                46

#define  ELEVATOR_TOP_RT_PB_SEN         45
#define  ELEVATOR_LOW_RT_PB_SEN         44
#define  ELEVATOR_TOP_RT_QB_SEN         43
#define  SPEED_CHANGE_RT_SEN            42
#define  SPEED_CHANGE_PLATFORM_SEN      41
#define  ELEVATOR_HOME_SEN              40
#define  QB_PRESENT_SEN                 39
#define  ELEVATOR_LOW_RT_QB_SEN         38

#define  UP_SAFETY_SEN                  35
#define  PB_WAFER_SEN                   34
#define  OVER_HEAT_SEN                  33
#define  PB_HBAR_SEN                    32
#define  PB_DIRECTION_SEN_FRONT         31
#define  PB_DIRECTION_SEN_BACK          30

#define  START_SEN                      0
#define  PAUSE_BUTTON_SEN               1



#define  ALARM_TRIG                     15

#define  PUSHER_STEP_DIR_TRIG           13
#define  PUSHER_STEP_PULSE_TRIG         14

/** Outputs */
#define  LOW_RET_OPEN_TRIG              2
#define  LOW_RET_CLOSE_TRIG             3
#define  ELEV_DIR_TRIG                  4
#define  ELEV_RUN_TRIG                  5
#define  ELEV_SPEED_TRIG                6

#define  TOP_RET_OPEN_TRIG             7
#define  TOP_RET_CLOSE_TRIG            8

#define  INDEX_TO_BACK_TRIG        9
#define  INDEX_TO_FRONT_TRIG       10

