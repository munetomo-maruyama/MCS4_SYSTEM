//===========================================================
// mmRISC Project
//-----------------------------------------------------------
// File Name   : gpio.h
// Description : GPIO Header
//-----------------------------------------------------------
// History :
// Rev.01 2021.05.08 M.Maruyama First Release
//-----------------------------------------------------------
// Copyright (C) 2020-2021 M.Maruyama
//===========================================================

#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>
#include "common.h"

//-------------------------
// Define Registers
//-------------------------
#define GPIO_PDR0 0xa0000000
#define GPIO_PDR1 0xa0000004
#define GPIO_PDR2 0xa0000008
#define GPIO_PDR3 0xa000000c
#define GPIO_PDR4 0xa0000010
#define GPIO_PDR5 0xa0000014
//
#define GPIO_PDD0 0xa0000020
#define GPIO_PDD1 0xa0000024
#define GPIO_PDD2 0xa0000028
#define GPIO_PDD3 0xa000002c
#define GPIO_PDD4 0xa0000030
#define GPIO_PDD5 0xa0000034

//---------------
// 7-segment LED
//---------------
#define LED_0  (~(0x3f))
#define LED_1  (~(0x06))
#define LED_2  (~(0x5b))
#define LED_3  (~(0x4f))
#define LED_4  (~(0x66))
#define LED_5  (~(0x6d))
#define LED_6  (~(0x7d))
#define LED_7  (~(0x07))
#define LED_8  (~(0x7f))
#define LED_9  (~(0x6f))
#define LED_A  (~(0x77))
#define LED_B  (~(0x7c))
#define LED_C  (~(0x39))
#define LED_D  (~(0x5e))
#define LED_E  (~(0x79))
#define LED_F  (~(0x71))
#define LED_DP ( (0x7f)) // .
//
// Characters on 7-seg LED is based on Hitachi H68/TR console.
// https://www.hitachihyoron.com/jp/pdf/1977/05/1977_05_12.pdf
#define LED_G  (~(0x3d))
#define LED_H  (~(0x76))
#define LED_I  (~(0x19))
#define LED_J  (~(0x1e))
#define LED_K  (~(0x7a))
#define LED_L  (~(0x38))
#define LED_M  (~(0x55))
#define LED_N  (~(0x54))
#define LED_O  (~(0x5d))
#define LED_P  (~(0x73))
#define LED_Q  (~(0x67))
#define LED_R  (~(0x70))
#define LED_S  (~(0x6c))
#define LED_T  (~(0x31))
#define LED_U  (~(0x3e))
#define LED_V  (~(0x7e))
#define LED_W  (~(0x1d))
#define LED_X  (~(0x6a))
#define LED_Y  (~(0x6e))
#define LED_Z  (~(0x49))
#define LED_SUB (~(0x40)) // -
#define LED_ADD (~(0x46)) // +
#define LED_EQU (~(0x48)) // =
#define LED_NUM (~(0x2d)) // #
#define LED_DIV (~(0x52)) // /
#define LED_MUL (~(0x21)) // *
#define LED_PER (~(0x24)) // %
#define LED_COM (~(0x0c)) // ,
#define LED_DOL (~(0x64)) // $
#define LED_SPC (~(0x00)) // _(space)

//
static const uint8_t LED7SEG[] =
{
    LED_0, LED_1, LED_2, LED_3, LED_4, LED_5, LED_6, LED_7,
    LED_8, LED_9, LED_A, LED_B, LED_C, LED_D, LED_E, LED_F
};
//
static const uint8_t LED7SEG_ASCII[] =
{
    LED_SPC, LED_SPC, LED_SPC, LED_SPC, LED_SPC, LED_SPC, LED_SPC, LED_SPC, // 0x00-0x07
    LED_SPC, LED_SPC, LED_SPC, LED_SPC, LED_SPC, LED_SPC, LED_SPC, LED_SPC, // 0x08-0x0f
    LED_SPC, LED_SPC, LED_SPC, LED_SPC, LED_SPC, LED_SPC, LED_SPC, LED_SPC, // 0x10-0x17
    LED_SPC, LED_SPC, LED_SPC, LED_SPC, LED_SPC, LED_SPC, LED_SPC, LED_SPC, // 0x18-0x1f
    LED_SPC, LED_SPC, LED_SPC, LED_NUM, LED_DOL, LED_PER, LED_SPC, LED_SPC, // 0x20-0x27
    LED_SPC, LED_SPC, LED_MUL, LED_ADD, LED_COM, LED_SUB, LED_DP , LED_DIV, // 0x28-0x2f
    LED_0  , LED_1  , LED_2  , LED_3  , LED_4  , LED_5  , LED_6  , LED_7  , // 0x30-0x37
    LED_8  , LED_9  , LED_SPC, LED_SPC, LED_SPC, LED_EQU, LED_SPC, LED_SPC, // 0x38-0x3f
    LED_SPC, LED_A  , LED_B  , LED_C  , LED_D  , LED_E  , LED_F  , LED_G  , // 0x40-0x47
    LED_H  , LED_I  , LED_J  , LED_K  , LED_L  , LED_M  , LED_N  , LED_O  , // 0x48-0x4f
    LED_P  , LED_Q  , LED_R  , LED_S  , LED_T  , LED_U  , LED_V  , LED_W  , // 0x50-0x57
    LED_X  , LED_Y  , LED_Z  , LED_SPC, LED_SPC, LED_SPC, LED_SPC, LED_SPC, // 0x58-0x5f
    LED_SPC, LED_SPC, LED_SPC, LED_SPC, LED_SPC, LED_SPC, LED_SPC, LED_SPC, // 0x60-0x67
    LED_SPC, LED_SPC, LED_SPC, LED_SPC, LED_SPC, LED_SPC, LED_SPC, LED_SPC, // 0x68-0x6f
    LED_SPC, LED_SPC, LED_SPC, LED_SPC, LED_SPC, LED_SPC, LED_SPC, LED_SPC, // 0x70-0x77
    LED_SPC, LED_SPC, LED_SPC, LED_SPC, LED_SPC, LED_SPC, LED_SPC, LED_SPC  // 0x78-0x8f
};

//---------------
// Prototype
//---------------
void GPIO_Init(void);
void GPIO_SetSEG(uint32_t num);
void GPIO_PutCharSEG(uint8_t ascii);
void GPIO_SetLED(uint32_t bit);
uint32_t GPIO_GetKEY(void);
uint32_t GPIO_GetSW10(void);

#endif
//===========================================================
// End of Program
//===========================================================
