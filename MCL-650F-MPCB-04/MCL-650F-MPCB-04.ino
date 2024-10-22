/*******************************************************************************
 *               Copyright(c) 2022, Mactronix Inc. All rights reserved
 *
 *               File:         MCL-650F-MPCB-01.ino
 *               Description:  arduino program for all-electrical
 *                             MCL SR/JR machine
 *               Note:  same software for SR or JR
 *                      set g_bSrJrTransfer = 1 for JR only
 *                      set g_bSrJrTransfer = 2 for SR only
 *                      set g_bSrJrTransfer = 3 for JR and SR
 *                      set g_bAdaptor = TRUE  for QB with adaptor
 *                      reset g_bAdaptor = FALSE for QB w/o adaptor
 *                      set   g_bPusher  = TRUE with auto pusher
 *                      reset g_bPusher  = FALSE w/o auto pusher
 *              Author: Jered Yang
 *              Date:   2022-07-01
 ******************************************************************************/

#include <Wire.h>
#include <Keypad_MC17.h>
#include <Keypad.h>          // GDY120705
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

#include "global.h"
#include "defines.h"
#include "err.h"
#include "settings.h"
#include "declared.h"
#include "io.h"
#include "sensors.h"
#include "index.h"
#include "retainers.h"
#include "display.h"
#include "motion.h"
#include "func.h"

void setup() {
    // put your setup code here, to run once:
    int i;

    Serial.begin(9600);

    Wire.begin();            // GDY200622
    keypad.begin();          // GDY120705

    // initialize the buzzer
    for (i = 0; i <= 7; i++) {
        keypad.pin_mode(i, INPUT_PULLUP);
    }

    keypad.pin_mode(ALARM_TRIG, OUTPUT);
    keypad.pin_write(ALARM_TRIG, 1);

    // initialize the LCD
    lcd.begin();

    // Turn on the blacklight and print a message.
    lcd.backlight();

    for (i = 2; i <= 19; i++) {
        pinMode(i, OUTPUT);
        digitalWrite(i, 1);
    }

    for (i = 22; i <= 53; i++) {
        pinMode(i, INPUT_PULLUP);
    }
}

void loop() {
    // put your main code here, to run repeatedly:
    unsigned long end;
    char cKey;
    int  re, iMode;

    /** Get command from keypad, process the message, and display on LCD */
    strcpy(g_Password,  DEFAULT_PASSWORD);
    strcpy(g_Password2, SETUP_PASSWORD);
    DisplayMactronix();      // show MCL
    Beep();
    RestoreSettings();

    if ((g_bSrJrTransfer < JR_ONLY) || (g_bSrJrTransfer > JR_N_SR)) {
        g_bSrJrTransfer = JR_N_SR;
    }

    if ((g_bAdaptor != TRUE) && (g_bAdaptor != FALSE)) {
        g_bAdaptor = TRUE;
    }

    if ((g_bPusher != TRUE) && (g_bPusher != FALSE)) {
        g_bPusher = FALSE;
    }

    if ((g_bPusherForPB != TRUE) && (g_bPusherForPB != FALSE)) {
        g_bPusherForPB = FALSE;
    }

    if ((g_bCheckOverHeat != TRUE) && (g_bCheckOverHeat != FALSE)) {
        g_bCheckOverHeat = TRUE;
    }

    if ((g_heatSetting < 150) || (g_heatSetting > 200)) {
        g_heatSetting = 165;
    }

    if ((g_bPusherUpPosPB1 < 5000) || (g_bPusherUpPosPB1 > 15000)) {
        g_bPusherUpPosPB1 = 10000;
    }

    if ((g_bPusherUpPosPB2 < 5000) || (g_bPusherUpPosPB2 > 15000)) {
        g_bPusherUpPosPB2 = 10000;
    }

    if ((g_bPusherUpPosQB < 5000) || (g_bPusherUpPosQB > 15000)) {
        g_bPusherUpPosQB = 10000;
    }

    sprintf(szDisplayString, "g_bPusherUpPosPB1 = %d", g_bPusherUpPosPB1);
    Serial.println(szDisplayString);

    sprintf(szDisplayString, "g_bPusherUpPosPB2 = %d", g_bPusherUpPosPB2);
    Serial.println(szDisplayString);

    sprintf(szDisplayString, "g_bPusherUpPosQB  = %d", g_bPusherUpPosQB);
    Serial.println(szDisplayString);

    // main loop
    while (TRUE) {
        re                  = NO_ERROR;
        g_bNeedRecovery     = FALSE;
        g_bNeedMachineCycle = FALSE;
        g_bTech             = FALSE;

        if (!IsElevHome() || ((g_bPusher == TRUE) && !IsPusherHome())) {
            g_bNeedInitialize = TRUE;
        } else {
            g_bNeedInitialize = FALSE;
        }

        if (g_bNeedInitialize == TRUE) {
            DisplayResetTechMode();
            iMode = 2;
        } else if (!IsLowRetainerOpen() ||
                   ((g_bSrJrTransfer > JR_ONLY) && !IsTopRetainerOpen())) {
            DisplayRecoverTechMode();
            iMode = 3;
        } else {
            DisplayOperationMode();
            iMode = 1;
        }

        end = MS_TIMER + TIMEOUT_DISPLAY;

        while ((cKey = keypad.getKey()) == 0 && !IsStartPressed()) {
            if (g_bCheckOverHeat == TRUE) {
                IsOverHeated(); // read the heat sensor and turn on alarm if
                // triggered
            }

            if ((long)(MS_TIMER - end) > 0) {
                end = MS_TIMER + TIMEOUT_DISPLAY;

                if (!IsElevHome() ||
                    ((g_bPusher == TRUE) && !IsPusherHome())) {
                    g_bNeedInitialize = TRUE;
                } else {
                    g_bNeedInitialize = FALSE;
                }

                //          KeypadReset();

                if (g_bNeedInitialize == TRUE) {
                    DisplayResetTechMode();
                    iMode = 2;
                } else if (!IsLowRetainerOpen() ||
                           ((g_bSrJrTransfer > JR_ONLY) && !IsTopRetainerOpen())) {
                    DisplayRecoverTechMode();
                    iMode = 3;
                } else {
                    DisplayOperationMode();
                    iMode = 1;
                }
            }
        }

        Serial.println(cKey);

        if ((cKey == '1') || IsStartPressed()) {
            while (IsStartPressed()) {}

            g_bHighSpeed = FALSE;

            if (iMode == 1) {
                if (g_bSrJrTransfer == SR_ONLY) {
                    re = SrTransfer();
                } else if (g_bSrJrTransfer == JR_ONLY) {
                    re = JrTransfer();
                } else if (cKey == '1') {
                    re = JrTransfer();
                }
            }

            if (iMode == 2) {
                re = MachineReset();
            }

            if (iMode == 3) {
                re = DoRecovery();
            }
        }

        if (cKey == '2') {
            // STEVE ADDED 2/11/2008
            g_bHighSpeed = FALSE;

            if ((iMode == 1) && (g_bSrJrTransfer == JR_N_SR)) {
                re = SrTransfer();
            } else if (CheckPassword() == NO_ERROR) {
                re = DoTechnician();
            }
        }

        if ((iMode == 1) && (cKey == '3') && (g_bSrJrTransfer == JR_N_SR)) {
            if (CheckPassword() == NO_ERROR) {
                re = DoTechnician();
            }
        }

        if (cKey == '4') {
            if (g_bMode == FACE_TO_FACE) {
                g_bMode = STANDARD;
            } else {
                g_bMode = FACE_TO_FACE;
            }

            SaveSettings();
        }

        if ((re != NO_ERROR) && (re != NEEDABORT) && !g_bTech) {
            DisplayErrorMessage(re, FALSE);

            while (TRUE) {
                cKey = keypad.getKey();

                if (cKey == '*') {
                    AlarmOff();
                    break;
                } else if (cKey == '0') {
                    AlarmOff();
                }
            }
        }
    }
}
