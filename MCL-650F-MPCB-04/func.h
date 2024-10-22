/*******************************************************************************
 *               Copyright(c) 2007, Mactronix Inc. All rights reserved
 *
 *               File:         func.lib Description:  General functions
 *Author:       Marvin Zhang Date:         09/20/2007
 ******************************************************************************/
/*****************************  Functions List
   ********************************
** int  MachineReset();
** int  JrTransfer();
** int  DoJrLoad();
** int  DoJrUnload();
** int  SrTransfer();
** int  DoPbToQbLoad();
** int  DoPbToQbUnload();
** int  DoQbToPbLoad();
** int  DoQbToPbUnload();
** int  DoRecovery();
** void DoMachineCycle();
** int  DoTechnician();
** int  SystemConfig();
** int  TechInput();
** int  TechOutput();
** void init();
** void AlarmOn();
** void AlarmOff();
** void Beep();
** void InitIOBoard();
** void setMotorDrive(int motor, int direction);
** int  myinp(int port);
** int  BoatCheck();
** int  checkBoatAndWafer(int wafer);
** int  checkPBDirectionAfterPusher(int dir);
** void Pause();
** int  upSafetyCheck();
** int  pauseCheck();
** int  overHeatCheck();
** int  waitCmdAfterPause();
** int  waitCmdAfterOverheat();
** int  IsPbPresent();
** int  IsWaferInBoat();
** int  IsQbPresent();
** int  IsQbPresent2();
** int  IsStartButtonPressed();
** int  IsJrButtonPressed();
** int  IsPauseButtonPressed();
** int  IsAdaptorPresent();
** void msDelay(unsigned int wDelayTime);
** void Delay10uSeconds(unsigned int wDelayTime);
** void Delay100usec(unsigned int wDelayTime);
******************************************************************************/
/*==============================================================================
 *                        Function: int MachineReset()
 *============================================================================*/
/*** BeginHeader MachineReset */
int MachineReset();
/*** EndHeader */
int MachineReset() {
    int re;

    AlarmOff();
    g_bTech      = FALSE;
    g_bCombEmpty = FALSE;

    if (IsPbPresent() || IsQbPresent()) {
        g_bChkBoat = TRUE;

        if (IsPbPresent()) {
            g_wBoatType = PBOAT_TOP;
        } else {
            g_wBoatType = QBOAT_TOP;
        }
    } else {
        g_bChkBoat = FALSE;
    }

    DisplayInOperation();

    if ((g_bSrJrTransfer > JR_ONLY) && IsElevAtTopRetainerPB()) {
        if ((re = TopLowRetainerOpen()) != NO_ERROR) {
            return re;
        }

        if ((re = ElevMoveHome()) != NO_ERROR) {
            return re;
        }
    } else if (IsElevAtLowRetainerPB()) {
        if ((re = LowRetainerOpen()) != NO_ERROR) {
            return re;
        }

        if ((re = ElevMoveHome()) != NO_ERROR) {
            return re;
        }
    } else {
        if ((re = ElevMoveHome()) != NO_ERROR) {
            return re;
        }
    }

    if ((g_bPusher == TRUE) && !IsPusherHome()) {
        DisplayInPreoperation();

        if ((re = PushDown()) != NO_ERROR) {
            return re;
        }
    }

    g_bChkBoat = FALSE;

    if (((g_bSrJrTransfer > JR_ONLY) && IsTopRetainerClose()) ||
        IsLowRetainerClose()) {
        return ERR_RETAINER_CLOSE;
    }

    return NO_ERROR;
}

/*==============================================================================
 *                        Function: int JrTransfer()
 *============================================================================*/
/*** BeginHeader JrTransfer */
int JrTransfer();
/*** EndHeader */
int JrTransfer() {
    char cKey;
    int  re;

    g_wBoatType = 0;
    DisplayLoadFullBoat();

    while (TRUE) {
        while ((cKey = keypad.getKey()) == 0 && !IsStartPressed()) {
            if (g_bCheckOverHeat == TRUE) {
                IsOverHeated();  // read the heat sensor and turn on alarm if
                                 // triggered
            }
        }

        if ((cKey == '#') || IsStartPressed()) { // start
            break;
        } else if (cKey == '*') {    // abort
            return NEEDABORT;
        }
    }

    if (checkBoatAndWafer(1) != NO_ERROR) {
        return NEEDABORT;
    }

    if ((re = DoJrLoad()) != NO_ERROR) {
        return re;
    }

    g_wBoatType = 0;
    DisplayLoadEmptyContainer();

    while (TRUE) {
        while ((cKey = keypad.getKey()) == 0 && !IsStartPressed()) {
            if (g_bCheckOverHeat == TRUE) {
                IsOverHeated();  // read the heat sensor and turn on alarm if
                                 // triggered
            }
        }

        if ((cKey == '#') || IsStartPressed()) { // start
            break;
        } else if (cKey == '*') {    // abort
            return NEEDABORT;
        }
    }

    if (checkBoatAndWafer(0) != NO_ERROR) {
        return NEEDABORT;
    }

    if ((re = DoJrUnload()) != NO_ERROR) {
        return re;
    }

    return NO_ERROR;
}

/*==============================================================================
 *                        Function: int DoJrLoad()
 *============================================================================*/
/*** BeginHeader DoJrLoad */
int DoJrLoad();
/*** EndHeader */
int DoJrLoad() {
    char cKey;
    int  re;

    g_wBoatType = 0;

    if (checkBoatAndWafer(1) != NO_ERROR) {
        return NEEDABORT;
    }

    if (IsPbPresent()) {
        g_wBoatType = PBOAT_LOW;
    } else {
        g_wBoatType = QBOAT_LOW;
    }

    g_bCombEmpty = FALSE;
    g_bChkBoat   = TRUE;

    if (((g_bSrJrTransfer == JR_N_SR) && !IsTopRetainerOpen()) ||
        !IsLowRetainerOpen()
        || ((g_bSrJrTransfer == JR_N_SR) && IsTopRetainerClose()) ||
        IsLowRetainerClose()) {
        return ERR_RETAINER_CLOSE;
    }

    if (checkBoatAndWafer(1) != NO_ERROR) {
        return NEEDABORT;
    }

    if ((g_bPusher == TRUE) &&
        ((g_wBoatType == PBOAT_LOW) || (g_bAdaptor == FALSE))) {
        if ((re = PushUp(0)) != NO_ERROR) {
            return re;
        }

        if (checkPBDirectionAfterPusher(PB_HB_BACK) != NO_ERROR) {
            PushDown();
            return NEEDABORT;
        }

        DisplayInPreoperation();

        if (checkPBhbar() != NO_ERROR) {
            return NEEDABORT;
        }
    }

    DisplayInOperation();

    if ((re = ElevUp()) != NO_ERROR) {
        return re;
    }

    /*
       if(!IsElevAtLowRetainerPB())
       {
          return ERR_ELEV_POSITION;
       }
     */
    if ((re = LowRetainerClose()) != NO_ERROR) {
        return re;
    }

    g_bCombEmpty = TRUE;

    if ((re = ElevMoveHome()) != NO_ERROR) {
        return re;
    }

    if ((g_bPusher == TRUE) &&
        ((g_wBoatType == PBOAT_LOW) || (g_bAdaptor == FALSE))) {
        DisplayInPreoperation();

        if ((re = PushDown()) != NO_ERROR) {
            return re;
        }
    }

    if (g_bNeedMachineCycle == FALSE) {
        DisplayRemoveContainer();

        while (IsPbPresent() || IsQbPresent()) {}
    }

    return NO_ERROR;
}

/*==============================================================================
 *                        Function: int DoJrUnload()
 *============================================================================*/
/*** BeginHeader DoJrUnload */
int DoJrUnload();
/*** EndHeader */
int DoJrUnload() {
    char cKey;
    int  re;

    g_bCombEmpty = TRUE;
    g_bChkBoat   = TRUE;

    g_wBoatType = 0;

    if (checkBoatAndWafer(0) != NO_ERROR) {
        return NEEDABORT;
    }

    if (IsPbPresent()) {
        g_wBoatType = PBOAT_LOW;
    } else {
        g_wBoatType = QBOAT_LOW;
    }

    if (g_bNeedRecovery != TRUE) {
        if (IsLowRetainerOpen()) {
            return ERR_RETAINER_OPEN;
        }
    }

    if (checkBoatAndWafer(0) != NO_ERROR) {
        return NEEDABORT;
    }

    if ((g_bPusher == TRUE) &&
        ((g_wBoatType == PBOAT_LOW) || (g_bAdaptor == FALSE))) {
        if ((re = PushUp(0)) != NO_ERROR) {
            return re;
        }

        if (checkPBDirectionAfterPusher(PB_HB_BACK) != NO_ERROR) {
            PushDown();
            return NEEDABORT;
        }

        DisplayInPreoperation();

        if (checkPBhbar() != NO_ERROR) {
            return NEEDABORT;
        }
    }

    DisplayInOperation();

    if ((re = ElevUp()) != NO_ERROR) {
        return re;
    }

    /*
       if(!IsElevAtLowRetainerPB())
       {
          return ERR_ELEV_POSITION;
       }
     */
    if ((re = LowRetainerOpen()) != NO_ERROR) {
        return re;
    }

    g_bCombEmpty = FALSE;

    if ((re = ElevMoveHome()) != NO_ERROR) {
        return re;
    }

    if ((g_bPusher == TRUE) &&
        ((g_wBoatType == PBOAT_LOW) || (g_bAdaptor == FALSE))) {
        DisplayInPreoperation();

        if ((re = PushDown()) != NO_ERROR) {
            return re;
        }
    }

    if (g_bNeedMachineCycle == FALSE) {
        DisplayRemoveContainer();

        while (IsPbPresent() || IsQbPresent()) {}
    }
    return NO_ERROR;
}

/*==============================================================================
 *                        Function: int SrTransfer()
 *============================================================================*/
/*** BeginHeader SrTransfer */
int SrTransfer();
/*** EndHeader */
int SrTransfer() {
    char cKey;
    int  re;

    g_wBoatType = 0;
    DisplayLoadFullBoat();

    while (TRUE) {
        while ((cKey = keypad.getKey()) == 0 && !IsStartPressed()) {
            if (g_bCheckOverHeat == TRUE) {
                IsOverHeated();  // read the heat sensor and turn on alarm if
                                 // triggered
            }
        }

        if ((cKey == '#') || IsStartPressed()) { // start
            break;
        } else if (cKey == '*') {    // abort
            return NEEDABORT;
        }
    }

    if (checkBoatAndWafer(1) != NO_ERROR) {
        return NEEDABORT;
    }

    if (IsPbPresent()) {
        if ((re = DoPbToQbLoad()) != NO_ERROR) {
            return re;
        }

        g_bPbtoQbTransfer = TRUE;
    } else {
        if ((re = DoQbToPbLoad()) != NO_ERROR) {
            return re;
        }

        g_bPbtoQbTransfer = FALSE;
    }

    g_wBoatType = 0;

    if (g_bPbtoQbTransfer == TRUE) {
        DisplayLoadEmptyQB();
    } else {
        DisplayLoadEmptyPB();
    }

    while (TRUE) {
        while ((cKey = keypad.getKey()) == 0 && !IsStartPressed()) {
            if (g_bCheckOverHeat == TRUE) {
                IsOverHeated();  // read the heat sensor and turn on alarm if
                                 // triggered
            }
        }

        if ((cKey == '#') || IsStartPressed()) { // start
            break;
        } else if (cKey == '*') {    // abort
            return NEEDABORT;
        }
    }

    if (g_bPbtoQbTransfer == TRUE) {
        if ((re = DoPbToQbUnload()) != NO_ERROR) {
            return re;
        }
    } else {
        if ((re = DoQbToPbUnload()) != NO_ERROR) {
            return re;
        }
    }

    return NO_ERROR;
}

/*==============================================================================
 *                        Function: int DoPbToQbLoad()
 *============================================================================*/
/*** BeginHeader DoPbToQbLoad */
int DoPbToQbLoad();
/*** EndHeader */
int DoPbToQbLoad() {
    char cKey;
    int  re;

    g_wBoatType  = PBOAT_TOP;
    g_bCombEmpty = FALSE;
    g_bChkBoat   = TRUE;

    if (!IsTopRetainerOpen() || !IsLowRetainerOpen()
        || IsTopRetainerClose() || IsLowRetainerClose()) {
        return ERR_RETAINER_CLOSE;
    }

    if (checkBoatAndWafer(1) != NO_ERROR) {
        return NEEDABORT;
    }

    // DisplayInOperation();

    if ((re = IndexToBack()) != NO_ERROR) {
        return re;
    }

    if ((g_bPusher == TRUE) &&
        ((g_wBoatType == PBOAT_TOP) || (g_bAdaptor == FALSE))) {
        if (g_bMode == FACE_TO_FACE) {
            // @Jered 2022-04-04 10:49:49 need to check Carrier direction BEFORE
            // autopush
            if (checkPBDirectionBeforePusher()) {
                return NEEDABORT;
            }

            if ((re = PushUp(1)) != NO_ERROR) {
                return re;
            }

            if (checkPBDirectionAfterPusher(PB_HB_FRONT) != NO_ERROR) {
                PushDown();
                return NEEDABORT;
            }

            DisplayInPreoperation();
        } else {
            // @Jered 2022-04-04 10:49:49 need to check Carrier direction BEFORE
            // autopush
            if (checkPBDirectionBeforePusher()) {
                return NEEDABORT;
            }

            if ((re = PushUp(0)) != NO_ERROR) {
                return re;
            }

            if (checkPBDirectionAfterPusher(PB_HB_BACK) != NO_ERROR) {
                PushDown();
                return NEEDABORT;
            }

            DisplayInPreoperation();
        }

        if (checkPBhbar() != NO_ERROR) {
            return NEEDABORT;
        }
    }

    DisplayInOperation();

    if ((re = ElevUp()) != NO_ERROR) {
        return re;
    }

    if (!IsElevAtTopRetainerPB()) {
        return ERR_ELEV_POSITION;
    }

    if ((re = TopRetainerClose()) != NO_ERROR) {
        return re;
    }

    g_bCombEmpty = TRUE;

    if ((re = ElevMoveHome()) != NO_ERROR) {
        return re;
    }

    if ((re = IndexToFront()) != NO_ERROR) {
        return re;
    }

    if ((g_bPusher == TRUE) &&
        ((g_wBoatType == PBOAT_TOP) || (g_bAdaptor == FALSE))) {
        DisplayInPreoperation();

        if ((re = PushDown()) != NO_ERROR) {
            return re;
        }
    }

    DisplayRemoveCarrier();

    while (IsPbPresent()) {}

    DisplayLoadFullPB();

    while (TRUE) {
        while ((cKey = keypad.getKey()) == 0 && !IsStartPressed()) {
            if (g_bCheckOverHeat == TRUE) {
                IsOverHeated();  // read the heat sensor and turn on alarm if
                                 // triggered
            }
        }

        if ((cKey == '#') || IsStartPressed()) { // start
            break;
        } else if (cKey == '*') {    // abort
            return NEEDABORT;
        }
    }

    g_wBoatType  = PBOAT_LOW;
    g_bCombEmpty = FALSE;
    g_bChkBoat   = TRUE;

    if (!IsLowRetainerOpen()) {
        return ERR_RETAINER_CLOSE;
    }

    if (checkBoatAndWafer(1) != NO_ERROR) {
        return NEEDABORT;
    }

    if ((g_bPusher == TRUE) &&
        ((g_wBoatType == PBOAT_LOW) || (g_bAdaptor == FALSE))) {
        // @Jered 2022-04-04 10:49:49 need to check Carrier direction BEFORE
        // autopush
        if (checkPBDirectionBeforePusher()) {
            return NEEDABORT;
        }

        if ((re = PushUp(0)) != NO_ERROR) {
            return re;
        }

        if (checkPBDirectionAfterPusher(PB_HB_BACK) != NO_ERROR) {
            PushDown();
            return NEEDABORT;
        }

        DisplayInPreoperation();

        if (checkPBhbar() != NO_ERROR) {
            return NEEDABORT;
        }
    }

    DisplayInOperation();

    if ((re = ElevUp()) != NO_ERROR) {
        return re;
    }

    if (!IsElevAtLowRetainerPB()) {
        return ERR_ELEV_POSITION;
    }

    if ((re = LowRetainerClose()) != NO_ERROR) {
        return re;
    }

    g_bCombEmpty = TRUE;

    if ((re = ElevMoveHome()) != NO_ERROR) {
        return re;
    }

    if ((g_bPusher == TRUE) &&
        ((g_wBoatType == PBOAT_LOW) || (g_bAdaptor == FALSE))) {
        DisplayInPreoperation();

        if ((re = PushDown()) != NO_ERROR) {
            return re;
        }
    }

    DisplayRemoveCarrier();

    while (IsPbPresent()) {}
    return NO_ERROR;
}

/*==============================================================================
 *                        Function: int DoPbToQbUnload()
 *============================================================================*/
/*** BeginHeader DoPbToQbUnload */
int DoPbToQbUnload();
/*** EndHeader */
int DoPbToQbUnload() {
    char cKey;
    int  re;

    g_bCombEmpty = FALSE;
    g_bChkBoat   = TRUE;

    if (g_bAdaptor == TRUE) {
        g_wBoatType = QBOAT_LOW;
    } else {
        g_wBoatType = QBOAT_TOP;
    }

    if (IsLowRetainerOpen()) {
        if (g_bNeedRecovery == TRUE) {
            g_wBoatType = QBOAT_TOP;

            if ((re = IndexToFront()) != NO_ERROR) {
                return re;
            }
        } else {
            return ERR_RETAINER_OPEN;
        }
    }

    if (checkBoatAndWafer(0) != NO_ERROR) {
        return NEEDABORT;
    }

    if ((g_bPusher == TRUE) &&
        ((g_wBoatType == PBOAT_LOW) || (g_bAdaptor == FALSE))) {
        if ((re = PushUp(0)) != NO_ERROR) {
            return re;
        }

        if (checkPBDirectionAfterPusher(PB_HB_BACK) != NO_ERROR) {
            PushDown();
            return NEEDABORT;
        }

        DisplayInPreoperation();

        if (checkPBhbar() != NO_ERROR) {
            return NEEDABORT;
        }
    }

    DisplayInOperation();

    if (g_wBoatType == QBOAT_LOW) {
        if ((re = ElevUp()) != NO_ERROR) {
            return re;
        }

        if (!IsElevAtLowRetainerQB()) {
            return ERR_ELEV_POSITION;
        }

        if ((re = LowRetainerOpen()) != NO_ERROR) {
            return re;
        }
    }

    g_wBoatType = QBOAT_TOP;

    if ((re = ElevUp()) != NO_ERROR) {
        return re;
    }

    /*
       if(!IsElevAtTopRetainerQB())
       {
          return ERR_ELEV_POSITION;
       }
     */
    if (g_bAdaptor == TRUE) {
        if ((re = TopRetainerOpen()) != NO_ERROR) {
            return re;
        }
    } else {
        if ((re = TopLowRetainerOpen()) != NO_ERROR) {
            return re;
        }
    }

    if ((re = ElevMoveHome()) != NO_ERROR) {
        return re;
    }

    if ((g_bPusher == TRUE) &&
        ((g_wBoatType == PBOAT_LOW) || (g_bAdaptor == FALSE))) {
        DisplayInPreoperation();

        if ((re = PushDown()) != NO_ERROR) {
            return re;
        }
    }

    if (g_bNeedMachineCycle == FALSE) {
        DisplayRemoveBoat();

        while (IsQbPresent()) {}
    }

    return NO_ERROR;
}

/*==============================================================================
 *                        Function: int DoQbToPbLoad()
 *============================================================================*/
/*** BeginHeader DoQbToPbLoad */
int DoQbToPbLoad();
/*** EndHeader */
int DoQbToPbLoad() {
    char cKey;
    int  re;

    g_wBoatType  = QBOAT_TOP;
    g_bCombEmpty = FALSE;
    g_bChkBoat   = TRUE;

    if (!IsTopRetainerOpen() || !IsLowRetainerOpen()
        || IsTopRetainerClose() || IsLowRetainerClose()) {
        return ERR_RETAINER_CLOSE;
    }

    if (checkBoatAndWafer(1) != NO_ERROR) {
        return NEEDABORT;
    }

    // DisplayInOperation();

    if ((re = IndexToFront()) != NO_ERROR) {
        return re;
    }

    if ((g_bPusher == TRUE) &&
        ((g_wBoatType == PBOAT_LOW) || (g_bAdaptor == FALSE))) {
        if ((re = PushUp(0)) != NO_ERROR) {
            return re;
        }

        if (checkPBDirectionAfterPusher(PB_HB_BACK) != NO_ERROR) {
            PushDown();
            return NEEDABORT;
        }

        DisplayInPreoperation();

        if (checkPBhbar() != NO_ERROR) {
            return NEEDABORT;
        }
    }

    DisplayInOperation();

    if ((re = ElevUp()) != NO_ERROR) {
        return re;
    }

    if (g_bAdaptor == TRUE) {
        if (!IsElevAtTopRetainerQB()) {
            return ERR_ELEV_POSITION;
        }

        if ((re = TopRetainerClose()) != NO_ERROR) {
            return re;
        }

        g_wBoatType = QBOAT_LOW;

        if ((re = ElevMoveDown()) != NO_ERROR) {
            return re;
        }

        if (!IsElevAtLowRetainerQB()) {
            return ERR_ELEV_POSITION;
        }

        if ((re = LowRetainerClose()) != NO_ERROR) {
            return re;
        }
    } else {
        if (!IsElevAtTopRetainerPB()) {
            return ERR_ELEV_POSITION;
        }

        if ((re = TopLowRetainerClose()) != NO_ERROR) {
            return re;
        }
    }

    if ((re = ElevMoveHome()) != NO_ERROR) {
        return re;
    }

    if ((g_bPusher == TRUE) &&
        ((g_wBoatType == PBOAT_LOW) || (g_bAdaptor == FALSE))) {
        DisplayInPreoperation();

        if ((re = PushDown()) != NO_ERROR) {
            return re;
        }
    }

    if (g_bNeedMachineCycle == FALSE) {
        DisplayRemoveBoat();

        while (IsQbPresent()) {}
    }

    return NO_ERROR;
}

/*==============================================================================
 *                        Function: int DoQbToPbUnload()
 *============================================================================*/
/*** BeginHeader DoQbToPbUnload */
int DoQbToPbUnload();
/*** EndHeader */
int DoQbToPbUnload() {
    char cKey;
    int  re;

    g_bCombEmpty = TRUE;
    g_bChkBoat   = TRUE;

    if (g_bNeedRecovery == TRUE) {
        if (IsLowRetainerOpen()) {
            g_wBoatType = PBOAT_TOP;

            if ((re = IndexToBack()) != NO_ERROR) {
                return re;
            }
        } else {
            g_wBoatType = PBOAT_LOW;
        }
    } else {
        if (IsLowRetainerOpen()) {
            return ERR_RETAINER_OPEN;
        }

        g_wBoatType = PBOAT_LOW;
    }

    if (g_wBoatType == PBOAT_LOW) {
        if (checkBoatAndWafer(0) != NO_ERROR) {
            return NEEDABORT;
        }

        if ((g_bPusher == TRUE) &&
            ((g_wBoatType == PBOAT_LOW) || (g_bAdaptor == FALSE))) {
            // @Jered 2022-04-04 10:49:49 need to check Carrier direction BEFORE
            // autopush
            if (checkPBDirectionBeforePusher()) {
                return NEEDABORT;
            }

            if ((re = PushUp(0)) != NO_ERROR) {
                return re;
            }

            if (checkPBDirectionAfterPusher(PB_HB_BACK) != NO_ERROR) {
                PushDown();
                return NEEDABORT;
            }

            DisplayInPreoperation();

            if (checkPBhbar() != NO_ERROR) {
                return NEEDABORT;
            }
        }

        DisplayInOperation();

        if ((re = ElevUp()) != NO_ERROR) {
            return re;
        }

        if (!IsElevAtLowRetainerPB()) {
            return ERR_ELEV_POSITION;
        }

        if ((re = LowRetainerOpen()) != NO_ERROR) {
            return re;
        }

        g_bCombEmpty = FALSE;

        if ((re = ElevMoveHome()) != NO_ERROR) {
            return re;
        }

        if ((g_bPusher == TRUE) &&
            ((g_wBoatType == PBOAT_LOW) || (g_bAdaptor == FALSE))) {
            DisplayInPreoperation();

            if ((re = PushDown()) != NO_ERROR) {
                return re;
            }
        }

        DisplayRemoveCarrier();

        while (IsPbPresent()) {}
    }

    if (IsTopRetainerOpen()) {
        if (g_bNeedRecovery == TRUE) {
            return NO_ERROR;
        } else {
            return ERR_RETAINER_OPEN;
        }
    }

    if (g_wBoatType == PBOAT_LOW) { // do not show for recovery and top RT
                                    // only
        DisplayLoadEmptyPB();

        while (TRUE) {
            while ((cKey = keypad.getKey()) == 0 && !IsStartPressed()) {
                if (g_bCheckOverHeat == TRUE) {
                    IsOverHeated();  // read the heat sensor and turn on alarm
                                     // if triggered
                }
            }

            if ((cKey == '#') || IsStartPressed()) { // start
                break;
            } else if (cKey == '*') {    // abort
                return NEEDABORT;
            }
        }
    }

    g_wBoatType  = PBOAT_TOP;
    g_bCombEmpty = TRUE;
    g_bChkBoat   = TRUE;

    if (checkBoatAndWafer(0) != NO_ERROR) {
        return NEEDABORT;
    }

    // DisplayInOperation();

    if ((re = IndexToBack()) != NO_ERROR) {
        return re;
    }

    if ((g_bPusher == TRUE) &&
        ((g_wBoatType == PBOAT_TOP) || (g_bAdaptor == FALSE))) {
        if (g_bMode) {
            // @Jered 2022-04-04 10:49:49 need to check Carrier direction BEFORE
            // autopush
            if (checkPBDirectionBeforePusher()) {
                return NEEDABORT;
            }

            if ((re = PushUp(1)) != NO_ERROR) {
                return re;
            }

            if (checkPBDirectionAfterPusher(PB_HB_FRONT) != NO_ERROR) {
                PushDown();
                return NEEDABORT;
            }

            DisplayInPreoperation();
        } else {
            // @Jered 2022-04-04 10:49:49 need to check Carrier direction BEFORE
            // autopush
            if (checkPBDirectionBeforePusher()) {
                return NEEDABORT;
            }

            if ((re = PushUp(0)) != NO_ERROR) {
                return re;
            }

            if (checkPBDirectionAfterPusher(PB_HB_BACK) != NO_ERROR) {
                PushDown();
                return NEEDABORT;
            }

            DisplayInPreoperation();
        }

        if (checkPBhbar() != NO_ERROR) {
            return NEEDABORT;
        }
    }

    DisplayInOperation();

    if ((re = ElevUp()) != NO_ERROR) {
        return re;
    }

    if (!IsElevAtTopRetainerPB()) {
        return ERR_ELEV_POSITION;
    }

    if ((re = TopRetainerOpen()) != NO_ERROR) {
        return re;
    }

    g_bCombEmpty = FALSE;

    if ((re = ElevMoveHome()) != NO_ERROR) {
        return re;
    }

    if ((g_bPusher == TRUE) &&
        ((g_wBoatType == PBOAT_TOP) || (g_bAdaptor == FALSE))) {
        DisplayInPreoperation();

        if ((re = PushDown()) != NO_ERROR) {
            return re;
        }
    }

    DisplayRemoveCarrier();

    while (IsPbPresent()) {}
    return NO_ERROR;
}

/*==============================================================================
 *                        Function: int DoRecovery()
 *============================================================================*/
/*** BeginHeader DoRecovery */
int DoRecovery();
/*** EndHeader */
int DoRecovery() {
    char cKey;

    g_bNeedRecovery = TRUE;
    g_wBoatType     = 0;
    DisplayRecoveryUnload();

    while (TRUE) {
        while ((cKey = keypad.getKey()) == 0 && !IsStartPressed()) {
            if (g_bCheckOverHeat == TRUE) {
                IsOverHeated();  // read the heat sensor and turn on alarm if
                                 // triggered
            }
        }

        if ((cKey == '#') || IsStartPressed()) { // start
            break;
        } else if (cKey == '*') {    // abort
            return NEEDABORT;
        }
    }

    if (checkBoatAndWafer(0) != NO_ERROR) {
        return NEEDABORT;
    }

    if ((g_bSrJrTransfer > JR_ONLY) && !IsTopRetainerOpen()) {
        if (IsPbPresent()) {
            DoQbToPbUnload();
        } else {
            DoPbToQbUnload();
        }
    } else {
        DoJrUnload();
    }
}

/*==============================================================================
 *                        Function: void DoMachineCycle()
 *============================================================================*/
/*** BeginHeader DoMachineCycle */
void DoMachineCycle();
/*** EndHeader */
void DoMachineCycle() {
    int re;

    // Index wear-out test

    /* for(;;)
       {
          if((re = IndexToFront()) != NO_ERROR)
          {
             CannotCyclingIndex();
             Beep();
             return;
          }

          msDelay(1000);

          if((re = IndexToBack()) != NO_ERROR)
          {
             CannotCyclingIndex();
             Beep();
             return;
          }

          msDelay(1000);
       } */

    if (!IsElevHome() || !IsLowRetainerOpen()
        || ((g_bSrJrTransfer > JR_ONLY) && !IsTopRetainerOpen())) {
        DisplayCannotCycling();
        Beep();
        return;
    }

    g_bNeedMachineCycle = TRUE;
    DisplayInCycling();

    while (TRUE) {
        if (g_bSrJrTransfer > JR_ONLY) {
            if (DoQbToPbLoad() != NO_ERROR) {
                break;
            }

            msDelay(1000);

            if (DoPbToQbUnload() != NO_ERROR) {
                break;
            }

            msDelay(1000);
        } else {
            if (DoJrLoad() != NO_ERROR) {
                break;
            }

            msDelay(1000);

            if (DoJrUnload() != NO_ERROR) {
                break;
            }

            msDelay(1000);
        }
    }
}

/*==============================================================================
 *                        Function: int DoTechnician()
 *============================================================================*/
/*** BeginHeader DoTechnician */
int DoTechnician();
/*** EndHeader */
int DoTechnician() {
    char cKey, cKey6Pressed;

    cKey6Pressed = FALSE;
    g_bTech      = TRUE;

    while (TRUE) {
        DisplayTechMenu();

        while ((cKey = keypad.getKey()) == 0) {
            if (g_bCheckOverHeat == TRUE) {
                IsOverHeated();  // read the heat sensor and turn on alarm if
                                 // triggered
            }
        }

        if (cKey == '1') {                            // input
            TechInput();
            cKey6Pressed = FALSE;
        } else if (cKey == '2') {    // output
            TechOutput();
            cKey6Pressed = FALSE;
        } else if (cKey == '3') {    // cycle
            DoMachineCycle();
            g_bNeedMachineCycle = FALSE;
            cKey6Pressed        = FALSE;
        } else if ((cKey == '4') && (g_bPusher == TRUE) &&
                   ((g_bPusherForPB == TRUE) || (g_bAdaptor == FALSE))) {
            CalibratePusher();
            cKey6Pressed = FALSE;
        } else if (cKey == '6') {
            cKey6Pressed = TRUE;
        } else if ((cKey == '8') && (cKey6Pressed == TRUE)) {
            if (CheckPassword2() == NO_ERROR) {
                SystemConfig();
            }

            cKey6Pressed = FALSE;
        } else {
            cKey6Pressed = FALSE;
        }

        if (cKey == '*') {
            g_bTech = FALSE;
            return NO_ERROR;
        }
    }
}

/*==============================================================================
 *                        Function: int SystemConfig()
 *============================================================================*/
/*** BeginHeader SystemConfig */
int SystemConfig();
/*** EndHeader */
int SystemConfig() {
    int  functionTemp, adaptorTemp, pusherTemp, pusherPbTemp, heatSensorTemp;
    char cKey;

    functionTemp   = g_bSrJrTransfer;
    adaptorTemp    = g_bAdaptor;
    pusherTemp     = g_bPusher;
    pusherPbTemp   = g_bPusherForPB;
    heatSensorTemp = g_bCheckOverHeat;

    DisplayConfigPage();
    DisplayConfigData();

    while (TRUE) {
        while ((cKey = keypad.getKey()) == 0) {}

        if (cKey == '1') {
            functionTemp++;

            if ((functionTemp < 1) || (functionTemp > 3)) {
                functionTemp = 1;
            }

            if (functionTemp == 1) {
                lcd.setCursor(15, 0);
                lcd.print("JR   ");
            } else if (functionTemp == 2) {
                lcd.setCursor(15, 0);
                lcd.print("SR   ");
            } else {
                lcd.setCursor(15, 0);
                lcd.print("SR/JR");
            }
        } else if (cKey == '2') {
            if (pusherTemp == TRUE) {
                pusherTemp = FALSE;
                lcd.setCursor(9, 1);
                lcd.print("N");
            } else {
                pusherTemp = TRUE;
                lcd.setCursor(9, 1);
                lcd.print("Y");
            }
        } else if (cKey == '3') {
            if (adaptorTemp == TRUE) {
                adaptorTemp = FALSE;
                lcd.setCursor(19, 1);
                lcd.print("N");
            } else {
                adaptorTemp = TRUE;
                lcd.setCursor(19, 1);
                lcd.print("Y");
            }
        } else if (cKey == '4') {
            if (pusherPbTemp == TRUE) {
                pusherPbTemp = FALSE;
                lcd.setCursor(9, 2);
                lcd.print("N");
            } else {
                pusherPbTemp = TRUE;
                lcd.setCursor(9, 2);
                lcd.print("Y");
            }
        } else if (cKey == '5') {
            if (heatSensorTemp == TRUE) {
                heatSensorTemp = FALSE;
                lcd.setCursor(19, 2);
                lcd.print("N");
            } else {
                heatSensorTemp = TRUE;
                lcd.setCursor(19, 2);
                lcd.print("Y");
            }
        } else if (cKey == '#') {
            g_bSrJrTransfer  = functionTemp;
            g_bPusher        = pusherTemp;
            g_bAdaptor       = adaptorTemp;
            g_bPusherForPB   = pusherPbTemp;
            g_bCheckOverHeat = heatSensorTemp;
            SaveSettings();
            break;
        } else if (cKey == '*') {
            break;
        }
    }
}

/*==============================================================================
 *                        Function: int TechInput()
 *============================================================================*/
/*** BeginHeader TechInput */
int TechInput();
/*** EndHeader */
int TechInput() {
    char cKey, pageChange;
    int  page;
    unsigned long end;

    page       = 1;
    pageChange = TRUE;
    end        = MS_TIMER + TIMEOUT;

    while (TRUE) {
        if (pageChange == TRUE) {
            if (((g_bSrJrTransfer == JR_ONLY) && (page > 2)) ||
                ((g_bSrJrTransfer > JR_ONLY) && (page > 4))) {
                page = 1;
            }

            if (page == 1) {
                DisplayTechInputPage_1();
                DisplayTechInputPage_1Data();
            } else if (page == 2) {
                DisplayTechInputPage_2();
                DisplayTechInputPage_2Data();
            } else if (page == 3) {
                DisplayTechInputPage_3();
                DisplayTechInputPage_3Data();
            } else if (page == 4) {
                DisplayTechInputPage_4();
                DisplayTechInputPage_4Data();
            }

            pageChange = FALSE;
        }

        while (MS_TIMER > end) {
            if (((page > 2) && (g_bSrJrTransfer == JR_ONLY)) ||
                ((page > 4) && (g_bSrJrTransfer > JR_ONLY))) {
                page = 1;
            }

            if (page == 1) {
                DisplayTechInputPage_1Data();
            } else if (page == 2) {
                DisplayTechInputPage_2Data();
            } else if (page == 3) {
                DisplayTechInputPage_3Data();
            } else if (page == 4) {
                DisplayTechInputPage_4Data();
            }

            end = MS_TIMER + TIMEOUT;
        }

        if (g_bCheckOverHeat == TRUE) {
            IsOverHeated();  // read the heat sensor and turn on alarm if
                             // triggered
        }

        if ((cKey = keypad.getKey()) == 0) {
            continue;
        }

        if (cKey == '#') {   // next input page
            page++;
            pageChange = TRUE;
        } else if (cKey == '*') {
            return NO_ERROR;
        }
    }
}

/*==============================================================================
 *                        Function: int TechOutput()
 *============================================================================*/
/*** BeginHeader TechOutput */
int TechOutput();
/*** EndHeader */
int TechOutput() {
    char cKey;
    int  page;
    int  re, cycle, cycleNumber;
    unsigned long end;

    page = 1;

    while (TRUE) {
        if (((g_bSrJrTransfer == JR_ONLY) && (page > 1)) ||
            ((g_bSrJrTransfer > JR_ONLY) && (page > 2))) {
            page = 1;
        }

        if (page == 1) {
            DisplayTechOutputPage_1();
        } else if (page == 2) {
            DisplayTechOutputPage_2();
        }

        g_bChkBoat   = FALSE;
        g_bCombEmpty = TRUE;
        g_wBoatType  = PBOAT_TOP;

        while ((cKey = keypad.getKey()) == 0) {
            if (g_bCheckOverHeat == TRUE) {
                IsOverHeated();  // read the heat sensor and turn on alarm if
                                 // triggered
            }
        }

        if (page == 1) {
            if (cKey == '1') {                        // elev up
                DisplayElevMoving();

                if (g_bSrJrTransfer > JR_ONLY) {
                    g_wBoatType = PBOAT_TOP;
                } else {
                    g_wBoatType = PBOAT_LOW;
                }

                ElevUp();
            } else if (cKey == '2') {    // elev down
                DisplayElevMoving();
                ElevMoveHome();
            } else if (cKey == '3') {    // low rt open
                DisplayRTMoving();
                LowRetainerOpen();
            } else if (cKey == '4') {    // low rt close
                DisplayRTMoving();
                LowRetainerClose();
            } else if (g_bSrJrTransfer > JR_ONLY) {
                if (cKey == '5') {      // Alarm
                    Beep();
                }
            } else if (g_bPusher == TRUE) {
                if (cKey == '5') {      // push up
                    DisplayPusherMoving();

                    if (((g_bAdaptor == FALSE) && IsQbPresent()) ||
                        (g_bPusherForPB != TRUE)) {
                        g_wBoatType = QBOAT_LOW;
                    } else {
                        g_wBoatType = PBOAT_LOW;
                    }

                    PushUp(0);
                } else if (cKey == '6') {    // push down
                    DisplayPusherMoving();
                    PushDown();
                }
            }
        } else if (page == 2) {
            if (cKey == '1') {                        // top rt open
                DisplayRTMoving();
                TopRetainerOpen();
            } else if (cKey == '2') {    // top rt close
                DisplayRTMoving();
                TopRetainerClose();
            } else if (cKey == '5') {    // index to front
                IndexToFront();
            } else if (cKey == '6') {    // index to back
                IndexToBack();
            } else if (g_bPusher == TRUE) {
                if (cKey == '3') {      // push up
                    DisplayPusherMoving();

                    if (((g_bAdaptor == FALSE) && IsQbPresent()) ||
                        (g_bPusherForPB != TRUE)) {
                        g_wBoatType = QBOAT_LOW;
                    } else {
                        g_wBoatType = PBOAT_LOW;
                    }

                    PushUp(0);
                } else if (cKey == '4') {    // push down
                    DisplayPusherMoving();
                    PushDown();
                }
            } else if (g_bPusher == FALSE) {
                if (cKey == '3') {      // Cycle index
                    cycle       = TRUE;
                    cycleNumber = 0;

                    while (cycle == TRUE) {
                        if (cycleNumber > 50000) {
                            cycleNumber = 0;
                        }

                        lcd.clear();
                        lcd.setCursor(0, 0);
                        lcd.print("Index is Cycling!");
                        lcd.setCursor(0, 1);
                        lcd.print("Cycle Number:");
                        lcd.setCursor(15, 1);
                        lcd.print(cycleNumber);
                        msDelay(3000);

                        if ((re = IndexToFront()) != NO_ERROR) {
                            DisplayErrorMessage(ERR_INDEX_TO_FRONT_FAIL,
                                                TRUE);

                            if ((re = waitCmdAfterPause()) == NEEDABORT) {
                                break;
                            }
                        }

                        msDelay(2000);

                        if ((re = IndexToBack()) != NO_ERROR) {
                            DisplayErrorMessage(ERR_INDEX_TO_BACK_FAIL, TRUE);

                            if ((re = waitCmdAfterPause()) == NEEDABORT) {
                                break;
                            }
                        }

                        cycleNumber++;
                        DisplayInOperation();
                        end = MS_TIMER + 2000;

                        while (MS_TIMER < end) {
                            if ((re = pauseCheck()) == NEEDABORT) {
                                cycle = FALSE;
                            }
                        }
                    }
                }
            }
        }

        if (cKey == '#') {   // next output page
            page++;
        } else if (cKey == '*') {
            return NO_ERROR;
        }
    }
}

/*==============================================================================
 *                        Function: void AlarmOn()
 *============================================================================*/
/*** BeginHeader AlarmOn */
void AlarmOn();
/*** EndHeader */
void AlarmOn() {
    keypad.pin_write(ALARM_TRIG, 0);
}

/*==============================================================================
 *                        Function: void AlarmOff()
 *============================================================================*/
/*** BeginHeader AlarmOff */
void AlarmOff();
/*** EndHeader */
void AlarmOff() {
    keypad.pin_write(ALARM_TRIG, 1);
}

/*==============================================================================
 *                        Function: void Beep()
 *============================================================================*/
/*** BeginHeader Beep */
void Beep();
/*** EndHeader */
void Beep() {
    AlarmOn();
    msDelay(1000);
    AlarmOff();
}

/*==============================================================================
 *               Function: void setMotorDrive(int motor, int direction)
 *============================================================================*/
/*** BeginHeader setMotorDrive */
void setMotorDrive(int motor,
                   int direction);
/*** EndHeader */
void setMotorDrive(int motor, int direction) {
    switch (motor) {
        case  ELEVATOR:
            digitalWrite(ELEV_DIR_TRIG, direction);
            digitalWrite(ELEV_RUN_TRIG, 0);           // enable motor to RUN

            if (g_bHighSpeed == TRUE) {
                digitalWrite(ELEV_SPEED_TRIG, 1);  // move Elevator with high
                                                   // speed
            } else {
                digitalWrite(ELEV_SPEED_TRIG, 0);
            }
            break;

        /*    case  RETAINER:
                    digitalWrite(RETAINER_DIR_TRIG, direction);
                    break; */

        default:
            break;
    }
}

/*==============================================================================
 *                        Function: int myinp(int port)
 *============================================================================*/
/*** BeginHeader myinp */
int myinp(int port);
/*** EndHeader */
int myinp(int port) {
    /** read input port
    ** @return TRUE or FALSE */
    int i, data;

    while (TRUE) {
        data = 0;

        for (i = 0; i < 3; i++) {
            data += digitalRead(port);
        }

        if (data > 2) {
            return TRUE;
        } else {
            return FALSE;
        }
    }
}

/*==============================================================================
 *                        Function: int myinp2(int port)
 *============================================================================*/
/*** BeginHeader myinp2 */
int myinp2(int port);
/*** EndHeader */
int myinp2(int port) {
    /** read input port
    ** @return TRUE or FALSE */
    int   i, data;
    float temp;

    while (TRUE) {
        data = 0;

        for (i = 0; i < 3; i++) {
            if (port > 22) { // DIO08-DIO15 AND DIN16-DIN31 digital inputs
                data += digitalRead(port);
            } else {   // channel 0-7 for analog inputs with gaincode 2 for 5V
                       // range
                //          temp = analogRead(port);
                //          sprintf(szDisplayString, "Channel = %2d Voltage =
                // %4d", port, temp);
                //          Serial.println(szDisplayString);

                if (analogRead(port) > 512) { // treat as high if > 2.5 volts
                    data += 1;
                }
            }
        }

        if (data > 2) {
            return TRUE;
        } else {
            return FALSE;
        }
    }
}

/*==============================================================================
 *                        Function: int BoatCheck()
 *============================================================================*/
/*** BeginHeader BoatCheck */
int BoatCheck();
/*** EndHeader */
int BoatCheck() {
    int re;

    // if boat off, pause the system. report error and wait for next command
    if ((g_bChkBoat == FALSE) ||
        ((g_bTech == TRUE) && (g_bNeedMachineCycle == FALSE))) {
        return NO_ERROR;
    }

    if ((IsPbPresent() &&
         ((g_wBoatType == PBOAT_TOP) || (g_wBoatType == PBOAT_LOW)))
        || (g_wBoatType == QBOAT_TOP) || (g_wBoatType == QBOAT_LOW)) {
        return NO_ERROR;
    }

    Pause();
    DisplayErrorMessage(ERR_MISSING_RUN_BOAT, TRUE);

    while ((re = waitCmdAfterPause()) == NEEDRESUME) {
        if (IsPbPresent() &&
            ((g_wBoatType == PBOAT_TOP) || (g_wBoatType == PBOAT_LOW))) {
            return NEEDRESUME;
        }

        DisplayErrorMessage(ERR_MISSING_RUN_BOAT, TRUE);
    }

    return re;
}

/*==============================================================================
 *                        Function: int checkPBhbar()
 *============================================================================*/
/*** BeginHeader checkPBhbar */
int checkPBhbar();
/*** EndHeader */
int checkPBhbar() {
    int re;

    return NO_ERROR;

    if (IsPBhBarOk()) {
        return NO_ERROR;
    }

    msDelay(250);

    if (IsPBhBarOk()) {
        return NO_ERROR;
    }

    msDelay(250);

    if (IsPBhBarOk()) {
        return NO_ERROR;
    }

    msDelay(250);

    Pause();
    DisplayErrorMessage(ERR_NOT_PB_HBAR, TRUE);

    while ((re = waitCmdAfterPause()) == NEEDRESUME) {
        if (IsPBhBarOk()) {
            return NEEDRESUME;
        }

        DisplayErrorMessage(ERR_NOT_PB_HBAR, TRUE);
    }

    return re;
}

/*==============================================================================
 *                        Function: int checkBoatAndWafer(int wafer)
 *============================================================================*/
/*** BeginHeader checkBoatAndWafer */
int checkBoatAndWafer(int wafer);
/*** EndHeader */
int checkBoatAndWafer(int wafer) {
    int re;

    // if boat off, wafer missing or full per corresponding flags
    // pause the system. report error and wait for next command
    re = NO_ERROR;

    if ((((g_wBoatType == PBOAT_TOP) || (g_wBoatType == PBOAT_LOW)) &&
         !IsPbPresent())
        || (((g_wBoatType == QBOAT_TOP) || (g_wBoatType == QBOAT_LOW)) &&
            !IsQbPresent())
        || ((g_bAdaptor == TRUE) &&
            ((g_wBoatType == QBOAT_TOP) || (g_wBoatType == QBOAT_LOW)) &&
            !IsAdaptorPresent())
        || ((g_wBoatType == 0) && !IsPbPresent() && !IsQbPresent())) {
        re = ERR_MISSING_BOAT;
    } else if (g_bCheckOverHeat && IsOverHeated()) {
        re = ERR_OVER_HEATED;
    } else if ((wafer == 0) && IsWaferInBoat()) {
        re = ERR_WAFER_IN_BOAT;
    } else if ((wafer == 1) && !IsWaferInBoat()) {
        re = ERR_NO_WAFER_IN_BOAT;
    }

    if (!re) {
        return NO_ERROR;
    }

    Pause();
    DisplayErrorMessage(re, TRUE);

    while ((re = waitCmdAfterPause()) == NEEDRESUME) {
        re = NO_ERROR;

        if ((((g_wBoatType == PBOAT_TOP) || (g_wBoatType == PBOAT_LOW)) &&
             !IsPbPresent())
            || (((g_wBoatType == QBOAT_TOP) || (g_wBoatType == QBOAT_LOW)) &&
                !IsQbPresent())
            || ((g_bAdaptor == TRUE) &&
                ((g_wBoatType == QBOAT_TOP) || (g_wBoatType == QBOAT_LOW)) &&
                !IsAdaptorPresent())
            || ((g_wBoatType == 0) && !IsPbPresent() && !IsQbPresent())) {
            re = ERR_MISSING_BOAT;
        } else if (g_bCheckOverHeat && IsOverHeated()) {
            re = ERR_OVER_HEATED;
        } else if ((wafer == 0) && IsWaferInBoat()) {
            re = ERR_WAFER_IN_BOAT;
        } else if ((wafer == 1) && !IsWaferInBoat()) {
            re = ERR_NO_WAFER_IN_BOAT;
        }

        if (!re) {
            return NO_ERROR;
        }

        DisplayErrorMessage(re, TRUE);
    }

    return re;
}

/*==============================================================================
 *                        Function: int checkPBDirectionAfterPusher(int dir)
 *============================================================================*/
/*** BeginHeader checkPBDirectionAfterPusher */
int checkPBDirectionAfterPusher(int dir);
/*** EndHeader */
int checkPBDirectionAfterPusher(int dir) {
    int re;

    // if boat off, wafer missing or full per corresponding flags
    // pause the system. report error and wait for next command
    re = NO_ERROR;

    if ((dir == PB_HB_BACK) && IsPBHBDirFront()) {
        re = ERR_PB_DIRECTION;
    } else if ((dir == PB_HB_FRONT) && !IsPBHBDirFront()) {
        re = ERR_PB_DIRECTION;
    }

    if (!re) {
        return NO_ERROR;
    }

    Pause();
    DisplayErrorMessage(re, TRUE);

    while ((re = waitCmdAfterPause()) == NEEDRESUME) {
        re = NO_ERROR;

        if ((dir == PB_HB_BACK) && IsPBHBDirFront()) {
            re = ERR_PB_DIRECTION;
        } else if ((dir == PB_HB_FRONT) && !IsPBHBDirFront()) {
            re = ERR_PB_DIRECTION;
        }

        if (!re) {
            return NO_ERROR;
        }

        DisplayErrorMessage(re, TRUE);
    }

    return re;
}

/*==============================================================================
 *                        Function: int checkPBDirectionBeforePusher(int dir)
 *============================================================================*/
/*** BeginHeader checkPBDirectionBeforePusher */
int checkPBDirectionBeforePusher();
/*** EndHeader */
int checkPBDirectionBeforePusher() {
    int re;

    // if boat off, wafer missing or full per corresponding flags
    // pause the system. report error and wait for next command
    re = NO_ERROR;

    if (g_bMode == FACE_TO_FACE) {
        if ((g_wBoatType == PBOAT_TOP) && IsPBDirFrontOn()) {
            re = ERR_PB_DIRECTION;
        } else if ((g_wBoatType == PBOAT_LOW) && IsPBDirBackOn()) {
            re = ERR_PB_DIRECTION;
        }
    } else if ((g_bMode == STANDARD) && IsPBDirBackOn()) {
        re = ERR_PB_DIRECTION;
    }

    if (!re) {
        return NO_ERROR;
    }

    Pause();
    DisplayErrorMessage(re, TRUE);

    while ((re = waitCmdAfterPause()) == NEEDRESUME) {
        re = NO_ERROR;

        if ((g_bMode == FACE_TO_FACE) && IsPBDirFrontOn()) {
            re = ERR_PB_DIRECTION;
        } else if ((g_bMode == STANDARD) && IsPBDirBackOn()) {
            re = ERR_PB_DIRECTION;
        }

        if (!re) {
            return NO_ERROR;
        }

        DisplayErrorMessage(re, TRUE);
    }

    return re;
}

/*==============================================================================
 *                        Function: int Pause()
 *============================================================================*/
/*** BeginHeader Pause */
void Pause();
/*** EndHeader */
void Pause() {
    digitalWrite(ELEV_RUN_TRIG, 1);                   // disable stepper from
                                                      // RUN
}

/*==============================================================================
 *                        Function: int pauseCheck()
 *============================================================================*/
/*** BeginHeader pauseCheck */
int pauseCheck();
/*** EndHeader */
int pauseCheck() {
    // check pause from keypad and PAUSE button, if received, pause the
    // system.
    // and wait for next key action
    if ((keypad.getKey() != '*') && !IsPauseButtonPressed()) {
        return NO_ERROR;
    }

    Pause();
    DisplayResumeOrAbort();
    return waitCmdAfterPause();
}

/*==============================================================================
 *                        Function: int waitCmdAfterPause()
 *============================================================================*/
/*** BeginHeader waitCmdAfterPause */
int waitCmdAfterPause();
/*** EndHeader */
int waitCmdAfterPause() {
    int wKey;

    /** wait resume/abort message from host */
    while (TRUE) {
        do{
            wKey = keypad.getKey();
        }while (wKey != '*' && wKey != '#' && wKey != '0' &&
                !IsStartPressed());

        AlarmOff();

        if ((wKey == '#') || IsStartPressed()) {
            //       Serial.println("Do resume after pause\n");
            return NEEDRESUME;
        } else if (wKey == '*') {
            return NEEDABORT;
        } else if (wKey == '0') {    // if it's 0 then turn off alarm only
            AlarmOff();
        }
    }
}

/*==============================================================================
 *                        Function: int IsPbPresent()
 *============================================================================*/
/*** BeginHeader IsPbPresent */
int IsPbPresent();
/*** EndHeader */
int IsPbPresent() {
    return !myinp(PB_PRESENT_SEN);
}

/*==============================================================================
 *                        Function: int IsWaferInBoat()
 *============================================================================*/
/*** BeginHeader IsWaferInBoat */
int IsWaferInBoat();
/*** EndHeader */
int IsWaferInBoat() {
    return !myinp(PB_WAFER_SEN);
}

/*==============================================================================
 *                        Function: int IsQbPresent()
 *============================================================================*/
/*** BeginHeader IsQbPresent */
int IsQbPresent();
/*** EndHeader */
int IsQbPresent() {
    return !myinp(QB_PRESENT_SEN);
}

/*==============================================================================
 *                        Function: int IsAdaptorPresent()
 *============================================================================*/
/*** BeginHeader IsAdaptorPresent */
int IsAdaptorPresent();
/*** EndHeader */
int IsAdaptorPresent() {
    return !myinp(QB_PRESENT_SEN);  // use the same sensor for both qb and its
                                    // adaptor
}

/*==============================================================================
 *                  Function: void msDelay(unsigned int wDelayTime)
 *============================================================================*/
/*** BeginHeader msDelay */
void msDelay(unsigned int wDelayTime);
/*** EndHeader */
void msDelay(unsigned int wDelayTime) {
    delay(wDelayTime);
}

/*==============================================================================
 *               Function: void DelayMilliseconds(unsigned int wDelayTime)
 *============================================================================*/
/*** BeginHeader DelayMilliseconds */
void DelayMilliseconds(unsigned int wDelayTime);
/*** EndHeader */
void DelayMilliseconds(unsigned int wDelayTime) {
    delay(wDelayTime);
}

/*==============================================================================
 *               Function: void Delay10uSeconds(unsigned int wDelayTime)
 *============================================================================*/
/*** BeginHeader Delay10uSeconds */
void Delay10uSeconds(unsigned int wDelayTime);
/*** EndHeader */
void Delay10uSeconds(unsigned int wDelayTime) {
    do{
        delayMicroseconds(10);
    }while (wDelayTime-- > 0);
}

/*==============================================================================
 *               Function: void Delay100usec(unsigned int wDelayTime)
 *============================================================================*/
/*** BeginHeader Delay100usec */
void Delay100usec(unsigned int wDelayTime);
/*** EndHeader */
void Delay100usec(unsigned int wDelayTime) {
    do{
        Delay10uSeconds(10);
    }while (wDelayTime-- > 0);
}

// Steve added 0n 2/13/2008

/*==============================================================================
 *                        Function: int upSafetyCheck()
 *============================================================================*/
/*** BeginHeader upSafetyCheck */
int upSafetyCheck();
/*** EndHeader */
int upSafetyCheck() {
    unsigned long end;

    // check elev up safety sensor and if triggered, pause the system.
    // and wait for next key action
    if (IsElevUpSafe()) {
        return NO_ERROR;
    }

    Pause();
    msDelay(250);

    // STEVE ADDED 2/11/2008
    g_bHighSpeed = FALSE;
    setMotorDrive(ELEVATOR, ELEV_DOWN_DIR);

    // change to low speed
    digitalWrite(ELEV_SPEED_TRIG, 0);                 // STEVE ADDED 2/11/2008

    end = MS_TIMER + 5000;                            // 1000; Steve changed
                                                      // per QC 2/4/2008

    while (MS_TIMER < end) {
        if (IsElevHome()) {
            // stop elevator motor RUN
            msDelay(20);                              // to better trigger the
                                                      // sensor
            digitalWrite(ELEV_RUN_TRIG, 1);
            break;
        }
    }

    Pause();

    // DisplayErrorMessage(ERR_MOVING_ELEV, TRUE);
    DisplayErrorMessage(ERR_UPSAFETY_FAILED, TRUE);  // STEVE
    return waitCmdAfterPause();
}

/*---------------------------- end of func.lib
   -------------------------------*/
