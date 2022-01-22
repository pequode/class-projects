`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/12/2021 03:41:35 AM
// Design Name: 
// Module Name: VerificationAdd
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


module VerificationAdd#(parameter N = 5)(clk,q_out,c_in,cout,a,b,mux_in);
input clk;
input c_in;
input [N-1:0]a;
input [N-1:0]b;
input mux_in;
output cout;
output reg [N-1:0]q_out;
wire  [N-1:0]L;
assign {cout,L} = a+b+c_in;
always @(posedge clk)
        if (mux_in ==0)
            q_out=L;
        else 
            q_out=~L;
endmodule
