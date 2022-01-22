`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/12/2021 03:51:23 AM
// Design Name: 
// Module Name: VNot
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


module VNot#(parameter N = 5)(a,not_a);
input [N-1:0]a;
output [N-1:0]not_a;

assign not_a = ~a;

endmodule
