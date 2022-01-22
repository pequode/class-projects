`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/12/2021 02:13:52 AM
// Design Name: 
// Module Name: Parm_TLM_tb
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////
//`define	N		6
module Parm_TLM_tb;
	// Inputs
	// initalize vars
	reg [6:0]a;
	reg [6:0]b;
	reg c_in;
    reg clk;
    reg mux;
	// Outputs
	wire c_out;
	wire [6:0]qout;
    wire c_outv;
	wire [6:0]qoutv;
	// Instantiate the Unit Under Test (UUT)





	Parm_TopLevMod#(.N(7)) aa(.clk(clk),
                             .q_out(qout),
                             .c_in(c_in),
                             .cout(c_out),
                             .a(a),
                             .b(b),
                             .mux_in(mux));
    VerificationAdd#(.N(7)) ab(.clk(clk),
                             .q_out(qoutv),
                             .c_in(c_in),
                             .cout(c_outv),
                             .a(a),
                             .b(b),.mux_in(mux));
	initial begin
		// Initialize Inputs
		a = 14;
		b = 16;
		c_in = 0;
		clk = 0;
		mux = 1; 
		#100;
		a = 14;
		b = 12;
		mux = 1; 
		#100;
		a = 14;
		b = 12;
		mux = 0; 
	end
    always
    #5 clk = ~clk;     
endmodule    