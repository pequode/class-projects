`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/12/2021 04:02:54 AM
// Design Name: 
// Module Name: VerTop
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


module VerTop#(parameter N = 5)(clk,q_out,c_in,cout,a,b,mux_in);
    input clk;
    input mux_in;
    input c_in;
    input [N-1:0]a;
    input [N-1:0]b;
    
    output [N-1:0]q_out;
    output cout;
    
    
endmodule
