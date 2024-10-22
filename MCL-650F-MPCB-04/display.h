/*******************************************************************************
 *               Copyright(c) 2022, Mactronix Inc. All rights reserved
 *
 *               File:         display.h
 *               Description:  all display related functions
 *               Author: Jered Yang
 ******************************************************************************/
void DisplayMactronix() {
    lcd.clear();
    lcd.setCursor(6, 1);
    lcd.print("MACTRONIX");
    lcd.setCursor(7, 2);
    lcd.print("MCL-650F");
}

void DisplayOperationMode() {
    if (g_bSrJrTransfer <= SR_ONLY) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("1: To Transfer");
        lcd.setCursor(0, 1);
        lcd.print("2: Technician");

        if (g_bMode == FACE_TO_FACE) {
            lcd.setCursor(0, 3);
            lcd.print("4: Mode Face to Face");
        } else {
            lcd.setCursor(0, 3);
            lcd.print("4: Mode Standard");
        }
    } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("1: Jr. Transfer");
        lcd.setCursor(0, 1);
        lcd.print("2: Sr. Transfer");
        lcd.setCursor(0, 2);
        lcd.print("3: Technician");

        if (g_bMode) {
            lcd.setCursor(0, 3);
            lcd.print("4: Mode Face to Face");
        } else {
            lcd.setCursor(0, 3);
            lcd.print("4: Mode Standard");
        }
    }
}

void DisplayResetTechMode() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("The Tool Needs to");
    lcd.setCursor(0, 1);
    lcd.print("Be Initialized.");
    lcd.setCursor(0, 2);
    lcd.print("1 or START: Initiali");
    lcd.setCursor(0, 3);
    lcd.print("2: Technician");
}

void DisplayRecoverTechMode() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Retainer not Open.");
    lcd.setCursor(0, 1);
    lcd.print("Recover/Tech to Open");
    lcd.setCursor(0, 2);
    lcd.print("1 or START: Recover");
    lcd.setCursor(0, 3);
    lcd.print("2: Technician");
}

void DisplayLoadFullBoat() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Wafer to Retainer");
    lcd.setCursor(0, 1);
    lcd.print("Load a Full CR/BT");
    lcd.setCursor(0, 2);
    lcd.print("Press #/START to TRF");
    lcd.setCursor(0, 3);
    lcd.print("Or * Key to Abort.");
}

void DisplayLoadEmptyContainer() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Wafer to CR/BT");
    lcd.setCursor(0, 1);
    lcd.print("Load an Empty CR/BT");
    lcd.setCursor(0, 2);
    lcd.print("Press #/START to TRF");
    lcd.setCursor(0, 3);
    lcd.print("Or * Key to Abort.");
}

void DisplayLoadFullPB() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Wafer to Retainer");
    lcd.setCursor(0, 1);
    lcd.print("Load a Full Carrier");
    lcd.setCursor(0, 2);
    lcd.print("Press #/START to TRF");
    lcd.setCursor(0, 3);
    lcd.print("Or * Key to Abort.");
}

void DisplayLoadEmptyPB() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Wafer to Carrier");
    lcd.setCursor(0, 1);
    lcd.print("Load an Empty Carrier");
    lcd.setCursor(0, 2);
    lcd.print("Press #/START to TRF");
    lcd.setCursor(0, 3);
    lcd.print("Or * Key to Abort.");
}

void DisplayLoadFullQB() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Wafer to Retainer");
    lcd.setCursor(0, 1);
    lcd.print("Load a Full QB");
    lcd.setCursor(0, 2);
    lcd.print("Press #/START to TRF");
    lcd.setCursor(0, 3);
    lcd.print("Or * Key to Abort.");
}

void DisplayLoadEmptyQB() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Wafer to Boat");
    lcd.setCursor(0, 1);
    lcd.print("Load an Empty Boat");
    lcd.setCursor(0, 2);
    lcd.print("Press #/START to TRF");
    lcd.setCursor(0, 3);
    lcd.print("Or * Key to Abort.");
}

void DisplayRecoveryUnload() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("To Do Recovery");
    lcd.setCursor(0, 1);
    lcd.print("Load an Empty CR/BT");
    lcd.setCursor(0, 2);
    lcd.print("Press #/START to TRF");
    lcd.setCursor(0, 3);
    lcd.print("Or * Key to Abort.");
}

void DisplayRemoveContainer() {
    // KeypadReset();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Remove CR/BT for ");
    lcd.setCursor(0, 1);
    lcd.print("next operation.");
}

void DisplayRemoveBoat() {
    // KeypadReset();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Remove Boat for ");
    lcd.setCursor(0, 1);
    lcd.print("next operation.");
}

void DisplayRemoveCarrier() {
    // KeypadReset();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Remove Carrier for");
    lcd.setCursor(0, 1);
    lcd.print("next operation.");
}

void DisplayInPreoperation() {
    // KeypadReset();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tool is in Operation");
}

void DisplayInOperation() {
    // KeypadReset();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tool is in Operation");
    lcd.setCursor(0, 2);
    lcd.print("To Pause Operation");
    lcd.setCursor(0, 3);
    lcd.print("Press * Key or STOP");
}

void DisplayIndexing() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Index is Moving!");
}

void DisplayPusherMoving() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pusher is Moving!");
}

void DisplayRTMoving() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Retainer is Moving!");
    lcd.setCursor(0, 2);
    lcd.print("To Pause Operation");
    lcd.setCursor(0, 3);
    lcd.print("Press * Key or STOP");
}

void DisplayElevMoving() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Elevator is Moving!");
    lcd.setCursor(0, 2);
    lcd.print("To Pause Operation");
    lcd.setCursor(0, 3);
    lcd.print("Press * Key or STOP");
}

void CannotCyclingIndex() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Index Fail!");
}

void DisplayInPreCycling() {
    // KeypadReset();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tool is in Cycle!");
}

void DisplayCannotCycling() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Need Retainer and");
    lcd.setCursor(0, 1);
    lcd.print("Elevator Home for");
    lcd.setCursor(0, 2);
    lcd.print("Cycle!");
}

void DisplayInCycling() {
    // KeypadReset();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tool is in Cycle!");
    lcd.setCursor(0, 2);
    lcd.print("To Pause Operation");
    lcd.setCursor(0, 3);
    lcd.print("Press * Key or STOP");
}

void DisplayResumeOrAbort() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Operation Is Paused.");
    lcd.setCursor(0, 2);
    lcd.print("Press #/START to RES");
    lcd.setCursor(0, 3);
    lcd.print("Or * Key to Abort.");
}

void DisplayTechMenu() {
    if ((g_bPusher == TRUE) &&
        ((g_bPusherForPB == TRUE) || (g_bAdaptor == FALSE))) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("1: Input, 2: Output");
        lcd.setCursor(0, 1);
        lcd.print("3: Cycle, 4: CalPush");

        //    lcd.setCursor(0, 2);
        //    lcd.print("5: Internal Use");
        lcd.setCursor(0, 3);
        lcd.print("Press * to Quit");
    } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("1: Input, 2: Output");
        lcd.setCursor(0, 1);
        lcd.print("3: Cycle");

        //    lcd.setCursor(0, 2);
        //    lcd.print("5: Internal Use");
        lcd.setCursor(0, 3);
        lcd.print("Press * to Quit");
    }
}

void DisplayConfigPage() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("1:SysFunction:      ");
    lcd.setCursor(0, 1);
    lcd.print("2:Pusher  ,3:Adapt  ");
    lcd.setCursor(0, 2);
    lcd.print("4:PushPb  ,5:Heat   ");
    lcd.setCursor(0, 3);
    lcd.print("Key#:Save, Key*:Quit");
}

void DisplayConfigData() {
    if (g_bSrJrTransfer == JR_ONLY) {
        lcd.setCursor(15, 0);
        lcd.print("JR   ");
    } else if (g_bSrJrTransfer == SR_ONLY) {
        lcd.setCursor(15, 0);
        lcd.print("SR   ");
    } else {
        lcd.setCursor(15, 0);
        lcd.print("SR/JR");
    }

    if (g_bPusher == TRUE) {
        lcd.setCursor(9, 1);
        lcd.print("Y");
    } else {
        lcd.setCursor(9, 1);
        lcd.print("N");
    }

    if (g_bAdaptor == TRUE) {
        lcd.setCursor(19, 1);
        lcd.print("Y");
    } else {
        lcd.setCursor(19, 1);
        lcd.print("N");
    }

    if (g_bPusherForPB == TRUE) {
        lcd.setCursor(9, 2);
        lcd.print("Y");
    } else {
        lcd.setCursor(9, 2);
        lcd.print("N");
    }

    if (g_bCheckOverHeat == TRUE) {
        lcd.setCursor(19, 2);
        lcd.print("Y");
    } else {
        lcd.setCursor(19, 2);
        lcd.print("N");
    }
}

void DisplayTechInputPage_1() {
    if (g_bAdaptor == TRUE) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Carrier   ,QB/Adap  ");
        lcd.setCursor(0, 1);
        lcd.print("LowRtOp   ,LowRtCl  ");

        if (g_bCheckOverHeat == TRUE) {
            lcd.setCursor(0, 2);
            lcd.print("Heat      ,PBdir    ");
        } else {
            lcd.setCursor(0, 2);
            lcd.print("PBdirF    ,PBdirB   ");
        }

        lcd.setCursor(0, 3);
        lcd.print("Key#:Next, Key*:Quit");
    } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Carrier   ,QB       ");
        lcd.setCursor(0, 1);
        lcd.print("LowRtOp   ,LowRtCl  ");

        if (g_bCheckOverHeat == TRUE) {
            lcd.setCursor(0, 2);
            lcd.print("Heat      ,PBdir    ");
        } else {
            lcd.setCursor(0, 2);
            lcd.print("PBdirF    ,PBdirB   ");
        }

        lcd.setCursor(0, 3);
        lcd.print("Key#:Next, Key*:Quit");
    }
}

void DisplayTechInputPage_1Data() {
    int wPbPresent;
    int wQbPresent;
    int wLowRtOpen;
    int wLowRtClose;
    int wQbAdaptor;
    int wOverHeat;
    int wPBDirFront;
    int wPBDirBack;

    if (IsPbPresent()) {
        wPbPresent = 1;
    } else {
        wPbPresent = 0;
    }

    if (IsQbPresent()) {
        wQbPresent = 1;
    } else {
        wQbPresent = 0;
    }

    if (IsLowRetainerOpen()) {
        wLowRtOpen = 1;
    } else {
        wLowRtOpen = 0;
    }

    if (IsLowRetainerClose()) {
        wLowRtClose = 1;
    } else {
        wLowRtClose = 0;
    }

    if (IsAdaptorPresent()) {
        wQbAdaptor = 1;
    } else {
        wQbAdaptor = 0;
    }

    if (IsOverHeated()) {
        wOverHeat = 1;
    } else {
        wOverHeat = 0;
    }

    if (IsPBDirFrontOn()) {
        wPBDirFront = 1;
    } else {
        wPBDirFront = 0;
    }

    if (IsPBDirBackOn()) {
        wPBDirBack = 1;
    } else {
        wPBDirBack = 0;
    }

    if (g_bAdaptor == TRUE) {
        lcd.setCursor(9, 0);
        lcd.print(wPbPresent);
        lcd.setCursor(19, 0);
        lcd.print(wQbPresent);

        lcd.setCursor(9, 1);
        lcd.print(wLowRtOpen);
        lcd.setCursor(19, 1);
        lcd.print(wLowRtClose);

        //    lcd.setCursor(9, 2);
        //    lcd.print(wQbAdaptor);

        if (g_bCheckOverHeat == TRUE) {
            lcd.setCursor(9, 2);
            lcd.print(wOverHeat);
            lcd.setCursor(19, 2);
            lcd.print(wPBDirFront);
        } else {
            lcd.setCursor(9, 2);
            lcd.print(wPBDirFront);
            lcd.setCursor(19, 2);
            lcd.print(wPBDirBack);
        }
    } else {
        lcd.setCursor(9, 0);
        lcd.print(wPbPresent);
        lcd.setCursor(19, 0);
        lcd.print(wQbPresent);

        lcd.setCursor(9, 1);
        lcd.print(wLowRtOpen);
        lcd.setCursor(19, 1);
        lcd.print(wLowRtClose);

        if (g_bCheckOverHeat == TRUE) {
            lcd.setCursor(9, 2);
            lcd.print(wOverHeat);
            lcd.setCursor(19, 2);
            lcd.print(wPBDirFront);
        } else {
            lcd.setCursor(9, 2);
            lcd.print(wPBDirFront);
            lcd.setCursor(19, 2);
            lcd.print(wPBDirBack);
        }
    }
}

void DisplayTechInputPage_2() {
    if (g_bSrJrTransfer == JR_ONLY) {
        if (g_bAdaptor == FALSE) {
            if (g_bPusher == TRUE) {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("PbRT");
                lcd.setCursor(0, 1);
                lcd.print("RTSpd     ,PlatSpd  ");
                lcd.setCursor(0, 2);
                lcd.print("ElevHm    ,PushHm   ");
                lcd.setCursor(0, 3);
                lcd.print("Key#:Next, Key*:Quit");
            } else {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("PbRT");
                lcd.setCursor(0, 1);
                lcd.print("RTSpd     ,PlatSpd  ");
                lcd.setCursor(0, 2);
                lcd.print("ElevHm");
                lcd.setCursor(0, 3);
                lcd.print("Key#:Next, Key*:Quit");
            }
        } else {
            if (g_bPusher == TRUE) {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("PbRT      ,QbRT     ");
                lcd.setCursor(0, 1);
                lcd.print("RTSpd     ,PlatSpd  ");
                lcd.setCursor(0, 2);
                lcd.print("ElevHm    ,PushHm   ");
                lcd.setCursor(0, 3);
                lcd.print("Key#:Next, Key*:Quit");
            } else {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("PbRT      ,QbRT     ");
                lcd.setCursor(0, 1);
                lcd.print("RTSpd     ,PlatSpd  ");
                lcd.setCursor(0, 2);
                lcd.print("ElevHm");
                lcd.setCursor(0, 3);
                lcd.print("Key#:Next, Key*:Quit");
            }
        }
    } else {                 // Sr. + Jr. && Sr.
        if (g_bPusher == TRUE) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("PbTopRT   ,PbLowRT  ");
            lcd.setCursor(0, 1);
            lcd.print("RTSpd     ,PlatSpd  ");
            lcd.setCursor(0, 2);
            lcd.print("ElevHm    ,PushHm   ");
            lcd.setCursor(0, 3);
            lcd.print("Key#:Next, Key*:Quit");
        } else {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("PbTopRT   ,PbLowRT  ");
            lcd.setCursor(0, 1);
            lcd.print("RTSpd     ,PlatSpd  ");
            lcd.setCursor(0, 2);
            lcd.print("ElevHm");
            lcd.setCursor(0, 3);
            lcd.print("Key#:Next, Key*:Quit");
        }
    }
}

void DisplayTechInputPage_2Data() {
    int wPbTop;
    int wPbLow;
    int wQbLow;
    int wQbSpeed;
    int wPlatformSpeed;
    int wElevHomePos;
    int wPushHomePos;

    if (IsElevAtTopRetainerPB()) {
        wPbTop = 1;
    } else {
        wPbTop = 0;
    }

    if (IsElevAtLowRetainerPB()) {
        wPbLow = 1;
    } else {
        wPbLow = 0;
    }

    if (IsElevAtLowRetainerQB()) {
        wQbLow = 1;
    } else {
        wQbLow = 0;
    }

    if (IsElevQbSpeedChange()) {
        wQbSpeed = 1;
    } else {
        wQbSpeed = 0;
    }

    if (IsElevPlatformSpeedChange()) {
        wPlatformSpeed = 1;
    } else {
        wPlatformSpeed = 0;
    }

    if (IsElevHome()) {
        wElevHomePos = 1;
    } else {
        wElevHomePos = 0;
    }

    if (IsPusherHome()) {
        wPushHomePos = 1;
    } else {
        wPushHomePos = 0;
    }

    if (g_bSrJrTransfer == JR_ONLY) {
        if (g_bAdaptor == FALSE) {
            lcd.setCursor(9, 0);
            lcd.print(wPbLow);
        } else {
            lcd.setCursor(9, 0);
            lcd.print(wPbLow);
            lcd.setCursor(19, 0);
            lcd.print(wQbLow);
        }

        lcd.setCursor(9, 1);
        lcd.print(wQbSpeed);
        lcd.setCursor(19, 1);
        lcd.print(wPlatformSpeed);

        if (g_bPusher == TRUE) {
            lcd.setCursor(9, 2);
            lcd.print(wElevHomePos);
            lcd.setCursor(19, 2);
            lcd.print(wPushHomePos);
        } else {
            lcd.setCursor(9, 2);
            lcd.print(wElevHomePos);
        }
    } else {
        lcd.setCursor(9, 0);
        lcd.print(wPbTop);
        lcd.setCursor(19, 0);
        lcd.print(wPbLow);

        lcd.setCursor(9, 1);
        lcd.print(wQbSpeed);
        lcd.setCursor(19, 1);
        lcd.print(wPlatformSpeed);

        if (g_bPusher == TRUE) {
            lcd.setCursor(9, 2);
            lcd.print(wElevHomePos);
            lcd.setCursor(19, 2);
            lcd.print(wPushHomePos);
        } else {
            lcd.setCursor(9, 2);
            lcd.print(wElevHomePos);
        }
    }
}

void DisplayTechInputPage_3() {
    if (g_bAdaptor == TRUE) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("QbTopRT   ,QbLowRT  ");
        lcd.setCursor(0, 1);
        lcd.print("I_FrontL  ,I_BackL  ");
        lcd.setCursor(0, 2);
        lcd.print("TopRtOp   ,TopRtCl  ");
        lcd.setCursor(0, 3);
        lcd.print("Key#:Next, Key*:Quit");
    } else {
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("I_FrontL  ,I_BackL  ");
        lcd.setCursor(0, 2);
        lcd.print("TopRtOp   ,TopRtCl  ");
        lcd.setCursor(0, 3);
        lcd.print("Key#:Next, Key*:Quit");
    }
}

void DisplayTechInputPage_3Data() {
    int wQbTop;
    int wQbLow;
    int wFrontIndexPos;
    int wBackIndexPos;
    int wTopRtOpen;
    int wTopRtClose;

    if (IsElevAtTopRetainerQB()) {
        wQbTop = 1;
    } else {
        wQbTop = 0;
    }

    if (IsElevAtLowRetainerQB()) {
        wQbLow = 1;
    } else {
        wQbLow = 0;
    }

    if (IsIndexAtFront()) {
        wFrontIndexPos = 1;
    } else {
        wFrontIndexPos = 0;
    }

    if (IsIndexAtBack()) {
        wBackIndexPos = 1;
    } else {
        wBackIndexPos = 0;
    }

    if (IsTopRetainerOpen()) {
        wTopRtOpen = 1;
    } else {
        wTopRtOpen = 0;
    }

    if (IsTopRetainerClose()) {
        wTopRtClose = 1;
    } else {
        wTopRtClose = 0;
    }

    if (g_bAdaptor == TRUE) {
        lcd.setCursor(9, 0);
        lcd.print(wQbTop);
        lcd.setCursor(19, 0);
        lcd.print(wQbLow);

        lcd.setCursor(9, 1);
        lcd.print(wFrontIndexPos);
        lcd.setCursor(19, 1);
        lcd.print(wBackIndexPos);

        lcd.setCursor(9, 2);
        lcd.print(wTopRtOpen);
        lcd.setCursor(19, 2);
        lcd.print(wTopRtClose);
    } else {
        lcd.setCursor(9, 1);
        lcd.print(wFrontIndexPos);
        lcd.setCursor(19, 1);
        lcd.print(wBackIndexPos);

        lcd.setCursor(9, 2);
        lcd.print(wTopRtOpen);
        lcd.setCursor(19, 2);
        lcd.print(wTopRtClose);
    }
}

void DisplayTechInputPage_4() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Carrier Wafer       ");
    lcd.setCursor(0, 1);
    lcd.print("UpSafety            ");
    lcd.setCursor(0, 2);
    lcd.print("Start     ,Stop     ");
    lcd.setCursor(0, 3);
    lcd.print("Key#:Next, Key*:Quit");
}

void DisplayTechInputPage_4Data() {
    int wFrontIndexPos;
    int wBackIndexPos;
    int waferInPB;
    int upSafetySensor;
    int start, stop;

    if (IsElevUpSafe()) {
        upSafetySensor = 1;
    } else {
        upSafetySensor = 0;
    }

    if (IsWaferInBoat()) {
        waferInPB = 1;
    } else {
        waferInPB = 0;
    }

    if (IsStartPressed()) {
        start = 1;
    } else {
        start = 0;
    }

    if (IsPauseButtonPressed()) {
        stop = 1;
    } else {
        stop = 0;
    }

    lcd.setCursor(19, 0);
    lcd.print(waferInPB);

    lcd.setCursor(19, 1);
    lcd.print(upSafetySensor);

    lcd.setCursor(9, 2);
    lcd.print(start);
    lcd.setCursor(19, 2);
    lcd.print(stop);
}

void DisplayTechOutputPage_1() {
    if (g_bSrJrTransfer == JR_ONLY) {
        if (g_bPusher == TRUE) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("1:ElevUp, 2:ElevDown");
            lcd.setCursor(0, 1);
            lcd.print("3:RtOpen, 4:RtClose");
            lcd.setCursor(0, 2);
            lcd.print("5:PushUp, 6:PushDown");
            lcd.setCursor(0, 3);
            lcd.print("Key*:Quit");
        } else {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("1:ElevUp, 2:ElevDown");
            lcd.setCursor(0, 1);
            lcd.print("3:RtOpen, 4:RtClose");
            lcd.setCursor(0, 3);
            lcd.print("Key*:Quit");
        }
    } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("1:ElevUp, 2:Elev Dn");
        lcd.setCursor(0, 1);
        lcd.print("3:LowOpen,4:LowClose");
        lcd.setCursor(0, 2);
        lcd.print("5:Alarm");
        lcd.setCursor(0, 3);
        lcd.print("Key#:Next, Key*:Quit");
    }
}

void DisplayTechOutputPage_2() {
    if (g_bPusher == TRUE) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("1:TopOpen,2:TopClose");
        lcd.setCursor(0, 1);
        lcd.print("3:PushUp, 4:PushDown");
        lcd.setCursor(0, 2);
        lcd.print("5:IndexFd,6:IndexBk");
        lcd.setCursor(0, 3);
        lcd.print("Key#:Next, Key*:Quit");
    } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("1:TopOpen,2:TopClose");
        lcd.setCursor(0, 1);
        lcd.print("3:Cycle Index");
        lcd.setCursor(0, 2);
        lcd.print("5:IndexFd,6:IndexBk");
        lcd.setCursor(0, 3);
        lcd.print("Key#:Next, Key*:Quit");
    }
}

void DisplayCalPusherMenu() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Calibrate Pusher  ");
    lcd.setCursor(0, 1);
    lcd.print("1:CarrierHB is Back");
    lcd.setCursor(0, 2);
    lcd.print("2:CarrierHB is Front");
    lcd.setCursor(0, 3);
    lcd.print("Key#:Save, Key*:Quit");
}

void DisplayCalPusher() {
    if (g_bAdaptor == TRUE) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("  Calibrate Pusher  ");
        lcd.setCursor(0, 1);
        lcd.print("1:UpforPB, 2:DnforPB");
        lcd.setCursor(0, 3);
        lcd.print("Key#:Save, Key*:Quit");
    } else if (g_bPusherForPB == TRUE) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("  Calibrate Pusher  ");
        lcd.setCursor(0, 1);
        lcd.print("1:UpforPB, 2:DnforPB");
        lcd.setCursor(0, 2);
        lcd.print("3:UpforQB, 4:DnforQB");
        lcd.setCursor(0, 3);
        lcd.print("Key#:Save, Key*:Quit");
    } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("  Calibrate Pusher  ");
        lcd.setCursor(0, 2);
        lcd.print("3:UpforQB, 4:DnforQB");
        lcd.setCursor(0, 3);
        lcd.print("Key#:Save, Key*:Quit");
    }
}

void DisplayCalPusherResult(int pb_steps, int qb_steps) {
    lcd.clear();

    if (g_bAdaptor == TRUE) {
        lcd.setCursor(0, 0);
        lcd.print("PB:  ");
        lcd.setCursor(5, 0);
        lcd.print(pb_steps);
    } else if (g_bPusherForPB == TRUE) {
        lcd.setCursor(0, 0);
        lcd.print("PB:  ");
        lcd.setCursor(5, 0);
        lcd.print(pb_steps);
        
        lcd.setCursor(0, 1);
        lcd.print("QB:  ");
        lcd.setCursor(5, 1);
        lcd.print(qb_steps);
    } else {
        lcd.setCursor(0, 0);
        lcd.print("QB:  ");
        lcd.setCursor(5, 0);
        lcd.print(qb_steps);
    }

    lcd.setCursor(0, 3);
    lcd.print("Press * to Save");

    while (TRUE) {
        if (keypad.getKey() == '*') {
            break;
        }
    }
}

void DisplayErrorMessage(int wErrorCode, int wRetry) {
    char szErrorString[32];

    // KeypadReset();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Error Happened");
    lcd.setCursor(0, 1);
    GetErrorStringFromCode(wErrorCode, szErrorString);
    lcd.print(szErrorString);

    if (wRetry) {
        lcd.setCursor(0, 2);
        lcd.print("#/START to Retry");
        lcd.setCursor(0, 3);
        lcd.print("Press * to Abort");
    } else {
        lcd.setCursor(0, 3);
        lcd.print("Press * to Abort");
    }

    AlarmOn();
}

void GetErrorStringFromCode(int wErrorCode, char *szErrorString) {
    switch (wErrorCode) {
        case  ERR_INDEX_FAIL: // 1
            strcpy(szErrorString, "RT Index Fail");
            break;

        case  ERR_MISSING_BOAT: // 2
            strcpy(szErrorString, "Missing/Wrong Boat");
            break;

        case  ERR_OPEN_RETAINER_FAIL: // 3
            strcpy(szErrorString, "Retainer Open Fail");
            break;

        case  ERR_ELEV_HIT_UP_LIMIT: // 4
            strcpy(szErrorString, "Elev Hit Up Limit");
            break;

        case  ERR_OPERATION_TIMEOUT: // 5
            strcpy(szErrorString, "Operation Time Out");
            break;

        case  ERR_ELEV_POSITION: // 6
            strcpy(szErrorString, "Elev Sensors Fail");
            break;

        case  ERR_ELEV_HOME: // 7
            strcpy(szErrorString, "Elev Home Fail");
            break;

        case  ERR_MOVING_ELEV: // 8
            strcpy(szErrorString, "Elevator Move Fail");
            break;

        case  ERR_CLOSE_RETAINER_FAIL: // 9
            strcpy(szErrorString, "Retainer Close Fail");
            break;

        case  ERR_RETAINER_CLOSE: // 10
            strcpy(szErrorString, "Retainer Is Closed");
            break;

        case  ERR_RETAINER_OPEN: // 11
            strcpy(szErrorString, "Retainer Is Open");
            break;

        case  ERR_MISSING_RUN_BOAT: // 12
            strcpy(szErrorString, "Missing Boat");
            break;

        case  ERR_PUSHER_FAIL: // 13
            strcpy(szErrorString, "Pusher Motion Fail");
            break;

        case  ERR_RETAINER_POS: // 14
            strcpy(szErrorString, "Bad Retainer Pos");
            break;

        case  ERR_OVER_HEATED: // 15
            strcpy(szErrorString, "QB is Over Heated");
            break;

        case  ERR_WAFER_IN_BOAT: // 16
            strcpy(szErrorString, "Boat is not Empty");
            break;

        case  ERR_NO_WAFER_IN_BOAT:                       // 17
            //          strcpy(szErrorString,"Boat is with Wafer");
            strcpy(szErrorString, "No Wafer is in Boat"); // steve changed
                                                          // 2/14/08
            break;

        case  ERR_UPSAFETY_FAILED: // 18   //STEVE
            strcpy(szErrorString, "Up-Safety Triggered");
            break;

        case  ERR_INDEX_TO_FRONT_FAIL: // 19
            strcpy(szErrorString, "Front Index Fail");
            break;

        case  ERR_INDEX_TO_BACK_FAIL: // 20
            strcpy(szErrorString, "Back Index Fail");
            break;

        case  ERR_NOT_PB_HBAR:                        // 21
            strcpy(szErrorString, "Carrier-Hbar Fail");
            break;

        case  ERR_PB_DIRECTION:                       // 22
            strcpy(szErrorString, "Carrier Wrong Dir");
            break;

        default:
            sprintf(szErrorString, "Unknown. Code %d", wErrorCode);
            break;
    }
}

void DisplayAskPassword() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Input Password:");
    lcd.setCursor(0, 2);
    lcd.print("Press # to Start");
    lcd.setCursor(0, 3);
    lcd.print("Or * to Quit.");
}

int CheckPassword() {
    char cKey;
    char szMyInput[8];
    int  wMyTimes;

    wMyTimes = 0;
    strcpy(szMyInput, "");

    DisplayAskPassword();

    while (TRUE) {
        while ((cKey = keypad.getKey()) == 0) {
            if (g_bCheckOverHeat == TRUE) {
                IsOverHeated(); // read the heat sensor and turn on alarm if
                                // triggered
            }
        }

        if (cKey == '*') {   // user wants to quit
            return NEEDABORT;
        } else if (cKey == '#') {
            if (!strcmp(szMyInput, g_Password)) {
                return NO_ERROR;
            } else {
                DisplayAskPassword();
                wMyTimes = 0;
                strcpy(szMyInput, "");
            }
        } else {
            if (wMyTimes > 3) {
                DisplayAskPassword();
                wMyTimes = 0;
                strcpy(szMyInput, "");
            } else {
                lcd.setCursor(16 + wMyTimes, 0);
                lcd.print("*");

                szMyInput[wMyTimes] = cKey;
                wMyTimes++;
                szMyInput[wMyTimes] = '\0';
            }
        }
    }
}

int CheckPassword2() {
    char cKey;
    char szMyInput[8];
    int  wMyTimes;

    wMyTimes = 0;
    strcpy(szMyInput, "");

    DisplayAskPassword();

    while (TRUE) {
        while ((cKey = keypad.getKey()) == 0) {
            if (g_bCheckOverHeat == TRUE) {
                IsOverHeated(); // read the heat sensor and turn on alarm if
                                // triggered
            }
        }

        if (cKey == '*') {   // user wants to quit
            return NEEDABORT;
        } else if (cKey == '#') {
            if (!strcmp(szMyInput, g_Password2)) {
                return NO_ERROR;
            } else {
                DisplayAskPassword();
                wMyTimes = 0;
                strcpy(szMyInput, "");
            }
        } else {
            if (wMyTimes > 3) {
                DisplayAskPassword();
                wMyTimes = 0;
                strcpy(szMyInput, "");
            } else {
                lcd.setCursor(16 + wMyTimes, 0);
                lcd.print("*");

                szMyInput[wMyTimes] = cKey;
                wMyTimes++;
                szMyInput[wMyTimes] = '\0';
            }
        }
    }
}

void DisplayPasswordSetting() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("New Password:");
    lcd.setCursor(0, 2);
    lcd.print("Press # for OK");
    lcd.setCursor(0, 3);
    lcd.print("Or * for Cancel");
}

void SetPassword() {
    char cKey;
    char szMyInput[8];
    int  wMyTimes;

    wMyTimes = 0;
    strcpy(szMyInput, "");

    DisplayPasswordSetting();

    while (TRUE) {
        while ((cKey = keypad.getKey()) == 0) {
            if (g_bCheckOverHeat == TRUE) {
                IsOverHeated(); // read the heat sensor and turn on alarm if
                                // triggered
            }
        }

        if (cKey == '*') {   // user wants to quit
            return;
        } else if (cKey == '#') {
            strcpy(g_Password, szMyInput);
            return;
        } else {
            if (wMyTimes > 3) {
                DisplayPasswordSetting();
                wMyTimes = 0;
                strcpy(szMyInput, "");
            } else {
                lcd.setCursor(16 + wMyTimes, 0);
                lcd.print(cKey);

                szMyInput[wMyTimes] = cKey;
                wMyTimes++;
                szMyInput[wMyTimes] = '\0';
            }
        }
    }
}
