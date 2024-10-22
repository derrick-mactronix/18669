/*******************************************************************************
 *               Copyright(c) 2007, Mactronix Inc. All rights reserved
 *
 *               File:         motion.lib Description:  Motion module Author:
 *      Marvin Zhang Date:         04/09/2007
 ******************************************************************************/
/*****************************  Functions List


** int  ElevUp();
** int  ElevMoveDown();
** int  ElevMoveHome();

** int  IndexToFront();
** int  IndexToBack();
** void MoveOneStepCW();
** void MoveOneStepCCW();
** int  CalibratePusher();
** int  PushUp();
** int  PushDown();

** int  IsIndexAtFront();
** int  IsIndexAtBack();

** int  IsOverHeated();
** int  IsElevAtTopRetainerPB();
** int  IsElevAtLowRetainerPB();
** int  IsElevAtTopRetainerQB();
** int  IsElevAtLowRetainerQB();
** int  IsElevQbSpeedChange();
** int  IsElevPlatformSpeedChange();
** int  IsElevHome();
** int  IsPusherHome();
** int  IsTopRetainerOpen();
** int  IsTopRetainerClose();
** int  IsLowRetainerOpen();
** int  IsLowRetainerClose();
** int  IsElevUpSafe();
** int  IsPBHBDirFront();
******************************************************************************/

/*==============================================================================
 *                        Function: int ElevUp()
 *============================================================================*/
/*** BeginHeader ElevUp */
int ElevUp();
/*** EndHeader */
int ElevUp() {
    unsigned long end;
    int  up, re;
    char nearTargetPos;

    nearTargetPos = FALSE; // add this check to prevent RT open too early

    if ((g_bAdaptor == TRUE) && (g_bSrJrTransfer > JR_ONLY)) {
        if (IsElevHome() &&
            (IsElevAtLowRetainerPB() || IsElevAtTopRetainerPB()
             || IsElevAtLowRetainerQB() ||
             IsElevAtTopRetainerQB())) {
            return ERR_ELEV_POSITION;
        }
    } else if ((g_bAdaptor == TRUE) && (g_bSrJrTransfer == JR_ONLY)) {
        if (IsElevHome() &&
            (IsElevAtLowRetainerPB() || IsElevAtLowRetainerQB())) {
            return ERR_ELEV_POSITION;
        }
    } else if ((g_bAdaptor == FALSE) && (g_bSrJrTransfer > JR_ONLY)) {
        if (IsElevHome() &&
            (IsElevAtLowRetainerPB() || IsElevAtTopRetainerPB())) {
            return ERR_ELEV_POSITION;
        }
    } else {
        if (IsElevHome() && IsElevAtLowRetainerPB()) {
            return ERR_ELEV_POSITION;
        }
    }

    if (((g_bSrJrTransfer > JR_ONLY) && IsElevAtTopRetainerPB())
        || ((g_bSrJrTransfer == JR_ONLY) && IsElevAtLowRetainerPB())) {
        digitalWrite(ELEV_RUN_TRIG, 1);
        return NO_ERROR;
    }

    setMotorDrive(ELEVATOR, ELEV_UP_DIR);
    end = MS_TIMER + TIMEOUT_ELEV;

    while (MS_TIMER < end) {
        if (((re = pauseCheck()) != NO_ERROR)
            || ((re = upSafetyCheck()) != NO_ERROR)
            || ((re = BoatCheck()) != NO_ERROR)) {
            if (re == NEEDRESUME) {
                end = MS_TIMER + TIMEOUT_ELEV; // reset timeout timer
                setMotorDrive(ELEVATOR, ELEV_UP_DIR);

                if (g_bNeedMachineCycle == TRUE) {
                    DisplayInCycling();
                } else if (g_bTech == TRUE) {
                    DisplayElevMoving();
                } else {
                    DisplayInOperation();
                }
            } else {
                return re;
            }
        }

        if (IsElevPlatformSpeedChange()) {
            // change to high speed
            digitalWrite(ELEV_SPEED_TRIG, 1);
            g_bHighSpeed = TRUE;
        }

        if (g_bAdaptor == FALSE) {
            switch (g_wBoatType) {
                case PBOAT_TOP:
                    if (IsElevAtLowRetainerPB()) {
                        // change to low speed
                        digitalWrite(ELEV_SPEED_TRIG, 0);
                        g_bHighSpeed  = FALSE;
                        nearTargetPos = TRUE;
                    }
                    break;

                case QBOAT_TOP:
                    if (IsElevAtLowRetainerQB()) {
                        // change to low speed
                        digitalWrite(ELEV_SPEED_TRIG, 0);
                        g_bHighSpeed  = FALSE;
                        nearTargetPos = TRUE;
                    }
                    break;
                
                case PBOAT_LOW:
                case QBOAT_LOW:
                default:
                    if (IsElevQbSpeedChange()) {
                        // change to low speed
                        digitalWrite(ELEV_SPEED_TRIG, 0);
                        g_bHighSpeed  = FALSE;
                        nearTargetPos = TRUE;
                    }
                    break;
            }

            // conditional stop
            switch (g_wBoatType) {
                case PBOAT_LOW:
                case QBOAT_LOW:
                    if (nearTargetPos && IsElevAtLowRetainerPB()) {
                        // stop motor RUN
                        msDelay(20); // to better trigger the sensor
                        digitalWrite(ELEV_RUN_TRIG, 1);
                        return NO_ERROR;
                    }
                    break;
                case PBOAT_TOP:
                case QBOAT_TOP:
                    if (IsElevAtTopRetainerPB()) {
                        // stop motor RUN
                        msDelay(20); // to better trigger the sensor
                        digitalWrite(ELEV_RUN_TRIG, 1);
                        return NO_ERROR;
                    }
                    break;
                default:
                    break;
            }
        } else {
            // with qb adaptor
            switch (g_wBoatType) {
                case PBOAT_TOP:
                    if (IsElevAtLowRetainerPB()) {
                        // change to low speed
                        digitalWrite(ELEV_SPEED_TRIG, 0);
                        g_bHighSpeed  = FALSE;
                        nearTargetPos = TRUE;
                    }
                    break;

                case QBOAT_TOP:
                case PBOAT_LOW:
                    if (IsElevAtLowRetainerQB()) {
                        // change to low speed
                        digitalWrite(ELEV_SPEED_TRIG, 0);
                        g_bHighSpeed  = FALSE;
                        nearTargetPos = TRUE;                        
                    }
                    break;
                
                case QBOAT_LOW:
                default:
                    if (IsElevQbSpeedChange()) {
                        // change to low speed
                        digitalWrite(ELEV_SPEED_TRIG, 0);
                        g_bHighSpeed  = FALSE;
                        nearTargetPos = TRUE;                        
                    }
                    break;
            }

            // conditional stop
            switch (g_wBoatType) {
                case PBOAT_LOW:
                    if (nearTargetPos && IsElevAtLowRetainerPB()) {
                        // stop motor RUN
                        msDelay(20); // to better trigger the sensor
                        digitalWrite(ELEV_RUN_TRIG, 1);
                        return NO_ERROR;
                    }
                    break;
                case QBOAT_LOW:
                    if (nearTargetPos && IsElevAtLowRetainerQB()) {
                        // stop motor RUN
                        msDelay(20); // to better trigger the sensor
                        digitalWrite(ELEV_RUN_TRIG, 1);
                        return NO_ERROR;
                    }
                    break;
                case PBOAT_TOP:
                    if (IsElevAtTopRetainerPB()) {
                        // stop motor RUN
                        msDelay(20); // to better trigger the sensor
                        digitalWrite(ELEV_RUN_TRIG, 1);
                        return NO_ERROR;
                    }
                    break;
                case QBOAT_TOP:
                    if (IsElevAtTopRetainerQB()) {
                        // stop motor RUN
                        msDelay(20); // to better trigger the sensor
                        digitalWrite(ELEV_RUN_TRIG, 1);
                        return NO_ERROR;
                    }
                    break;
                default:
                    break;
            }
        }

        // unconditional stop
        if (g_bSrJrTransfer > JR_ONLY) {
            if (IsElevAtTopRetainerPB()) {
                // stop motor RUN
                msDelay(20); // to better trigger the sensor
                digitalWrite(ELEV_RUN_TRIG, 1);
                return NO_ERROR;
            }
        } else if (g_bSrJrTransfer == JR_ONLY) {
            if (IsElevAtLowRetainerPB()) {
                // stop motor RUN
                msDelay(20); // to better trigger the sensor
                digitalWrite(ELEV_RUN_TRIG, 1);
                return NO_ERROR;
            }
        }
    }

    digitalWrite(ELEV_RUN_TRIG, 1);
    return ERR_OPERATION_TIMEOUT;
}

/*==============================================================================
 *                        Function: int ElevMoveDown()
 *============================================================================*/
/*** BeginHeader ElevMoveDown */
int ElevMoveDown();
/*** EndHeader */
int ElevMoveDown() {
    unsigned long end;
    int re;

    g_bHighSpeed = FALSE;
    setMotorDrive(ELEVATOR, ELEV_DOWN_DIR);
    end = MS_TIMER + TIMEOUT_ELEV;

    while (MS_TIMER < end) {
        if (((re = BoatCheck()) != NO_ERROR)
            || ((re = pauseCheck()) != NO_ERROR)) {
            if (re == NEEDRESUME) {
                end = MS_TIMER + TIMEOUT_ELEV; // reset timeout timer
                setMotorDrive(ELEVATOR, ELEV_DOWN_DIR);

                if (g_bNeedMachineCycle == TRUE) {
                    DisplayInCycling();
                } else if (g_bTech == TRUE) {
                    DisplayElevMoving();
                } else {
                    DisplayInOperation();
                }
            } else {
                return re;
            }
        }

        //conditional stop
        if ((g_bAdaptor == FALSE) && (g_wBoatType == QBOAT_LOW)) {
            if (IsElevAtLowRetainerPB()) {
                msDelay(20); // to better trigger the sensor
                // stop elevator motor RUN
                digitalWrite(ELEV_RUN_TRIG, 1);
                return NO_ERROR;
            }
        } else if ((g_bAdaptor == TRUE) && (g_wBoatType == QBOAT_LOW)) {
            if (IsElevAtLowRetainerQB()) {
                msDelay(20); // to better trigger the sensor
                // stop elevator motor RUN
                digitalWrite(ELEV_RUN_TRIG, 1);
                return NO_ERROR;
            }
        }

        //unconditional stop
        if (IsElevHome()) {
            msDelay(20); // to better trigger the sensor
            // stop elevator motor RUN
            digitalWrite(ELEV_RUN_TRIG, 1);
            // change to low speed
            digitalWrite(ELEV_SPEED_TRIG, 0);
            g_bChkBoat = FALSE;

            return NO_ERROR;
        }
    }

    digitalWrite(ELEV_RUN_TRIG, 1); // disable elevator from RUN
    return ERR_OPERATION_TIMEOUT;
}

/*==============================================================================
 *                        Function: int ElevMoveHome()
 *============================================================================*/
/*** BeginHeader ElevMoveHome */
int ElevMoveHome();
/*** EndHeader */
int ElevMoveHome() {
    unsigned long end;
    int  re;
    char changeSpeedToLow;

    changeSpeedToLow = FALSE;

    if (IsElevHome()) {
        digitalWrite(ELEV_RUN_TRIG, 1);
        return NO_ERROR;
    }

    setMotorDrive(ELEVATOR, ELEV_DOWN_DIR);
    end = MS_TIMER + TIMEOUT_ELEV;

    while (MS_TIMER < end) {
        if (((re = BoatCheck()) != NO_ERROR)
            || ((re = pauseCheck()) != NO_ERROR)) {
            if (re == NEEDRESUME) {
                end = MS_TIMER + TIMEOUT_ELEV; // reset timeout timer
                setMotorDrive(ELEVATOR, ELEV_DOWN_DIR);

                if (g_bNeedMachineCycle == TRUE) {
                    DisplayInCycling();
                } else if (g_bTech == TRUE) {
                    DisplayElevMoving();
                } else {
                    DisplayInOperation();
                }
            } else {
                return re;
            }
        }

        if (g_bTech && !changeSpeedToLow) {
            // change to high speed
            digitalWrite(ELEV_SPEED_TRIG, 1);
            g_bHighSpeed = TRUE;
        } else if (g_bAdaptor) {
            switch (g_wBoatType)
            {
            case PBOAT_TOP:
                if (IsElevAtLowRetainerPB()) {
                    digitalWrite(ELEV_SPEED_TRIG, 1);
                    g_bHighSpeed = TRUE;
                }
                break;
            case PBOAT_LOW:
            case QBOAT_TOP:
                if (IsElevAtLowRetainerQB()) {
                    digitalWrite(ELEV_SPEED_TRIG, 1);
                    g_bHighSpeed = TRUE;
                }
                break;
            case QBOAT_LOW:
                if (IsElevQbSpeedChange()) {
                    digitalWrite(ELEV_SPEED_TRIG, 1);
                    g_bHighSpeed = TRUE;
                }
            
            default:
                break;
            }
        } else {
            switch (g_wBoatType)
            {
            case PBOAT_TOP:
            case QBOAT_TOP:
                if (IsElevAtLowRetainerPB()) {
                    // change to high speed
                    digitalWrite(ELEV_SPEED_TRIG, 1);
                    g_bHighSpeed = TRUE;
                }
                break;
            case PBOAT_LOW:
            case QBOAT_LOW:
                if (IsElevQbSpeedChange()) {
                    // change to high speed
                    digitalWrite(ELEV_SPEED_TRIG, 1);
                    g_bHighSpeed = TRUE;
                }
            
            default:
                break;
            }
        }

        if (IsElevPlatformSpeedChange()) {
            // change to low speed
            digitalWrite(ELEV_SPEED_TRIG, 0);
            g_bHighSpeed     = FALSE;
            changeSpeedToLow = TRUE;
        }

        //unconditional stop
        if (IsElevHome()) {
            msDelay(20); // to better trigger the sensor
            // stop elevator motor RUN
            digitalWrite(ELEV_RUN_TRIG, 1);
            // change to low speed
            digitalWrite(ELEV_SPEED_TRIG, 0);
            g_bChkBoat = FALSE;
            return NO_ERROR;
        }
    }

    digitalWrite(ELEV_RUN_TRIG, 1); // disable elevator from RUN
    return ERR_OPERATION_TIMEOUT;
}

/*==============================================================================
 *                        Function: void MoveOneStepCW()
 *============================================================================*/
/*** BeginHeader MoveOneStepCW */
void MoveOneStepCW();
/*** EndHeader */
void MoveOneStepCW() {
    // Half step sequence for VEXTA 2-phase stepper. Motor wiring as follows:
    // Hout0 to black; Hout1 to green; Hout2 to red and Hout3 to blue
    // +12v to white and yellow
    digitalWrite(PUSHER_STEP_DIR_TRIG,   1);

    digitalWrite(PUSHER_STEP_PULSE_TRIG, 0);
    Delay100usec(2);
    digitalWrite(PUSHER_STEP_PULSE_TRIG, 1);
}

/*==============================================================================
 *                        Function: void MoveOneStepCCW()
 *============================================================================*/
/*** BeginHeader MoveOneStepCCW */
void MoveOneStepCCW();
/*** EndHeader */
void MoveOneStepCCW() {
    // Half step sequence for VEXTA 2-phase stepper. Motor wiring as follows:
    // Hout0 to black; Hout1 to green; Hout2 to red and Hout3 to blue
    // +12v to white and yellow
    digitalWrite(PUSHER_STEP_DIR_TRIG,   0);

    digitalWrite(PUSHER_STEP_PULSE_TRIG, 0);
    Delay100usec(2);
    digitalWrite(PUSHER_STEP_PULSE_TRIG, 1);
}

/*==============================================================================
 *                        Function: int CalibratePusher()
 *============================================================================*/
/*** BeginHeader CalibratePusher */
int CalibratePusher();
/*** EndHeader */
int CalibratePusher() {
    char cKey;

    while (TRUE) {
        DisplayCalPusherMenu();

        while ((cKey = keypad.getKey()) == 0) {}

        if (cKey == '1') {
            CalibratePusher1();
        } else if (cKey == '2') {
            CalibratePusher2();
        } else if (cKey == '#') {
            sprintf(szDisplayString,
                    "g_bPusherUpPosPB1 = %d",
                    g_bPusherUpPosPB1);
            Serial.println(szDisplayString);
            sprintf(szDisplayString,
                    "g_bPusherUpPosPB2 = %d",
                    g_bPusherUpPosPB2);
            Serial.println(szDisplayString);
            sprintf(szDisplayString,
                    "g_bPusherUpPosQB  = %d",
                    g_bPusherUpPosQB);
            Serial.println(szDisplayString);
            SaveSettings();
            break;
        } else if (cKey == '*') {
            sprintf(szDisplayString,
                    "g_bPusherUpPosPB1 = %d",
                    g_bPusherUpPosPB1);
            Serial.println(szDisplayString);
            sprintf(szDisplayString,
                    "g_bPusherUpPosPB2 = %d",
                    g_bPusherUpPosPB2);
            Serial.println(szDisplayString);
            sprintf(szDisplayString,
                    "g_bPusherUpPosQB  = %d",
                    g_bPusherUpPosQB);
            Serial.println(szDisplayString);
            break;
        }
    }
}

/*==============================================================================
 *                        Function: int CalibratePusher1()
 *============================================================================*/
/*** BeginHeader CalibratePusher1 */
int CalibratePusher1();
/*** EndHeader */
int CalibratePusher1() {
    char cKey;
    int  i, pb_temp_steps, qb_temp_steps, stepToChange;

    pb_temp_steps = 0;
    qb_temp_steps = 0;
    stepToChange  = 10;

    if (IsPusherHome()) {
        if (((g_bAdaptor == FALSE) && IsQbPresent()) ||
            (g_bPusherForPB != TRUE)) {
            g_wBoatType = QBOAT_LOW;
        } else {
            g_wBoatType = PBOAT_LOW;
        }

        PushUp(0);
    }

    while (TRUE) {
        DisplayCalPusher();

        while ((cKey = keypad.getKey()) == 0) {}

        if (cKey == '1') {                            // pusher up a little
            pb_temp_steps += stepToChange;

            for (i = 0; i < stepToChange; i++) {
                Delay100usec(5);
                MoveOneStepCCW();
            }
        } else if (cKey == '2') {                     // pusher down a little
            pb_temp_steps -= stepToChange;

            for (i = 0; i < stepToChange; i++) {
                Delay100usec(5);
                MoveOneStepCW();
            }
        } else if ((g_bAdaptor == FALSE) && (cKey == '3')) {        // pusher
                                                                    // up a
                                                                    // little
            qb_temp_steps += stepToChange;

            for (i = 0; i < stepToChange; i++) {
                Delay100usec(5);
                MoveOneStepCCW();
            }
        } else if ((g_bAdaptor == FALSE) && (cKey == '4')) {        // pusher
                                                                    // down a
                                                                    // little
            qb_temp_steps -= stepToChange;

            for (i = 0; i < stepToChange; i++) {
                Delay100usec(5);
                MoveOneStepCW();
            }
        } else if (cKey == '#') {
            g_bPusherUpPosPB1 += pb_temp_steps;
            g_bPusherUpPosQB  += qb_temp_steps;
            sprintf(szDisplayString,
                    "g_bPusherUpPosPB1 = %d",
                    g_bPusherUpPosPB1);
            Serial.println(szDisplayString);
            sprintf(szDisplayString,
                    "g_bPusherUpPosQB  = %d",
                    g_bPusherUpPosQB);
            Serial.println(szDisplayString);
            DisplayCalPusherResult(g_bPusherUpPosPB1, g_bPusherUpPosQB);
            SaveSettings();
            PushDown();
            break;
        } else if (cKey == '*') {
            sprintf(szDisplayString,
                    "g_bPusherUpPosPB1 = %d",
                    g_bPusherUpPosPB1);
            Serial.println(szDisplayString);
            sprintf(szDisplayString,
                    "g_bPusherUpPosQB  = %d",
                    g_bPusherUpPosQB);
            Serial.println(szDisplayString);
            PushDown();
            break;
        }
    }
}

/*==============================================================================
 *                        Function: int CalibratePusher2()
 *============================================================================*/
/*** BeginHeader CalibratePusher2 */
int CalibratePusher2();
/*** EndHeader */
int CalibratePusher2() {
    char cKey;
    int  i, pb_temp_steps, qb_temp_steps, stepToChange;

    pb_temp_steps = 0;
    qb_temp_steps = 0;
    stepToChange  = 10;

    if (IsPusherHome()) {
        if (((g_bAdaptor == FALSE) && IsQbPresent()) ||
            (g_bPusherForPB != TRUE)) {
            g_wBoatType = QBOAT_LOW;
        } else {
            g_wBoatType = PBOAT_LOW;
        }

        PushUp(1);
    }

    while (TRUE) {
        DisplayCalPusher();

        while ((cKey = keypad.getKey()) == 0) {}

        if (cKey == '1') {                            // pusher up a little
            pb_temp_steps += stepToChange;

            for (i = 0; i < stepToChange; i++) {
                Delay100usec(5);
                MoveOneStepCCW();
            }
        } else if (cKey == '2') {                     // pusher down a little
            pb_temp_steps -= stepToChange;

            for (i = 0; i < stepToChange; i++) {
                Delay100usec(5);
                MoveOneStepCW();
            }
        } else if ((g_bAdaptor == FALSE) && (cKey == '3')) {        // pusher
                                                                    // up a
                                                                    // little
            qb_temp_steps += stepToChange;

            for (i = 0; i < stepToChange; i++) {
                Delay100usec(5);
                MoveOneStepCCW();
            }
        } else if ((g_bAdaptor == FALSE) && (cKey == '4')) {        // pusher
                                                                    // down a
                                                                    // little
            qb_temp_steps -= stepToChange;

            for (i = 0; i < stepToChange; i++) {
                Delay100usec(5);
                MoveOneStepCW();
            }
        } else if (cKey == '#') {
            g_bPusherUpPosPB2 += pb_temp_steps;
            g_bPusherUpPosQB  += qb_temp_steps;
            sprintf(szDisplayString,
                    "g_bPusherUpPosPB2 = %d",
                    g_bPusherUpPosPB2);
            Serial.println(szDisplayString);
            sprintf(szDisplayString,
                    "g_bPusherUpPosQB  = %d",
                    g_bPusherUpPosQB);
            Serial.println(szDisplayString);
            DisplayCalPusherResult(g_bPusherUpPosPB2, g_bPusherUpPosQB);
            SaveSettings();
            PushDown();
            break;
        } else if (cKey == '*') {
            sprintf(szDisplayString,
                    "g_bPusherUpPosPB2 = %d",
                    g_bPusherUpPosPB2);
            Serial.println(szDisplayString);
            sprintf(szDisplayString,
                    "g_bPusherUpPosQB  = %d",
                    g_bPusherUpPosQB);
            Serial.println(szDisplayString);
            PushDown();
            break;
        }
    }
}

/*==============================================================================
 *                        Function: int PushUp(int dir)
 *============================================================================*/
/*** BeginHeader PushUp */
int PushUp(int dir);
/*** EndHeader */
int PushUp(int dir) {
    unsigned long end;
    int i, iEnd;
    int re;

    if (g_bPusher == FALSE) {
        return NO_ERROR;
    } else if ((g_bAdaptor == TRUE) && IsAdaptorPresent()) {
        return NO_ERROR;
    } else if ((g_bPusherForPB == FALSE)
               && ((g_wBoatType == PBOAT_LOW) ||
                   (g_wBoatType == PBOAT_TOP))) {
        return NO_ERROR;
    }

    if (!IsPusherHome()) {
        return ERR_PUSHER_FAIL;
    }

    g_wStepPhaseSequence = 1;

    if ((g_wBoatType == PBOAT_LOW) || (g_wBoatType == PBOAT_TOP)) {
        if (dir == 0) {
            iEnd = g_bPusherUpPosPB1; // HBar Back  0
            sprintf(szDisplayString,
                    "g_bPusherUpPosPB1 = %d",
                    g_bPusherUpPosPB1);
            Serial.println(szDisplayString);
        } else {
            iEnd = g_bPusherUpPosPB2; // HBar Front 1
            sprintf(szDisplayString,
                    "g_bPusherUpPosPB2 = %d",
                    g_bPusherUpPosPB2);
            Serial.println(szDisplayString);
        }
    } else if ((g_wBoatType == QBOAT_LOW) ||
               (g_wBoatType == QBOAT_TOP)) {
        iEnd = g_bPusherUpPosQB;
    } else {
        return NO_ERROR;
    }

    for (i = 0; i < iEnd; i++) {
        if (i < 9) {
            Delay100usec(9 - i);                      // acceleration
        }

        if ((iEnd - i) < 9) {
            Delay100usec((i - iEnd) + 9); // deceleration
        }

        MoveOneStepCCW();
    }

    if ((g_wStepPhaseSequence == 2) || (g_wStepPhaseSequence == 4)
        || (g_wStepPhaseSequence == 6) || (g_wStepPhaseSequence == 8)) {
        // move one more step to end up with one phase power on
        MoveOneStepCCW();
        return NO_ERROR;
    } else {
        return NO_ERROR;
    }
}

/*==============================================================================
 *                        Function: int PushDown()
 *============================================================================*/
/*** BeginHeader PushDown */
int PushDown();
/*** EndHeader */
int PushDown() {
    unsigned long end;
    int i, iEnd;
    int re;

    if ((g_bPusher == FALSE) || IsPusherHome()) {
        return NO_ERROR;
    }

    i                    = 0;
    iEnd                 = 0;
    g_wStepPhaseSequence = 1;
    end                  = MS_TIMER + TIMEOUT_RT;

    while (MS_TIMER < end) {
        if (i++ < 9) {
            Delay100usec(9 - i);                      // acceleration
        }

        if (IsPusherHome()) {
            if (iEnd++ < 15) {
                Delay100usec(iEnd); // deceleration
            } else if ((g_wStepPhaseSequence == 2) ||
                       (g_wStepPhaseSequence == 4)
                       || (g_wStepPhaseSequence == 6) ||
                       (g_wStepPhaseSequence == 8)) {
                // move one more step to end up with one phase power on
                MoveOneStepCW();
                return NO_ERROR;
            } else {
                return NO_ERROR;
            }
        }

        MoveOneStepCW();
    }

    return ERR_PUSHER_FAIL;
}