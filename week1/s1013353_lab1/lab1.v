// Copyright (C) 1991-2010 Altera Corporation
// Your use of Altera Corporation's design tools, logic functions 
// and other software and tools, and its AMPP partner logic 
// functions, and any output files from any of the foregoing 
// (including device programming or simulation files), and any 
// associated documentation or information are expressly subject 
// to the terms and conditions of the Altera Program License 
// Subscription Agreement, Altera MegaCore Function License 
// Agreement, or other applicable license agreement, including, 
// without limitation, that your use is for the sole purpose of 
// programming logic devices manufactured by Altera and sold by 
// Altera or its authorized distributors.  Please refer to the 
// applicable agreement for further details.

// PROGRAM		"Quartus II"
// VERSION		"Version 10.1 Build 153 11/29/2010 SJ Web Edition"
// CREATED		"Fri Feb 26 11:15:37 2016"

module lab1(
	SW_0,
	SW_1,
	SW_2,
	SW_3,
	SW_4,
	SW_5,
	SW_6,
	SW_7,
	Button_0,
	Button_1,
	Button_2,
	SEG7_0_D0,
	SEG7_0_D1,
	SEG7_0_D2,
	SEG7_0_D3,
	SEG7_0_D4,
	SEG7_0_D5,
	SEG7_0_D6,
	SEG7_0_D7,
	LED_0,
	LED_1,
	LED_2
);


input wire	SW_0;
input wire	SW_1;
input wire	SW_2;
input wire	SW_3;
input wire	SW_4;
input wire	SW_5;
input wire	SW_6;
input wire	SW_7;
input wire	Button_0;
input wire	Button_1;
input wire	Button_2;
output wire	SEG7_0_D0;
output wire	SEG7_0_D1;
output wire	SEG7_0_D2;
output wire	SEG7_0_D3;
output wire	SEG7_0_D4;
output wire	SEG7_0_D5;
output wire	SEG7_0_D6;
output wire	SEG7_0_D7;
output wire	LED_0;
output wire	LED_1;
output wire	LED_2;





assign	SEG7_0_D0 =  ~SW_0;

assign	SEG7_0_D1 =  ~SW_1;

assign	LED_2 =  ~Button_2;

assign	SEG7_0_D2 =  ~SW_2;

assign	SEG7_0_D3 =  ~SW_3;

assign	SEG7_0_D4 =  ~SW_4;

assign	SEG7_0_D5 =  ~SW_5;

assign	SEG7_0_D6 =  ~SW_6;

assign	SEG7_0_D7 =  ~SW_7;

assign	LED_0 =  ~Button_0;

assign	LED_1 =  ~Button_1;


endmodule
