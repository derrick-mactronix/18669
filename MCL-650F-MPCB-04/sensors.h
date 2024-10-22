/*******************************************************************************
 *               Copyright(c) 2022, Mactronix. All rights reserved
 *
 *               File:         sensors.h
 *               Description:  all sensor input functions
 *               Author:       Jered Yang
 *               Date:         2022-07-06
 ******************************************************************************/

int IsIndexAtFront() {
    if (!myinp(INDEX_FRONT_SEN)) {
        msDelay(10);
        if (!myinp(INDEX_FRONT_SEN)) {
            return TRUE;
        }
    }

    return FALSE;
    // return !myinp(INDEX_FRONT_SEN);
}

int IsIndexAtBack() {
    if (!myinp(INDEX_BACK_SEN)) {
        msDelay(10);
        if (!myinp(INDEX_BACK_SEN)) {
            return TRUE;
        }
    }

    return FALSE;
    // return !myinp(INDEX_BACK_SEN);
}

int IsOverHeated() {
    int data;

    data = myinp(OVER_HEAT_SEN);

    if (data == FALSE) {
        AlarmOn();
        return TRUE;
    } else {
        AlarmOff();
        return FALSE;
    }
}

int IsPBhBarOk() {
    return !myinp(PB_HBAR_SEN);
}

int IsElevAtTopRetainerPB() {
    return myinp(ELEVATOR_TOP_RT_PB_SEN);
}

int IsElevAtLowRetainerPB() {
    return myinp(ELEVATOR_LOW_RT_PB_SEN);
}

int IsElevAtTopRetainerQB() {
    return myinp(ELEVATOR_TOP_RT_QB_SEN);
}

int IsElevAtLowRetainerQB() {
    return myinp(ELEVATOR_LOW_RT_QB_SEN);
}

int IsElevQbSpeedChange() {
    return myinp(SPEED_CHANGE_RT_SEN);
}

int IsElevPlatformSpeedChange() {
    return myinp(SPEED_CHANGE_PLATFORM_SEN);
}

int IsElevHome() {
    return myinp(ELEVATOR_HOME_SEN);
}

int IsPusherHome() {
    return !myinp(PUSHER_HOME_SEN);
}

int IsTopRetainerOpen() {
    if (!myinp(TOP_RT_OPEN_SEN)) {
        msDelay(10);
        if (!myinp(TOP_RT_OPEN_SEN)) {
            return TRUE;
        }
    }

    return FALSE;
    // return !myinp(TOP_RT_OPEN_SEN);
}

int IsTopRetainerClose() {
    if (!myinp(TOP_RT_CLOSE_SEN)) {
        msDelay(10);
        if (!myinp(TOP_RT_CLOSE_SEN)) {
            return TRUE;
        }
    }

    return FALSE;
    // return !myinp(TOP_RT_CLOSE_SEN);
 }

int IsLowRetainerOpen() {
    if (!myinp(LOW_RT_OPEN_SEN)) {
        msDelay(10);
        if (!myinp(LOW_RT_OPEN_SEN)) {
            return TRUE;
        }
    }

    return FALSE;
    // return !myinp(LOW_RT_OPEN_SEN);
}

int IsLowRetainerClose() {
    if (!myinp(LOW_RT_CLOSE_SEN)) {
        msDelay(10);
        if (!myinp(LOW_RT_CLOSE_SEN)) {
            return TRUE;
        }
    }

    return FALSE;
    // return !myinp(LOW_RT_CLOSE_SEN);
}

int IsElevUpSafe() {
    return !myinp(UP_SAFETY_SEN);
}

int IsPBHBDirFront() {
    if (IsPBDirBackOn()) {
        return TRUE;
    } else if (!IsPBDirFrontOn()) {
        return TRUE;
    }

    return FALSE;
}

int IsPBDirFrontOn() {
    return !myinp(PB_DIRECTION_SEN_FRONT);
}

int IsPBDirBackOn() {
    return !myinp(PB_DIRECTION_SEN_BACK);
}

int IsStartPressed() {
    return !keypad.pin_read(START_SEN);
}

int IsPauseButtonPressed() {
    return !keypad.pin_read(PAUSE_BUTTON_SEN);
}
