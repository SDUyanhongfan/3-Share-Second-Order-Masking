/*
* -----------------------------------------------------------------
* COMPANY : Shandong University
* AUTHOR  : Yanhong Fan,Chaoran Wang, Lixuan Wu,      Meiqin Wang
* DOCUMENT: "A Fast Search Method for 3-Share Second-Order Masking Schemes for Lightweight S-Boxes"  
* -----------------------------------------------------------------
*
* Copyright c 2023, Yanhong Fan,Chaoran Wang, Lixuan Wu,  Meiqin Wang
*
* All rights reserved.
* Please see LICENSE and README for license and further instructions.
*/


module SkinnySbox ( clk, in1, in2, in3, r, out1, out2, out3 );
  (* SILVER="[3:0]_0" *) input [3:0] in1;
  (* SILVER="[3:0]_1" *) input [3:0] in2;
  (* SILVER="[3:0]_2" *) input [3:0] in3;
  (* SILVER="refresh" *) input [7:0] r;
  (* SILVER="[3:0]_0" *) output [3:0] out1;
  (* SILVER="[3:0]_1" *) output [3:0] out2;
  (* SILVER="[3:0]_2" *) output [3:0] out3;
  (* SILVER="clock" *) input clk;
  wire   F_N5, F_N4, F_N3, F_N2, F_N1, F_N0, n45, n46, n48, n49, n50, n51, n52,
         n53, n54, n55, n56, n57, n58, n59, n60, n61, n62, n63, n64, n65, n66,
         n67, n68, n69, n70, n71, n72, n73, n74, n75, n76, n77, n78, n79, n80,
         n81, n82, n83, n84, n85, n86, n87, n88, n89, n90, n91, n92;
  wire   [3:0] Rq1;
  wire   [3:0] F_in1;
  wire   [3:0] Rq2;
  wire   [3:0] F_in2;
  wire   [3:0] Rq3;
  wire   [3:0] F_in3;
  wire   [17:0] F_CF_Reg;
  wire   [17:0] F_CF_Out;
  wire   [17:0] G_CF_Reg;
  wire   [17:1] G_CF_Out;

  DFF_X1 F_CF_Reg_reg_0_ ( .D(F_CF_Out[0]), .CK(clk), .Q(F_CF_Reg[0]) );
  DFF_X1 F_CF_Reg_reg_1_ ( .D(F_CF_Out[1]), .CK(clk), .Q(F_CF_Reg[1]) );
  DFF_X1 F_CF_Reg_reg_2_ ( .D(F_CF_Out[2]), .CK(clk), .Q(F_CF_Reg[2]) );
  DFF_X1 Rq1_reg_3_ ( .D(F_in1[3]), .CK(clk), .Q(Rq1[3]), .QN(n92) );
  DFF_X1 F_CF_Reg_reg_3_ ( .D(F_CF_Out[3]), .CK(clk), .Q(F_CF_Reg[3]) );
  DFF_X1 F_CF_Reg_reg_4_ ( .D(F_CF_Out[4]), .CK(clk), .Q(F_CF_Reg[4]) );
  DFF_X1 F_CF_Reg_reg_5_ ( .D(F_CF_Out[5]), .CK(clk), .Q(F_CF_Reg[5]) );
  DFF_X1 Rq2_reg_3_ ( .D(F_in2[3]), .CK(clk), .Q(Rq2[3]), .QN(n86) );
  DFF_X1 F_CF_Reg_reg_6_ ( .D(F_CF_Out[6]), .CK(clk), .Q(F_CF_Reg[6]) );
  DFF_X1 F_CF_Reg_reg_7_ ( .D(F_CF_Out[7]), .CK(clk), .Q(F_CF_Reg[7]) );
  DFF_X1 F_CF_Reg_reg_8_ ( .D(F_CF_Out[8]), .CK(clk), .Q(F_CF_Reg[8]) );
  DFF_X1 Rq3_reg_3_ ( .D(F_in3[3]), .CK(clk), .Q(Rq3[3]), .QN(n85) );
  DFF_X1 F_CF_Reg_reg_9_ ( .D(F_CF_Out[9]), .CK(clk), .Q(F_CF_Reg[9]) );
  DFF_X1 F_CF_Reg_reg_10_ ( .D(F_CF_Out[10]), .CK(clk), .Q(F_CF_Reg[10]) );
  DFF_X1 F_CF_Reg_reg_11_ ( .D(F_CF_Out[11]), .CK(clk), .Q(F_CF_Reg[11]) );
  DFF_X1 Rq1_reg_2_ ( .D(F_in1[2]), .CK(clk), .Q(Rq1[2]), .QN(n91) );
  DFF_X1 F_CF_Reg_reg_12_ ( .D(F_CF_Out[12]), .CK(clk), .Q(F_CF_Reg[12]) );
  DFF_X1 F_CF_Reg_reg_13_ ( .D(F_CF_Out[13]), .CK(clk), .Q(F_CF_Reg[13]) );
  DFF_X1 F_CF_Reg_reg_14_ ( .D(F_CF_Out[14]), .CK(clk), .Q(F_CF_Reg[14]) );
  DFF_X1 Rq2_reg_2_ ( .D(F_in2[2]), .CK(clk), .Q(Rq2[2]), .QN(n89) );
  DFF_X1 F_CF_Reg_reg_15_ ( .D(F_CF_Out[15]), .CK(clk), .Q(F_CF_Reg[15]) );
  DFF_X1 F_CF_Reg_reg_16_ ( .D(F_CF_Out[16]), .CK(clk), .Q(F_CF_Reg[16]) );
  DFF_X1 F_CF_Reg_reg_17_ ( .D(F_CF_Out[17]), .CK(clk), .Q(F_CF_Reg[17]) );
  DFF_X1 Rq3_reg_2_ ( .D(F_in3[2]), .CK(clk), .Q(Rq3[2]), .QN(n90) );
  DFF_X1 F_out2_reg_2_ ( .D(F_N1), .CK(clk), .Q(F_in2[1]) );
  DFF_X1 Rq2_reg_1_ ( .D(F_in2[1]), .CK(clk), .Q(Rq2[1]), .QN(n88) );
  DFF_X1 F_out2_reg_3_ ( .D(F_N4), .CK(clk), .Q(F_in2[0]) );
  DFF_X1 Rq2_reg_0_ ( .D(F_in2[0]), .CK(clk), .Q(Rq2[0]) );
  DFF_X1 F_out3_reg_2_ ( .D(F_N2), .CK(clk), .Q(F_in3[1]) );
  DFF_X1 Rq3_reg_1_ ( .D(F_in3[1]), .CK(clk), .Q(Rq3[1]), .QN(n87) );
  DFF_X1 F_out3_reg_3_ ( .D(F_N5), .CK(clk), .Q(F_in3[0]) );
  DFF_X1 Rq3_reg_0_ ( .D(F_in3[0]), .CK(clk), .Q(Rq3[0]) );
  DFF_X1 F_out1_reg_2_ ( .D(F_N0), .CK(clk), .Q(F_in1[1]) );
  DFF_X1 Rq1_reg_1_ ( .D(F_in1[1]), .CK(clk), .Q(Rq1[1]) );
  DFF_X1 F_out1_reg_3_ ( .D(F_N3), .CK(clk), .Q(F_in1[0]) );
  DFF_X1 Rq1_reg_0_ ( .D(F_in1[0]), .CK(clk), .Q(Rq1[0]) );
  DFF_X1 G_CF_Reg_reg_0_ ( .D(n46), .CK(clk), .Q(G_CF_Reg[0]) );
  DFF_X1 G_CF_Reg_reg_1_ ( .D(G_CF_Out[1]), .CK(clk), .Q(G_CF_Reg[1]) );
  DFF_X1 G_CF_Reg_reg_2_ ( .D(G_CF_Out[2]), .CK(clk), .Q(G_CF_Reg[2]) );
  DFF_X1 G_CF_Reg_reg_3_ ( .D(G_CF_Out[3]), .CK(clk), .Q(G_CF_Reg[3]) );
  DFF_X1 G_CF_Reg_reg_4_ ( .D(G_CF_Out[4]), .CK(clk), .Q(G_CF_Reg[4]) );
  DFF_X1 G_CF_Reg_reg_5_ ( .D(G_CF_Out[5]), .CK(clk), .Q(G_CF_Reg[5]) );
  DFF_X1 G_CF_Reg_reg_6_ ( .D(G_CF_Out[6]), .CK(clk), .Q(G_CF_Reg[6]) );
  DFF_X1 G_CF_Reg_reg_7_ ( .D(G_CF_Out[7]), .CK(clk), .Q(G_CF_Reg[7]) );
  DFF_X1 G_CF_Reg_reg_8_ ( .D(G_CF_Out[8]), .CK(clk), .Q(G_CF_Reg[8]) );
  DFF_X1 G_CF_Reg_reg_9_ ( .D(n45), .CK(clk), .Q(G_CF_Reg[9]) );
  DFF_X1 G_CF_Reg_reg_10_ ( .D(G_CF_Out[10]), .CK(clk), .Q(G_CF_Reg[10]) );
  DFF_X1 G_CF_Reg_reg_11_ ( .D(G_CF_Out[11]), .CK(clk), .Q(G_CF_Reg[11]) );
  DFF_X1 G_CF_Reg_reg_12_ ( .D(G_CF_Out[12]), .CK(clk), .Q(G_CF_Reg[12]) );
  DFF_X1 G_CF_Reg_reg_13_ ( .D(G_CF_Out[13]), .CK(clk), .Q(G_CF_Reg[13]) );
  DFF_X1 G_CF_Reg_reg_14_ ( .D(G_CF_Out[14]), .CK(clk), .Q(G_CF_Reg[14]) );
  DFF_X1 G_CF_Reg_reg_15_ ( .D(G_CF_Out[15]), .CK(clk), .Q(G_CF_Reg[15]) );
  DFF_X1 G_CF_Reg_reg_16_ ( .D(G_CF_Out[16]), .CK(clk), .Q(G_CF_Reg[16]) );
  DFF_X1 G_CF_Reg_reg_17_ ( .D(G_CF_Out[17]), .CK(clk), .Q(G_CF_Reg[17]) );
  DFF_X1 G_out1_reg_2_ ( .D(n91), .CK(clk), .Q(out1[2]) );
  DFF_X1 G_out1_reg_3_ ( .D(n92), .CK(clk), .Q(out1[3]) );
  DFF_X1 G_out2_reg_2_ ( .D(Rq2[2]), .CK(clk), .Q(out2[2]) );
  DFF_X1 G_out2_reg_3_ ( .D(Rq2[3]), .CK(clk), .Q(out2[3]) );
  DFF_X1 G_out3_reg_2_ ( .D(Rq3[2]), .CK(clk), .Q(out3[2]) );
  DFF_X1 G_out3_reg_3_ ( .D(Rq3[3]), .CK(clk), .Q(out3[3]) );
  INV_X1 U102 ( .A(in1[2]), .ZN(n68) );
  AND2_X1 U103 ( .A1(n68), .A2(in2[3]), .ZN(F_CF_Out[1]) );
  INV_X1 U104 ( .A(in3[2]), .ZN(n72) );
  AND2_X1 U105 ( .A1(n72), .A2(in1[3]), .ZN(F_CF_Out[6]) );
  AND2_X1 U106 ( .A1(n68), .A2(in1[1]), .ZN(F_CF_Out[9]) );
  INV_X1 U107 ( .A(in2[2]), .ZN(n69) );
  AND2_X1 U108 ( .A1(n69), .A2(in2[1]), .ZN(F_CF_Out[13]) );
  AND2_X1 U109 ( .A1(n72), .A2(in3[1]), .ZN(F_CF_Out[17]) );
  AND2_X1 U110 ( .A1(n69), .A2(in3[3]), .ZN(F_CF_Out[5]) );
  AND2_X1 U111 ( .A1(Rq1[1]), .A2(Rq3[3]), .ZN(G_CF_Out[6]) );
  XOR2_X1 U112 ( .A(r[5]), .B(r[4]), .Z(n49) );
  XNOR2_X1 U113 ( .A(F_CF_Reg[7]), .B(F_CF_Reg[8]), .ZN(n48) );
  XNOR2_X1 U114 ( .A(n49), .B(n48), .ZN(n50) );
  XOR2_X1 U115 ( .A(F_CF_Reg[6]), .B(n50), .Z(F_in3[3]) );
  XOR2_X1 U116 ( .A(F_CF_Reg[4]), .B(F_CF_Reg[3]), .Z(n52) );
  XNOR2_X1 U117 ( .A(r[5]), .B(F_CF_Reg[5]), .ZN(n51) );
  XNOR2_X1 U118 ( .A(n52), .B(n51), .ZN(F_in2[3]) );
  XOR2_X1 U119 ( .A(F_CF_Reg[1]), .B(F_CF_Reg[0]), .Z(n54) );
  XNOR2_X1 U120 ( .A(r[4]), .B(F_CF_Reg[2]), .ZN(n53) );
  XNOR2_X1 U121 ( .A(n54), .B(n53), .ZN(F_in1[3]) );
  XOR2_X1 U122 ( .A(r[7]), .B(r[6]), .Z(n56) );
  XNOR2_X1 U123 ( .A(F_CF_Reg[16]), .B(F_CF_Reg[17]), .ZN(n55) );
  XNOR2_X1 U124 ( .A(n56), .B(n55), .ZN(n57) );
  XOR2_X1 U125 ( .A(F_CF_Reg[15]), .B(n57), .Z(F_in3[2]) );
  XOR2_X1 U126 ( .A(F_CF_Reg[13]), .B(F_CF_Reg[12]), .Z(n59) );
  XNOR2_X1 U127 ( .A(r[7]), .B(F_CF_Reg[14]), .ZN(n58) );
  XNOR2_X1 U128 ( .A(n59), .B(n58), .ZN(F_in2[2]) );
  XOR2_X1 U129 ( .A(F_CF_Reg[10]), .B(F_CF_Reg[9]), .Z(n61) );
  XNOR2_X1 U130 ( .A(r[6]), .B(F_CF_Reg[11]), .ZN(n60) );
  XNOR2_X1 U131 ( .A(n61), .B(n60), .ZN(F_in1[2]) );
  XNOR2_X1 U132 ( .A(in3[2]), .B(r[2]), .ZN(n62) );
  XNOR2_X1 U133 ( .A(n62), .B(r[3]), .ZN(F_N5) );
  XOR2_X1 U134 ( .A(r[3]), .B(in2[2]), .Z(F_N4) );
  XNOR2_X1 U135 ( .A(r[2]), .B(in1[2]), .ZN(F_N3) );
  XNOR2_X1 U136 ( .A(in3[1]), .B(r[0]), .ZN(n63) );
  XNOR2_X1 U137 ( .A(n63), .B(r[1]), .ZN(F_N2) );
  XOR2_X1 U138 ( .A(r[1]), .B(in2[1]), .Z(F_N1) );
  XNOR2_X1 U139 ( .A(r[0]), .B(in1[1]), .ZN(F_N0) );
  NAND2_X1 U140 ( .A1(in1[2]), .A2(in1[3]), .ZN(n64) );
  XNOR2_X1 U141 ( .A(n64), .B(in1[0]), .ZN(F_CF_Out[0]) );
  NOR2_X1 U142 ( .A1(in3[3]), .A2(n68), .ZN(F_CF_Out[2]) );
  NOR2_X1 U143 ( .A1(in1[3]), .A2(n69), .ZN(F_CF_Out[3]) );
  NAND2_X1 U144 ( .A1(in2[3]), .A2(in2[2]), .ZN(n65) );
  XNOR2_X1 U145 ( .A(n65), .B(in2[0]), .ZN(F_CF_Out[4]) );
  NOR2_X1 U146 ( .A1(in2[3]), .A2(n72), .ZN(F_CF_Out[7]) );
  NAND2_X1 U147 ( .A1(in3[3]), .A2(in3[2]), .ZN(n66) );
  XNOR2_X1 U148 ( .A(n66), .B(in3[0]), .ZN(F_CF_Out[8]) );
  NAND2_X1 U149 ( .A1(in2[1]), .A2(in1[2]), .ZN(n67) );
  XNOR2_X1 U150 ( .A(n67), .B(in2[3]), .ZN(F_CF_Out[10]) );
  NOR2_X1 U151 ( .A1(in3[1]), .A2(n68), .ZN(F_CF_Out[11]) );
  NOR2_X1 U152 ( .A1(in1[1]), .A2(n69), .ZN(F_CF_Out[12]) );
  NAND2_X1 U153 ( .A1(in2[2]), .A2(in3[1]), .ZN(n70) );
  XNOR2_X1 U154 ( .A(n70), .B(in3[3]), .ZN(F_CF_Out[14]) );
  NAND2_X1 U155 ( .A1(in1[1]), .A2(in3[2]), .ZN(n71) );
  XNOR2_X1 U156 ( .A(n71), .B(in1[3]), .ZN(F_CF_Out[15]) );
  NOR2_X1 U157 ( .A1(in2[1]), .A2(n72), .ZN(F_CF_Out[16]) );
  NAND2_X1 U158 ( .A1(Rq2[1]), .A2(Rq1[3]), .ZN(n73) );
  XNOR2_X1 U159 ( .A(n73), .B(Rq2[0]), .ZN(G_CF_Out[1]) );
  NOR2_X1 U160 ( .A1(Rq1[3]), .A2(n87), .ZN(G_CF_Out[2]) );
  NAND2_X1 U161 ( .A1(Rq2[3]), .A2(Rq1[1]), .ZN(n74) );
  XNOR2_X1 U162 ( .A(n74), .B(Rq1[0]), .ZN(G_CF_Out[3]) );
  NOR2_X1 U163 ( .A1(Rq2[3]), .A2(n88), .ZN(G_CF_Out[4]) );
  NOR2_X1 U164 ( .A1(n86), .A2(n87), .ZN(G_CF_Out[5]) );
  NOR2_X1 U165 ( .A1(Rq3[3]), .A2(n88), .ZN(G_CF_Out[7]) );
  NAND2_X1 U166 ( .A1(Rq3[1]), .A2(n85), .ZN(n75) );
  XNOR2_X1 U167 ( .A(Rq3[0]), .B(n75), .ZN(G_CF_Out[8]) );
  NAND2_X1 U168 ( .A1(Rq2[2]), .A2(Rq1[3]), .ZN(n76) );
  XNOR2_X1 U169 ( .A(n76), .B(Rq2[1]), .ZN(G_CF_Out[10]) );
  NOR2_X1 U170 ( .A1(Rq1[3]), .A2(n90), .ZN(G_CF_Out[11]) );
  NAND2_X1 U171 ( .A1(Rq1[2]), .A2(Rq2[3]), .ZN(n77) );
  XNOR2_X1 U172 ( .A(n77), .B(Rq1[1]), .ZN(G_CF_Out[12]) );
  NOR2_X1 U173 ( .A1(Rq2[3]), .A2(n89), .ZN(G_CF_Out[13]) );
  NOR2_X1 U174 ( .A1(n86), .A2(n90), .ZN(G_CF_Out[14]) );
  NOR2_X1 U175 ( .A1(n85), .A2(n91), .ZN(G_CF_Out[15]) );
  NOR2_X1 U176 ( .A1(Rq3[3]), .A2(n89), .ZN(G_CF_Out[16]) );
  NAND2_X1 U177 ( .A1(n85), .A2(Rq3[2]), .ZN(n78) );
  XNOR2_X1 U178 ( .A(n78), .B(Rq3[1]), .ZN(G_CF_Out[17]) );
  XNOR2_X1 U179 ( .A(G_CF_Reg[17]), .B(G_CF_Reg[16]), .ZN(n79) );
  XNOR2_X1 U180 ( .A(n79), .B(G_CF_Reg[15]), .ZN(out3[0]) );
  XNOR2_X1 U181 ( .A(G_CF_Reg[14]), .B(G_CF_Reg[13]), .ZN(n80) );
  XNOR2_X1 U182 ( .A(n80), .B(G_CF_Reg[12]), .ZN(out2[0]) );
  XNOR2_X1 U183 ( .A(G_CF_Reg[11]), .B(G_CF_Reg[10]), .ZN(n81) );
  XNOR2_X1 U184 ( .A(n81), .B(G_CF_Reg[9]), .ZN(out1[0]) );
  XNOR2_X1 U185 ( .A(G_CF_Reg[8]), .B(G_CF_Reg[7]), .ZN(n82) );
  XNOR2_X1 U186 ( .A(n82), .B(G_CF_Reg[6]), .ZN(out3[1]) );
  XNOR2_X1 U187 ( .A(G_CF_Reg[5]), .B(G_CF_Reg[4]), .ZN(n83) );
  XNOR2_X1 U188 ( .A(n83), .B(G_CF_Reg[3]), .ZN(out2[1]) );
  XNOR2_X1 U189 ( .A(G_CF_Reg[2]), .B(G_CF_Reg[1]), .ZN(n84) );
  XNOR2_X1 U190 ( .A(n84), .B(G_CF_Reg[0]), .ZN(out1[1]) );
  NAND2_X1 U191 ( .A1(Rq1[3]), .A2(Rq1[1]), .ZN(n46) );
  NAND2_X1 U192 ( .A1(Rq1[3]), .A2(Rq1[2]), .ZN(n45) );
endmodule

