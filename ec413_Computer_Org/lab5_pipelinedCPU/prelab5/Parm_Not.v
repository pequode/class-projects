`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/12/2021 03:50:56 AM
// Design Name: 
// Module Name: Parm_Not
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


module Parm_Not#(parameter N = 5)(a,not_a);
input [N-1:0]a;
output [N-1:0]not_a;
    genvar i;
    generate
        for (i=0; i<N; i=i+1) begin:nots 
            not not1 (not_a[i],a[i]); 
        end
    endgenerate

endmodule
