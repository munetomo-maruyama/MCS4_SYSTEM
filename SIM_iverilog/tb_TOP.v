//===========================================================
// MCS-4 Project
//-----------------------------------------------------------
// File Name   : mcs4_tb.v
// Description : Testbench of MCS-4 System
//-----------------------------------------------------------
// History :
// Rev.01 2025.05.19 M.Maruyama First Release
//-----------------------------------------------------------
// Copyright (C) 2025 M.Maruyama
//===========================================================

`timescale 1ns/100ps
`define TB_CYCLE 1000 //ns (1MHz)
`define TB_FINISH_COUNT 2000000 //cyc

//---------------
// State Number
//---------------
`define A1 0
`define A2 1
`define A3 2
`define M1 3
`define M2 4
`define X1 5
`define X2 6
`define X3 7

//------------------
// Top of Test Bench
//------------------
module TB_TOP();

integer i;

//-----------------------------
// Generate Wave File to Check
//-----------------------------
initial
begin
    $dumpfile("tb.vcd");
    $dumpvars(0, TB_TOP);
end

//-------------------------------
// Generate Clock
//-------------------------------
reg tb_clk;
//
initial tb_clk = 1'b0;
always #(`TB_CYCLE / 2) tb_clk = ~tb_clk;

//--------------------------
// Generate Reset
//--------------------------
reg tb_res;
//
initial
begin
    tb_res = 1'b0;
	# (`TB_CYCLE * 4)
    tb_res = 1'b1;
	# (`TB_CYCLE * 100)
    tb_res = 1'b0;	
end

//----------------------
// Cycle Counter
//----------------------
reg [31:0] tb_cycle_counter;
//
always @(posedge tb_clk, posedge tb_res)
begin
    if (tb_res)
        tb_cycle_counter <= 32'h0;
    else
        tb_cycle_counter <= tb_cycle_counter + 32'h1;
end
//
always @*
begin
    if (tb_cycle_counter == `TB_FINISH_COUNT)
    begin
        $display("***** SIMULATION TIMEOUT ***** at %d", tb_cycle_counter);
        $finish;
    end
end

//-----------------------
// Signals in TestBench
//-----------------------
wire        sync_n;
wire        cm_rom_n;
wire [ 3:0] cm_ram_n;
wire        test;
//
wire [ 3:0] data;
wire [ 3:0] c_data_i;
wire [ 3:0] c_data_o;
wire        c_data_oe;
wire [ 3:0] s_data_i;
wire [ 3:0] s_data_o;
wire        s_data_oe;
//
reg  [31:0] port_keyprt_cmd;
wire [31:0] port_keyprt_res;

//----------------------
// MCS4 Data Bus
//----------------------
pullup(data[0]);
pullup(data[1]);
pullup(data[2]);
pullup(data[3]);
//
assign c_data_i = data;
assign s_data_i = data;
assign data[0] = (c_data_oe & ~c_data_o[0])? 1'b0 : 1'bz; // open-drain
assign data[1] = (c_data_oe & ~c_data_o[1])? 1'b0 : 1'bz; // open-drain
assign data[2] = (c_data_oe & ~c_data_o[2])? 1'b0 : 1'bz; // open-drain
assign data[3] = (c_data_oe & ~c_data_o[3])? 1'b0 : 1'bz; // open-drain
assign data[0] = (s_data_oe & ~s_data_o[0])? 1'b0 : 1'bz; // open-drain
assign data[1] = (s_data_oe & ~s_data_o[1])? 1'b0 : 1'bz; // open-drain
assign data[2] = (s_data_oe & ~s_data_o[2])? 1'b0 : 1'bz; // open-drain
assign data[3] = (s_data_oe & ~s_data_o[3])? 1'b0 : 1'bz; // open-drain

//---------------------------------
// MCS-4 CPU Chip i4004
//---------------------------------
MCS4_CPU U_MCS4_CPU
(
    .CLK   (tb_clk),  // clock
    .RES_N (~tb_res), // reset_n
    //
    .SYNC_N   (sync_n),   // Sync Signal
    //
    .DATA_I   (c_data_i ), // Data Input
    .DATA_O   (c_data_o ), // Data Output
    .DATA_OE  (c_data_oe), // Data Output Enable
    //
    .CM_ROM_N (cm_rom_n), // Memory Control for ROM
    .CM_RAM_N (cm_ram_n), // Memory Control for RAM
    .TEST     (test)      // Test Input
);

//---------------------------------------------
// MCS-4 System ROM + RAM + Key&Printer I/F
//---------------------------------------------
MCS4_SYS U_MCS4_SYS
(
    // CPU Interfface (i4004)
    .CLK   (tb_clk),  // clock
    .RES_N (~tb_res), // reset_n
    //
    .SYNC_N   (sync_n),   // Sync Signal
    //
    .DATA_I   (s_data_i ), // Data Input
    .DATA_O   (s_data_o ), // Data Output
    .DATA_OE  (s_data_oe), // Data Output Enable
    //
    .CM_ROM_N (cm_rom_n), // Memory Control for ROM
    .CM_RAM_N (cm_ram_n), // Memory Control for RAM
    .TEST     (test),     // Test Input
    //
    // Calculator Command : Host MCU (UI) --> MCS4_SYS
    .PORT_KEYPRT_CMD (port_keyprt_cmd),
    //
    // Calculator Response : MCS4_SYS --> Host MCU (UI)
    .PORT_KEYPRT_RES (port_keyprt_res),
    //
    // Initialization of ROM
    .ROM_INIT_ENB   (1'b0),
    .ROM_INIT_ADDR  (12'h000),
    .ROM_INIT_RE    (1'b0),
    .ROM_INIT_WE    (1'b0),
    .ROM_INIT_WDATA (8'h00),
    .ROM_INIT_RDATA ()    
);

//----------------------------
// Simulation Stop Condition
//----------------------------
wire [7:0] opropa0;
wire       multi_cycle;
wire       state_x3;
//
assign opropa0     = U_MCS4_CPU.opropa0;
assign multi_cycle = U_MCS4_CPU.multi_cycle;
assign state_x3    = U_MCS4_CPU.state[`X3];
//
always @*
begin
    if (state_x3 & ~multi_cycle & (opropa0 == 8'hff))
    begin
        $display("***** SIMULATION FINISHED ***** at %d", tb_cycle_counter);
        $finish;
    end
end

//------------------------
// Dump CPU Resource
//------------------------
integer handle_dump;
//
wire        state_a1;
wire [11:0] pc;
wire [ 3:0] acc;
wire        cy;
reg  [ 3:0] r[0:15];
wire [ 2:0] dcl;
wire [ 7:0] src;
//
initial handle_dump = $fopen("dump.sim");
//
assign state_a1 = U_MCS4_CPU.state[`A1];
assign pc       = U_MCS4_CPU.pc;
assign acc      = U_MCS4_CPU.acc;
assign cy       = U_MCS4_CPU.cy;
always @* for (i = 0; i < 16; i = i + 1) r[i] = U_MCS4_CPU.r[i];
assign dcl =  U_MCS4_CPU.dcl;
assign src =  U_MCS4_CPU.src;
//
always @(posedge tb_clk)
begin
    if (state_a1 & ~multi_cycle)
    begin
        $fwrite(handle_dump, "  PC=%03H ACC=%01X CY=%01X", pc, acc, cy);
        $fwrite(handle_dump, " R0-15=");
        for (i = 0; i < 16; i = i + 1) $fwrite(handle_dump, "%01X", r[i]);
        $fwrite(handle_dump, " DCL=%01X SRC=%02X\n", dcl, src);
    end
end

//--------------------------------
// Test Pattern (Stimulus)
//--------------------------------
reg [15:0] rdata;
//
initial
begin
    //
    // Initialize
    port_keyprt_cmd = 32'h00000000;
    //
    // Wait for Reset Done
    while(tb_res == 1'b0) #(`TB_CYCLE);
    while(tb_res == 1'b1) #(`TB_CYCLE);
    #(`TB_CYCLE);
    //
    // Key and Printer
        #(`TB_CYCLE * 50000);
    //----------------------------------------------------------------
    port_keyprt_cmd = 32'h8000009b; // 1
        #(`TB_CYCLE * 50000);
    port_keyprt_cmd = 32'h80000000; // OFF
        #(`TB_CYCLE * 50000);
    //----------------------------------------------------------------
    port_keyprt_cmd = 32'h80000097; // 2
        #(`TB_CYCLE * 50000);
    port_keyprt_cmd = 32'h80000000; // OFF
        #(`TB_CYCLE * 50000);
    //----------------------------------------------------------------
    port_keyprt_cmd = 32'h8000008e; // +
        #(`TB_CYCLE * 50000);
    port_keyprt_cmd = 32'h80000000; // OFF
        #(`TB_CYCLE * 50000);
    //----------------------------------------------------------------
    port_keyprt_cmd = 32'h80000093; // 3
        #(`TB_CYCLE * 50000);
    port_keyprt_cmd = 32'h80000000; // OFF
        #(`TB_CYCLE * 50000);
    //----------------------------------------------------------------
    port_keyprt_cmd = 32'h8000009a; // 4
        #(`TB_CYCLE * 50000);
    port_keyprt_cmd = 32'h80000000; // OFF
        #(`TB_CYCLE * 50000);
    //----------------------------------------------------------------
    port_keyprt_cmd = 32'h8000008e; // +
  //port_keyprt_cmd = 32'h8000008d; // -
        #(`TB_CYCLE * 50000);
    port_keyprt_cmd = 32'h80000000; // OFF
        #(`TB_CYCLE * 50000);
    //----------------------------------------------------------------
    port_keyprt_cmd = 32'h8000008c; // = 
        #(`TB_CYCLE * 50000);
    port_keyprt_cmd = 32'h80000000; // OFF
        #(`TB_CYCLE * 50000);
    //----------------------------------------------------------------
    port_keyprt_cmd = 32'h80008000; // FIFO POP 
        #(`TB_CYCLE * 4);
    if (port_keyprt_res != 32'h80002c01) // col=...0000, row=11
    begin
        // Error
        $display("##### Unexpected port_keyprt_res ##### at %d", tb_cycle_counter);
        #(`TB_CYCLE * 10);
        $finish;
    end
        #(`TB_CYCLE * 10000);
    port_keyprt_cmd = 32'h80000000; // OFF
        #(`TB_CYCLE * 10000);
    //----------------------------------------------------------------
    port_keyprt_cmd = 32'h80008000; // FIFO POP 
        #(`TB_CYCLE * 4);
    if (port_keyprt_res != 32'h80003001) // col=...0000, row=12
    begin
        // Error
        $display("##### Unexpected port_keyprt_res ##### at %d", tb_cycle_counter);
        #(`TB_CYCLE * 10);
        $finish;
    end
        #(`TB_CYCLE * 10000);
    port_keyprt_cmd = 32'h80000000; // OFF
        #(`TB_CYCLE * 10000);
    //----------------------------------------------------------------
        port_keyprt_cmd = 32'h80008000; // FIFO POP 
        #(`TB_CYCLE * 4);
    if (port_keyprt_res != 32'h80000001) // col=...0000, row=0
    begin
        // Error
        $display("##### Unexpected port_keyprt_res ##### at %d", tb_cycle_counter);
        #(`TB_CYCLE * 10);
        $finish;
    end
        #(`TB_CYCLE * 10000);
    port_keyprt_cmd = 32'h80000000; // OFF
        #(`TB_CYCLE * 10000);
    //----------------------------------------------------------------
    port_keyprt_cmd = 32'h80008000; // FIFO POP 
        #(`TB_CYCLE * 4);
    if (port_keyprt_res != 32'h80028401) // col=...1010, row=1 (...1__+)
    begin
        // Error
        $display("##### Unexpected port_keyprt_res ##### at %d", tb_cycle_counter);
        #(`TB_CYCLE * 10);
        $finish;
    end
        #(`TB_CYCLE * 10000);
    port_keyprt_cmd = 32'h80000000; // OFF
        #(`TB_CYCLE * 10000);
    //----------------------------------------------------------------
    port_keyprt_cmd = 32'h80008000; // FIFO POP 
        #(`TB_CYCLE * 4);
    if (port_keyprt_res != 32'h80010801) // col=...0100, row=2 (..._2__)
    begin
        // Error
        $display("##### Unexpected port_keyprt_res ##### at %d", tb_cycle_counter);
        #(`TB_CYCLE * 10);
        $finish;
    end
        #(`TB_CYCLE * 10000);
    port_keyprt_cmd = 32'h80000000; // OFF
        #(`TB_CYCLE * 10000);
    //----------------------------------------------------------------
    port_keyprt_cmd = 32'h80008000; // FIFO POP 
        #(`TB_CYCLE * 4);
    if (port_keyprt_res != 32'h80000c01) // col=...0000, row=3
    begin
        // Error
        $display("##### Unexpected port_keyprt_res ##### at %d", tb_cycle_counter);
        #(`TB_CYCLE * 10);
        $finish;
    end
        #(`TB_CYCLE * 10000);
    port_keyprt_cmd = 32'h80000000; // OFF
        #(`TB_CYCLE * 10000);
    //----------------------------------------------------------------
    port_keyprt_cmd = 32'h80008000; // FIFO POP 
        #(`TB_CYCLE * 4);
    if (port_keyprt_res != 32'h80001001) // col=...0000, row=4
    begin
        // Error
        $display("##### Unexpected port_keyprt_res ##### at %d", tb_cycle_counter);
        #(`TB_CYCLE * 10);
        $finish;
    end
        #(`TB_CYCLE * 10000);
    port_keyprt_cmd = 32'h80000000; // OFF
        #(`TB_CYCLE * 10000);
    //----------------------------------------------------------------
    port_keyprt_cmd = 32'h80008000; // FIFO POP 
        #(`TB_CYCLE * 4);
    if (port_keyprt_res != 32'h80001401) // col=...000, row=5
    begin
        // Error
        $display("##### Unexpected port_keyprt_res ##### at %d", tb_cycle_counter);
        #(`TB_CYCLE * 10);
        $finish;
    end
        #(`TB_CYCLE * 10000);
    port_keyprt_cmd = 32'h80000000; // OFF
        #(`TB_CYCLE * 10000);
    //----------------------------------------------------------------
    //
    // Finish
        #(`TB_CYCLE * 1000000);
    $display("***** STIMULAS FINISHED ***** at %d", tb_cycle_counter);
    $finish;
end

endmodule
//===========================================================
// End of File
//===========================================================
