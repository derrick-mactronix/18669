/*******************************************************************************
 *               Copyright(c) 2022, Mactronix Inc. All rights reserved
 *
 *               File:         global.h
 *               Description:  all global variables
 *               Author: Jered Yang
 ******************************************************************************/

char g_bSrJrTransfer;
char g_bAdaptor;
char g_bPusher;
char g_bPusherForPB;
char g_bCheckOverHeat;
char g_bMode;
int  g_bPusherUpPosPB1;      // HBar Back  0
int  g_bPusherUpPosPB2;      // HBar Front 1
int  g_bPusherUpPosQB;

char g_bTech;
char g_bChkBoat;             // set TRUE to check
                             // boat missing
char g_bHighSpeed;           // set TRUE to activate Speed Driver for high speed
int  g_wBoatType;
char g_Password[8];
char g_Password2[8];
char g_bNeedInitialize;
char g_bCombEmpty;           // TRUE=high speed, FALSE=need low to high change
char g_bNeedRecovery;
char g_bNeedMachineCycle;
char g_bPbtoQbTransfer;
int  g_wStepPhaseSequence;
int  g_heatSetting;

char szDisplayString[64];

#define I2CADDR 0x20
const byte ROWS = 4;         // four rows
const byte COLS = 3;         // four columns

// define the symbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
    { '1', '2', '3' },
    { '4', '5', '6' },
    { '7', '8', '9' },
    { '*', '0', '#' }
};

// connect to the row pinouts of the keypad
byte rowPins[ROWS] = { 14, 13, 12, 11 };
// connect to the column pinouts of the keypad
byte colPins[COLS] = { 10, 9, 8 };       

// initialize an instance of class NewKeypad
Keypad_MC17 keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS,
                   I2CADDR);

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 20, 4);

struct AppSettings {
    char g_bSrJrTransfer;
    char g_bAdaptor;
    char g_bPusher;
    char g_bPusherForPB;
    char g_bCheckOverHeat;
    char g_bMode;
    int  g_bPusherUpPosPB1;
    int  g_bPusherUpPosPB2;
    int  g_bPusherUpPosQB;
};

AppSettings mySettings;
