//===========================================================
// MCS-4 Project
//-----------------------------------------------------------
// File Name   : fpga_top.v
// Description : MCS-4 System implemented in a FPGA
//-----------------------------------------------------------
// History :
// Rev.01 2025.05.25 M.Maruyama First Release
//-----------------------------------------------------------
// Copyright (C) 2025 M.Maruyama
//===========================================================

// < FPGA Board Pin Assignment>
// Pin01 C1  TDI            D0
// Pin02 E1  CLK0p          D1
// Pin03 C5  PLL_R_CLKOUTp  D2
// Pin04 B6  PLL_R_CLKOUTp  D3
// Pin05 C6  CLK3n          CLK
// Pin06 D5  CLK3p
// Pin07 C3  TMS            /SYNC
// Pin08 GND                GND
// Pin09 D6  CLK2p          /RESET
// Pin10 D3  TCK            TEST
// Pin11 E6  CLK2n          /CM_ROM
// Pin12 F4                 /CM_RAM3
// Pin13 D2  TDO            /CM_RAM2
// Pin14 E3                 /CM_RAM1
// Pin15 D1  CLK0n          /CM_RAM0
// Pin16 VCC                VCC

//---------------------------------
// FPGA TOP
//---------------------------------
module FPGA_TOP
(
    input  wire CLK,   // Clock Input
    input  wire RES_N, // Reset Input (Negative)
    //
    output wire        SYNC_N,   // MCS4_CPU SYNC_N Output
    input  wire        TEST,     // MCS4_CPU TEST Input
    output wire        CM_ROM_N, // MCS4_CPU CM_ROM_N Output
    output wire [ 3:0] CM_RAM_N, // MCS4_CPU CM_RAM_N Output
    inout  wire [ 3:0] DATA      // MCS4_CPU DATA Inout
    //
    ,
    output reg  CLKOUT
);

//------------------------------
// Internal Oscillator (Trial)
//------------------------------
wire oscena;
wire oscclk;
reg  oscclk_div_2;
assign oscena = 1'b1;
//
OSC U_OSC
(
    .oscena (oscena),
	.clkout (oscclk)
);
//
always @(posedge oscclk, negedge RES_N)
begin
    if (~RES_N)
        oscclk_div_2 <= 1'b0;
    else
        oscclk_div_2 <= ~oscclk_div_2;
end
//
//CLKCTRL U_CLKCTRL
//(
//    .inclk  (osc_clk_div_2),
//    .outclk (glbclk)
//);	
//
always @(posedge oscclk_div_2, negedge RES_N)
begin
    if (~RES_N)
        CLKOUT <= 1'b0;
    else
        CLKOUT <= ~CLKOUT;
end

//--------------------------------------------------
// DATA I/O (Open Drain)
//--------------------------------------------------
wire [3:0] data_i;
wire [3:0] data_o;
wire       data_oe;
//
assign DATA[0] = (data_oe & ~data_o[0])? 1'b0 : 1'bz; 
assign DATA[1] = (data_oe & ~data_o[1])? 1'b0 : 1'bz; 
assign DATA[2] = (data_oe & ~data_o[2])? 1'b0 : 1'bz; 
assign DATA[3] = (data_oe & ~data_o[3])? 1'b0 : 1'bz; 
//
assign data_i[0] = DATA[0];
assign data_i[1] = DATA[1];
assign data_i[2] = DATA[2];
assign data_i[3] = DATA[3];

//---------------------------------
// MCS-4 CPU i4004
//---------------------------------
MCS4_CPU U_MCS4_CPU
(
    .CLK   (CLK),   // clock
    .RES_N (RES_N), // reset_n
    //
    .SYNC_N   (SYNC_N),   // Sync Signal
    //
    .DATA_I   (data_i ), // Data Input
    .DATA_O   (data_o ), // Data Output
    .DATA_OE  (data_oe), // Data Output Enable
    //
    .CM_ROM_N (CM_ROM_N), // Memory Control for ROM
    .CM_RAM_N (CM_RAM_N), // Memory Control for RAM
    .TEST     (TEST)      // Test Input
);

endmodule
//===========================================================
// End of File
//===========================================================
