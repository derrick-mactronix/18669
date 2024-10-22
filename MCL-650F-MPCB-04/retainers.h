/*******************************************************************************
 *               Copyright(c) 2022, Mactronix. All rights reserved
 *
 *               File:         retainers.h
 *               Description:  all retainers movement functions
 *               Author:       Jered Yang
 *               Date:         2022-07-06
 ******************************************************************************/
int TopRetainerOpen() {
    unsigned long end;
    int  Count;
    char MoveDone;

    if (IsTopRetainerOpen() && !IsTopRetainerClose()) {
        return NO_ERROR;
    }

    Count    = 0;
    MoveDone = FALSE;

    digitalWrite(TOP_RET_CLOSE_TRIG, 1);
    digitalWrite(TOP_RET_OPEN_TRIG,  0);

    DisplayRTMoving();
    end = MS_TIMER + TIMEOUT_RT;

    while (MS_TIMER < end) {
        if (IsTopRetainerOpen() && !IsTopRetainerClose()) {
            if (Count++ > 5) {
                MoveDone = TRUE;
            } 
            // else {
            //     msDelay(10);
            // }
        }

        if (MoveDone) {
            break;
        }
    }

    digitalWrite(TOP_RET_OPEN_TRIG, 1);

    msDelay(50);
    if (IsTopRetainerOpen() && !IsTopRetainerClose()) {
        return NO_ERROR;
    }

    return ERR_OPEN_RETAINER_FAIL;
}

int TopRetainerClose() {
    unsigned long end;
    int  Count;
    char MoveDone;

    if (IsTopRetainerClose() && !IsTopRetainerOpen()) {
        return NO_ERROR;
    }

    Count    = 0;
    MoveDone = FALSE;

    digitalWrite(TOP_RET_OPEN_TRIG,  1);
    digitalWrite(TOP_RET_CLOSE_TRIG, 0);

    DisplayRTMoving();
    end = MS_TIMER + TIMEOUT_RT;

    while (MS_TIMER < end) {
        if (IsTopRetainerClose() && !IsTopRetainerOpen()) {
            if (Count++ > 5) {
                MoveDone = TRUE;
            } 
            // else {
            //     msDelay(10);
            // }
        }

        if (MoveDone) {
            break;
        }
    }

    digitalWrite(TOP_RET_CLOSE_TRIG, 1);

    msDelay(50);
    if (IsTopRetainerClose() && !IsTopRetainerOpen()) {
        return NO_ERROR;
    }
    return ERR_CLOSE_RETAINER_FAIL;
}

int LowRetainerOpen() {
    unsigned long end;
    int  Count;
    char MoveDone;

    if (IsLowRetainerOpen() && !IsLowRetainerClose()) {
        return NO_ERROR;
    }

    Count    = 0;
    MoveDone = FALSE;

    digitalWrite(LOW_RET_CLOSE_TRIG, 1);
    digitalWrite(LOW_RET_OPEN_TRIG,  0);

    DisplayRTMoving();
    end = MS_TIMER + TIMEOUT_RT;

    while (MS_TIMER < end) {
        if (IsLowRetainerOpen() && !IsLowRetainerClose()) {
            if (Count++ > 5) {
                MoveDone = TRUE;
            } 
            // else {
            //     msDelay(10);
            // }
        }

        if (MoveDone) {
            break;
        }
    }

    digitalWrite(LOW_RET_OPEN_TRIG, 1);

    msDelay(50);
    if (IsLowRetainerOpen() && !IsLowRetainerClose()) {
        return NO_ERROR;
    }
    return ERR_OPEN_RETAINER_FAIL;
}

int LowRetainerClose() {
    unsigned long end;
    int  Count;
    char MoveDone;

    if (IsLowRetainerClose() && !IsLowRetainerOpen()) {
        return NO_ERROR;
    }

    Count    = 0;
    MoveDone = FALSE;

    digitalWrite(LOW_RET_OPEN_TRIG,  1);
    digitalWrite(LOW_RET_CLOSE_TRIG, 0);

    DisplayRTMoving();
    end = MS_TIMER + TIMEOUT_RT;

    while (MS_TIMER < end) {
        if (IsLowRetainerClose() && !IsLowRetainerOpen()) {
            if (Count++ > 5) {
                MoveDone = TRUE;
            } 
            // else {
            //     msDelay(10);
            // }
        }

        if (MoveDone) {
            break;
        }
    }

    digitalWrite(LOW_RET_CLOSE_TRIG, 1);

    msDelay(50);
    if (IsLowRetainerClose() && !IsLowRetainerOpen()) {
        return NO_ERROR;
    }

    return ERR_CLOSE_RETAINER_FAIL;
}

int TopLowRetainerOpen() {
    unsigned long end;
    int  topCount, lowCount;
    char topMoveDone, lowMoveDone;

    if (IsTopRetainerOpen() && IsLowRetainerOpen()
        && !IsTopRetainerClose() && !IsLowRetainerClose()) {
        return NO_ERROR;
    }

    topCount    = 0;
    lowCount    = 0;
    topMoveDone = FALSE;
    lowMoveDone = FALSE;

    digitalWrite(TOP_RET_CLOSE_TRIG, 1);
    digitalWrite(TOP_RET_OPEN_TRIG,  0);
    digitalWrite(LOW_RET_CLOSE_TRIG, 1);
    digitalWrite(LOW_RET_OPEN_TRIG,  0);

    DisplayRTMoving();
    end = MS_TIMER + TIMEOUT_RT;

    while (MS_TIMER < end) {
        if (IsTopRetainerOpen() && !IsTopRetainerClose()) {
            if (topCount++ > 5) {
                digitalWrite(TOP_RET_OPEN_TRIG, 1);
                topMoveDone = TRUE;
            } 
            // else {
            //     msDelay(10);
            // }
        }

        if (IsLowRetainerOpen() && !IsLowRetainerClose()) {
            if (lowCount++ > 5) {
                digitalWrite(LOW_RET_OPEN_TRIG, 1);
                lowMoveDone = TRUE;
            } 
            // else {
            //     msDelay(10);
            // }
        }

        if (topMoveDone && lowMoveDone) {
            break;
        }
    }

    digitalWrite(TOP_RET_OPEN_TRIG, 1);
    digitalWrite(LOW_RET_OPEN_TRIG, 1);

    msDelay(50);
    if (IsTopRetainerOpen() && IsLowRetainerOpen()
        && !IsTopRetainerClose() && !IsLowRetainerClose()) {
        return NO_ERROR;
    }

    return ERR_OPEN_RETAINER_FAIL;
}

int TopLowRetainerClose() {
    unsigned long end;
    int  topCount, lowCount;
    char topMoveDone, lowMoveDone;

    if (IsTopRetainerClose() && IsLowRetainerClose()
        && !IsTopRetainerOpen() && !IsLowRetainerOpen()) {
        return NO_ERROR;
    }

    topCount    = 0;
    lowCount    = 0;
    topMoveDone = FALSE;
    lowMoveDone = FALSE;

    digitalWrite(TOP_RET_CLOSE_TRIG, 0);
    digitalWrite(TOP_RET_OPEN_TRIG,  1);
    digitalWrite(LOW_RET_CLOSE_TRIG, 0);
    digitalWrite(LOW_RET_OPEN_TRIG,  1);

    DisplayRTMoving();
    end = MS_TIMER + TIMEOUT_RT;

    while (MS_TIMER < end) {
        if (IsTopRetainerClose() && !IsTopRetainerOpen()) {
            if (topCount++ > 5) {
                digitalWrite(TOP_RET_CLOSE_TRIG, 1);
                topMoveDone = TRUE;
            } 
            // else {
            //     msDelay(10);
            // }
        }

        if (IsLowRetainerClose() && !IsLowRetainerOpen()) {
            if (lowCount++ > 5) {
                digitalWrite(LOW_RET_CLOSE_TRIG, 1);
                lowMoveDone = TRUE;
            } 
            // else {
            //     msDelay(10);
            // }
        }

        if (topMoveDone && lowMoveDone) {
            break;
        }
    }

    digitalWrite(TOP_RET_CLOSE_TRIG, 1);
    digitalWrite(LOW_RET_CLOSE_TRIG, 1);

    msDelay(50);
    if (IsTopRetainerClose() && IsLowRetainerClose()
        && !IsTopRetainerOpen() && !IsLowRetainerOpen()) {
        return NO_ERROR;
    }
    
    return ERR_CLOSE_RETAINER_FAIL;
}

int LowOpenTopClose() {
    unsigned long end;
    int  topCount, lowCount;
    char topMoveDone, lowMoveDone;

    if (IsTopRetainerClose() && IsLowRetainerOpen()
        && !IsTopRetainerOpen() && !IsLowRetainerClose()) {
        return NO_ERROR;
    }

    topCount    = 0;
    lowCount    = 0;
    topMoveDone = FALSE;
    lowMoveDone = FALSE;

    digitalWrite(TOP_RET_CLOSE_TRIG, 0);
    digitalWrite(TOP_RET_OPEN_TRIG,  1);
    digitalWrite(LOW_RET_CLOSE_TRIG, 1);
    digitalWrite(LOW_RET_OPEN_TRIG,  0);

    DisplayRTMoving();
    end = MS_TIMER + TIMEOUT_RT;

    while (MS_TIMER < end) {
        if (IsTopRetainerClose() && !IsTopRetainerOpen()) {
            if (topCount++ > 5) {
                digitalWrite(TOP_RET_CLOSE_TRIG, 1);
                topMoveDone = TRUE;
            } 
            // else {
            //     msDelay(10);
            // }
        }

        if (IsLowRetainerOpen() && !IsLowRetainerClose()) {
            if (lowCount++ > 5) {
                digitalWrite(LOW_RET_OPEN_TRIG, 1);
                lowMoveDone = TRUE;
            }
            // else {
            //     msDelay(10);
            // }
        }

        if (topMoveDone && lowMoveDone) {
            break;
        }
    }

    digitalWrite(TOP_RET_CLOSE_TRIG, 1);
    digitalWrite(LOW_RET_OPEN_TRIG, 1);

    msDelay(50);

    if (IsTopRetainerClose() && IsLowRetainerOpen()
        && !IsTopRetainerOpen() && !IsLowRetainerClose()) {
        return NO_ERROR;
    }
    
    if (!topMoveDone) {
        return ERR_CLOSE_RETAINER_FAIL;
    } else {
        return ERR_OPEN_RETAINER_FAIL;
    }
}
