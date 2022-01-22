`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/12/2021 01:19:43 AM
// Design Name: 
// Module Name: Parm_Add
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


module Parm_Add#(parameter N = 5)(c_out, sum, a, b, c_in);
    // initialize vars
    input c_in;
    input [N-1:0]a;
    input [N-1:0]b;
    output [N-1:0]sum;
    output c_out;
    // generate each loop throuhg of Full adder 
    wire [N-1:0]w;// creates temp wires to hold values 
    FA_str b1(.c_out(w[0]),.sum(sum[0]), .a(a[0]), .b(b[0]), .c_in(w[c_in]));// first val with c_in being the cin
    genvar i;
    generate
        for (i=1; i<N; i=i+1) begin:Fba 
            FA_str uut (.c_out(w[i]), .sum(sum[i]), .a(a[i]) , .b(b[i]), .c_in(w[i-1]) );// go through each and let the cin wire be the previous itter
        end
    endgenerate
    assign c_out = w[N-1];// make sure cout is assigned 
    
endmodule
