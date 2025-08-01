//===========================================================
// mmRISC Project
//-----------------------------------------------------------
// File Name   : mcs4.c
// Description : MCS4 Utility Routine
//-----------------------------------------------------------
// History :
// Rev.01 2025.07.07 M.Maruyama First Release
//-----------------------------------------------------------
// Copyright (C) 2017-2025 M.Maruyama
//===========================================================

#include <stdint.h>
#include "common.h"
#include "gpio.h"
#include "mcs4.h"
#include "system.h"

//---------------------------------------
// Calculator 141-PF Program
//---------------------------------------
const uint32_t calc141pf_siz = 0x4c0;
const uint8_t  calc141pf_hex[] = "\
F0110150B0515FADB1F0515FAD1C2968517327ECF5B368F051A0F3B3F5E16627\
EAF5F7140052464000B0ECF8F8E427EAE7506427EAE63420A0A5B130685173D0\
E1D1F3F5FC851A00F00000114F50B02620281053005100715A60144BF7145743\
02D440D4D329E2D0E2C06C222023EAF6736D1A76F0BCC0A914D92800F0514A40\
F7BBC76353191A6858054131182212050C9D6D3DBD8D5D2D067D4D1D0DADA40E\
BF069198F1CDD7FD8A0561F9D7D7CAC5506A2807506479B426182200D1506527\
EAFCB9A2F5F71C77A979CD407A1461B2F5FAF6B283B3D082B2506477BF29A2F5\
F714F8EFF2F71CF7ECB929A3E06929E91C7AA2E069A9E4DFE72800261019FDC0\
33A5F2F286B8B6410E666666666627E929E069770E27ECB3ED29E5B3E4C0D485\
B629E927EBFBE0697721F1C0D485B84133D485B6FAF929E8F127EBFBE0697735\
1A436DC168686868686829E0794AE4E5C0686829E9BDE07953C0DEB9AD6868BD\
A9F8F1B929E9BDE0A91C61C0686829EEF8F3C16868686829EEF6C127EEF5C166\
666627E6C06666D14181D84181A4418227EEF5FAF6E6C0D485B8DEB941A2DEB9\
BD6829DFEB79A2F3C1ADFBC1ADF8BDF3C1D795C1DC84C1A5F6B5F3C1A4F6C1D4\
85B829ABE5C029EDBBC07BCD6AC0DD9BF3D09AC142D300429442A342AA42AE42\
B342B942CA42DE42E742EC424644005180518151812A0040006F6F6F6F6F6FBF\
F4BF7F10DA514A2EFFBADFB929E0422C7F17DFBFA54226D18FF71425A4BFBEF6\
F3DEF64226A4BE29EDBAEDBB112CD2BDECF6F7E150B0686BABB951A2F7143711\
3FF0E1E27D532A0C2E00D8114BE150B07B4BC0506AB8DD9FF11C5FBADF426127\
E97777AA1C68528FAF528AAE528A196ED229E150B2423F528AAA148397F11C83\
DA528AA79BF71456425C9CF11C8FFAD1F5F54065A4BD264027EE1CA1D8E6F051\
4A41C6510A51465149C0D3B5FAC1D1B3BB42C252F9EFE542C252F9DD9BF182BA\
F7BA93BBF3BA99BAF1C052F9A38B82BBF7BAC0D485B627ECB229EC82F6C152D6\
F76627E4DFBDC029ECF4E4C0DB8D1AF16ED029EBFBE079F1C027EDB229EDB3C0\
32C030404BED6C14750ED9FCA70FFB8D040287EFFC6D0F7B0F76468DA23C48A0\
73E19E329A36E5515134292151A93F52A72952CAA72253CF3CDDA724FF85F15D\
CE73DD5DA7408D03E3E50E49525E5AA956AC4D21A751A040CF3C5E5ADDA75686\
F3FECACAA767FE7B6F90764702A71C040CA76A0DC2B110B47B6E9EDFCF9ACE84\
CA5FA77CDD539A7CA73C6C667566D9A7986C987597A79882AE7BB1AA77A3FDEB\
B4A8F1E99A9EA73CDBABFCC603BCB0E7D4B71E97BD313C31BD1E2CBC010DBFB4\
FFB7AC8AEF8249D94AFC4A7FF16CD575D30B46FCEFFDF1D7A9DF539AE35FF3BC\
5FE7F374E8A7EE00CACEEDDD5FC2B7DAF3FD020E030C040DF109FA44F109FAF1\
2028110650B02620281032F054507111601402F7140E30440200000000000000\
000000000000000051A753613E6563449C5B556A36587A5D415F85579835A95B\
9F7A963659932E0000000000000000003341FE4148414A686841534104413441\
2141A2419ABD29EDBBC02E6DABB7BAF6ABF68EBBF7BAB7F6F3C1AFB9FAD029EB\
FBE0797DC0AFB9F329E997128ED9E07987F0C07B966AFAC1AFF8BFC1415F0027\
E620402600404B41024104000000000000000000000000000000000000000000";

//----------------------------------
// pi4004 Program
//----------------------------------
const uint32_t pi4004_siz = 0x22a;
const uint8_t  pi4004_hex[] = "\
:10000000F0B0D8B1A0FDF0220023E07309720960BE\
:100010007104D2FD2001D821E0D4FD2000D921E0D7\
:1000200061D521E061D621E0F0FD200021E4E5E684\
:10003000D0BCD2BDD5BED2B050DAD2BCD3BDD9BEB1\
:10004000D4B050DAD4B050DAD3B0D5B1D7B250A7CB\
:10005000514FD6B050DAA31C72F0FD200021EEF60D\
:10006000D1B0D7B1D1B2126C5076406E50A7513C8E\
:10007000403051684074DEBAF12E00AEF4BCAFF4EB\
:10008000BDA0FD2DE9BBA1FD2DE98BFBB2FDB22D7D\
:10009000E07F7B7E7BA0F6F1F5B0A1F6F1F5B1A291\
:1000A000F6F1F5B27A79C0DEBAFA2E00AEF4BCAF42\
:1000B000F4BDA1FDF92DE8BBF1A0FD2DE98BFBB24C\
:1000C000FDB22DE07FAC7EACA0F6F1F5B0A1F6F16B\
:1000D000F5B1A2F6F1F5B27AAAC0D1B328002A0090\
:1000E000DEB52600B9B8BAB9BBBAA0FD27E9BB5046\
:1000F000FFB4E014F7F0B377E476E46075E2C0F0A3\
:10010000B45120641201510CA4F8B4C0F1AB8EFBC1\
:10011000BBAA8DFBBAA98CFBB9D0BFA88FFBB8C016\
:10012000FAF99EF18BFBBBF99DF18AFBBAF99CF1C0\
:1001300089FBB9D0BFF99FF188FBB8C0F0FD26005C\
:1001400027FAEE87FBE6ED87FBE5EC87FBE4C0F0E2\
:10015000FD260027FAEEB7A787FBBEEDB7A787FB02\
:10016000BDECB7A787FBBCC05175DBB3D6B4517FDC\
:10017000746E736CC0F0FD2E102FE4E5D3E6C0F072\
:10018000B051C1A01C8151C1A01C8651D1D6BA5119\
:10019000E551F9A1F1901C9BD1419CF0B2520A7A31\
:1001A0008FF0B2520A520A520A520A520A520A52A4\
:1001B0000A520A521851D151C1DAF1901C8D5221C4\
:1001C000C019C111C32E202FEAF612CE60C0F0B0C4\
:1001D000C0F0FD2E102FDABFEEF18FE6D0BFED8F0D\
:1001E000E5EC8FE4C0F0FD2E102FD0BFFAEE9FE6B5\
:1001F000F3ED9FE5F3EC9FE4C0F0FD2E102FECBB78\
:10020000EDBCEEBDABFD2DE9B1C02E002FA2141345\
:10021000D64214D4E2F0E2C0F0FD2E00D2E1F0E1CB\
:0A022000C0F0FD2E00D8E1F0E1C0AF\
:00000001FF";

//---------------------------------------
// MCS4 Load 141-PF Program to ROM
//---------------------------------------
uint32_t MCS4_ROM_Stote_141PF(void)
{
    uint32_t addr;
    uint32_t pos;
    uint32_t ch0, ch1;
    uint32_t wbyte;
    uint32_t wdata;
    uint32_t rbyte;
    uint32_t rdata;
    uint32_t error = 0;
    //
    // MCS4 Reset, MCS4 Init ROM Enable
    // mcs_res_n = 0, mcs4_init_rom_enb = 1
    mem_wr32(GPIO_PDR5, 0x40000000);
    //
    // Download & Verify
    pos = 0;
    for (addr = 0; addr < calc141pf_siz; addr++)
    {
        ch1 = calc141pf_hex[pos];
        pos = pos + 1;
        ch0 = calc141pf_hex[pos];
        pos = pos + 1;
        //
        ch1 = ((ch1 >= '0') && (ch1 <= '9'))? (ch1 - '0')
            : ((ch1 >= 'A') && (ch1 <= 'F'))? (ch1 - 'A' + 10)
            : 0;
        ch0 = ((ch0 >= '0') && (ch0 <= '9'))? (ch0 - '0')
            : ((ch0 >= 'A') && (ch0 <= 'F'))? (ch0 - 'A' + 10)
            : 0;
        wbyte = ch1 * 16 + ch0;
        //
        // Store
        wdata = (addr << 16) + (wbyte << 8);
        mem_wr32(GPIO_PDR5, 0x60000000 + wdata);
        Wait_mSec(1);
        mem_wr32(GPIO_PDR5, 0x40000000 + wdata);
        Wait_mSec(1);
        //
        // Load
        wdata = (addr << 16);
        mem_wr32(GPIO_PDR5, 0x50000000 + wdata);
        Wait_mSec(1);
        rdata = mem_rd32(GPIO_PDR5);
        rbyte = rdata & 0x000000ff;
        //
        // Verify
        if (wbyte != rbyte) // Verify Error
        {
            error = 1;
            break;
        }
    }
    // MCS4 Run, MCS4 Init ROM Disable
    // mcs_res_n = 1, mcs4_init_rom_enb = 0
    mem_wr32(GPIO_PDR5, 0x80000000);
    //
    return error;
}

//---------------------------------------
// MCS4 Load pi4004 Program to ROM
//---------------------------------------
uint32_t MCS4_ROM_Stote_PI4004(void)
{
    uint32_t addr;
    uint32_t pos;
    uint32_t ch0, ch1;
    uint32_t wbyte;
    uint32_t wdata;
    uint32_t rbyte;
    uint32_t rdata;
    uint32_t error = 0;
    //
    // MCS4 Reset, MCS4 Init ROM Enable
    // mcs_res_n = 0, mcs4_init_rom_enb = 1
    mem_wr32(GPIO_PDR5, 0x40000000);
    //
    // Download & Verify
    pos = 0;
    for (addr = 0; addr < pi4004_siz; addr++)
    {
        if ((addr % 16) == 0)
        {
            pos = pos + 9;
        }
        //
        ch1 = (uint32_t) pi4004_hex[pos];
        pos = pos + 1;
        ch0 = (uint32_t) pi4004_hex[pos];
        pos = pos + 1;
        //
        ch1 = ((ch1 >= '0') && (ch1 <= '9'))? (ch1 - '0')
            : ((ch1 >= 'A') && (ch1 <= 'F'))? (ch1 - 'A' + 10)
            : 0;
        ch0 = ((ch0 >= '0') && (ch0 <= '9'))? (ch0 - '0')
            : ((ch0 >= 'A') && (ch0 <= 'F'))? (ch0 - 'A' + 10)
            : 0;
        wbyte = ch1 * 16 + ch0;
        //
        // Store
        wdata = (addr << 16) + (wbyte << 8);
        mem_wr32(GPIO_PDR5, 0x60000000 + wdata);
        Wait_mSec(1);
        mem_wr32(GPIO_PDR5, 0x40000000 + wdata);
        Wait_mSec(1);
        //
        // Load
        wdata = (addr << 16);
        mem_wr32(GPIO_PDR5, 0x50000000 + wdata);
        Wait_mSec(1);
        rdata = mem_rd32(GPIO_PDR5);
        rbyte = rdata & 0x000000ff;
        //
        // Verify
        if (wbyte != rbyte) // Verify Error
        {
            error = 1;
            break;
        }
        //
        if ((addr % 16) == 15)
        {
            pos = pos + 2;
        }
    }
    // MCS4 Run, MCS4 Init ROM Disable
    // mcs_res_n = 1, mcs4_init_rom_enb = 0
    mem_wr32(GPIO_PDR5, 0x80000000);
    //
    return error;
}

//---------------------------------------
// MCS4 Detect ROM Program
//---------------------------------------
uint32_t MCS4_ROM_Detection(void)
{
    uint32_t addr;
    uint32_t wdata;
    uint32_t rbyte;
    uint32_t rdata;
    uint32_t result;
    //
    // Load 2nd byte to distinguish program code
    addr = 1; // 2nd Byte
    wdata = (addr << 16);
    mem_wr32(GPIO_PDR5, 0x50000000 + wdata);
    Wait_mSec(1);
    rdata = mem_rd32(GPIO_PDR5);
    rbyte = rdata & 0x000000ff;
    //
    result = (rbyte == 0x11)? 0 : 1;
    return result; // 0:141-PF, 1:pi4004
}

/*
000         //==========================================
000         // pi Calculation by 4004 CPU
000         //------------------------------------------
000         // Rev.01 2017.01.01 Munetomo Maruyama
000         //------------------------------------------
000         // Copyright (C) 2016 by Munetomo Maruyama
000         //==========================================
000
000         //-------------------------------------------------
000         // Calculate the Circular Constant Pi
000         //-------------------------------------------------
000         // (1) Machin's formula
000         // PI/4 =  4*arctan(1/5) -   arctan(1/239)
000         // PI   = 16*arctan(1/5) - 4*arctan(1/239)
000         // Here, arctan(1/p) = 1/p - 1/(3*p^3) + 1/(5*p^5) - 1/(7*p^7) + ...
000         // Then,
000         // PI =  (16*1/5     - 4*1/239)
000         //     - (16*1/3*5^3 - 4*1/3*239^3)
000         //     + (16*1/5*5^5 - 4*1/5*239^5)
000         //     - (16*1/7*5^7 - 4*1/7*239^7)
000         //     +...
000         //    =  (1/1)*(16*5/(5*5)^1 - 4*239/(239*239)^1)
000         //     - (1/3)*(16*5/(5*5)^2 - 4*239/(239*239)^2)
000         //     + (1/5)*(16*5/(5*5)^3 - 4*239/(239*239)^3)
000         //     - (1/7)*(16*5/(5*5)^4 - 4*239/(239*239)^4)
000         //     +...
000         //-------------------------------------------------
000         // (2) Define Arrays for Long Figure Number
000         // Each element has Octal 4 figures.
000         //     PI[] : Value to be converged to Pi
000         //     T1[] : (16*  5)/(  5*  5)^n (n=1...)
000         //     T2[] : ( 4*239)/(239*239)^n (n=1...)
000         //     T3[] : (-1)*(n+1)*(1/(2n-1))*(T1[]-T2[])
000         //-------------------------------------------------
000         // (3) Example
000         // n TI[0] TI[1] T2[0] T2[1] T3[0] T3[1] PI[0] PI[1]
000         // 0 0080  0000  0956  0000  0000  0000  0000  0000
000         // 1 0003  2000  0000  0167  0003  1833  0003  1833 (+)
000         // 2 0000  1280  0000  0000  0000  0426  0003  1407 (-)
000         // 3 0000  0051  0000  0000  0000  0010  0003  1417 (+)
000         // 4 0000  0002  0000  0000  0000  0000  0003  1417 (-)
000         //-------------------------------------------------
000
000         //-------------------------------------------------
000         // Global RAM Assignment
000         //-------------------------------------------------
000         // RAM Memory Character :RAMCH[Bank][SRC]
000         // 8bank x 4chip x 4reg x 16char = 2048char
000         // PI[512] Bank0(SRC=0x00-0xFF) , Bank1(SRC=0x00-0xFF)
000         // T1[512] Bank2(SRC=0x00-0xFF) , Bank3(SRC=0x00-0xFF)
000         // T2[512] Bank4(SRC=0x00-0xFF) , Bank5(SRC=0x00-0xFF)
000         // T3[512] Bank6(SRC=0x00-0xFF) , Bank7(SRC=0x00-0xFF)
000         //-------------------------------------------------
000         // RAM Status Character :RAMST[Bank][SRC][Pos]
000         // Bank Chip Reg Pos
000         // 0    0    0   0x0 Index[11:8]
000         //               0x1 Index[ 7:4]
000         //               0x2 Index[ 3:0]
000         //               0x3 Reserved
000         // Note: [SRC]=[Chip][Reg]
000         //-------------------------------------------------
000
000         //-------------------------------------------------
000         // Major Rn Assignment
000         //-------------------------------------------------
000         // R0 : 2nd Bank of Augend/Minuend for Long Add/Sub
000         // R1 : 2nd Bank of Addend/Subtrahend for Long Add/Sub
000         // R2 : 2nd Bank of Result for Long Add/Sub
000         // R3 : Converged Flag
000         // R4 :
000         // R5 :
000         // R6 :
000         // R7 :
000         // R8 : Dividend's Highest Digit for Partial Division
000         // R9 : Dividend's 2nd     Digit for Partial Division
000         // R10: Dividend's 3rd     Digit for Partial Division
000         // R11: Dividend's Lowest  Digit for Partial Division
000         // R12: Divisor's Highest Digit for Long Division
000         // R13: Divisor's Middle  Digit for Long Division
000         // R14: Divisor's Lowest  Digit for Long Division
000         // R15:
000         //-------------------------------------------------
000
000         //------------------------------------
000             org 0x0000
000         RESET:
000         //====================================
000         // Main Routine
000         // (1) Calculate Pi 512digits
000         // (2) Printout Pi on 141-PF Printer
000         //====================================
000         MAIN:
000             //----------------------------
000             // Clear All Banks of RAM
000             //----------------------------
000             // Clear Bank Number:R0
000 F0          CLB
001 B0          XCH  0
002             // Bank Counter Loop
002 D8          LDM -8
003 B1          XCH  1     // R1=Initial Bank Counter=-8(0x8)
004         MAIN1:
004 A0          LD   0
005 FD          DCL        // Select New Bank
006 F0          CLB        // ACC=0, CY=0
007             // SRC Address Loop
007 22 00       FIM  1P 0  // {R2,R3}=0x00 (Initial SRC Address)
009         MAIN2:
009 23          SRC  1P
00A E0          WRM        // RAMCH[bankR0][R1P]=0
00B 73 09       ISZ  3 MAIN2 // R3=R3+1, if NZ jump
00D 72 09       ISZ  2 MAIN2 // R2=R2+1, if NZ jump
00F             //
00F 60          INC  0       // R0=R0+1, next Bank
010 71 04       ISZ  1 MAIN1 // R1=R1+1, if NZ jump
012             //----------------------------
012             // Initialize Buffer Data
012             //----------------------------
012             // T1=16*5=080.000... :Bank2
012 D2          LDM  2
013 FD          DCL          // Select Bank2
014 20 01       FIM  0P 0x01 // {R0,R1}=0x01
016 D8          LDM  8
017 21          SRC  0P
018 E0          WRM          // RAMCH[bank2][0x01]=8
019             // T2=4*239=956.000... :Bank4
019 D4          LDM  4
01A FD          DCL          // Select Bank4
01B 20 00       FIM  0P 0x00 // {R0,R1}=0x00
01D D9          LDM  9
01E 21          SRC  0P
01F E0          WRM          // RAMCH[bank4][0x00]=9
020 61          INC  1       // {R0,R1}=0x01
021 D5          LDM  5
022 21          SRC  0P
023 E0          WRM          // RAMCH[bank4][0x01]=5
024 61          INC  1       // {R0,R1}=0x02
025 D6          LDM  6
026 21          SRC  0P
027 E0          WRM          // RAMCH[bank4][0x02]=6
028             //-------------------------------------------
028             // Clear Index (RAMST[bank0][0x00][pos0:2]=0)
028             //-------------------------------------------
028 F0          CLB
029 FD          DCL         // Select Bank0
02A 20 00       FIM 0P 0x00 // {R0,R1}=0x00
02C 21          SRC 0P
02D E4          WR0         // RAMST[bank0][0x00][pos0]=0
02E E5          WR1         // RAMST[bank0][0x00][pos1]=0
02F E6          WR2         // RAMST[bank0][0x00][pos2]=0
030             //-----------------------------
030             // Loop until Converged
030             //-----------------------------
030         MAIN_LOOP:
030             //---------------------------------
030             // Make T1=(16*5)/(5*5)^n (n=1...)
030             //---------------------------------
030 D0          LDM  0
031 BC          XCH 12       // R12=0
032 D2          LDM  2
033 BD          XCH 13       // R13=2
034 D5          LDM  5
035 BE          XCH 14       // R14=5
036             //
036 D2          LDM  2
037 B0          XCH  0       // R0=2 (T1:Bank2,3)
038             // RAMCH[bank2:3][]=RAMCH[bank2:3][]/R[12:14]
038 50 DA       JMS  LONGDIV
03A             //--------------------------------------
03A             // Make T2=(4*239)/(239*239)^n (n=1...)
03A             //--------------------------------------
03A D2          LDM  2
03B BC          XCH 12       // R12=2
03C D3          LDM  3
03D BD          XCH 13       // R13=3
03E D9          LDM  9
03F BE          XCH 14       // R14=9
040             //
040 D4          LDM  4
041 B0          XCH  0       // R0=4 (T2:Bank4,5)
042             // RAMCH[bank4:5][]=RAMCH[bank4:5][]/R[12:14]
042 50 DA       JMS  LONGDIV
044             //
044 D4          LDM  4
045 B0          XCH  0       // R0=4 (T2:Bank4,5)
046             // RAMCH[bank4:5][]=RAMCH[bank4:5][]/R[12:14]
046 50 DA       JMS  LONGDIV
048             //-----------------------
048             // Make T3
048             //-----------------------
048 D3          LDM  3
049 B0          XCH  0        // R0=3 (T1:Bank2,3)
04A D5          LDM  5
04B B1          XCH  1        // R1=5 (T2:Bank4,5)
04C D7          LDM  7
04D B2          XCH  2        // R2=7 (T3:Bank6,7)
04E             // RAMCH[bank6:7][]=RAMCH[bank2:3][]-RAMCH[bank4:5][]
04E 50 A7       JMS  LONGSUB
050             //
050             // R[12:14]=2*RAMST[bank0][0x00][pos0:2]+1
050 51 4F       JMS  INDEXODD
052             //
052 D6          LDM  6
053 B0          XCH  0        // R0=6 (T3:Bank6,7)
054             // RAMCH[bank6:7][]=RAMCH[bank6:7][]/R[12:14]
054 50 DA       JMS  LONGDIV
056             //--------------------------
056             // If Converged, break loop
056             //--------------------------
056 A3          LD   3            // ACC=R3
057 1C 72       JCN  AN CONVERGED // if ACC==1 jump, else continue
059             //-------------------
059             // Accumulate to PI
059             //-------------------
059 F0          CLB
05A FD          DCL        // Select Bank0
05B 20 00       FIM 0P 0   // {R0,R1}=0x00
05D 21          SRC 0P
05E EE          RD2        // ACC=RAMST[bank0][0x00][pos2], LSB of Index
05F F6          RAR        // CY=ACC[0](LSB)
060             //
060 D1          LDM  1
061 B0          XCH  0     // R0=1 (PI:Bank0,1)
062 D7          LDM  7
063 B1          XCH  1     // R1=7 (T3:Bank6,7)
064 D1          LDM  1
065 B2          XCH  2     // R2=1 (PI:Bank0,1)
066             //
066 12 6C       JCN C1 PISUB // if Index is even do Add, else do Sub
068         PIADD:
068             // RAMCH[bank0:1][]=RAMCH[bank0:1][]+RAMCH[bank6:7][]
068 50 76       JMS  LONGADD
06A 40 6E       JUN  PIEND
06C         PISUB:
06C             // RAMCH[bank0:1][]=RAMCH[bank0:1][]-RAMCH[bank6:7][]
06C 50 A7       JMS  LONGSUB
06E         PIEND:
06E             //---------------------------
06E             // Increment Index and Loop
06E             //---------------------------
06E             // RAMST[bank0][0x00][pos0:2]=RAMST[bank0][0x00][pos0:2]+1
06E 51 3C       JMS  INDEXINC
070 40 30       JUN  MAIN_LOOP // Do Next Loop
072             //------------
072             // Converged
072             //------------
072         CONVERGED:
072             //-----------------------
072             // Print Out Result PI[]
072             //-----------------------
072         PRINTOUT:
072 51 68       JMS PRINTER_MAIN // Print RAMCH[bank0:1][]
074             //----------------
074             // Stop
074             //----------------
074         STOP:
074 40 74       JUN STOP
076
076         //====================================
076         // Long Addition (512digits)
076         //   Input Parameters
076         //     R0 = 2nd Bank(odd) of Augend
076         //     R1 = 2nd Bank(odd) of Addend
076         //     R2 = 2nd Bank(odd) of Result
076         //   Registers to be broken
076         //     R10, R11, R12, R13, R14, R15
076         //====================================
076         LONGADD:
076             //---------------------------------
076             // Set Loop Counter R10 for 2banks
076             //---------------------------------
076 DE          LDM -2
077 BA          XCH 10     // R10=-2(14)
078             //----------------------------
078             // Clear CY for Long Addition
078             //----------------------------
078 F1          CLC
079             //-----------------------------
079             // For 256bytes in each bank,
079             // BANK(R2)=BANK(R0)+BANK(R1)
079             //-----------------------------
079         LONGADD1:
079 2E 00       FIM 7P 0   // {R14,R15}=0, RAM address counter
07B         LONGADD2:
07B             //---------------------------
07B             // {R12,R13}=0xFF-{R14,R15}
07B             // as SRC Address (reverse)
07B             //---------------------------
07B AE          LD  14
07C F4          CMA
07D BC          XCH 12     // R12=~R14 (R12=0xF-R14)
07E AF          LD  15
07F F4          CMA
080 BD          XCH 13     // R13=~R15 (R13=0xF-R15)
081             //--------------------
081             // Load Augend Digit
081             //--------------------
081 A0          LD  0
082 FD          DCL        // Select Bank Specified by R0
083 2D          SRC 6P
084 E9          RDM
085 BB          XCH 11     // R11=RAMCH[bankR0][R6P]
086             //--------------------
086             // Load Addend Digit
086             //--------------------
086 A1          LD  1
087 FD          DCL        // Select Bank Specified by R1
088 2D          SRC 6P
089 E9          RDM        // ACC=RAMCH[bankR1][R6P]
08A             //--------------------
08A             // Execute Addition
08A             //--------------------
08A 8B          ADD 11     // ACC=ACC+R11
08B FB          DAA        // Decimal Adjust
08C             //-----------------------------
08C             // Store Addition Result Digit
08C             //-----------------------------
08C B2          XCH  2
08D FD          DCL        // Select Bank Specified by R2
08E B2          XCH  2     // Revert ACC
08F 2D          SRC 6P
090 E0          WRM        // RAMCH[bankR2][R6P]=ACC
091             //--------------------
091             // Repeat 256 counts
091             //--------------------
091 7F 7B       ISZ 15 LONGADD2 // R15=R15+1, if NZ jump
093 7E 7B       ISZ 14 LONGADD2 // R14=R14+1, if NZ jump
095             //-----------------------------------
095             // Decrement Bank Number R0, keep CY
095             //-----------------------------------
095 A0          LD   0     // Simpley clear LSB of R0
096 F6          RAR
097 F1          CLC
098 F5          RAL
099 B0          XCH  0
09A             //-----------------------------------
09A             // Decrement Bank Number R1, keep CY
09A             //-----------------------------------
09A A1          LD   1     // Simpley clear LSB of R1
09B F6          RAR
09C F1          CLC
09D F5          RAL
09E B1          XCH  1
09F             //-----------------------------------
09F             // Decrement Bank Number R2, keep CY
09F             //-----------------------------------
09F A2          LD   2     // Simpley clear LSB of R2
0A0 F6          RAR
0A1 F1          CLC
0A2 F5          RAL
0A3 B2          XCH  2
0A4             //---------------------
0A4             // Repeat for 2 banks
0A4             //---------------------
0A4 7A 79       ISZ 10 LONGADD1 // R10=R10+1, if NZ jump
0A6             //--------
0A6             // Return
0A6             //--------
0A6 C0          BBL 0
0A7
0A7         //====================================
0A7         // Long Subtraction (512digits)
0A7         //   Input Parameters
0A7         //     R0 = 2nd Bank(odd) of Minuend
0A7         //     R1 = 2nd Bank(odd) of Subtrahend
0A7         //     R2 = 2nd Bank(odd) of Result
0A7         //   Registers to be broken
0A7         //     R10, R11, R12, R13, R14, R15
0A7         //====================================
0A7         LONGSUB:
0A7             //---------------------------------
0A7             // Set Loop Counter R10 for 2banks
0A7             //---------------------------------
0A7 DE          LDM -2
0A8 BA          XCH 10     // R10=-2(14)
0A9             //---------------------------------
0A9             // Set CY for Long Subtraction
0A9             //---------------------------------
0A9 FA          STC        // No Borrow
0AA             //----------------------------
0AA             // For 256bytes in each bank,
0AA             // BANK(R2)=BANK(R0)-BANK(R1)
0AA             //----------------------------
0AA         LONGSUB1:
0AA 2E 00       FIM 7P 0   // {R14,R15}=0, RAM address counter
0AC         LONGSUB2:
0AC             //----------------------------
0AC             // {R12,R13}=0xFF-{R14,R15}
0AC             // as SRC Address (reverse)
0AC             //----------------------------
0AC AE          LD  14
0AD F4          CMA
0AE BC          XCH 12     // R12=~R14 (R12=0xF-R14)
0AF AF          LD  15
0B0 F4          CMA
0B1 BD          XCH 13     // R13=~R15 (R13=0xF-R15)
0B2             //---------------------------------------------
0B2             // Load Subtrahend Digit and Subtract from 10
0B2             //---------------------------------------------
0B2 A1          LD  1
0B3 FD          DCL        // Select Bank Specified by R1
0B4 F9          TCS        // if no borrow ACC=10, else ACC=9
0B5 2D          SRC 6P
0B6 E8          SBM
0B7 BB          XCH 11     // R11=ACC-RAMCH[bankR1][R6P]
0B8 F1          CLC        // CY=0
0B9             //---------------------
0B9             // Load Minuend Digit
0B9             //---------------------
0B9 A0          LD  0
0BA FD          DCL        // Select Bank Specified by R0
0BB 2D          SRC 6P
0BC E9          RDM        // ACC=RAMCH[bankR0][R6P]
0BD             //---------------------
0BD             // Execute Subtraction
0BD             //---------------------
0BD 8B          ADD 11     // ACC=ACC+R11
0BE FB          DAA        // Decimal Adjust
0BF             //-----------------------------
0BF             // Store Subtract Result Digit
0BF             //-----------------------------
0BF B2          XCH  2
0C0 FD          DCL        // Select Bank Specified by R2
0C1 B2          XCH  2     // Revert ACC
0C2 2D          SRC 6P
0C3 E0          WRM        // RAMCH[bankR2][R6P]=ACC
0C4             //-------------------
0C4             // Repeat 256 counts
0C4             //-------------------
0C4 7F AC       ISZ 15 LONGSUB2 // R15=R15+1, if NZ jump
0C6 7E AC       ISZ 14 LONGSUB2 // R14=R14+1, if NZ jump
0C8             //-----------------------------------
0C8             // Decrement Bank Number R0, keep CY
0C8             //-----------------------------------
0C8 A0          LD   0     // Simpley clear LSB of R0
0C9 F6          RAR
0CA F1          CLC
0CB F5          RAL
0CC B0          XCH  0
0CD             //-----------------------------------
0CD             // Decrement Bank Number R1, keep CY
0CD             //-----------------------------------
0CD A1          LD   1     // Simpley clear LSB of R1
0CE F6          RAR
0CF F1          CLC
0D0 F5          RAL
0D1 B1          XCH  1
0D2             //-----------------------------------
0D2             // Decrement Bank Number R2, keep CY
0D2             //-----------------------------------
0D2 A2          LD   2     // Simpley clear LSB of R2
0D3 F6          RAR
0D4 F1          CLC
0D5 F5          RAL
0D6 B2          XCH  2
0D7             //--------------------
0D7             // Repeat for 2 banks
0D7             //--------------------
0D7 7A AA       ISZ 10 LONGSUB1 // R10=R10+1, if NZ jump
0D9             //---------
0D9             // Return
0D9             //---------
0D9 C0          BBL 0
0DA
0DA         //====================================
0DA         // Long Division (512digits)
0DA         //   Input Parameters
0DA         //     Dividend  RAMCH[bankR0][all]:RAMCH[bankR0+1][all]
0DA         //     Divisor   R[12:14]   RRR
0DA         //     Converged Flag R3
0DA         //   Output Parameters
0DA         //     Result    RAMCH[bankR0][all]:RAMCH[bankR0+1][all]
0DA         //     If Converged, R3=1
0DA         //     Converged Flag R3
0DA         //   Registers to be broken
0DA         //     R4...R15
0DA         //====================================
0DA         LONGDIV:
0DA             //-----------------------------------
0DA             // Set Converged Flag (R3) 1, so far
0DA             //-----------------------------------
0DA D1          LDM  1
0DB B3          XCH  3
0DC             //--------------------------------------------
0DC             // Clear Dividend R8-R11 for Partial Division
0DC             //--------------------------------------------
0DC 28 00       FIM  4P 0    // R8 =0, R9 =0
0DE 2A 00       FIM  5P 0    // R10=0, R11=0
0E0             //--------------------------------
0E0             // Set Loop Counter R5 for 2banks
0E0             //--------------------------------
0E0 DE          LDM -2
0E1 B5          XCH  5       // R5=-2(14)
0E2         LONGDIV1:
0E2             //------------------------------------------
0E2             // Set {R6,R7}=0 as RAM SRC address pointer
0E2             //------------------------------------------
0E2 26 00       FIM 3P 0
0E4         LONGDIV2:
0E4             //----------------------------------
0E4             // Chain Moves; {R8,R10}<--{R9,R11}
0E4             //----------------------------------
0E4             //-----------
0E4             // R8<--R9
0E4             //-----------
0E4 B9          XCH  9
0E5 B8          XCH  8
0E6             //-----------
0E6             // R9<--R10
0E6             //-----------
0E6 BA          XCH 10
0E7 B9          XCH  9
0E8             //-----------
0E8             // R10<--R11
0E8             //-----------
0E8 BB          XCH 11
0E9 BA          XCH 10
0EA             //----------------------------------------------
0EA             // Final Chain Moves; R11<--RAMCH[bankR0][R3P]
0EA             //----------------------------------------------
0EA A0          LD  0
0EB FD          DCL        // Select Bank Specified by R0
0EC 27          SRC 3P
0ED E9          RDM
0EE BB          XCH 11
0EF             //------------------------------------------------
0EF             // Dividend is prepared, so exec Partial Division
0EF             //------------------------------------------------
0EF 50 FF       JMS PARTDIV
0F1             //-----------------------------------------
0F1             // Store Quotient R4 at RAMCH[bankR0][R3P]
0F1             //-----------------------------------------
0F1 B4          XCH  4
0F2 E0          WRM
0F3             //--------------------------------------
0F3             // If Quotient is not zero,
0F3             // then set Flag R3 as "Not Converged"
0F3             //--------------------------------------
0F3 14 F7       JCN AZ LONGDIV3 // if ACC==0, skip
0F5 F0          CLB
0F6 B3          XCH  3          // Clear R3
0F7         LONGDIV3:
0F7             //--------------------
0F7             // Repeat 256 counts
0F7             //--------------------
0F7 77 E4       ISZ 7 LONGDIV2 // R7=R7+1, if NZ jump
0F9 76 E4       ISZ 6 LONGDIV2 // R6=R6+1, if NZ jump
0FB             //-----------------------
0FB             // Increment Bank Number
0FB             //-----------------------
0FB 60          INC 0      // R0=R0+1
0FC             //---------------
0FC             // Repeat 2banks
0FC             //---------------
0FC 75 E2       ISZ 5 LONGDIV1 // R5=R5+1, if NZ jump
0FE             //--------
0FE             // Return
0FE             //--------
0FE C0          BBL 0
0FF
0FF         //====================================
0FF         // Partial Division
0FF         //   Input Parameters
0FF         //     Dividend  R[8:11]   RRRR
0FF         //     Divisor   R[12:14]   RRR
0FF         //   Output Parameters
0FF         //     Quotient  R4
0FF         //     Remainder R[8:11]   RRRR
0FF         //   Registers to be broken
0FF         //     none
0FF         //====================================
0FF         PARTDIV:
0FF             //-----------------------------
0FF             // Initialize Quotient to Zero
0FF             //-----------------------------
0FF F0          CLB
100 B4          XCH  4     // Quotient(R4)=0
101         PARTDIV1:
101             //----------------------------------
101             // Repeat Subtraction until Borrow
101             //----------------------------------
101 51 20       JMS  PARTSUB     // Partial Subtract
103 64          INC  4           // Increment Quotient(R4)
104 12 01       JCN  C1 PARTDIV1 // if (CY==1, No Borrow) repeat
106         PARTDIV2:
106             //---------------------------
106             // Restore Extra Subtraction
106             //---------------------------
106 51 0C       JMS  PARTADD // Partial Addition
108             //------------------------------
108             // Decrement Quotient(R4)
108             // according to Last Restoring
108             //------------------------------
108 A4          LD  4
109 F8          DAC
10A B4          XCH 4
10B             //---------
10B             // Return
10B             //---------
10B C0          BBL  0
10C
10C         //====================================
10C         // Partial Addition
10C         //   Input Parameters
10C         //     Augend  R[8:11]   RRRR
10C         //     Addend  R[12:14]   RRR
10C         //   Output Parameters
10C         //     Result  R[8:11]   RRRR
10C         //   Registers to be broken
10C         //     R15
10C         //====================================
10C         PARTADD:
10C             //-----------------------------
10C             // Clear CY for Long Addition
10C             //-----------------------------
10C F1          CLC
10D             //-----------------
10D             // R11=R11+R14+CY
10D             //-----------------
10D AB          LD  11
10E 8E          ADD 14
10F FB          DAA
110 BB          XCH 11
111             //-----------------
111             // R10=R10+R13+CY
111             //-----------------
111 AA          LD  10
112 8D          ADD 13
113 FB          DAA
114 BA          XCH 10
115             //-----------------
115             // R9=R9+R12+CY
115             //-----------------
115 A9          LD   9
116 8C          ADD 12
117 FB          DAA
118 B9          XCH  9
119             //-----------------
119             // R8=R8+0+CY
119             //-----------------
119 D0          LDM  0
11A BF          XCH 15     // R15=0
11B A8          LD   8
11C 8F          ADD 15
11D FB          DAA
11E B8          XCH  8
11F             //---------
11F             // Return
11F             //---------
11F C0          BBL  0
120
120         //====================================
120         // Partial Subtract
120         //   Input Parameters
120         //     Minuend    R[8:11]   RRRR
120         //     Subtrahend R[12:14]   RRR
120         //   Output Parameters
120         //     Result     R[8:11]   RRRR
120         //   Registers to be broken
120         //     R15
120         //====================================
120         PARTSUB:
120             //------------------------------
120             // Set CY for Long Subtraction
120             //------------------------------
120 FA          STC        // No Borrow
121             //---------------------
121             // R11=R11+(10-R14)-CY
121             //---------------------
121 F9          TCS        // if no borrow ACC=10, else ACC=9
122 9E          SUB 14
123 F1          CLC
124 8B          ADD 11
125 FB          DAA
126 BB          XCH 11
127             //---------------------
127             // R10=R10+(10-R13)-CY
127             //---------------------
127 F9          TCS        // if no borrow ACC=10, else ACC=9
128 9D          SUB 13
129 F1          CLC
12A 8A          ADD 10
12B FB          DAA
12C BA          XCH 10
12D             //---------------------
12D             // R9=R9+(10-R12)-CY
12D             //---------------------
12D F9          TCS        // if no borrow ACC=10, else ACC=9
12E 9C          SUB 12
12F F1          CLC
130 89          ADD  9
131 FB          DAA
132 B9          XCH  9
133             //---------------------
133             // R8=R8-(10-0)-CY
133             //---------------------
133 D0          LDM  0
134 BF          XCH 15     // R15=0
135 F9          TCS        // if no borrow ACC=10, else ACC=9
136 9F          SUB 15
137 F1          CLC
138 88          ADD  8
139 FB          DAA
13A B8          XCH  8
13B             //---------
13B             // Return
13B             //---------
13B C0          BBL  0
13C
13C         //====================================
13C         // Increment Index by 1
13C         //   Input Parameters
13C         //     RAMST[bank0][0x00][pos0:2] : Index
13C         //   Output Parameters
13C         //     RAMST[bank0][0x00][pos0:2] : Index + 1
13C         //   Registers to be broken
13C         //     R6, R7
13C         //====================================
13C         INDEXINC:
13C             //------------------------------------
13C             // Select RAM at Bank0, Chip=0, Reg=0
13C             //------------------------------------
13C F0          CLB
13D FD          DCL        // Select Bank 0
13E 26 00       FIM 3P 0   // {R6,R7}=0x00
140 27          SRC 3P     // Select Bank0, Chip=0, Reg=0
141             //---------------------------
141             // Preparation to Increment
141             //---------------------------
141 FA          STC        // CY=1
142             //---------------------------
142             // Addition of Lowest Digit
142             //---------------------------
142 EE          RD2        // ACC=RAMST[bank0][0x00][pos2]
143 87          ADD 7      // ACC=ACC+R7+CY (R7=0)
144 FB          DAA        // Decimal Adjust
145 E6          WR2        // RAMST[bank0][0x00][pos2]=ACC
146             //---------------------------
146             // Addition of Middle Digit
146             //---------------------------
146 ED          RD1        // ACC=RAMST[bank0][0x00][pos1]
147 87          ADD 7      // ACC=ACC+R7+CY (R7=0)
148 FB          DAA        // Decimal Adjust
149 E5          WR1        // RAMST[bank0][0x00][pos1]=ACC
14A             //---------------------------
14A             // Addition of Highest Digit
14A             //---------------------------
14A EC          RD0        // ACC=RAMST[bank0][0x00][pos0]
14B 87          ADD 7      // ACC=ACC+R7+CY (R7=0)
14C FB          DAA        // Decimal Adjust
14D E4          WR0        // RAMST[bank0][0x00][pos0]=ACC
14E             //--------
14E             // Return
14E             //--------
14E C0          BBL 0
14F
14F         //====================================
14F         // Make Odd Number from Index
14F         //   Input Parameters
14F         //     RAMST[bank0][0x00][pos0:2] : Index
14F         //   Output Parameters
14F         //     R[12:14] = 2 * Index + 1
14F         //   Registers to be broken
14F         //     R6, R7
14F         //====================================
14F         INDEXODD:
14F             //------------------------------------
14F             // Select RAM at Bank0, Chip=0, Reg=0
14F             //------------------------------------
14F F0          CLB
150 FD          DCL        // Select Bank 0
151 26 00       FIM 3P 0   // {R6,R7}=0x00
153 27          SRC 3P     // Select Bank0, Chip=0, Reg=0
154             //------------------------
154             // Preparation to Add One
154             //------------------------
154 FA          STC        // CY=1
155             //-------------------------------------------
155             // Addition of Lowest Digit (Index + Index)
155             //-------------------------------------------
155 EE          RD2        // ACC=RAMST[bank0][0x00[pos2]
156 B7          XCH  7     // R7=ACC
157 A7          LD   7     // ACC=R7
158 87          ADD  7     // ACC=ACC+R7+CY
159 FB          DAA        // Decimal Adjust
15A BE          XCH 14     // R14=ACC
15B             //-------------------------------------------
15B             // Addition of Middle Digit (Index + Index)
15B             //-------------------------------------------
15B ED          RD1        // ACC=RAMST[bank0][0x00][pos1]
15C B7          XCH  7     // R7<->ACC
15D A7          LD   7     // ACC=R7
15E 87          ADD  7     // ACC=ACC+R7+CY
15F FB          DAA        // Decimal Adjust
160 BD          XCH 13     // R13=ACC
161             //-------------------------------------------
161             // Addition of Highest Digit (Index + Index)
161             //-------------------------------------------
161 EC          RD0        // ACC=RAMST[bank0][0x00][pos0]
162 B7          XCH  7     // R7<->ACC
163 A7          LD   7     // ACC=R7
164 87          ADD  7     // ACC=ACC+R7+CY
165 FB          DAA        // Decimal Adjust
166 BC          XCH 12     // R12=ACC
167             //---------
167             // Return
167             //---------
167 C0          BBL  0
168
168         //==========================================
168         // Printer Main Routine
168         //   Printout 500digits in Buffer RAMCH[bank0:1][]
168         //   Register to be broken
168         //     R3, R4: Loop Counter
168         //     R0, R1, R2, R11, R12, R13, R14, R15
168         //==========================================
168         PRINTER_MAIN:
168             //---------------------------
168             // Initialize Buffer Pointer
168             //---------------------------
168 51 75       JMS PRINTER_BUFPTR_INIT
16A             //----------------------
16A             // Repeat 5x10=50 times
16A             //----------------------
16A DB          LDM  16-5
16B B3          XCH  3 // R3=#-5(0xB)
16C         PRINTER_MAIN1:
16C D6          LDM  16-10
16D B4          XCH  4 // R4=#-10(0x6)
16E         PRINTER_MAIN2:
16E             //-------------------------------
16E             // Printout 10digits from Buffer
16E             //-------------------------------
16E 51 7F       JMS PRINTER_TEN_DIGIT
170             //-------------
170             // Repeat Loop
170             //-------------
170 74 6E       ISZ  4 PRINTER_MAIN2 // R4=R4+1, if NZ jump
172 73 6C       ISZ  3 PRINTER_MAIN1 // R3=R3+1, if NZ jump
174             //---------
174             // Return
174             //---------
174 C0          BBL  0
175
175         //==================================
175         // Initialize Buffer Pointer
175         //   Output Parameters
175         //     RAMST[bank0][chip0][reg1][0]: Bank No. of Buffer at Next
175         //     RAMST[bank0][chip0][reg1][1]: Addr H of Buffer at Next
175         //     RAMST[bank0][chip0][reg1][2]: Addr L of Buffer at Next
175         //   Register to be broken
175         //     R14, R15
175         //==================================
175         PRINTER_BUFPTR_INIT:
175             //----------------------
175             // Select RAM at Bank0
175             //----------------------
175 F0          CLB
176 FD          DCL
177             //----------------------
177             // Select Chip0 Reg1
177             //----------------------
177 2E 10       FIM 7P 0x10
179 2F          SRC 7P
17A             //----------------------
17A             // Initial Bank=0
17A             //----------------------
17A E4          WR0
17B             //----------------------
17B             // Initial Address=0x03
17B             //----------------------
17B E5          WR1
17C D3          LDM 3
17D E6          WR2
17E             //---------
17E             // Return
17E             //---------
17E C0          BBL  0
17F
17F         //==================================
17F         // Print 10 Digits
17F         //   Input Parameters
17F         //     RAMST[bank0][chip0][reg1][0]: Bank No. of Buffer at Start
17F         //     RAMST[bank0][chip0][reg1][1]: Addr H of Buffer at Start
17F         //     RAMST[bank0][chip0][reg1][2]: Addr L of Buffer at Start
17F         //   Output Parameters
17F         //     RAMST[bank0][chip0][reg1][0]: Bank No. of Buffer at Next
17F         //     RAMST[bank0][chip0][reg1][1]: Addr H of Buffer at Next
17F         //     RAMST[bank0][chip0][reg1][2]: Addr L of Buffer at Next
17F         //   Register to be broken
17F         //     R0: Drum Sector No.
17F         //     R1: A Digit taken from Buffer
17F         //     R2: Shift Out Data (0 or 1)
17F         //     R10: Shift Out Loop Counter
17F         //      R11, R12, R13, R14, R15
17F         //==================================
17F         PRINTER_TEN_DIGIT:
17F             //---------------------------------------------------
17F             // Wait for Drum Index Position, twice
17F             // (twice means to prevent overflow in FPGA buffer)
17F             // and Set Drum Sectror No. R0 to Zero
17F             //---------------------------------------------------
17F F0          CLB
180 B0          XCH  0
181         PRINTER_TEN_DIGIT00:
181 51 C1       JMS PRINTER_DRUM_SECTOR
183 A0          LD  0
184 1C 81       JCN AN PRINTER_TEN_DIGIT00
186         PRINTER_TEN_DIGIT01:
186 51 C1       JMS PRINTER_DRUM_SECTOR
188 A0          LD  0
189 1C 86       JCN AN PRINTER_TEN_DIGIT01
18B             //--------------------------
18B             // Proceed Buffer Pointer
18B             //--------------------------
18B 51 D1       JMS PRINTER_BUFPTR_ADD_TEN
18D             //-------------------------------
18D             // Main Loop (Drum Sector 0-9)
18D             //-------------------------------
18D         PRINTER_TEN_DIGIT1:
18D             //--------------------------------------
18D             // Shift Out Ten Digits to PRS8-PRS17
18D             // PRS18-PRS19 will be undefined, but OK
18D             //--------------------------------------
18D D6          LDM   6
18E BA          XCH  10 // R10=#-10(0x06) as Loop Counter
18F         PRINTER_TEN_DIGIT2:
18F             //--------------------------
18F             // Decrement Buffer Pointer
18F             //--------------------------
18F 51 E5       JMS PRINTER_BUFPTR_DEC
191             //--------------------------
191             // Take a Digit from Buffer
191             //--------------------------
191 51 F9       JMS PRINTER_BUFPTR_GET_DIGIT // R1=Digit
193             //-----------------------------------------------
193             // If the Digit is same as Current Sector No. R0,
193             // then Shift Out 1, else Shift Out 0
193             //-----------------------------------------------
193 A1          LD   1 // ACC=R1
194 F1          CLC
195 90          SUB  0 // ACC=ACC-R0
196 1C 9B       JCN AN PRINTER_TEN_DIGIT3 // if not equal, jump
198 D1          LDM 1 // ACC=1
199 41 9C       JUN PRINTER_TEN_DIGIT4
19B         PRINTER_TEN_DIGIT3:
19B F0          CLB   // ACC=0
19C         PRINTER_TEN_DIGIT4:
19C B2          XCH 2 // R2=ACC
19D 52 0A       JMS PRINTER_SHIFT_OUT
19F             //------------------------------------
19F             // Repeat the Shift Out Loop 10 times
19F             //------------------------------------
19F 7A 8F       ISZ 10 PRINTER_TEN_DIGIT2 // R10=R10+1, if NZ jump
1A1             //---------------------------
1A1             // Shift Out 0 to PRS0-PRS7
1A1             //---------------------------
1A1 F0          CLB
1A2 B2          XCH  2
1A3 52 0A       JMS PRINTER_SHIFT_OUT // PRS7
1A5 52 0A       JMS PRINTER_SHIFT_OUT // PRS6
1A7 52 0A       JMS PRINTER_SHIFT_OUT // PRS5
1A9 52 0A       JMS PRINTER_SHIFT_OUT // PRS4
1AB 52 0A       JMS PRINTER_SHIFT_OUT // PRS3
1AD 52 0A       JMS PRINTER_SHIFT_OUT // PRS2
1AF 52 0A       JMS PRINTER_SHIFT_OUT // PRS1
1B1 52 0A       JMS PRINTER_SHIFT_OUT // PRS0
1B3             //---------------
1B3             // Fire Hammers
1B3             //---------------
1B3 52 18       JMS PRINTER_HAMMER
1B5             //---------------------------
1B5             // Proceed Buffer Pointer
1B5             //---------------------------
1B5 51 D1       JMS PRINTER_BUFPTR_ADD_TEN
1B7             //---------------------------
1B7             // Wait for Next Drum Sector
1B7             // and Update Sector No. R0
1B7             //---------------------------
1B7 51 C1       JMS PRINTER_DRUM_SECTOR
1B9             //-----------------------------------
1B9             // If Drum Sector != 10, Repeat Loop
1B9             // (Skip Drum Sector 10, 11, 12)
1B9             //-----------------------------------
1B9 DA          LDM 10 // ACC=#10
1BA F1          CLC    // CY=0 (no borrow)
1BB 90          SUB  0 // ACC=ACC-R0
1BC 1C 8D       JCN AN PRINTER_TEN_DIGIT1
1BE             //-------------
1BE             // Paper Feed
1BE             //-------------
1BE 52 21       JMS PRINTER_PAPER_FEED
1C0             //---------
1C0             // Return
1C0             //---------
1C0 C0          BBL  0
1C1
1C1         //==================================
1C1         // Update Drum Sector
1C1         //   Input Parameters
1C1         //     R0: Drum Sector No.
1C1         //   Output Parameters
1C1         //     R0: Drum Sector No.
1C1         //   Register to be broken
1C1         //      R0, R14, R15
1C1         //==================================
1C1         PRINTER_DRUM_SECTOR:
1C1             //------------------------------------
1C1             // Wait for Sector signal becomes Low
1C1             //------------------------------------
1C1         PRINTER_DRUM_SECTOR1:
1C1 19 C1       JCN TN PRINTER_DRUM_SECTOR1
1C3             //-------------------------------------------
1C3             // Wait for Sector signal High (Rising Edge)
1C3             //-------------------------------------------
1C3         PRINTER_DRUM_SECTOR2:
1C3 11 C3       JCN TZ PRINTER_DRUM_SECTOR2
1C5             //--------------------------------
1C5             // Read ROM#2 IO0 (Index Signal)
1C5             //--------------------------------
1C5 2E 20       FIM  7P 0x20
1C7 2F          SRC  7P
1C8 EA          RDR
1C9             //--------------------------------------
1C9             // If Index Signal is Low, Incremnt R0
1C9             //--------------------------------------
1C9 F6          RAR
1CA 12 CE       JCN C1 PRINTER_DRUM_SECTOR3
1CC 60          INC  0
1CD             //---------
1CD             // Return
1CD             //---------
1CD C0          BBL  0
1CE         PRINTER_DRUM_SECTOR3:
1CE             //--------------------------------------
1CE             // If Index Signal is High, Clear R0
1CE             //--------------------------------------
1CE F0          CLB
1CF B0          XCH  0
1D0             //---------
1D0             // Return
1D0             //---------
1D0 C0          BBL  0
1D1
1D1         //==================================
1D1         // Add 10 to Buffer Pointer
1D1         //   Input Parameters
1D1         //     RAMST[bank0][chip0][reg1][0]: Bank No. of Buffer at Start
1D1         //     RAMST[bank0][chip0][reg1][1]: Addr H of Buffer at Start
1D1         //     RAMST[bank0][chip0][reg1][2]: Addr L of Buffer at Start
1D1         //   Output Parameters
1D1         //     RAMST[bank0][chip0][reg1][0]: Bank No. of Buffer at Next
1D1         //     RAMST[bank0][chip0][reg1][1]: Addr H of Buffer at Next
1D1         //     RAMST[bank0][chip0][reg1][2]: Addr L of Buffer at Next
1D1         //   Register to be broken
1D1         //     R14, R15
1D1         //==================================
1D1         PRINTER_BUFPTR_ADD_TEN:
1D1             //----------------------
1D1             // Select RAM at Bank0
1D1             //----------------------
1D1 F0          CLB
1D2 FD          DCL
1D3             //----------------------
1D3             // Select Chip0 Reg1
1D3             //----------------------
1D3 2E 10       FIM 7P 0x10
1D5 2F          SRC 7P
1D6             //-------------------
1D6             // Add Addr L and 10
1D6             //-------------------
1D6 DA          LDM 10
1D7 BF          XCH 15
1D8 EE          RD2
1D9 F1          CLC
1DA 8F          ADD 15
1DB E6          WR2
1DC             //-------------------
1DC             // Add Addr H and CY
1DC             //-------------------
1DC D0          LDM 0
1DD BF          XCH 15
1DE ED          RD1
1DF 8F          ADD 15
1E0 E5          WR1
1E1             //-------------------
1E1             // Add Bank and CY
1E1             //-------------------
1E1 EC          RD0
1E2 8F          ADD 15
1E3 E4          WR0
1E4             //---------
1E4             // Return
1E4             //---------
1E4 C0          BBL  0
1E5
1E5         //==================================
1E5         // Decrement Buffer Pointer
1E5         //   Input Parameters
1E5         //     RAMST[bank0][chip0][reg1][0]: Bank No. of Buffer at Start
1E5         //     RAMST[bank0][chip0][reg1][1]: Addr H of Buffer at Start
1E5         //     RAMST[bank0][chip0][reg1][2]: Addr L of Buffer at Start
1E5         //   Output Parameters
1E5         //     RAMST[bank0][chip0][reg1][0]: Bank No. of Buffer at Next
1E5         //     RAMST[bank0][chip0][reg1][1]: Addr H of Buffer at Next
1E5         //     RAMST[bank0][chip0][reg1][2]: Addr L of Buffer at Next
1E5         //   Register to be broken
1E5         //     R14, R15
1E5         //==================================
1E5         PRINTER_BUFPTR_DEC:
1E5             //---------------------
1E5             // Select RAM at Bank0
1E5             //---------------------
1E5 F0          CLB
1E6 FD          DCL
1E7             //-------------------
1E7             // Select Chip0 Reg1
1E7             //-------------------
1E7 2E 10       FIM 7P 0x10
1E9 2F          SRC 7P
1EA             //--------------------------
1EA             // Subtract One from Addr L
1EA             //--------------------------
1EA D0          LDM 0
1EB BF          XCH 15
1EC FA          STC    // CY=1, borrow
1ED EE          RD2
1EE 9F          SUB 15
1EF E6          WR2
1F0 F3          CMC
1F1             //---------------
1F1             // Borrow Chain
1F1             //---------------
1F1 ED          RD1
1F2 9F          SUB 15
1F3 E5          WR1
1F4 F3          CMC
1F5 EC          RD0
1F6 9F          SUB 15
1F7 E4          WR0
1F8             //---------
1F8             // Return
1F8             //---------
1F8 C0          BBL  0
1F9
1F9         //==================================
1F9         // Get a Digit from Buffer
1F9         //   Input Parameters
1F9         //     RAMST[bank0][chip0][reg1][0]: Bank No. of Buffer at Start
1F9         //     RAMST[bank0][chip0][reg1][1]: Addr H of Buffer at Start
1F9         //     RAMST[bank0][chip0][reg1][2]: Addr L of Buffer at Start
1F9         //   Output Parameters
1F9         //     RAMST[bank0][chip0][reg1][0]: Bank No. of Buffer at Next
1F9         //     RAMST[bank0][chip0][reg1][1]: Addr H of Buffer at Next
1F9         //     RAMST[bank0][chip0][reg1][2]: Addr L of Buffer at Next
1F9         //     R1: Digit
1F9         //   Register to be broken
1F9         //      R11, R12, R13, R14, R15
1F9         //==================================
1F9         PRINTER_BUFPTR_GET_DIGIT:
1F9             //----------------------
1F9             // Select RAM at Bank0
1F9             //----------------------
1F9 F0          CLB
1FA FD          DCL
1FB             //----------------------
1FB             // Select Chip0 Reg1
1FB             //----------------------
1FB 2E 10       FIM 7P 0x10
1FD 2F          SRC 7P
1FE             //-------------------------------
1FE             // Set Bank No. of Buffer in R11
1FE             //-------------------------------
1FE EC          RD0
1FF BB          XCH 11
200             //-------------------------------
200             // Set Addr of Buffer in R6P
200             //-------------------------------
200 ED          RD1
201 BC          XCH 12
202 EE          RD2
203 BD          XCH 13
204             //-------------------------------------------
204             // Read a Digit from Buffer and Set it in R1
204             //-------------------------------------------
204 AB          LD  11
205 FD          DCL
206 2D          SRC 6P
207 E9          RDM
208 B1          XCH  1
209             //---------
209             // Return
209             //---------
209 C0          BBL  0
20A
20A         //==================================
20A         // Shift Out One Bit
20A         //   Input Parameters
20A         //     R2: A bit (0 or 1) to be shifted out
20A         //   Registers to be broken
20A         //     R14, R15
20A         //==================================
20A         PRINTER_SHIFT_OUT:
20A             //-----------------------------------
20A             // ROM#0 bit2=CLOCK, bit1=DATAIN
20A             // Set Shift Out Data and Set Clock
20A             //-----------------------------------
20A 2E 00       FIM 7P 0x00
20C 2F          SRC 7P
20D A2          LD  2 // R2=0 or 1
20E 14 13       JCN AZ PRINTER_SHIFT_OUT1
210 D6          LDM 6 // ACC=0110
211 42 14       JUN PRINTER_SHIFT_OUT2
213         PRINTER_SHIFT_OUT1:
213 D4          LDM 4 // ACC=0100
214         PRINTER_SHIFT_OUT2:
214 E2          WRR
215             //-----------------------------------
215             // Clear Shift Out Data and Clock
215             //-----------------------------------
215 F0          CLB
216 E2          WRR
217             //--------
217             // Return
217             //--------
217 C0          BBL  0
218
218         //==================================
218         // Fire Hammers
218         //   Registers to be broken
218         //     R14, R15
218         //==================================
218         PRINTER_HAMMER:
218             //--------------------
218             // RAM#0 bit1=HAMMER
218             //--------------------
218 F0          CLB
219 FD          DCL
21A 2E 00       FIM 7P 0x00
21C D2          LDM  2
21D E1          WMP // Set
21E F0          CLB
21F E1          WMP // Clear
220             //---------
220             // Return
220             //---------
220 C0          BBL  0
221
221         //==================================
221         // Paper Feed
221         //   Registers to be broken
221         //     R14, R15
221         //==================================
221         PRINTER_PAPER_FEED:
221             //-----------------------
221             // RAM#0 bit3=PAPER_FEED
221             //-----------------------
221 F0          CLB
222 FD          DCL
223 2E 00       FIM 7P 0x00
225 D8          LDM  8
226 E1          WMP // Set
227 F0          CLB
228 E1          WMP // Clear
229             //---------
229             // Return
229             //---------
229 C0          BBL  0
22A
22A         END
22A         //==========================================
22A         // End of Program
22A         //==========================================
-----Label Table-----
MAIN     = 0x0000
RESET    = 0x0000
MAIN1    = 0x0004
MAIN2    = 0x0009
MAIN_LOOP = 0x0030
PIADD    = 0x0068
PISUB    = 0x006C
PIEND    = 0x006E
PRINTOUT = 0x0072
CONVERGED = 0x0072
STOP     = 0x0074
LONGADD  = 0x0076
LONGADD1 = 0x0079
LONGADD2 = 0x007B
LONGSUB  = 0x00A7
LONGSUB1 = 0x00AA
LONGSUB2 = 0x00AC
LONGDIV  = 0x00DA
LONGDIV1 = 0x00E2
LONGDIV2 = 0x00E4
LONGDIV3 = 0x00F7
PARTDIV  = 0x00FF
PARTDIV1 = 0x0101
PARTDIV2 = 0x0106
PARTADD  = 0x010C
PARTSUB  = 0x0120
INDEXINC = 0x013C
INDEXODD = 0x014F
PRINTER_MAIN = 0x0168
PRINTER_MAIN1 = 0x016C
PRINTER_MAIN2 = 0x016E
PRINTER_BUFPTR_INIT = 0x0175
PRINTER_TEN_DIGIT = 0x017F
PRINTER_TEN_DIGIT00 = 0x0181
PRINTER_TEN_DIGIT01 = 0x0186
PRINTER_TEN_DIGIT1 = 0x018D
PRINTER_TEN_DIGIT2 = 0x018F
PRINTER_TEN_DIGIT3 = 0x019B
PRINTER_TEN_DIGIT4 = 0x019C
PRINTER_DRUM_SECTOR1 = 0x01C1
PRINTER_DRUM_SECTOR = 0x01C1
PRINTER_DRUM_SECTOR2 = 0x01C3
PRINTER_DRUM_SECTOR3 = 0x01CE
PRINTER_BUFPTR_ADD_TEN = 0x01D1
PRINTER_BUFPTR_DEC = 0x01E5
PRINTER_BUFPTR_GET_DIGIT = 0x01F9
PRINTER_SHIFT_OUT = 0x020A
PRINTER_SHIFT_OUT1 = 0x0213
PRINTER_SHIFT_OUT2 = 0x0214
PRINTER_HAMMER = 0x0218
PRINTER_PAPER_FEED = 0x0221
-----End of Label Table-----
Total Error = 0
 */

//===========================================================
// End of Program
//===========================================================
