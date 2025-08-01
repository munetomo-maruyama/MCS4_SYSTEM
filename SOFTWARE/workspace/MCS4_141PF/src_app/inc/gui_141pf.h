//===========================================================
// MCS4 Project
//-----------------------------------------------------------
// File Name   : gui_141pf.h
// Description : MCS4 Calculator Header
//-----------------------------------------------------------
// History :
// Rev.01 2025.06.22 M.Maruyama First Release
//-----------------------------------------------------------
// Copyright (C) 2025 M.Maruyama
//===========================================================

#ifndef GUI_141PF_H_
#define GUI_141PF_H_

#include "touchlcd_tft.h"
#include "touchlcd_res.h"
#include "touchlcd_cap.h"

//-----------------------------------------
// Key Index
//-----------------------------------------
// S  7  8  9  -  DM SQ  CM
// EX 4  5  6  +  /  %   RM
// CE 1  2  3  +  x  M=- M-
// C  0  00 .  =  =  M=+ M+
//
#define KEY_COUNT 32
//
#define KEY_INDEX_S    0
#define KEY_INDEX_EX   1
#define KEY_INDEX_CE   2
#define KEY_INDEX_C    3
#define KEY_INDEX_7    4
#define KEY_INDEX_4    5
#define KEY_INDEX_1    6
#define KEY_INDEX_0    7
#define KEY_INDEX_8    8
#define KEY_INDEX_5    9
#define KEY_INDEX_2   10
#define KEY_INDEX_00  11
#define KEY_INDEX_9   12
#define KEY_INDEX_6   13
#define KEY_INDEX_3   14
#define KEY_INDEX_DOT 15
#define KEY_INDEX_SUB 16
#define KEY_INDEX_ADD 17
#define KEY_INDEX_ADD2 18 // unused
#define KEY_INDEX_EQU 19
#define KEY_INDEX_NUM 20
#define KEY_INDEX_DIV 21
#define KEY_INDEX_MUL 22
#define KEY_INDEX_EQU2 23 // unused
#define KEY_INDEX_SQR 24
#define KEY_INDEX_PER 25
#define KEY_INDEX_MES 26
#define KEY_INDEX_MEA 27
#define KEY_INDEX_MC  28
#define KEY_INDEX_MR  29
#define KEY_INDEX_MS  30
#define KEY_INDEX_MA  31
//
#define KEY_SIZE 40
#define KEY_OFF 0
#define KEY_ON  1
//
#define FONT_DIAMOND 0x80
#define FONT_MEMADD  0x81
#define FONT_MEMSUB  0x82
#define FONT_MEMEQU  0x83
#define FONT_SQR     0x84
#define FONT_ROME2   0x85
#define FONT_ROME3   0x86
#define FONT_EX      0x87
#define FONT_DIV     0x88
#define FONT_MUL     0x89
#define FONT_SPACE   0x8a // last one

//--------------------------------------------------------
// Touch Panel Control for both Resistive and Capacitive
//--------------------------------------------------------
enum TOUCH_DEVICE {TOUCH_NONE, TOUCH_RESISTIVE, TOUCH_CAPACITIVE};

//--------------------------
// Configuration Status
//--------------------------
#define BTN_COUNT 12
enum CONFIG_STATUS {
    CONFIG_0, CONFIG_1, CONFIG_2, CONFIG_3, CONFIG_4, CONFIG_5, CONFIG_6, CONFIG_8,
    CONFIG_FLOT, CONFIG_ROUN, CONFIG_TRNC,
    CONFIG_OK, CONFIG_NONE
};

//----------------
// Ribbon Color
//----------------
#define PLINE_BLK 0
#define PLINE_RED 1

//---------------
// Prototype
//---------------
uint32_t TOUCH_Touched(void);
uint32_t TOUCH_Buffer_Empty(void);
void TOUCH_Get_Point(TS_Point *point);
void TOUCH_Buffer_Clear(void);
//
int Main_GUI_141PF(uint32_t touch_dev);
void Draw_Main_Screen(void);
void Draw_Key(uint32_t key_index, uint32_t onoff);
void Draw_Lamps(uint32_t ovf, uint32_t neg, uint32_t mem);
void Draw_Config_Controls(uint32_t btn_index, uint32_t onoff);
uint32_t Pos_in_PF_Activation_Area(uint16_t posx, uint16_t posy);
uint32_t Pos_in_Config_Activation_Area(uint16_t posx, uint16_t posy);
uint32_t Pos_in_Config_Button(uint16_t posx, uint16_t posy, uint32_t btn_index);
void Do_Config(void);
void Set_Config(uint32_t btn_index);
//
static void Task_GUI_141PF_Key( void *pvParameters );
void MCS4_GUI_141PF_Key_Control(uint32_t key_index, uint32_t key_status);
//
static void Task_GUI_141PF_Prt( void *pvParameters );
void MCS4_GUI_141PF_Prt_Control(uint32_t *pState);
void Draw_Paper_Feed(void);
void Draw_Bottom_Line(uint8_t *str, uint32_t red);

#endif // GUI_141PF_H_

//===========================================================
// End of Program
//===========================================================

