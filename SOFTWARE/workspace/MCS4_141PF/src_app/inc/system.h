//===========================================================
// mmRISC Project
//-----------------------------------------------------------
// File Name   : system.h
// Description : System Control Header
//-----------------------------------------------------------
// History :
// Rev.01 2021.10.23 M.Maruyama First Release
//-----------------------------------------------------------
// Copyright (C) 2020-2021 M.Maruyama
//===========================================================

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <stdint.h>
#include "common.h"

//---------------------------------
// Prototype
//---------------------------------
uint32_t Get_System_Freq(void);
void Wait_mSec(uint32_t mSec);
void Wait_uSec(uint32_t uSec);
void Wait_Cycle(uint64_t cyc);

#endif
//===========================================================
// End of Program
//===========================================================
