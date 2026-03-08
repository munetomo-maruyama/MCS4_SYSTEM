//altclkctrl CBX_SINGLE_OUTPUT_FILE="ON" CLOCK_TYPE="External Clock Output" DEVICE_FAMILY="MAX 10" ENA_REGISTER_MODE="double register" USE_GLITCH_FREE_SWITCH_OVER_IMPLEMENTATION="OFF" ena inclk outclk
//VERSION_BEGIN 24.1 cbx_altclkbuf 2025:03:05:20:06:36:SC cbx_cycloneii 2025:03:05:20:06:36:SC cbx_lpm_add_sub 2025:03:05:20:06:36:SC cbx_lpm_compare 2025:03:05:20:06:36:SC cbx_lpm_decode 2025:03:05:20:06:36:SC cbx_lpm_mux 2025:03:05:20:06:36:SC cbx_mgl 2025:03:05:20:07:01:SC cbx_nadder 2025:03:05:20:06:36:SC cbx_stratix 2025:03:05:20:06:36:SC cbx_stratixii 2025:03:05:20:06:36:SC cbx_stratixiii 2025:03:05:20:06:36:SC cbx_stratixv 2025:03:05:20:06:36:SC  VERSION_END
// synthesis VERILOG_INPUT_VERSION VERILOG_2001
// altera message_off 10463



// Copyright (C) 2025  Altera Corporation. All rights reserved.
//  Your use of Altera Corporation's design tools, logic functions 
//  and other software and tools, and any partner logic 
//  functions, and any output files from any of the foregoing 
//  (including device programming or simulation files), and any 
//  associated documentation or information are expressly subject 
//  to the terms and conditions of the Altera Program License 
//  Subscription Agreement, the Altera Quartus Prime License Agreement,
//  the Altera IP License Agreement, or other applicable license
//  agreement, including, without limitation, that your use is for
//  the sole purpose of programming logic devices manufactured by
//  Altera and sold by Altera or its authorized distributors.  Please
//  refer to the Altera Software License Subscription Agreements 
//  on the Quartus Prime software download page.



//synthesis_resources = clkctrl 1 
//synopsys translate_off
`timescale 1 ps / 1 ps
//synopsys translate_on
module  CLKCTRL_altclkctrl_0_sub
	( 
	ena,
	inclk,
	outclk) /* synthesis synthesis_clearbox=1 */;
	input   ena;
	input   [3:0]  inclk;
	output   outclk;
`ifndef ALTERA_RESERVED_QIS
// synopsys translate_off
`endif
	tri1   ena;
	tri0   [3:0]  inclk;
`ifndef ALTERA_RESERVED_QIS
// synopsys translate_on
`endif

	wire  wire_clkctrl1_outclk;
	wire [1:0]  clkselect;
	wire  [1:0]  clkselect_wire;
	wire  [3:0]  inclk_wire;

	fiftyfivenm_clkctrl   clkctrl1
	( 
	.clkselect(clkselect_wire),
	.ena(ena),
	.inclk(inclk_wire),
	.outclk(wire_clkctrl1_outclk)
	// synopsys translate_off
	,
	.devclrn(1'b1),
	.devpor(1'b1)
	// synopsys translate_on
	);
	defparam
		clkctrl1.clock_type = "External Clock Output",
		clkctrl1.ena_register_mode = "double register",
		clkctrl1.lpm_type = "fiftyfivenm_clkctrl";
	assign
		clkselect = {2{1'b0}},
		clkselect_wire = {clkselect},
		inclk_wire = {inclk},
		outclk = wire_clkctrl1_outclk;
	initial/*synthesis enable_verilog_initial_construct*/
 	begin
		$display("Warning: MGL_INTERNAL_WARNING: ( The parameter value is not one of the pre-specified values in the value list.) altclkctrl|stratixii_clkctrl inst clkctrl1|ena_register_mode The value assigned is double register and the valid value list is none|falling edge");
	end
endmodule //CLKCTRL_altclkctrl_0_sub
//VALID FILE // (C) 2001-2025 Altera Corporation. All rights reserved.
// Your use of Altera Corporation's design tools, logic functions and other 
// software and tools, and its AMPP partner logic functions, and any output 
// files from any of the foregoing (including device programming or simulation 
// files), and any associated documentation or information are expressly subject 
// to the terms and conditions of the Altera Program License Subscription 
// Agreement, Altera IP License Agreement, or other applicable 
// license agreement, including, without limitation, that your use is for the 
// sole purpose of programming logic devices manufactured by Altera and sold by 
// Altera or its authorized distributors.  Please refer to the applicable 
// agreement for further details.



// synopsys translate_off
`timescale 1 ps / 1 ps
// synopsys translate_on
module  CLKCTRL_altclkctrl_0  (
    inclk,
    outclk);

    input    inclk;
    output   outclk;

    wire  sub_wire0;
    wire  outclk;
    wire  sub_wire1;
    wire  sub_wire2;
    wire [3:0] sub_wire3;
    wire [2:0] sub_wire4;

    assign  outclk = sub_wire0;
    assign  sub_wire1 = 1'h1;
    assign  sub_wire2 = inclk;
    assign sub_wire3[3:0] = {sub_wire4, sub_wire2};
    assign sub_wire4[2:0] = 3'h0;

    CLKCTRL_altclkctrl_0_sub  CLKCTRL_altclkctrl_0_sub_component (
                .ena (sub_wire1),
                .inclk (sub_wire3),
                .outclk (sub_wire0));

endmodule