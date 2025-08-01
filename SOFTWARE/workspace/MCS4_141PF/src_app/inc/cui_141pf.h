//===========================================================
// MCS4 Project
//-----------------------------------------------------------
// File Name   : cui_141pf.h
// Description : MCS4 Calculator Header
//-----------------------------------------------------------
// History :
// Rev.01 2025.06.10 M.Maruyama First Release
//-----------------------------------------------------------
// Copyright (C) 2025 M.Maruyama
//===========================================================

#ifndef CUI_141PF_H_
#define CUI_141PF_H_

//-----------------------------
// 141-PF Key Index for CUI
//-----------------------------
#define C_KEY_S   'S' // S  Sign (for Negative Input)
#define C_KEY_EX  'X' // EX Exchange (for Division)
#define C_KEY_CE  'E' // CE Clear Entry
#define C_KEY_C   'C' // C  Clear All
//
#define C_KEY_7   '7' // 7
#define C_KEY_4   '4' // 4
#define C_KEY_1   '1' // 1
#define C_KEY_0   '0' // 0
//
#define C_KEY_8   '8' // 8
#define C_KEY_5   '5' // 5
#define C_KEY_2   '2' // 2
#define C_KEY_00  'Z' // 00
//
#define C_KEY_9   '9' // 9
#define C_KEY_6   '6' // 6
#define C_KEY_3   '3' // 3
#define C_KEY_DOT '.' // .
//
#define C_KEY_SUB '-' // -
#define C_KEY_ADD '+' // +
//
#define C_KEY_NUM '#' // #  Print Again
#define C_KEY_DIV '/' // /
#define C_KEY_MUL '*' // X
#define C_KEY_EQU '=' // =
//
#define C_KEY_SQR 'Q' // SQ Square Root
#define C_KEY_PER '%' // %  Percent
#define C_KEY_MES 'B' // M=- After Equal, Memory Sub
#define C_KEY_MEA 'D' // M=+ After Equal, Memory Add
//
#define C_KEY_MC  'L' // MC  Memory Clear
#define C_KEY_MR  'R' // MR  Memory Read
#define C_KEY_MS  'M' // M-  Memory Sub
#define C_KEY_MA  'P' // M+  Memory Add
//
#define C_KEY_FED 'F' // Paper Feed
//
#define ESC 0x1b // Escape Code

//---------------
// Prototype
//---------------
int Main_CUI_141PF(void);
static void Task_CUI_141PF_Key(void *pvParameters);
static void Task_CUI_141PF_Prt(void *pvParameters);
void MCS4_CUI_141PF_Key_Control(uint32_t *pState, uint8_t rxd);
void MCS4_CUI_141PF_Prt_Control(uint32_t *pState);

#endif // CUI_141PF_H_

//===========================================================
// End of Program
//===========================================================

