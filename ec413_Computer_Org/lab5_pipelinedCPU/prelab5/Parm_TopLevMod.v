`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/12/2021 01:37:18 AM
// Design Name: 
// Module Name: Parm_TopLevMod
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


module Parm_TopLevMod#(parameter N = 5)(clk,q_out,c_in,cout,a,b,mux_in);
    //define vars
    input clk;
    input mux_in;
    input c_in;
    input [N-1:0]a;
    input [N-1:0]b;
    
    output [N-1:0]q_out;
    output cout;
    wire [N-1:0]w;
    wire [N-1:0]wn;
    wire [N-1:0]wafter;
    //wire [N-1:0]q;
    Parm_Add#(.N(N)) b2 (.c_out(cout), .sum(w), .a(a), .b(b), .c_in(c_in)); // do add but connect sum to the wire
    //Parm_Reg#(.N(N)) a0 (.clk(clk),.qin(w),.qout(q));// wire sum to register
    Parm_Not#(.N(N)) notIF(.a(w),.not_a(wn));
    assign wafter = (mux_in ==0) ? w:wn;
    Parm_Reg#(.N(N)) a0 (.clk(clk),.qin(wafter),.qout(q_out));// wire sum to register
//    always @(posedge clk)
//        q_out=q;
    
endmodule
