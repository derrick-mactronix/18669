/*******************************************************************************
 *               Copyright(c) 2022, Mactronix Inc. All rights reserved
 *
 *               File:         settings.h
 *               Description:  all settings functions
 *               Author: Jered Yang
 ******************************************************************************/

void ClearEEPROM() {
    for (int i = 0; i < sizeof(mySettings); i++) {
        EEPROM.write(i, 0);
    }
}

void SaveSettings() {
    mySettings.g_bSrJrTransfer   = g_bSrJrTransfer;
    mySettings.g_bAdaptor        = g_bAdaptor;
    mySettings.g_bPusher         = g_bPusher;
    mySettings.g_bPusherForPB    = g_bPusherForPB;
    mySettings.g_bCheckOverHeat  = g_bCheckOverHeat;
    mySettings.g_bMode           = g_bMode;
    mySettings.g_bPusherUpPosPB1 = g_bPusherUpPosPB1;
    mySettings.g_bPusherUpPosPB2 = g_bPusherUpPosPB2;
    mySettings.g_bPusherUpPosQB  = g_bPusherUpPosQB;

    ClearEEPROM();
    int eeAddress = 0;

    EEPROM.put(eeAddress, mySettings);
}

void RestoreSettings() {
    int eeAddress = 0;

    EEPROM.get(eeAddress, mySettings);

    g_bSrJrTransfer   = mySettings.g_bSrJrTransfer;
    g_bAdaptor        = mySettings.g_bAdaptor;
    g_bPusher         = mySettings.g_bPusher;
    g_bPusherForPB    = mySettings.g_bPusherForPB;
    g_bCheckOverHeat  = mySettings.g_bCheckOverHeat;
    g_bMode           = mySettings.g_bMode;
    g_bPusherUpPosPB1 = mySettings.g_bPusherUpPosPB1;
    g_bPusherUpPosPB2 = mySettings.g_bPusherUpPosPB2;
    g_bPusherUpPosQB  = mySettings.g_bPusherUpPosQB;
}