`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/12/2021 01:03:38 AM
// Design Name: 
// Module Name: Parm_Reg
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


module Parm_Reg#(parameter N = 5)(clk,qin,qout);// uses the given flipflops to create a register defined by param size
    //init vars
    input clk;
    input [N-1:0]qin;
    output [N-1:0]qout;
    // generate all registers
    wire [N-1:0]qmed; // assign an intermedidate buss for the wires
    genvar i;
    generate
        for (i=0; i<N; i=i+1) begin:dffn 
            //dff a(.q(qmed[i]),.d(qin[i]),.clk(clk));
            dff a(.q(qout[i]),.d(qin[i]),.clk(clk));
        end
    endgenerate
//    always @(posedge clk)
//        qout=qmed;
endmodule
