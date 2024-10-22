/*******************************************************************************
 *               Copyright(c) 2022, Mactronix Inc. All rights reserved
 *
 *               File:         defines.h
 *               Description:  all global defines
 *               Author: Jered Yang
 ******************************************************************************/

#define  TRUE                           1
#define  FALSE                          0
#define  ON                             1
#define  OFF                            0
#define  NO_ERROR                       0 // good: no error happened
#define  ERROR                         -1

#define  DEFAULT_PASSWORD             "88"
#define  SETUP_PASSWORD             "0028"

#define  NEEDABORT                     200
#define  NEEDRESUME                    201

// define boat type being used
#define  NONE                           0
#define  PBOAT_TOP                      1
#define  PBOAT_LOW                      2
#define  QBOAT_TOP                      3
#define  QBOAT_LOW                      4

// define retainer motion
#define  TOP_OUT_HOME                   0
#define  TOP_CLOSE_POS                  1
#define  LOW_OUT_HOME                   2
#define  LOW_CLOSE_POS                  3

/** motors available */
#define  RETAINER                       1
#define  ELEVATOR                       2

/** retainer direction */
#define  RT_OPEN_DIR                    0
#define  RT_CLOSE_DIR                   1

/** elevator direction */
#define  ELEV_UP_DIR                    0
#define  ELEV_DOWN_DIR                  1

/** Carrier direction */
#define  PB_HB_BACK                     0
#define  PB_HB_FRONT                    1

/** Transfer mode */
#define  FACE_TO_FACE                   1
#define  STANDARD                       0

#define  JR_ONLY                        1
#define  SR_ONLY                        2
#define  JR_N_SR                        3


#define MS_TIMER millis()

const unsigned long TIMEOUT         = 800L;   // time out value
const unsigned long TIMEOUT_ELEV    = 15000L; // 15 sec
const unsigned long TIMEOUT_RT      = 8000L;  // 8  sec
const unsigned long TIMEOUT_INDEX   = 9000L;  // 9  sec
const unsigned long TIMEOUT_DISPLAY = 60000L; // 60  sec
