//===========================================================
// MCS4 Project
//-----------------------------------------------------------
// File Name   : gui_141pf.c
// Description : MCS4 Calculator Source Program (FreeRTOS)
//-----------------------------------------------------------
// History :
// Rev.01 2025.06.22 M.Maruyama First Release
//-----------------------------------------------------------
// Copyright (C) 2025 M.Maruyama
//===========================================================

// OS kernel includes
#include <stdio.h>
#include <stdint.h>
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"

// Application includes
#include "gui_141pf.h"
#include "gpio.h"
#include "i2c.h"
#include "riscv-virt.h"
#include "spi.h"
#include "uart.h"
#include "touchlcd_tft.h"
#include "touchlcd_res.h"
#include "touchlcd_cap.h"
#include "xprintf.h"

//----------------------------------------------
// Key Information
//----------------------------------------------
const uint16_t KEY_POSX[KEY_COUNT] =
{
      0,   0,   0,   0,  40,  40,  40,  40,
     80,  80,  80,  80, 120, 120, 120, 120,
    160, 160, 160, 160, 200, 200, 200, 160,
    240, 240, 240, 240, 280, 280, 280, 280
};
const uint16_t KEY_POSY[KEY_COUNT] =
{
     80, 120, 160, 200,  80, 120, 160, 200,
     80, 120, 160, 200,  80, 120, 160, 200,
     80, 120, 120, 200,  80, 120, 160, 200,
     80, 120, 160, 200,  80, 120, 160, 200
};
const uint16_t KEY_SIZX[KEY_COUNT] =
{
     40,  40,  40,  40,  40,  40,  40,  40,
     40,  40,  40,  40,  40,  40,  40,  40,
     40,  40,  40,  80,  40,  40,  40,  80,
     40,  40,  40,  40,  40,  40,  40,  40
};
const uint16_t KEY_SIZY[KEY_COUNT] =
{
     40,  40,  40,  40,  40,  40,  40,  40,
     40,  40,  40,  40,  40,  40,  40,  40,
     40,  80,  80,  40,  40,  40,  40,  40,
     40,  40,  40,  40,  40,  40,  40,  40
};
const uint16_t KEY_COLOR_OFF[KEY_COUNT] =
{
    COLOR_BLUE , COLOR_BLUE , COLOR_BLUE , COLOR_BLUE ,
    COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE,
    COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE,
    COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE,
    COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE,
    COLOR_BLUE , COLOR_BLUE , COLOR_BLUE , COLOR_WHITE,
    COLOR_BLUE , COLOR_BLUE , COLOR_BLUE , COLOR_BLUE ,
    COLOR_BLUE , COLOR_BLUE , COLOR_BLUE , COLOR_BLUE
};
const uint16_t KEY_COLOR_ON[KEY_COUNT] =
{
    COLOR_DARKBLUE , COLOR_DARKBLUE , COLOR_DARKBLUE , COLOR_DARKBLUE ,
    COLOR_LIGHTGRAY, COLOR_LIGHTGRAY, COLOR_LIGHTGRAY, COLOR_LIGHTGRAY,
    COLOR_LIGHTGRAY, COLOR_LIGHTGRAY, COLOR_LIGHTGRAY, COLOR_LIGHTGRAY,
    COLOR_LIGHTGRAY, COLOR_LIGHTGRAY, COLOR_LIGHTGRAY, COLOR_LIGHTGRAY,
    COLOR_LIGHTGRAY, COLOR_LIGHTGRAY, COLOR_LIGHTGRAY, COLOR_LIGHTGRAY,
    COLOR_DARKBLUE , COLOR_DARKBLUE , COLOR_DARKBLUE , COLOR_LIGHTGRAY,
    COLOR_DARKBLUE , COLOR_DARKBLUE , COLOR_DARKBLUE , COLOR_DARKBLUE,
    COLOR_DARKBLUE , COLOR_DARKBLUE , COLOR_DARKBLUE , COLOR_DARKBLUE
};
const char STR_DIA[] = {FONT_DIAMOND, 0};
const char STR_SQR[] = {FONT_SQR, 0};
const char STR_ME[]  = {FONT_MEMEQU, 0};
const char STR_MA[]  = {FONT_MEMADD, 0};
const char STR_MS[]  = {FONT_MEMSUB, 0};
const char STR_DIV[] = {FONT_DIV, 0};
const char STR_MUL[] = {FONT_MUL, 0};
const char *KEY_STRING[KEY_COUNT] =
{
    "S"    , "EX" , "CE"  , "C"   , "7"    , "4"  , "1"   , "0"   ,
    "8"    , "5"  , "2"   , "00"  , "9"    , "6"  , "3"   , "."   ,
    "-"    , "+"  , "+"   , "="   , STR_DIA, STR_DIV, STR_MUL, "="   ,
    STR_SQR, "%"  , STR_ME, STR_ME, "CM"   , "RM" , STR_MS, STR_MA
};
const uint16_t KEY_STRING_COLOR[KEY_COUNT] =
{
    COLOR_RED      , COLOR_WHITE    , COLOR_WHITE    , COLOR_WHITE    ,
    COLOR_BLACK    , COLOR_BLACK    , COLOR_BLACK    , COLOR_BLACK    ,
    COLOR_BLACK    , COLOR_BLACK    , COLOR_BLACK    , COLOR_BLACK    ,
    COLOR_BLACK    , COLOR_BLACK    , COLOR_BLACK    , COLOR_BLACK    ,
    COLOR_BLACK    , COLOR_BLACK    , COLOR_BLACK    , COLOR_BLACK    ,
    COLOR_WHITE    , COLOR_WHITE    , COLOR_WHITE    , COLOR_BLACK    ,
    COLOR_WHITE    , COLOR_WHITE    , COLOR_RED      , COLOR_WHITE    ,
    COLOR_WHITE    , COLOR_WHITE    , COLOR_RED      , COLOR_WHITE
};
const uint16_t KEY_STRING_POSX[KEY_COUNT] =
{
      5,   5,   5,   5,  45,  45,  45,  45,
     85,  85,  85,  85, 125, 125, 125, 125,
    165, 165, 165, 185, 205, 205, 205, 185,
    245, 245, 245, 245, 285, 285, 285, 285
};
//
const uint16_t KEY_STRING_POSY[KEY_COUNT] =
{
     85, 132, 172, 205,  85, 125, 165, 205,
     85, 125, 165, 212,  85, 125, 165, 205,
     85, 145, 145, 205,  85, 125, 165, 205,
     85, 125, 165, 205,  92, 132, 165, 205
};
const uint32_t KEY_STRING_SCALE[KEY_COUNT] =
{
    FONT_LARGE , FONT_MEDIUM, FONT_MEDIUM, FONT_LARGE ,
    FONT_LARGE , FONT_LARGE , FONT_LARGE , FONT_LARGE ,
    FONT_LARGE , FONT_LARGE , FONT_LARGE , FONT_MEDIUM,
    FONT_LARGE , FONT_LARGE , FONT_LARGE , FONT_LARGE ,
    FONT_LARGE , FONT_LARGE , FONT_LARGE , FONT_LARGE ,
    FONT_LARGE , FONT_LARGE , FONT_LARGE , FONT_LARGE ,
    FONT_LARGE , FONT_LARGE , FONT_LARGE , FONT_LARGE ,
    FONT_MEDIUM, FONT_MEDIUM, FONT_LARGE , FONT_LARGE
};
const uint32_t KEY_CODE[KEY_COUNT] =
{
    0x09d, 0x09e, 0x09f, 0x0a0, 0x099, 0x09a, 0x09b, 0x09c,
    0x095, 0x096, 0x097, 0x098, 0x091, 0x092, 0x093, 0x094,
    0x08d, 0x08e, 0x08e, 0x08c, 0x089, 0x08a, 0x08b, 0x08c,
    0x085, 0x086, 0x087, 0x088, 0x081, 0x082, 0x083, 0x084
};
const uint8_t KEY_LED7_CHAR[KEY_COUNT] =
{
    'S', 'X', 'E', 'C', '7', '4', '1', '0',
    '8', '5', '2', 'Z', '9', '6', '3', '.',
    '-', '+', '+', '=', '#', '/', '*', '=',
    'Q', '%', 'B', 'D', 'L', 'R', 'M', 'P'
};

//-----------------------------
// Configuration Buttons
//-----------------------------
const uint16_t BTN_POSX[BTN_COUNT] =
{
     40,  70, 100, 130, 160, 190, 220, 250,
     40, 120, 200, 240
};
const uint16_t BTN_POSY[BTN_COUNT] =
{
     70,  70,  70,  70,  70,  70,  70,  70,
    140, 140, 140, 180
};
const uint16_t BTN_SIZX[BTN_COUNT] =
{
     30,  30,  30,  30,  30,  30,  30,  30,
     80,  80,  80,  40
};
const uint16_t BTN_SIZY[BTN_COUNT] =
{
     20,  20,  20,  20,  20,  20,  20,  20,
     20,  20,  20,  20
};
const char *BTN_STRING[BTN_COUNT] =
{
    "0", "1", "2", "3", "4", "5", "6", "8",
    "FLOT", "ROUN", "TRNC", "OK"
};

// Priorities used by the tasks.
#define PRIORITY_TASK_GUI_141PF_KEY (tskIDLE_PRIORITY + 3)
#define PRIORITY_TASK_GUI_141PF_PRT (tskIDLE_PRIORITY + 4)

// Mutex Handle
static SemaphoreHandle_t xMutex_GUI_UART = NULL;
static SemaphoreHandle_t xMutex_GUI_GPIO = NULL;
static SemaphoreHandle_t xMutex_GUI_TLCD = NULL;

// Touch Panal Device
uint32_t GUI_TOUCH_DEV;

//---------------------------------------
// 141-PF Key/Switch Input Information
//---------------------------------------
uint32_t gui_decimal  = 0; // 0,1,2,3,4,5,6,,8
uint32_t gui_rounding = 0; // 0(float), 1(rounding), 8(truncate)
uint32_t gui_feed     = 0; // Paper Feed
uint32_t gui_keycode  = 0; // Key Code of Key-Matrix
//
// To draw 1st, set all one.
uint32_t gui_lamp_ovf = 1; // Lamp to show Overflow
uint32_t gui_lamp_neg = 1; // Lamp to show Negative
uint32_t gui_lamp_mem = 1; // Lamp to show Memory
//
uint32_t btn_index_decimal  = 0;
uint32_t btn_index_rounding = 8;
//
#define BTN_ONOFF(i)                   \
(                                      \
    (i ==  0)? (gui_decimal  == 0) :   \
    (i ==  1)? (gui_decimal  == 1) :   \
    (i ==  2)? (gui_decimal  == 2) :   \
    (i ==  3)? (gui_decimal  == 3) :   \
    (i ==  4)? (gui_decimal  == 4) :   \
    (i ==  5)? (gui_decimal  == 5) :   \
    (i ==  6)? (gui_decimal  == 6) :   \
    (i ==  7)? (gui_decimal  == 8) :   \
    (i ==  8)? (gui_rounding == 0) :   \
    (i ==  9)? (gui_rounding == 1) :   \
    (i == 10)? (gui_rounding == 8) : 0 \
)

//---------------------------------------
// 141-PF Print Line Buffer
//---------------------------------------
#define GUI_PLINE_MAX 18
uint8_t gui_pline0[GUI_PLINE_MAX+1];
uint8_t gui_pline1[GUI_PLINE_MAX+1];
uint8_t gui_pline2[GUI_PLINE_MAX+1];
uint8_t gui_pline3[GUI_PLINE_MAX+1];
uint32_t gui_pline0_red;
uint32_t gui_pline1_red;
uint32_t gui_pline2_red;
uint32_t gui_pline3_red;

//==========================================================
//----------------------------------------------------------
// Touch Panel Utilities
//----------------------------------------------------------
//==========================================================
//--------------------------------------------------------
// Touch Panel Control for both Resistive and Capacitive
//--------------------------------------------------------
uint32_t TOUCH_Touched(void)
{
    if (GUI_TOUCH_DEV == TOUCH_RESISTIVE ) return TOUCH_RES_Touched();
    if (GUI_TOUCH_DEV == TOUCH_CAPACITIVE) return TOUCH_CAP_Touched();
    return 0;
}
//
uint32_t TOUCH_Buffer_Empty(void)
{
    if (GUI_TOUCH_DEV == TOUCH_RESISTIVE)  return TOUCH_RES_Buffer_Empty();
    if (GUI_TOUCH_DEV == TOUCH_CAPACITIVE) return 0;
    return 0;
}
//
void TOUCH_Get_Point(TS_Point *point)
{
    if (GUI_TOUCH_DEV == TOUCH_RESISTIVE ) TOUCH_RES_Get_Point(point);
    if (GUI_TOUCH_DEV == TOUCH_CAPACITIVE) TOUCH_CAP_Get_Point(point);
}
//
void TOUCH_Buffer_Clear(void)
{
    if (GUI_TOUCH_DEV == TOUCH_RESISTIVE ) TOUCH_RES_Buffer_Clear();
    if (GUI_TOUCH_DEV == TOUCH_CAPACITIVE) return;
}

//==========================================================
//----------------------------------------------------------
// Main GUI Routine
//----------------------------------------------------------
//==========================================================
//--------------------------------------------------
// Main CUI 141-PF
//--------------------------------------------------
int Main_GUI_141PF(uint32_t touch_dev)
{
    uint32_t i;
    uint32_t posx, posy, sizx, sizy, colorf;
    //
    GUI_TOUCH_DEV = touch_dev;
    //
    // Clear Print Lines
    for (i = 0; i < GUI_PLINE_MAX; i++)
    {
        gui_pline0[i] = ' ';
        gui_pline1[i] = ' ';
        gui_pline2[i] = ' ';
        gui_pline3[i] = ' ';
    }
    gui_pline0[GUI_PLINE_MAX] = '\0';
    gui_pline1[GUI_PLINE_MAX] = '\0';
    gui_pline2[GUI_PLINE_MAX] = '\0';
    gui_pline3[GUI_PLINE_MAX] = '\0';
    gui_pline0_red = 0;
    gui_pline1_red = 0;
    gui_pline2_red = 0;
    gui_pline3_red = 0;
    //
    // Draw Main Screen
    Draw_Main_Screen();
    //
    // Create Mutex
    xMutex_GUI_UART = xSemaphoreCreateMutex();
    xMutex_GUI_GPIO = xSemaphoreCreateMutex();
    xMutex_GUI_TLCD = xSemaphoreCreateMutex();

    // Create Tasks
    if ((xMutex_GUI_UART != NULL) && (xMutex_GUI_GPIO != NULL)
     && (xMutex_GUI_TLCD != NULL))
    {
        xTaskCreate(Task_GUI_141PF_Key, "KEY", configMINIMAL_STACK_SIZE * 2U, NULL,
                PRIORITY_TASK_GUI_141PF_KEY, NULL );
        xTaskCreate(Task_GUI_141PF_Prt, "PRT", configMINIMAL_STACK_SIZE * 4U, NULL,
                PRIORITY_TASK_GUI_141PF_PRT, NULL );
    }

    // Start Tasks
    vTaskStartScheduler();
    return 0;
}

//--------------------------
// Draw Main Screen
//--------------------------
void Draw_Main_Screen(void)
{
    uint32_t i;
    //
    // Top Bar Area
    LCD_Draw_String("Tap Left area to configure. Right to PF.", 0,  0, COLOR_WHITE, COLOR_BLUE, FONT_SMALL);
    //
    // Draw Printing Area
    LCD_Fill_Rect(0, 8, 320, 72, COLOR_LIGHTGRAY);
    Draw_Paper_Feed();
    //
    // Draw Lamps
    Draw_Lamps(0, 0, 0);
    //
    // Key Board Area
    for (i = 0; i < KEY_COUNT; i++)
    {
        Draw_Key(i, KEY_OFF);
    }
}

//------------------------------
// Draw a Key
//------------------------------
void Draw_Key(uint32_t key_index, uint32_t onoff)
{
    uint16_t posx, posy;
    uint16_t sizx, sizy;
    uint16_t color;
    char *string_text;
    uint16_t string_posx, string_posy;
    uint16_t string_color_f, string_color_b;
    uint32_t string_scale;
    //
    posx  = KEY_POSX[key_index]; posy = KEY_POSY[key_index];
    sizx  = KEY_SIZX[key_index]; sizy = KEY_SIZY[key_index];
    color = (onoff)? KEY_COLOR_ON[key_index] : KEY_COLOR_OFF[key_index];
    //
    string_text    = (char*) KEY_STRING[key_index];
    string_posx    = KEY_STRING_POSX[key_index];
    string_posy    = KEY_STRING_POSY[key_index];
    string_color_f = KEY_STRING_COLOR[key_index];
    string_color_b = color;
    string_scale   = KEY_STRING_SCALE[key_index];
    //
    LCD_Fill_Rect(posx, posy, sizx, sizy, color);
    LCD_Draw_String_Any_Pos(string_text, string_posx, string_posy,
            string_color_f, string_color_b, string_scale);
    LCD_Draw_Rect(posx, posy, sizx, sizy, COLOR_BLACK, 1);
}

//------------------------
// Draw Lamps
//------------------------
void Draw_Lamps(uint32_t ovf, uint32_t neg, uint32_t mem)
{
    uint16_t color_ovf;
    uint16_t color_neg;
    uint16_t color_mem;

    if ((ovf == gui_lamp_ovf)
     && (neg == gui_lamp_neg)
     && (mem == gui_lamp_mem))
    {
        return;
    }
    gui_lamp_ovf = ovf;
    gui_lamp_neg = neg;
    gui_lamp_mem = mem;
    //
    color_ovf = (gui_lamp_ovf)? COLOR_RED : COLOR_DARKRED;
    color_neg = (gui_lamp_neg)? COLOR_GREEN : COLOR_DARKGREEN;
    color_mem = (gui_lamp_mem)? COLOR_WHITE : COLOR_DARKGRAY;
    //
    LCD_Fill_Rect(290, 11, 28, 20, color_ovf);
    LCD_Fill_Rect(290, 34, 28, 20, color_neg);
    LCD_Fill_Rect(290, 57, 28, 20, color_mem);
    LCD_Draw_Rect(290, 11, 28, 20, COLOR_BLACK, 1);
    LCD_Draw_Rect(290, 34, 28, 20, COLOR_BLACK, 1);
    LCD_Draw_Rect(290, 57, 28, 20, COLOR_BLACK, 1);
    //
    if (gui_lamp_ovf)
        LCD_Draw_String_Any_Pos("OVF", 293, 18, COLOR_BLACK, COLOR_RED, FONT_SMALL);
    if (gui_lamp_neg)
        LCD_Draw_String_Any_Pos("NEG", 293, 41, COLOR_BLACK, COLOR_GREEN, FONT_SMALL);
    if (gui_lamp_mem)
        LCD_Draw_String_Any_Pos("MEM", 293, 64, COLOR_BLACK, COLOR_WHITE, FONT_SMALL);
}

//-------------------------------
// Draw Configuration Controls
//-------------------------------
void Draw_Config_Controls(uint32_t btn_index, uint32_t onoff)
{
    uint16_t posx, posy;
    uint16_t sizx, sizy;
    uint16_t color;
    uint8_t keytop_char;
    char   *keytop_str;
    uint16_t keytop_posx, keytop_posy;
    uint16_t keytop_color_f, keytop_color_b;
    //
    posx = BTN_POSX[btn_index]; posy = BTN_POSY[btn_index];
    sizx = BTN_SIZX[btn_index]; sizy = BTN_SIZY[btn_index];
    color = (onoff)?  COLOR_BLACK : COLOR_WHITE;
    LCD_Fill_Rect(posx, posy, sizx, sizy, color);
    LCD_Draw_Rect(posx, posy, sizx, sizy, COLOR_BLACK, 1);
    keytop_str = (char*) BTN_STRING[btn_index];
    keytop_posx = posx + 7;
    keytop_posy = posy + 3;
    keytop_color_f = (onoff)? COLOR_WHITE : COLOR_BLACK;
    keytop_color_b = color;
    LCD_Draw_String_Any_Pos(keytop_str, keytop_posx, keytop_posy,
            keytop_color_f, keytop_color_b, FONT_MEDIUM);
}

//-----------------------------------------------------
// Whether the Position is in the PF Activation Area?
//-----------------------------------------------------
uint32_t Pos_in_PF_Activation_Area(uint16_t posx, uint16_t posy)
{
    if ((posx >= 160) && (posy >= 0) && (posx <= 320) && (posy <= 70))
        return 1;
    else
        return 0;
}

//----------------------------------------------------------------
// Whether the Position is in the Configuration Activation Area?
//----------------------------------------------------------------
uint32_t Pos_in_Config_Activation_Area(uint16_t posx, uint16_t posy)
{
    if ((posx >= 0) && (posy >= 0) && (posx <= 160) && (posy <= 70))
        return 1;
    else
        return 0;
}

//---------------------------------------------------------
// Whether the Position is in the Configuration Buttons?
//---------------------------------------------------------
uint32_t Pos_in_Config_Button(uint16_t posx, uint16_t posy, uint32_t btn_index)
{
    if ((posx >= BTN_POSX[btn_index]) && (posy >= BTN_POSY[btn_index])
     && (posx <= (BTN_POSX[btn_index] + BTN_SIZX[btn_index]))
     && (posy <= (BTN_POSY[btn_index] + BTN_SIZY[btn_index])))
        return 1;
    else
        return 0;
}

//----------------------------
// Do Configuration
//----------------------------
void Do_Config(void)
{
    uint32_t i;
    uint16_t posx, posy;
    uint16_t sizx, sizy;
    uint16_t color;
    uint8_t keytop_char;
    char   *keytop_str;
    uint16_t keytop_posx, keytop_posy;
    uint16_t keytop_color_f, keytop_color_b;
    uint32_t touched;
    TS_Point point;
    uint32_t state;
    uint32_t where;
    uint32_t btn_index_prev;;
    //
    // Draw Configuration Window
    LCD_Fill_Rect(20, 20, 280, 200, COLOR_WHITE);
    LCD_Draw_Rect(20, 20, 280, 200, COLOR_BLACK, 2);
    //
    // Draw Configuration Strings
    LCD_Draw_String_Any_Pos("Decimal Point", 40, 40,
            COLOR_BLUE, COLOR_WHITE, FONT_MEDIUM);
    LCD_Draw_String_Any_Pos("Rounding", 40, 110,
            COLOR_BLUE, COLOR_WHITE, FONT_MEDIUM);
    //
    // Draw All Config Buttons
    for (i = 0; i < BTN_COUNT; i++)
    {
        Draw_Config_Controls(i, BTN_ONOFF(i));
    }
    //
    // Touch Event Loop
    point.x = 0; point.y = 0; point.z = 0;
    state = 0;
    where = CONFIG_NONE;
    while(1)
    {
        // Get Touch Status
        touched = TOUCH_Touched();
        if (touched)
        {
            if (TOUCH_Buffer_Empty() == 0)
            {
                TOUCH_Get_Point(&point);
                TOUCH_Buffer_Clear();
            }
        }
        //
        switch (state)
        {
            // Have not Touched
            case 0:
            {
                if (touched)
                {
                    // Decimal Point Button?
                    for (i = CONFIG_0; i < CONFIG_FLOT; i++)
                    {
                        if (Pos_in_Config_Button(point.x, point.y, i))
                        {
                            if (i != btn_index_decimal)
                            {
                                Draw_Config_Controls(btn_index_decimal, KEY_OFF);
                                Draw_Config_Controls(i, KEY_ON);
                                btn_index_decimal = i;
                                Set_Config(i);
                            }
                            state = 1;
                            break;
                        }
                    }
                    // Rounding Button?
                    for (i = CONFIG_FLOT; i < CONFIG_OK; i++)
                    {
                        if (Pos_in_Config_Button(point.x, point.y, i))
                        {
                            if (i != btn_index_rounding)
                            {
                                Draw_Config_Controls(btn_index_rounding, KEY_OFF);
                                Draw_Config_Controls(i, KEY_ON);
                                btn_index_rounding = i;
                                Set_Config(i);
                                state = 1;
                                break;
                            }
                        }
                    }
                    // OK Button?
                    if (Pos_in_Config_Button(point.x, point.y, CONFIG_OK))
                    {
                        Draw_Config_Controls(CONFIG_OK, KEY_ON);
                        state = 1;
                    }
                }
                break;
            }
            // Have Touched
            case 1:
            {
                if (!touched)
                {
                    Draw_Config_Controls(CONFIG_OK, KEY_OFF);
                    if (Pos_in_Config_Button(point.x, point.y, CONFIG_OK))
                        where = CONFIG_OK;
                    else
                        where = CONFIG_NONE;
                    state = 0;
                }
                break;
            }
            // Never reach here
            default: break;
        }
        // Exit?
        if (where == CONFIG_OK) break;
    }
    //
    // Draw Main Screen
    Draw_Main_Screen();
}

//--------------------------------
// Set Configuration Variable
//--------------------------------
void Set_Config(uint32_t btn_index)
{
    switch (btn_index)
    {
        case CONFIG_0: gui_decimal = 0; break;
        case CONFIG_1: gui_decimal = 1; break;
        case CONFIG_2: gui_decimal = 2; break;
        case CONFIG_3: gui_decimal = 3; break;
        case CONFIG_4: gui_decimal = 4; break;
        case CONFIG_5: gui_decimal = 5; break;
        case CONFIG_6: gui_decimal = 6; break;
        case CONFIG_8: gui_decimal = 8; break;
        case CONFIG_FLOT: gui_rounding = 0; break;
        case CONFIG_ROUN: gui_rounding = 1; break;
        case CONFIG_TRNC: gui_rounding = 8; break;
        default: break;
    }
}

//==========================================================
//----------------------------------------------------------
// Task for Key Input
//----------------------------------------------------------
//==========================================================
//----------------------------------------------------
// Task 141-PF Key Input
//----------------------------------------------------
static void Task_GUI_141PF_Key( void *pvParameters )
{
    BaseType_t xStatus;
    const TickType_t xTicksToWait = 1000UL;
    uint32_t state = 0;
    uint32_t touched;
    TS_Point point;
    uint32_t key_index_touch, key_index_release;

    // Remove compiler warning about unused parameter.
    ( void ) pvParameters;

    // Main Task Loop
    for( ;; )
    {
        // Only when Expecting Key Touch and Release Operations
        if ((state == 0) || (state == 1))
        {
            // Take Mutex_TLCD
            xStatus = xSemaphoreTake(xMutex_GUI_TLCD, xTicksToWait);
            if (xStatus == pdTRUE)
            {
                // Get Touch Status
                touched = TOUCH_Touched();
                if (touched)
                {
                    point.x = 0; point.y = 0; point.z = 0;
                    if (TOUCH_Buffer_Empty() == 0)
                    {
                        TOUCH_Get_Point(&point);
                        TOUCH_Buffer_Clear();
                    }
                }
                //
                switch(state)
                {
                    // Have not Touched
                    case 0:
                    {
                        if (touched)
                        {
                            // In PF Button?
                            if (Pos_in_PF_Activation_Area(point.x, point.y))
                            {
                                key_index_touch = 32;
                                state = 1;
                            }
                            // In Printing Area to configure?
                            else if (Pos_in_Config_Activation_Area(point.x, point.y))
                            {
                                key_index_touch = 33;
                                state = 1;
                            }
                            // In Key Board?
                            else if (point.y >= KEY_SIZE*2)
                            {
                                key_index_touch = (point.y - (KEY_SIZE*2)) / KEY_SIZE
                                          + (point.x / KEY_SIZE * 4);
                                if (key_index_touch < 32)
                                {
                                    Draw_Key(key_index_touch, KEY_ON);
                                    state = 1;
                                }
                            }
                        }
                        break;
                    }
                    // Have Touched
                    case 1:
                    {
                        if (!touched)
                        {
                            // In PF Button?
                            if (key_index_touch == 32)
                            {
                                if (Pos_in_PF_Activation_Area(point.x, point.y))
                                {
                                    key_index_release = 32;
                                    state = 2; // Send Key Command to MCS4 System
                                }
                                else
                                {
                                    state = 0;
                                }
                            }
                            // In Printing Area to configure?
                            else if (key_index_touch == 33)
                            {
                                if (Pos_in_Config_Activation_Area(point.x, point.y))
                                {
                                    key_index_release = 33;
                                    Do_Config();
                                }
                                state = 0;
                            }
                            // In Key Board?
                            else
                            {
                                key_index_release = (point.y - (KEY_SIZE*2)) / KEY_SIZE
                                          + (point.x / KEY_SIZE * 4);
                                Draw_Key(key_index_touch, KEY_OFF);
                                if (key_index_touch == key_index_release)
                                {
                                    state = 2; // Send Key Command to MCS4 System
                                }
                                else
                                {
                                    state = 0;
                                }
                            }
                        }
                        break;
                    }
                    // Never reach here
                    default:
                    {
                        state = 0;
                        break;
                    }
                }
            }
            // Release Mutex_TLCD
            xSemaphoreGive(xMutex_GUI_TLCD);
        }
        // If touch key and release key are same
        else if (state == 2)
        {
            MCS4_GUI_141PF_Key_Control(key_index_release, KEY_ON);
            state = 3;
        }
        // After an interval.
        else // if (state == 3)
        {
            MCS4_GUI_141PF_Key_Control(key_index_release, KEY_OFF);
            state = 0;
        }
        //
        // Take Intervals
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

//-------------------------------------
// MCS4 141-PF Key Control
//-------------------------------------
void MCS4_GUI_141PF_Key_Control(uint32_t key_index, uint32_t key_status)
{
    BaseType_t xStatus;
    const TickType_t xTicksToWait = 1000UL;
    uint32_t port_key_prt_cmd;
    uint32_t port_key_prt_res;
    uint32_t rdata, wdata;
    uint8_t ch;
    uint32_t gui_key_code;
    //
    // When Key ON
    if (key_status == KEY_ON)
    {
        // Print 7-Seg LED
        xStatus = xSemaphoreTake(xMutex_GUI_GPIO, xTicksToWait);
        if (xStatus == pdTRUE)
        {
            ch = KEY_LED7_CHAR[key_index];
            GPIO_PutCharSEG(ch);
        }
        xSemaphoreGive(xMutex_GUI_GPIO);
        //
        // Make Key Code
        if (key_index == KEY_COUNT)
        {
            gui_feed = 1;
            gui_keycode = 0x000;
        }
        else
        {
            gui_feed = 0;
            gui_keycode = KEY_CODE[key_index];
        }
        //
        // Send Key Command
        port_key_prt_cmd = (1            << 31)  // enable 141-PF
                         | (gui_feed     << 14)  // paper feed
                         | (gui_rounding << 12)  // rounding switch
                         | (gui_decimal  <<  8)  // decimal point
                         | (gui_keycode  <<  0); // key code
        // maintain printer fifo pop request
        xStatus = xSemaphoreTake(xMutex_GUI_GPIO, xTicksToWait);
        if (xStatus == pdTRUE)
        {
            rdata = mem_rd32(GPIO_PDR3);
            wdata = rdata & (1 << 15);
            wdata = wdata | port_key_prt_cmd;
            mem_wr32(GPIO_PDR3, wdata);
        }
        xSemaphoreGive(xMutex_GUI_GPIO);
    }
    // When Key OFF
    else // if (key_status == KEY_OFF)
    {
        // Send Key Command
        port_key_prt_cmd = (1            << 31)  // enable 141-PF
                         | (gui_rounding << 12)  // rounding switch
                         | (gui_decimal  <<  8); // decimal point
        // maintain printer fifo pop request
        xStatus = xSemaphoreTake(xMutex_GUI_GPIO, xTicksToWait);
        if (xStatus == pdTRUE)
        {
            rdata = mem_rd32(GPIO_PDR3);
            wdata = rdata & (1 << 15);
            wdata = wdata | port_key_prt_cmd;
            mem_wr32(GPIO_PDR3, wdata);
        }
        xSemaphoreGive(xMutex_GUI_GPIO);
    }
}

//==========================================================
//----------------------------------------------------------
// Task for Print Out
//----------------------------------------------------------
//==========================================================
//----------------------------------------------------
// Task 141-PF Printer
//----------------------------------------------------
static void Task_GUI_141PF_Prt( void *pvParameters )
{
    BaseType_t xStatus;
    const TickType_t xTicksToWait = 1000UL;
    uint32_t state = 0;

    // Remove compiler warning about unused parameter.
    ( void ) pvParameters;

    for( ;; )
    {
        // Take Mutex_TLCD
        xStatus = xSemaphoreTake(xMutex_GUI_TLCD, xTicksToWait);
        if (xStatus == pdTRUE)
        {
            // Handle Printer
            MCS4_GUI_141PF_Prt_Control(&state);
        }
        xSemaphoreGive(xMutex_GUI_TLCD);
        //
        // Take Intervals
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

//-------------------------------------
// MCS4 141-PF Printer Control
//-------------------------------------
void MCS4_GUI_141PF_Prt_Control(uint32_t *pState)
{
    const char PRT_DRUM_COL_1_15[13] =
    {
        '0', '1', '2', '3', '4', '5',
        '6', '7', '8', '9', '.', '.', '-'
    };
    const char PRT_DRUM_COL_17[13] =
    {
        FONT_DIAMOND, '+', '-', 'x', '/', FONT_MEMADD,
        FONT_MEMSUB , '^', '=', FONT_SQR, '%', 'C', 'R'
    };
    const char PRT_DRUM_COL_18[13] =
    {
        '#', '*', 'I', FONT_ROME2, FONT_ROME3, FONT_MEMADD,
        FONT_MEMSUB, 'T', 'K', 'E', FONT_EX, 'C', 'M'
    };
    //
    BaseType_t xStatus;
    const TickType_t xTicksToWait = 1000UL;
    uint32_t port_key_prt_cmd;
    uint32_t port_key_prt_res;
    uint32_t rdata, wdata;
    uint32_t fifo_rdy;
    uint32_t prt_col;
    uint32_t prt_drum;
    uint32_t prt_red;
    uint32_t prt_feed;
    uint32_t lamp_neg;
    uint32_t lamp_ovf;
    uint32_t lamp_mem;
    uint32_t fifo_pop_ack;
    uint32_t col;
    uint32_t pos;
    uint8_t  ch;
    uint32_t len;
    uint32_t i;
    static uint32_t red_ribbon = 0;
    static uint8_t pline[GUI_PLINE_MAX+1] =
    {
        ' ',' ',' ',' ',' ',
        ' ',' ',' ',' ',' ',
        ' ',' ',' ',' ',' ',
        ' ',' ',' ','\0'
    };
    //
    // Dispatch State
    switch(*pState)
    {
        //
        // FIFO Pop Request
        case 0 :
        {
            // Check FIFO Status
            port_key_prt_res = mem_rd32(GPIO_PDR4);
            fifo_rdy = (port_key_prt_res >> 31) & 0x01;
            //
            // if FIFO has data
            if (fifo_rdy)
            {
                // Send FIFO Pop Request
                port_key_prt_cmd = (1        << 31)  // enable 141-PF
                                 | (1        << 15); // printer pop request
                // Maintain key input information
                xStatus = xSemaphoreTake(xMutex_GUI_GPIO, xTicksToWait);
                if (xStatus == pdTRUE)
                {
                    rdata = mem_rd32(GPIO_PDR3);
                    wdata = rdata & 0x7fff;
                    wdata = wdata | port_key_prt_cmd;
                    mem_wr32(GPIO_PDR3, wdata);
                }
                xSemaphoreGive(xMutex_GUI_GPIO);
                //
                *pState = 1;
            }
            break;
        }
        //
        // FIFO Pop Acknowledged?
        case 1 :
        {
            // Check FIFO Pop Acknowledge
            port_key_prt_res = mem_rd32(GPIO_PDR4);
            fifo_pop_ack = (port_key_prt_res >> 0) & 0x01;
            // if Ack
            if (fifo_pop_ack)
            {
                prt_col  = (port_key_prt_res >> 14) & 0x01ffff;
                prt_drum = (port_key_prt_res >> 10) & 0x0f;
                prt_red  = (port_key_prt_res >>  9) & 0x01;
                prt_feed = (port_key_prt_res >>  8) & 0x01;
                lamp_neg = (port_key_prt_res >>  7) & 0x01;
                lamp_ovf = (port_key_prt_res >>  6) & 0x01;
                lamp_mem = (port_key_prt_res >>  5) & 0x01;
                //
                // Control Lamps
                Draw_Lamps(lamp_ovf, lamp_neg, lamp_mem);
                //
                // Paper Feed?
                if (prt_feed)
                {
                    Draw_Paper_Feed();
                    for (i = 0; i < GUI_PLINE_MAX; i++) pline[i] = ' ';
                    red_ribbon = 0;
                }
                // Red Ink?
                else if (prt_red)
                {
                    red_ribbon = 1;
                }
                // Print Hammer
                else
                {
                    for (col = 0; col < 17; col++)
                    {
                        pos = (col <= 1)? 17 - col : 16 - col;
                        ch = ' ';
                        //
                        if ((col >= 2) && (prt_col & (1 << col)))
                        {
                            ch = (uint8_t) PRT_DRUM_COL_1_15[prt_drum];
                        }
                        else if ((col == 1) && (prt_col & (1 << col)))
                        {
                            ch = (uint8_t) PRT_DRUM_COL_17[prt_drum];
                        }
                        else if ((col == 0) && (prt_col & (1 << col)))
                        {
                            ch = (uint8_t) PRT_DRUM_COL_18[prt_drum];
                        }
                        //
                        if (ch != ' ') pline[pos] = ch;
                    }
                    //
                    Draw_Bottom_Line(pline, red_ribbon);
                }
                // Clear fifo pop request
                port_key_prt_cmd = (1        << 31)  // enable 141-PF
                                 | (0        << 15); // printer pop request
                // Maintain key input information
                xStatus = xSemaphoreTake(xMutex_GUI_GPIO, xTicksToWait);
                if (xStatus == pdTRUE)
                {
                    rdata = mem_rd32(GPIO_PDR3);
                    wdata = rdata & 0x7fff;
                    wdata = wdata | port_key_prt_cmd;
                    mem_wr32(GPIO_PDR3, wdata);
                }
                xSemaphoreGive(xMutex_GUI_GPIO);
                *pState = 0;
            }
            break;
        }
        //
        // You will never reach here.
        default :
        {
            *pState = 0;
            break;
        }
    }
}

//------------------------------
// Draw Paper Feed
//------------------------------
void Draw_Paper_Feed(void)
{
    uint32_t i;
    uint16_t color0, color1, color2, color3;
    //
    // Paper feed
    for (i = 0; i < GUI_PLINE_MAX; i++)
    {
        gui_pline0[i] = gui_pline1[i];
        gui_pline1[i] = gui_pline2[i];
        gui_pline2[i] = gui_pline3[i];
    }
    gui_pline0_red = gui_pline1_red;
    gui_pline1_red = gui_pline2_red;
    gui_pline2_red = gui_pline3_red;
    //
    // Make Bottom Line
    for (i = 0; i < GUI_PLINE_MAX; i++)
    {
        gui_pline3[i] = ' ';
    }
    gui_pline3_red = PLINE_BLK;
    //
    // Draw each Line
    color0 = (gui_pline0_red)? COLOR_RED : COLOR_BLACK;
    color1 = (gui_pline1_red)? COLOR_RED : COLOR_BLACK;
    color2 = (gui_pline2_red)? COLOR_RED : COLOR_BLACK;
    color3 = (gui_pline3_red)? COLOR_RED : COLOR_BLACK;
    LCD_Draw_String(gui_pline0, 0,  1, color0, COLOR_LIGHTGRAY, FONT_MEDIUM);
    LCD_Draw_String(gui_pline1, 0,  2, color1, COLOR_LIGHTGRAY, FONT_MEDIUM);
    LCD_Draw_String(gui_pline2, 0,  3, color2, COLOR_LIGHTGRAY, FONT_MEDIUM);
    LCD_Draw_String(gui_pline3, 0,  4, color3, COLOR_LIGHTGRAY, FONT_MEDIUM);
}

//----------------------------------
// Draw Bottom Line
//----------------------------------
void Draw_Bottom_Line(uint8_t *str, uint32_t red)
{
    uint32_t i;
    uint8_t ch;
    uint16_t color3;
    //
    // Make Bottom Line
    for (i = 0; i < GUI_PLINE_MAX; i++)
    {
        gui_pline3[i] = ' ';
    }
    for (i = 0; i < GUI_PLINE_MAX; i++)
    {
        ch = str[i];
        if (ch == '\0') break;
        gui_pline3[i] = ch;
    }
    gui_pline3_red = red;
    //
    // Draw bottom Line
    color3 = (gui_pline3_red)? COLOR_RED : COLOR_BLACK;
    LCD_Draw_String(gui_pline3, 0,  4, color3, COLOR_LIGHTGRAY, FONT_MEDIUM);
}

//===========================================================
// End of Program
//===========================================================
