/*******************************************************************************
 *               Copyright(c) 2022, Mactronix. All rights reserved
 *
 *               File:         index.h
 *               Description:  all index movement functions
 *               Author:       Jered Yang
 *               Date:         2022-07-06
 ******************************************************************************/

int IndexToFront() {
    unsigned long end;
    int  Count;
    char MoveDone;

    if (IsIndexAtFront() && !IsIndexAtBack()) {
        return NO_ERROR;
    }

    if (!IsElevHome() && !IsTopRetainerOpen()) {
        return ERR_INDEX_FAIL;
    }

    Count     = 0;
    MoveDone  = FALSE;

    digitalWrite(INDEX_TO_BACK_TRIG,   1);
    digitalWrite(INDEX_TO_FRONT_TRIG,  0);

    DisplayIndexing();
    end = MS_TIMER + TIMEOUT_INDEX;

    while (MS_TIMER < end) {
        if (IsIndexAtFront() && !IsIndexAtBack()) {
            if (Count++ > 5) {
                MoveDone = TRUE;
            }
            //  else {
            //     msDelay(10);
            // }
        }

        if (MoveDone) {
            break;
        }
    }

    digitalWrite(INDEX_TO_FRONT_TRIG,  1);

    msDelay(50);
    if (IsIndexAtFront() && !IsIndexAtBack()) {
        return NO_ERROR;
    }
    return ERR_INDEX_FAIL;
}

int IndexToBack() {
    unsigned long end;
    int  Count;
    char MoveDone;

    if (IsIndexAtBack() && !IsIndexAtFront()) {
        return NO_ERROR;
    }

    if (!IsElevHome() && !IsTopRetainerOpen()) {
        return ERR_INDEX_FAIL;
    }

    Count     = 0;
    MoveDone  = FALSE;

    digitalWrite(INDEX_TO_FRONT_TRIG,  1);
    digitalWrite(INDEX_TO_BACK_TRIG,   0);

    DisplayIndexing();
    end = MS_TIMER + TIMEOUT_INDEX;

    while (MS_TIMER < end) {
        if (!IsIndexAtFront() && IsIndexAtBack()) {
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

    digitalWrite(INDEX_TO_BACK_TRIG,  1);

    msDelay(50);
    if (IsIndexAtBack() && !IsIndexAtFront()) {
        return NO_ERROR;
    }
    
    return ERR_INDEX_FAIL;
}